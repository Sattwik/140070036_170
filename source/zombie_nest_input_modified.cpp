#include<SDL2/SDL.h>
#include<iostream>
#include<stdio.h>
#include "parameters.h"

using namespace std;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 582;
const int BUTTON_WIDTH = 25;
const int BUTTON_HEIGHT = 25;
const int LESS_BUTTON_LOC_X = 970;
const int MORE_BUTTON_LOC_X = 995;
const int BUTTON_BASELOC_Y = 200;
const int BUTTON_DIFF_Y = 50;
const int INPUT_GRID_BASELOC_X = 420;
int DONE_BUTTON_XZ =490, DONE_BUTTON_YZ= 500;
const int DONE_BUTTON_WIDTH =100, DONE_BUTTON_HEIGHT= 50;


bool insidedonez(int x,int y);
void handleMouseEventZN( SDL_Event& e ,int x, int y, int i, SDL_Surface * black_box, SDL_Surface * white_box,SDL_Surface * gsurface_zn, int & temp_str, int & temp_ir, int & temp_nz, int & temp_chr, bool &in_done)
{


		if ( insidedonez(x,y))
        {
            if ( e.type ==  SDL_MOUSEMOTION )
            {
                in_done=true;
            }
        }
        else in_done=false;
		//Check if mouse is in less button
		bool inside_less = true;

		//Mouse is left of the button
		if( x < LESS_BUTTON_LOC_X )
		{
			inside_less = false;
		}
		//Mouse is right of the button
		else if( x > LESS_BUTTON_LOC_X + BUTTON_WIDTH )
		{
			inside_less = false;
		}
		//Mouse above the button
		else if( y < BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT) )
		{
			inside_less = false;
		}
		//Mouse below the button
		else if( y > BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT) + BUTTON_HEIGHT )
		{
			inside_less = false;
		}


		//Mouse is inside button
		if (inside_less )
		{
			//Set mouse over sprite

			if(e.type ==  SDL_MOUSEBUTTONDOWN)
				{

					SDL_Rect pos;
					switch (i)
					{
						case 0 :
						if (temp_str != 1)
						{

							temp_str --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_str);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_zn, &pos);
						}
						break;

						case 1 :
						if (temp_ir != 1)
						{
							temp_ir --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_ir);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_zn, &pos);
						}

						break;

						case 2 :
						if (temp_nz != 1)
						{
							temp_nz --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_nz);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_zn, &pos);
						}

						break;

						case 3 :
						if (temp_chr != 1)
						{
							temp_chr --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_chr);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_zn, &pos);
						}
						break;

					}
				}



		}
		/***************************************************************************/
		//Check if mouse is in more button
		bool inside_more = true;

		//Mouse is left of the button
		if( x <  MORE_BUTTON_LOC_X)
		{
			inside_more = false;
		}
		//Mouse is right of the button
		else if( x >  MORE_BUTTON_LOC_X+ BUTTON_WIDTH )
		{
			inside_more = false;
		}
		//Mouse above the button
		else if( y < BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT) )
		{
			inside_more = false;
		}
		//Mouse below the button
		else if( y > BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT) + BUTTON_HEIGHT )
		{
			inside_more = false;
		}


		//Mouse is inside button
		if (inside_more )
		{
			if(e.type ==  SDL_MOUSEBUTTONDOWN)
			{
					SDL_Rect pos;
					switch (i)
					{
						case 0 :

						if (temp_str < 20)
						{


								pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_str);
								pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);

								SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
								temp_str++;


						}
						break;

						case 1 :
						if (temp_ir < 20)
						{

							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_ir);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);
							SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
							temp_ir ++;
						}

						break;

						case 2 :

						if ( temp_nz < 20)
						{

							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_nz);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);
							SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
							temp_nz ++;
						}

						break;

						case 3 :
						if (temp_chr < 20)
						{

							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_chr);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);
							SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
							temp_chr ++;
						}
						break;

					}
				}
		}

}

bool insidedonez(int x, int y)
{
	bool inside_done = true;

	//Mouse is left of the button
	if( x <  DONE_BUTTON_XZ)
	{
		inside_done = false;
	}
	//Mouse is right of the button
	else if( x >  DONE_BUTTON_XZ+ DONE_BUTTON_WIDTH )
	{
		inside_done = false;
	}
	//Mouse above the button
	else if( y < DONE_BUTTON_YZ)
	{
		inside_done = false;
	}
	//Mouse below the button
	else if( y > DONE_BUTTON_YZ + DONE_BUTTON_HEIGHT )
	{
		inside_done = false;
	}
	return inside_done;
}



