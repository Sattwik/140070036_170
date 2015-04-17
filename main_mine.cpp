#include"parameters.h"

long long int sim_time = 0;
const int X=500;
const int SCREEN_WIDTH = X;
const int SCREEN_HEIGHT = X;

vector<human> H;
vector<zombie> Z;
Configuration Input;
node grid[X][X];

vector<human>::iterator it_human;
vector<human_colony>::iterator it_human_colony;

vector<zombie>::iterator it_zombie;
vector<zombie_nest>::iterator it_zombie_nest;

human_colony h;
zombie_nest z;
food_source f;
//food_source f2;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
mt19937 eng((std::random_device())());

float random(double n)
{
		uniform_real_distribution<float> distribution(0,n);
		return distribution(eng);
}

float random(double n1, double n2)
{
	uniform_real_distribution<float> distribution(n1,n2);
	return distribution(eng);
}

int random (int n1, int n2)
{
	uniform_int_distribution<int> distribution(n1,n2);
	return distribution(eng);
}

float min(float a, float b)
{
	if ( a > b ) return b;
	else return a;
}
float max(float a, float b)
{
	if ( a > b ) return a;
	else return b;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void init ()
{

	h.pos.x = 100;
	h.pos.y = 100;

	h.birth_rate = 0;
	h.number_of_humans = 50;
	h.death_age = 10000;
	h.food_amount = 0;
	h.strength = 5;
	h.food_per_new_human = 10;


	h.food_max = 50;
	Input.human_colonies.push_back(h);





	f.x = 350;
	f.y = 350;
	f.food_source_area = 2601;
	f.food_per_source_node = 100;
	Input.food_sources.push_back(f);
	
	/*
	f2.x = 250;
	f2.y = 250;
	f2.food_source_area = 49;
	f2.food_per_source_node = 100000000;
	Input.food_sources.push_back(f2);
	*/



	
	z.pos.x = 450;
	z.pos.y = 450;
	z.strength = 10000;
	z.infection_rate = 0;
	z.number_of_zombies = 25;
	z.chase_radius = 15;
	Input.zombie_nests.push_back(z);
	
	
  
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" int main(int argc, char *argv[])
{
    init();
	srand (time(NULL)); // SEEDING RAND
	SDL_Window * gwindow = NULL;
	SDL_Surface * gsurface = NULL;
	SDL_Surface * human_image = NULL;
	SDL_Surface * zombie_image = NULL;
	SDL_Surface * human_colony_image = NULL;
	SDL_Surface * zombie_nest_image = NULL;
	SDL_Surface * background = NULL;
	SDL_Surface * food_source_image = NULL;
	
	


	/******************************************************************************************************************************/
	// making the window and setting the surface
	
	bool success = true;
	
	if (SDL_Init(SDL_INIT_VIDEO)<0) { cout << "SDL not initialized!! Error : " << SDL_GetError()<<endl; success = false;}
	
	else
	{
		gwindow = SDL_CreateWindow("ZAS",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		
		if( gwindow == NULL)
		{
			success = false;
			cout << " Error : "<< SDL_GetError()<<endl;
			
		}
		else
		{
			gsurface = SDL_GetWindowSurface (gwindow);
		}
	}
	
	if (!success )
	{
		cout << "FAILED TO INITIALIZE!"<<endl;		
	}
	
    // loading images
	success = true;
	
	background = SDL_LoadBMP ("background.bmp");
	human_colony_image = SDL_LoadBMP ("human_colony_image.bmp");
	zombie_nest_image = SDL_LoadBMP ("zombie_nest_image.bmp");
	human_image = SDL_LoadBMP ("human_image.bmp");
	zombie_image = SDL_LoadBMP ("zombie_image.bmp");
	food_source_image = SDL_LoadBMP ("food_source_image.bmp");
	
	
	if ( human_image == NULL|| zombie_image == NULL|| human_colony_image == NULL||zombie_nest_image == NULL||background == NULL||food_source_image == NULL)
	{
		cout << " Error : " << SDL_GetError() <<endl;
		success = false;
	}
	
	
	if (! success )
	{
		cout << "FAILED TO LOAD MEDIA!!!" <<endl;
	}
	else
	{
		cout << "Loaded images successfully!"<<endl;
	}
	
	SDL_BlitSurface (background, NULL, gsurface, NULL);
	
	SDL_Rect hcpos,znpos,fspos;
	hcpos.x = h.pos.x;
	hcpos.y = h.pos.y;
	SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
	fspos.x = f.x;
	fspos.y = f.y;
	SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
	
	znpos.x = z.pos.x;
	znpos.y = z.pos.y;
	SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
	

	
	/******************************************************************************************************************************/
	

	
	
	init_grid();
	init_human_list();
	
	init_zombie_list();



	/******************************************************************************************************************************/

		
		
		bool quit = false;
		
		while (!quit)
		{   
			SDL_Event e;
			
			while ( SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}


		    change_state();


			
			vector<human>::iterator tempith;

			vector<zombie>::iterator tempitz;
			
			
			SDL_BlitSurface (background, NULL, gsurface, NULL);
			SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
			SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
			SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
			for (tempith = H.begin(); tempith!= H.end(); tempith ++)
			{
				
				SDL_Rect temp_pos;
				temp_pos.x = tempith->pos.x;
				temp_pos.y = tempith->pos.y;
			

				SDL_BlitSurface (human_image, NULL, gsurface, &temp_pos);

			}
					
			
			for (tempitz = Z.begin(); tempitz!= Z.end(); tempitz ++)
			{
				SDL_Rect temp_pos;
				temp_pos.x = tempitz->pos.x;
				temp_pos.y = tempitz->pos.y;

	
				
				SDL_BlitSurface (zombie_image, NULL, gsurface, &temp_pos);

			}


			
			SDL_Delay(10);
		
		
		
		SDL_UpdateWindowSurface(gwindow);
	    }

		
	
	
	
	// closing the stuff
	SDL_FreeSurface(background);
	background = NULL;
	SDL_FreeSurface(human_colony_image);
	human_colony_image = NULL;
	SDL_FreeSurface(zombie_nest_image);
	zombie_nest_image = NULL;
	SDL_FreeSurface(human_image);
	human_image = NULL;
	SDL_FreeSurface(zombie_image);
	zombie_image = NULL;
	SDL_FreeSurface(food_source_image);
	food_source_image = NULL;
	
	SDL_DestroyWindow(gwindow);
	gwindow = NULL;
	SDL_Quit();
	

}

