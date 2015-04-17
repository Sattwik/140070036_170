#include<SDL2/SDL.h>
#include<iostream>
#include<stdio.h>
#include"parameters.h"

bool quit_st=false;

using namespace std;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 582;
const int START_X=380;
const int START_Y=500;
const int HELP_X=640;
const int HELP_Y=500;
const int START_BUTTON_WIDTH=120;
const int START_BUTTON_HEIGHT=60;


bool inside_start(int x, int y)
{
    		//Check if mouse is in less button
		bool start = true;

		//Mouse is left of the button
		if( x < START_X )
		{
			start = false;
		}
		//Mouse is right of the button
		else if( x > START_X + START_BUTTON_WIDTH )
		{
			start = false;
		}
		//Mouse above the button
		else if( y < START_Y)
		{
			start = false;
		}
		//Mouse below the button
		else if( y > START_Y  + START_BUTTON_HEIGHT )
		{
			start = false;
		}
		return start;
}
bool inside_help(int x,int y)
{
    bool help = true;

		//Mouse is left of the button
		if( x < HELP_X )
		{
			help = false;
		}
		//Mouse is right of the button
		else if( x > HELP_X + START_BUTTON_WIDTH )
		{
			help = false;
		}
		//Mouse above the button
		else if( y < HELP_Y)
		{
			help = false;
		}
		//Mouse below the button
		else if( y > HELP_Y  + START_BUTTON_HEIGHT )
		{
			help = false;
		}
		return help;
}
void handleMouseEventST(SDL_Event& e,int x, int y, SDL_Surface * st_i, SDL_Surface * st_f,SDL_Surface * hp_i, SDL_Surface * hp_f,SDL_Surface * gsurface_st,bool &quit_st,bool &st,bool &hp)
{
    if(inside_start(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            quit_st=true;
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            st=true;
        }
    }
    if(!inside_start(x,y))
        st=false;
    if(inside_help(x,y))
    {
        if(e.type==SDL_MOUSEBUTTONDOWN)
        {
            help_window(quit_st);
        }
        if(e.type==SDL_MOUSEMOTION)
        {
            hp=true;
        }
    }
    if(!inside_help(x,y))
        hp=false;
}
void start_window()
{
	//Mix_Music *gMusic = NULL;
    // Making the music

	SDL_Surface * gsurface_st = NULL;
	SDL_Surface * image = NULL;
	SDL_Surface * start_initial_image = NULL;
	SDL_Surface * start_final_image = NULL;
	SDL_Surface * help_initial_image = NULL;
	SDL_Surface * help_final_image = NULL;

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
			gsurface_st = SDL_GetWindowSurface (gwindow);
		}
	}

	if (!success )
	{
		cout << "FAILED TO INITIALIZE!"<<endl;
	}

	// loading start background image
	success = true;

    //Load music
    //gMusic = Mix_LoadMUS( "ohyeah.wav" );
    /*if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }*/

	image = SDL_LoadBMP ("img/cs_background.bmp");
	start_initial_image = SDL_LoadBMP ("img/START_INITIAL.bmp");
	start_final_image = SDL_LoadBMP ("img/START_FINAL.bmp");
	help_initial_image = SDL_LoadBMP ("img/HELP_INITIAL.bmp");
	help_final_image = SDL_LoadBMP ("img/HELP_FINAL.bmp");

	if ( image == NULL || start_initial_image == NULL ||start_final_image==NULL||help_initial_image==NULL||help_final_image==NULL)
	{
		cout << " Error : " << SDL_GetError() <<endl;
		success = false;
	}

	if (! success )
	{
		cout << "FAILED TO LOAD MEDIA!!!" <<endl;
	}

	// actually blitting the image

		while (!quit_st)
		{
			SDL_Event e;
            bool st,hp;
			while ( SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit_st = true;
					quit = true;
				}
				if(e.type==SDL_MOUSEMOTION||e.type==SDL_MOUSEBUTTONDOWN||e.type==SDL_MOUSEBUTTONUP)
				{
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    handleMouseEventST(e,x,y,start_initial_image,start_final_image,help_initial_image,help_final_image,gsurface_st,quit_st,st,hp);

				}
			}


			SDL_Rect dest_start,dest_help;
			dest_start.x = START_X;
			dest_start.y = START_Y;
			dest_help.x=HELP_X;
			dest_help.y=HELP_Y;
		SDL_BlitSurface (image, NULL, gsurface_st, NULL);
        if(!st)
            SDL_BlitSurface (start_initial_image, NULL, gsurface_st, &dest_start);
		else
            SDL_BlitSurface (start_final_image, NULL, gsurface_st, &dest_start);
		if(!hp)
            SDL_BlitSurface (help_initial_image, NULL, gsurface_st, &dest_help);
        else
            SDL_BlitSurface (help_final_image, NULL, gsurface_st, &dest_help);
		SDL_UpdateWindowSurface(gwindow);
	    }





	// closing the stuff
	//Free the music
    //Mix_FreeMusic( gMusic );
    //gMusic = NULL;

	SDL_FreeSurface(image);
	image = NULL;
	SDL_FreeSurface(start_initial_image);
	start_initial_image = NULL;
	SDL_FreeSurface(start_final_image);
	start_final_image = NULL;
	SDL_FreeSurface(help_initial_image);
	help_initial_image = NULL;
	SDL_FreeSurface(help_final_image);
	help_final_image = NULL;
	SDL_FreeSurface(gsurface_st);
	gsurface_st=NULL;

    //Mix_quit_st();


}