void zombie_nest_input( zombie_nest &zn)
{

	SDL_Surface * gsurface_zn = NULL;
	SDL_Surface * back_image = NULL;
	SDL_Surface * black_box = NULL;
	SDL_Surface * white_box = NULL;
	SDL_Surface * done_in = NULL;
	SDL_Surface * done_fn =NULL;

    //Variables
	/***************************************************************************/

	//int temp_str = int(max(int(zn.strength),1)), temp_ir = int(max(int(zn.infection_rate),1)), temp_nz = int(max(int(zn.number_of_zombies/10),1)), temp_chr =int(max(int(zn.chase_radius/5),1));
	
	int temp_str = 1, temp_ir = 1, temp_nz = 1, temp_chr = 1;


	// making the window and setting the surface
    /***************************************************************************/
	bool success = true;


			gsurface_zn = SDL_GetWindowSurface (gwindow);

    /***************************************************************************/
	// loading start background image
	success = true;

	back_image = SDL_LoadBMP ("img/zombie_nest_input_background.bmp");
	black_box = SDL_LoadBMP ("img/black_box.bmp");
	white_box = SDL_LoadBMP ("img/white_box.bmp");
    done_in=SDL_LoadBMP("img/DONE_INITIAL.bmp");
    done_fn=SDL_LoadBMP("img/DONE_FINAL.bmp");


	if ( black_box == NULL || back_image == NULL || white_box == NULL||done_fn==NULL||done_in==NULL)
	{
		cout << " Error : " << SDL_GetError() <<endl;
		success = false;
	}

	if (! success )
	{
		cout << "FAILED TO LOAD MEDIA!!!" <<endl;
	}


	/***************************************************************************/




	// actually blitting the image
	    SDL_BlitSurface (back_image, NULL, gsurface_zn, NULL);

		SDL_Rect pos,done_pos;

		// initital input grid blitted

		pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y;
		for(int i=1;i<=temp_str;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
            pos.x+=BUTTON_WIDTH;
        }
        pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y + BUTTON_DIFF_Y + BUTTON_HEIGHT;
		for(int i=1;i<=temp_ir;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
            pos.x+=BUTTON_WIDTH;
        }
        pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y +  2*(BUTTON_DIFF_Y + BUTTON_HEIGHT);
		for(int i=1;i<=temp_nz;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
            pos.x+=BUTTON_WIDTH;
        }
        pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y +  3*(BUTTON_DIFF_Y + BUTTON_HEIGHT);
		for(int i=1;i<=temp_chr;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_zn, &pos);
            pos.x+=BUTTON_WIDTH;
        }
        done_pos.x=DONE_BUTTON_XZ;
        done_pos.y=DONE_BUTTON_YZ;


		bool quit_zn = false;
        bool in_done=false;
		while (!quit_zn)
		{
			SDL_Event e;
			while ( SDL_PollEvent(&e) != 0)
			{

				if (e.type == SDL_QUIT)
				{
					quit_zn = true;
					quit=true;
				}

				if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
				{

					//Get mouse position
					int x, y;
					SDL_GetMouseState( &x, &y );

					if ( insidedonez(x,y))
					{

						if ( e.type ==  SDL_MOUSEBUTTONDOWN )
						{

							zn.strength = temp_str;
							//zn.infection_rate = temp_ir;
							zn.number_of_zombies = temp_nz*10;
							zn.chase_radius = temp_chr*5;

							quit_zn = true;
						}
					}

					for (int i = 0; i< 4 ;i ++)
					{
						handleMouseEventZN(  e,x, y, i,  black_box,white_box,gsurface_zn, temp_str, temp_ir, temp_nz, temp_chr,in_done);
				    }


				}


			}

		//SDL_BlitSurface (back_image, NULL, gsurface_zn, NULL);
		//SDL_BlitSurface (black_box, NULL, gsurface_zn, &dest);

        if(in_done)
            SDL_BlitSurface (done_fn, NULL, gsurface_zn, &done_pos);
        else SDL_BlitSurface(done_in, NULL, gsurface_zn, &done_pos);

		SDL_UpdateWindowSurface(gwindow);
	    }


	/***************************************************************************/
	// closing the stuff
	SDL_FreeSurface(back_image);
	back_image = NULL;
	SDL_FreeSurface(black_box);
	black_box = NULL;
	SDL_FreeSurface(white_box);
	white_box = NULL;
	SDL_FreeSurface(done_fn);
	done_fn = NULL;
	SDL_FreeSurface(done_in);
	done_in =NULL;
	SDL_FreeSurface(gsurface_zn);
	gsurface_zn=NULL;

}
