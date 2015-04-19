#include<SDL2/SDL.h>
#include<iostream>
#include<stdio.h>
#include"parameters.h"

using namespace std;



const int BACK_BUTTON_X=835;
const int BACK_BUTTON_Y=521;
const int BACK_BUTTON_WIDTH=200;
const int BACK_BUTTON_HEIGHT=40;
const int ONE_X=405;
const int ONE_Y=521;
const int ONE_WIDTH=40;
const int ONE_HEIGHT=40;
const int TWO_X=545;
const int TWO_Y=521;
const int THREE_X=695;
const int THREE_Y=521;

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

bool inside_one_hl(int x, int y)
{
    		//Check if mouse is in less button
		bool start = true;

		//Mouse is left of the button
		if( x < ONE_X )
		{
			start = false;
		}
		//Mouse is right of the button
		else if( x > ONE_X + ONE_WIDTH )
		{
			start = false;
		}
		//Mouse above the button
		else if( y < ONE_Y)
		{
			start = false;
		}
		//Mouse below the button
		else if( y > ONE_Y  + ONE_HEIGHT )
		{
			start = false;
		}
		return start;
}

bool inside_two_hl(int x, int y)
{
    		//Check if mouse is in less button
		bool start = true;

		//Mouse is left of the button
		if( x < TWO_X )
		{
			start = false;
		}
		//Mouse is right of the button
		else if( x > TWO_X + ONE_WIDTH )
		{
			start = false;
		}
		//Mouse above the button
		else if( y < TWO_Y)
		{
			start = false;
		}
		//Mouse below the button
		else if( y > TWO_Y  + ONE_HEIGHT )
		{
			start = false;
		}
		return start;
}

