#include<SDL2/SDL.h>
#include<iostream>
#include<stdio.h>
#include"parameters.h"

using namespace std;



const int BACK_BUTTON_X=380;
const int BACK_BUTTON_Y=500;
const int BACK_BUTTON_WIDTH=200;
const int BACK_BUTTON_HEIGHT=40;

bool inside_back_hl(int x, int y)
{
    		//Check if mouse is in less button
		bool start = true;

		//Mouse is left of the button
		if( x < BACK_BUTTON_X )
		{
			start = false;
		}
		//Mouse is right of the button
		else if( x > BACK_BUTTON_X + BACK_BUTTON_WIDTH )
		{
			start = false;
		}
		//Mouse above the button
		else if( y < BACK_BUTTON_Y)
		{
			start = false;
		}
		//Mouse below the button
		else if( y > BACK_BUTTON_Y  + BACK_BUTTON_HEIGHT )
		{
			start = false;
		}
		return start;
}

void handleMouseEventHL(SDL_Event &e_hl,int x, int y, bool &hl, bool &hl_quit )
{
    if(inside_back_hl(x,y))
    {
        if(e_hl.type ==  SDL_MOUSEBUTTONDOWN)
        {
            hl_quit=true;
        }
        if(e_hl.type== SDL_MOUSEMOTION)
        {
            hl=true;
        }
    }
    if(!inside_back_hl(x,y))
        hl=false;

}
void help_window(bool &qq)
{
	SDL_Surface * gsurface_hl = NULL;
	SDL_Surface * hl_background = NULL;
	SDL_Surface * hl_back_initial_image = NULL;
	SDL_Surface * hl_back_final_image = NULL;

	bool success = true;


    gsurface_hl = SDL_GetWindowSurface (gwindow);

	hl_background=SDL_LoadBMP("img/background.bmp");
	hl_back_final_image=SDL_LoadBMP("img/back_final.bmp");
	hl_back_initial_image=SDL_LoadBMP("img/back_initial.bmp");

	if(hl_background==NULL||hl_back_final_image==NULL||hl_back_initial_image==NULL)
	{
		cout << " Error : " << SDL_GetError() <<endl;
		success = false;
	}

	if (! success )
	{
		cout << "FAILED TO LOAD MEDIA!!!" <<endl;
	}

    bool quit_hl = false;

		while (!quit_hl)
		{
			SDL_Event e;
            bool hl;
			while ( SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit_hl = true;
					quit=true;
					qq=true;
				}
				if(e.type==SDL_MOUSEMOTION||e.type==SDL_MOUSEBUTTONDOWN||e.type==SDL_MOUSEBUTTONUP)
				{
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    handleMouseEventHL(e,x,y,hl,quit_hl);

				}
			}


			SDL_Rect dest_hl_bk;
			dest_hl_bk.x=BACK_BUTTON_X;
			dest_hl_bk.y=BACK_BUTTON_Y;
		SDL_BlitSurface (hl_background, NULL, gsurface_hl, NULL);
        if(!hl)
            SDL_BlitSurface (hl_back_initial_image, NULL, gsurface_hl, &dest_hl_bk);
		else
            SDL_BlitSurface (hl_back_final_image, NULL, gsurface_hl, &dest_hl_bk);
		SDL_UpdateWindowSurface(gwindow);
	    }

    //closing everything
    SDL_FreeSurface(gsurface_hl);
    gsurface_hl=NULL;
    SDL_FreeSurface(hl_background);
	hl_background = NULL;
	SDL_FreeSurface(hl_back_final_image);
	hl_back_final_image = NULL;
	SDL_FreeSurface(hl_back_initial_image);
	hl_back_initial_image = NULL;

}
