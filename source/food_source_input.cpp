#include<SDL2/SDL.h>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include"parameters.h"

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
int DONE_BUTTON_X =490, DONE_BUTTON_Y= 500;
const int DONE_BUTTON_WIDTH =100, DONE_BUTTON_HEIGHT= 50;

bool insidedonef(int x,int y);
void handleMouseEventFS( SDL_Event& e ,int x, int y, int i, SDL_Surface * black_box, SDL_Surface * white_box,SDL_Surface * gsurface_fs, int & temp_food_source_area, int & temp_food_per_source_node, bool &in_done)
{

        if ( insidedonef(x,y))
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
						if (temp_food_source_area != 1)
						{

							temp_food_source_area --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_food_source_area);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_fs, &pos);
						}
						break;

						case 1 :
						if (temp_food_per_source_node != 1)
						{
							temp_food_per_source_node --;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_food_per_source_node);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT)+2;
							SDL_BlitSurface (white_box, NULL, gsurface_fs, &pos);
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

						if (temp_food_source_area < 20)
						{
						    temp_food_source_area++;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_food_source_area-1);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);

							SDL_BlitSurface (black_box, NULL, gsurface_fs, &pos);

						}
						break;

						case 1 :

                        if (temp_food_per_source_node < 20)
						{
							temp_food_per_source_node ++;
							pos.x = INPUT_GRID_BASELOC_X + BUTTON_WIDTH * (temp_food_per_source_node-1);
							pos.y = BUTTON_BASELOC_Y + i * (BUTTON_DIFF_Y + BUTTON_HEIGHT);
							SDL_BlitSurface (black_box, NULL, gsurface_fs, &pos);
						}

						break;

					}
				}
		}

}

bool insidedonef(int x, int y)
{
	bool inside_done = true;

	//Mouse is left of the button
	if( x <  DONE_BUTTON_X)
	{
		inside_done = false;
	}
	//Mouse is right of the button
	else if( x >  DONE_BUTTON_X+ DONE_BUTTON_WIDTH )
	{
		inside_done = false;
	}
	//Mouse above the button
	else if( y < DONE_BUTTON_Y)
	{
		inside_done = false;
	}
	//Mouse below the button
	else if( y > DONE_BUTTON_Y + DONE_BUTTON_HEIGHT )
	{
		inside_done = false;
	}
	return inside_done;
}
void food_source_input(food_source &fs)
{

	SDL_Surface * gsurface_fs = NULL;
	SDL_Surface * back_image = NULL;
	SDL_Surface * black_box = NULL;
	SDL_Surface * white_box = NULL;
	SDL_Surface * done_in = NULL;
	SDL_Surface * done_fn =NULL;


    //Variables
	/***************************************************************************/

	//int temp_food_source_area = max(int(sqrt(fs.food_source_area)),1), temp_food_per_source_node= max(int(fs.food_per_source_node/1000),1);


	int temp_food_source_area = 1, temp_food_per_source_node = 1;
	
	// making the window and setting the surface
    /***************************************************************************/
	bool success = true;

    gsurface_fs = SDL_GetWindowSurface (gwindow);


    /***************************************************************************/
	// loading start background image
	success = true;

	back_image = SDL_LoadBMP ("img/food_source_input_background.bmp");
	black_box = SDL_LoadBMP ("img/brown_box.bmp");
	white_box = SDL_LoadBMP ("img/white_box.bmp");
    done_in=SDL_LoadBMP("img/FS_DONE_INITIAL.bmp");
    done_fn=SDL_LoadBMP("img/FS_DONE_FINAL.bmp");

	//done = SDL_LoadBMP ("done.bmp");


	if ( black_box == NULL || back_image == NULL || white_box == NULL)
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
	    SDL_BlitSurface (back_image, NULL, gsurface_fs, NULL);



		// initital input grid blitted
        SDL_Rect pos,done_pos;

		pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y;
		for(int i=1;i<=temp_food_source_area;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_fs, &pos);
            pos.x+=BUTTON_WIDTH;
        }

        pos.x = INPUT_GRID_BASELOC_X;
		pos.y = BUTTON_BASELOC_Y + BUTTON_DIFF_Y + BUTTON_HEIGHT;
		for(int i=1;i<=temp_food_per_source_node;i++)
		{
            SDL_BlitSurface (black_box, NULL, gsurface_fs, &pos);
            pos.x+=BUTTON_WIDTH;
        }

        done_pos.x=DONE_BUTTON_X;
        done_pos.y=DONE_BUTTON_Y;


		bool quit_fs = false;
        bool in_done = false;

		while (!quit_fs)
		{
			SDL_Event e;

			while ( SDL_PollEvent(&e) != 0)
			{

				if (e.type == SDL_QUIT)
				{
					quit_fs = true;
					quit=true;
				}

				if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
				{

					//Get mouse position
					int x, y;
					SDL_GetMouseState( &x, &y );

					if ( insidedonef(x,y))
					{

						if ( e.type ==  SDL_MOUSEBUTTONDOWN )
						{

							fs.food_source_area = (3*temp_food_source_area)*(3*temp_food_source_area);
							fs.food_per_source_node = temp_food_per_source_node*1000;


							quit_fs = true;




						}
					}

					for (int i = 0; i< 2 ;i ++)
					{
						handleMouseEventFS(  e,x, y, i,  black_box,white_box,gsurface_fs, temp_food_source_area, temp_food_per_source_node,in_done);
				    }


				}


			}

		//SDL_BlitSurface (back_image, NULL, gsurface_fs, NULL);
		//SDL_BlitSurface (black_box, NULL, gsurface_fs, &dest);
        if(in_done)
            SDL_BlitSurface (done_fn, NULL, gsurface_fs, &done_pos);
        else SDL_BlitSurface(done_in, NULL, gsurface_fs, &done_pos);
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
	done_in = NULL;
	SDL_FreeSurface(gsurface_fs);
	gsurface_fs=NULL;
}