bool inside_three_hl(int x, int y)
{
    		//Check if mouse is in less button
		bool start = true;

		//Mouse is left of the button
		if( x < THREE_X )
		{
			start = false;
		}
		//Mouse is right of the button
		else if( x > THREE_X + ONE_WIDTH )
		{
			start = false;
		}
		//Mouse above the button
		else if( y < THREE_Y)
		{
			start = false;
		}
		//Mouse below the button
		else if( y > THREE_Y  + ONE_HEIGHT )
		{
			start = false;
		}
		return start;
}
void handleMouseEventHL(SDL_Event &e_hl,int x, int y, bool &hl, bool &hl_quit ,bool &hl1, bool&hl2, bool&hl3, int&b)
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
    if(inside_one_hl(x,y))
    {
        if(e_hl.type ==  SDL_MOUSEBUTTONDOWN)
        {
            b=1;
        }
        if(e_hl.type== SDL_MOUSEMOTION)
        {
            hl1=true;
        }
    }
    if(!inside_one_hl(x,y))
        hl1=false;
    if(inside_two_hl(x,y))
    {
        if(e_hl.type ==  SDL_MOUSEBUTTONDOWN)
        {
            b=2;
        }
        if(e_hl.type== SDL_MOUSEMOTION)
        {
            hl2=true;
        }
    }
    if(!inside_two_hl(x,y))
        hl2=false;
    if(inside_three_hl(x,y))
    {
        if(e_hl.type ==  SDL_MOUSEBUTTONDOWN)
        {
            b=3;
        }
        if(e_hl.type== SDL_MOUSEMOTION)
        {
            hl3=true;
        }
    }
    if(!inside_three_hl(x,y))
        hl3=false;

}
void help_window(bool &qq)
{
	SDL_Surface * gsurface_hl = NULL;
	SDL_Surface * hl_background1 = NULL;
	SDL_Surface * hl_background2 = NULL;
	SDL_Surface * hl_background3 = NULL;
	SDL_Surface * hl_1_in=NULL;
	SDL_Surface * hl_1_fn=NULL;
	SDL_Surface * hl_2_in=NULL;
	SDL_Surface * hl_2_fn=NULL;
	SDL_Surface * hl_3_in=NULL;
	SDL_Surface * hl_3_fn=NULL;
	SDL_Surface * hl_back_initial_image = NULL;
	SDL_Surface * hl_back_final_image = NULL;

	bool success = true;


    gsurface_hl = SDL_GetWindowSurface (gwindow);

	hl_background1=SDL_LoadBMP("img/help_1.bmp");
	hl_background2=SDL_LoadBMP("img/help_2.bmp");
	hl_background3=SDL_LoadBMP("img/help_3.bmp");
	hl_1_in=SDL_LoadBMP("img/1_initial.bmp");
	hl_1_fn=SDL_LoadBMP("img/1_final.bmp");
	hl_2_in=SDL_LoadBMP("img/2_initial.bmp");
	hl_2_fn=SDL_LoadBMP("img/2_final.bmp");
	hl_3_in=SDL_LoadBMP("img/3_initial.bmp");
	hl_3_fn=SDL_LoadBMP("img/3_final.bmp");
	hl_back_final_image=SDL_LoadBMP("img/back_final.bmp");
	hl_back_initial_image=SDL_LoadBMP("img/back_initial.bmp");

	if(hl_background1==NULL||hl_back_final_image==NULL||hl_back_initial_image==NULL)
	{
		cout << " Error : " << SDL_GetError() <<endl;
		success = false;
	}

	if (! success )
	{
		cout << "FAILED TO LOAD MEDIA!!!" <<endl;
	}

    bool quit_hl = false;
    int b=1;
    switch(b)
    {
        case 1:SDL_BlitSurface (hl_background1, NULL, gsurface_hl, NULL);
        case 2:SDL_BlitSurface (hl_background2, NULL, gsurface_hl, NULL);
        case 3:SDL_BlitSurface (hl_background3, NULL, gsurface_hl, NULL);
        default:break;
    }
		while (!quit_hl)
		{
			SDL_Event e;
            bool hl, h1,h2,h3;
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
                    handleMouseEventHL(e,x,y,hl,quit_hl,h1,h2,h3,b);

				}
			}


			SDL_Rect dest_hl_bk,hl_1,hl_2,hl_3;
			hl_1.x=ONE_X;
			hl_1.y=ONE_Y;
			hl_2.x=TWO_X;
			hl_2.y=TWO_Y;
			hl_3.x=THREE_X;
			hl_3.y=THREE_Y;
			dest_hl_bk.x=BACK_BUTTON_X;
			dest_hl_bk.y=BACK_BUTTON_Y;
			cout << "b " << b << endl;
        switch(b)
        {
            case 1:SDL_BlitSurface (hl_background1, NULL, gsurface_hl, NULL); break;
            case 2:SDL_BlitSurface (hl_background2, NULL, gsurface_hl, NULL); break; 
            case 3:SDL_BlitSurface (hl_background3, NULL, gsurface_hl, NULL); break;
            default:break;
        }
        if(!hl)
            SDL_BlitSurface (hl_back_initial_image, NULL, gsurface_hl, &dest_hl_bk);
		else
            SDL_BlitSurface (hl_back_final_image, NULL, gsurface_hl, &dest_hl_bk);
         if(!h1)
            SDL_BlitSurface (hl_1_in, NULL, gsurface_hl, &hl_1);
		else
            SDL_BlitSurface (hl_1_fn, NULL, gsurface_hl, &hl_1);
        if(!h2)
            SDL_BlitSurface (hl_2_in, NULL, gsurface_hl, &hl_2);
		else
            SDL_BlitSurface (hl_2_fn, NULL, gsurface_hl, &hl_2);
        if(!h3)
            SDL_BlitSurface (hl_3_in, NULL, gsurface_hl, &hl_3);
		else
            SDL_BlitSurface (hl_3_fn, NULL, gsurface_hl, &hl_3);

		SDL_UpdateWindowSurface(gwindow);
	    }

    //closing everything
    SDL_FreeSurface(gsurface_hl);
    gsurface_hl=NULL;
    SDL_FreeSurface(hl_background1);
	hl_background1 = NULL;
    SDL_FreeSurface(hl_background2);
	hl_background2 = NULL;
    SDL_FreeSurface(hl_background3);
	hl_background3 = NULL;
	SDL_FreeSurface(hl_back_final_image);
	hl_back_final_image = NULL;
	SDL_FreeSurface(hl_back_initial_image);
	hl_back_initial_image = NULL;

}
