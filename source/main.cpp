#include"parameters.h"

long long int sim_time = 0;
const int X=490;
const int delay1=2,delay2=5,delay3=10,delay4=100;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 582;
const int FIELD_X=23;
const int FIELD_Y=60;
const int FIELD_WIDTH=X;
const int FIELD_HEIGHT=X;
const int PAUSE_X=820;
const int PAUSE_Y=76;
const int PAUSE_WIDTH=200;
const int PAUSE_HEIGHT=40;
const int BEGIN_X=820;
const int BEGIN_Y=12;
const int BEGIN_WIDTH=200;
const int BEGIN_HEIGHT=40;
const int DELAY_X=820;
const int DELAY_Y=140;
const int DELAY_WIDTH=200;
const int DELAY_HEIGHT=40;
const int H_COL_X=820;
const int H_COL_Y=332;
const int H_COL_WIDTH=200;
const int H_COL_HEIGHT=40;
const int Z_NEST_X=820;
const int Z_NEST_Y=396;
const int Z_NEST_WIDTH=200;
const int Z_NEST_HEIGHT=40;
const int FS_X=820;
const int FS_Y=460;
const int FS_WIDTH=200;
const int FS_HEIGHT=40;
const int BACK_X=820;
const int BACK_Y=268;
const int BACK_WIDTH=200;
const int BACK_HEIGHT=40;
const int RESET_X=820;
const int RESET_Y=204;
const int RESET_WIDTH=200;
const int RESET_HEIGHT=40;
const int H_COL_IMAGE_WIDTH=0;
const int H_COL_IMAGE_HEIGHT=0;
const int Z_NEST_IMAGE_WIDTH=0;
const int Z_NEST_IMAGE_HEIGHT=0;
const int F_SOURCE_IMAGE_WIDTH=0;
const int F_SOURCE_IMAGE_HEIGHT=0;

int delay=delay1;
int c_n=0;

SDL_Window * gwindow = NULL; //Window is used by all input functions also
SDL_Surface * gsurface = NULL;
SDL_Surface * background = NULL;
SDL_Surface * human_left_image = NULL;
SDL_Surface * human_up_image = NULL;
SDL_Surface * human_right_image = NULL;
SDL_Surface * human_down_image = NULL;

SDL_Surface * zombie_left_image = NULL;
SDL_Surface * zombie_right_image = NULL;
SDL_Surface * zombie_up_image = NULL;
SDL_Surface * zombie_down_image = NULL;

SDL_Surface * human_colony_image = NULL;
SDL_Surface * zombie_nest_image = NULL;

SDL_Surface * food_source_image = NULL;
SDL_Surface * begin_sim_in=NULL;
SDL_Surface * begin_sim_fn=NULL;
SDL_Surface * pause_in=NULL;
SDL_Surface * pause_fn=NULL;
SDL_Surface * delay_in=NULL;
SDL_Surface * delay_fn=NULL;
SDL_Surface * h_col_in=NULL;
SDL_Surface * h_col_fn=NULL;
SDL_Surface * z_nest_in=NULL;
SDL_Surface * z_nest_fn=NULL;
SDL_Surface * fs_in=NULL;
SDL_Surface * fs_fn=NULL;
SDL_Surface * reset_in=NULL;
SDL_Surface * reset_fn=NULL;
SDL_Surface * back_in=NULL;
SDL_Surface * back_fn=NULL;
SDL_Surface * bluedot = NULL;
bool quit=false;

vector<human> H;
vector<zombie> Z;
Configuration Input;
node grid[X][X];
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
vector<human>::iterator it_human;
vector<human_colony>::iterator it_human_colony;

vector<zombie>::iterator it_zombie;
vector<zombie_nest>::iterator it_zombie_nest;

//human_colony h;
//zombie_nest z;
//food_source f;
//food_source f2;

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface * loadedSurface = NULL;
	loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gsurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

bool inside_field(int x,int y)
{
    bool in = true;

		//Mouse is left of the button
		if( x <  FIELD_X)
		{
			in = false;
		}
		//Mouse is right of the button
		else if( x >  FIELD_X+ FIELD_WIDTH )
		{
			in = false;
		}
		//Mouse above the button
		else if( y < FIELD_Y )
		{
			in = false;
		}
		//Mouse below the button
		else if( y > FIELD_Y + FIELD_HEIGHT )
		{
			in = false;
		}
		return in;

}
void new_human_colony()
{
    human_colony new_h;
    human_colony_input(new_h);
	new_h.colony_number=c_n;
	c_n++;
	SDL_BlitSurface(background,NULL,gsurface,NULL);
	SDL_UpdateWindowSurface(gwindow);
    bool hc_quit=false;
    if(quit)
    return;
    while(!hc_quit)
    {
        SDL_Event eh;
        while(SDL_PollEvent(&eh) != 0)
        {
            if (eh.type == SDL_QUIT)
            {
                quit = true;
                hc_quit=true;
            }
            else if(eh.type==SDL_MOUSEBUTTONDOWN)
            {
                int hc_x,hc_y;
                SDL_GetMouseState(&hc_x,&hc_y);
                if(inside_field(hc_x,hc_y))
                {
                    hc_quit=true;
                    new_h.pos.x=hc_x-FIELD_X;
                    new_h.pos.y=hc_y-FIELD_Y;
                }
            }
        }
    }
    if(!quit)
		
    Input.human_colonies.push_back(new_h);
}
void new_zombie_nest()
{
    zombie_nest new_z;
    zombie_nest_input(new_z);
	SDL_BlitSurface(background,NULL,gsurface,NULL);
	SDL_UpdateWindowSurface(gwindow);
    bool zn_quit=false;
    if(quit)
    return;
    while(!zn_quit)
    {
        SDL_Event ez;
        while(SDL_PollEvent(&ez) != 0)
        {
            if (ez.type == SDL_QUIT)
            {
                quit = true;
                zn_quit = true;
            }
            if(ez.type==SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(inside_field(x,y))
                {
                    zn_quit=true;
                    new_z.pos.x=x-FIELD_X;
                    new_z.pos.y=y-FIELD_Y;
                }
            }
        }
    }
    if(!quit)
    Input.zombie_nests.push_back(new_z);
}
void new_food_source()
{
    food_source new_f;
    food_source_input(new_f);
	SDL_BlitSurface(background,NULL,gsurface,NULL);
	SDL_UpdateWindowSurface(gwindow);
    bool fs_quit=false;
    if(quit)
    return;
    while(!fs_quit)
    {
        SDL_Event ef;
        while(SDL_PollEvent(&ef) != 0)
        {
            if (ef.type == SDL_QUIT)
            {
                quit = true;
                fs_quit = true;
            }
            if(ef.type==SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(inside_field(x,y))
                {
                    fs_quit=true;
                    new_f.x=x-FIELD_X;
                    new_f.y=y-FIELD_Y;
                }
            }
        }
    }
    if(!quit)
		{Input.food_sources.push_back(new_f); init_grid2();}
}
void back_to_start()
{
    quit=true;
}
void reset()
{
    H.clear();
    Z.clear();
    Input.human_colonies.clear();
	
	for (vector<food_source>::iterator it = Input.food_sources.begin(); it != Input.food_sources.end(); it++)
	{	int i,j;
		int fs_size = int(sqrt(it->food_source_area));
		int rightextenti = (i + fs_size  > X-1)?X-1:i + fs_size;
		int downextentj = (j + fs_size > X-1 )?X-1: j + fs_size;
		for (i = it->x ; i <= rightextenti ; i++)
		{
			for(j = it->y ; j <= downextentj; j++)
			{
				grid[i][j].food = 0;
			}
		}
		
		
	}
    Input.food_sources.clear();
    Input.zombie_nests.clear();
    Input.number_of_colonies =  0;
    //Input.reference_pheromone = 0;
    Input.ev_rate = 0.999;
    Input.delay = 2000;
    Input.base_pheromone  = 0.000;
    Input.number_of_nests = 0;
    Input.number_of_food_sources = 0;
    it_human=H.begin();
    it_zombie=Z.begin();
    it_human_colony=Input.human_colonies.begin();
    it_zombie_nest=Input.zombie_nests.begin();
}
bool inside_begin(int x,int y)
{
    bool in = true;

		//Mouse is left of the button
		if( x <  BEGIN_X)
		{
			in = false;
		}
		//Mouse is right of the button
		else if( x >  BEGIN_X+ BEGIN_WIDTH )
		{
			in = false;
		}
		//Mouse above the button
		else if( y < BEGIN_Y )
		{
			in = false;
		}
		//Mouse below the button
		else if( y > BEGIN_Y + BEGIN_HEIGHT )
		{
			in = false;
		}
		return in;

}
bool inside_back(int x,int y)
{
    bool in = true;

		//Mouse is left of the button
		if( x <  BACK_X)
		{
			in = false;
		}
		//Mouse is right of the button
		else if( x >  BACK_X+ BACK_WIDTH )
		{
			in = false;
		}
		//Mouse above the button
		else if( y < BACK_Y )
		{
			in = false;
		}
		//Mouse below the button
		else if( y > BACK_Y + BACK_HEIGHT )
		{
			in = false;
		}
		return in;

}
bool inside_reset(int x,int y)
{
    bool in = true;

		//Mouse is left of the button
		if( x <  RESET_X)
		{
			in = false;
		}
		//Mouse is right of the button
		else if( x >  RESET_X+ RESET_WIDTH )
		{
			in = false;
		}
		//Mouse above the button
		else if( y < RESET_Y )
		{
			in = false;
		}
		//Mouse below the button
		else if( y > RESET_Y + RESET_HEIGHT )
		{
			in = false;
		}
		return in;

}
bool inside_fs(int x,int y)
{
    bool in = true;

		//Mouse is left of the button
		if( x <  FS_X)
		{
			in = false;
		}
		//Mouse is right of the button
		else if( x >  FS_X+ FS_WIDTH )
		{
			in = false;
		}
		//Mouse above the button
		else if( y < FS_Y )
		{
			in = false;
		}
		//Mouse below the button
		else if( y > FS_Y + FS_HEIGHT )
		{
			in = false;
		}
		return in;

}
bool inside_pause(int x, int y)
{
     bool ps = true;

		//Mouse is left of the button
		if( x <  PAUSE_X)
		{
			ps = false;
		}
		//Mouse is right of the button
		else if( x >  PAUSE_X+ PAUSE_WIDTH )
		{
			ps = false;
		}
		//Mouse above the button
		else if( y < PAUSE_Y )
		{
			ps = false;
		}
		//Mouse below the button
		else if( y > PAUSE_Y + PAUSE_HEIGHT )
		{
			ps = false;
		}
		return ps;
}
bool inside_delay(int x,int y)
{
    bool dl = true;

		//Mouse is left of the button
		if( x <  DELAY_X)
		{
			dl = false;
		}
		//Mouse is right of the button
		else if( x >  DELAY_X+ DELAY_WIDTH )
		{
			dl = false;
		}
		//Mouse above the button
		else if( y < DELAY_Y )
		{
			dl = false;
		}
		//Mouse below the button
		else if( y > DELAY_Y + DELAY_HEIGHT )
		{
			dl = false;
		}
		return dl;
}
bool inside_hcol(int x,int y)
{
    bool hhc = true;

		//Mouse is left of the button
		if( x <  H_COL_X)
		{
			hhc = false;
		}
		//Mouse is right of the button
		else if( x >  H_COL_X+ H_COL_WIDTH )
		{
			hhc = false;
		}
		//Mouse above the button
		else if( y < H_COL_Y )
		{
			hhc = false;
		}
		//Mouse below the button
		else if( y > H_COL_Y + H_COL_HEIGHT )
		{
			hhc = false;
		}
		return hhc;
}
bool inside_znest(int x,int y)
{
    bool zzn = true;

		//Mouse is left of the button
		if( x <  Z_NEST_X)
		{
			zzn = false;
		}
		//Mouse is right of the button
		else if( x >  Z_NEST_X+ Z_NEST_WIDTH )
		{
			zzn = false;
		}
		//Mouse above the button
		else if( y < Z_NEST_Y )
		{
			zzn = false;
		}
		//Mouse below the button
		else if( y > Z_NEST_Y + Z_NEST_HEIGHT )
		{
			zzn = false;
		}
		return zzn;
}
void handle_human_colonies(SDL_Event &e,int x, int y,bool &in, human_colony &h)
{
    bool in_h = true;

		//Mouse is left of the button
		if( x <  h.pos.x)
		{
			in_h = false;
		}
		//Mouse is right of the button
		else if( x >  h.pos.x+ H_COL_IMAGE_WIDTH )
		{
			in_h = false;
		}
		//Mouse above the button
		else if( y < h.pos.y )
		{
			in_h = false;
		}
		//Mouse below the button
		else if( y > h.pos.y + H_COL_IMAGE_HEIGHT )
		{
			in_h = false;
		}
    if(in_h)
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            human_colony_input(h);
            in=true;
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in=true;
        }
    }

}
void handle_zombie_nests(SDL_Event &e,int x, int y,bool &in, zombie_nest &z)
{
    bool in_z = true;

		//Mouse is left of the button
		if( x <  z.pos.x)
		{
			in_z = false;
		}
		//Mouse is right of the button
		else if( x >  z.pos.x+ Z_NEST_IMAGE_WIDTH )
		{
			in_z = false;
		}
		//Mouse above the button
		else if( y < z.pos.y )
		{
			in_z = false;
		}
		//Mouse below the button
		else if( y > z.pos.y + Z_NEST_IMAGE_HEIGHT )
		{
			in_z = false;
		}
    if(in_z)
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            zombie_nest_input(z);
            in=true;
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in=true;
        }
    }
}
void handle_food_sources(SDL_Event &e,int x, int y,bool &in, food_source &f)
{
    bool in_f = true;

		//Mouse is left of the button
		if( x <  f.x)
		{
			in_f = false;
		}
		//Mouse is right of the button
		else if( x >  f.x+ F_SOURCE_IMAGE_WIDTH )
		{
			in_f = false;
		}
		//Mouse above the button
		else if( y < f.y )
		{
			in_f = false;
		}
		//Mouse below the button
		else if( y > f.y + F_SOURCE_IMAGE_HEIGHT )
		{
			in_f = false;
		}
    if(in_f)
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            food_source_input(f);
            in=true;
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in=true;
        }
    }
}
void handleMouseEventMain(SDL_Event &e,int x, int y,bool &in_b, bool &in_p, bool &begin_sim, bool &pause,bool &in_d,bool &in_h,bool &in_z, bool &in_f, bool &in_res, bool &in_back)
{
    if(inside_begin(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            begin_sim=true;
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_b=true;
        }
    }
    if(!inside_begin(x,y))
        in_b=false;
    if(inside_field(x,y)&&e.type==SDL_MOUSEBUTTONDOWN)
    {
        bool in=false;
        vector<human_colony>::iterator it_human_colony1;
        vector<zombie_nest>::iterator it_zombie_nest1;
        vector<food_source>::iterator it_food_source1;
        for(it_zombie_nest1=Input.zombie_nests.begin();it_zombie_nest1!=Input.zombie_nests.end();it_zombie_nest1++)
        {
            zombie_nest &zt2= *it_zombie_nest1;
            handle_zombie_nests(e,x,y,in,zt2);
            if(in)break;
        }
        for(it_human_colony1=Input.human_colonies.begin();it_human_colony1!=Input.human_colonies.end();it_human_colony1++)
        {
            human_colony &ht2= *it_human_colony1;
            handle_human_colonies(e,x,y,in,ht2);
            if(in)break;
        }
        for(it_food_source1=Input.food_sources.begin();it_food_source1!=Input.food_sources.end();it_food_source1++)
        {
            food_source &ft2= *it_food_source1;
            handle_food_sources(e,x,y,in,ft2);
            if(in)break;
        }
    }
    if(inside_reset(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
           // reset();
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_res=true;
        }
    }
    if(!inside_reset(x,y))
        in_res=false;
    if(inside_back(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            back_to_start();
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_back=true;
        }
    }
    if(!inside_back(x,y))
        in_back=false;
    if(inside_fs(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
           // new_food_source();
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_f=true;
        }
    }
    if(!inside_fs(x,y))
        in_f=false;
    if(inside_delay(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            switch(delay)
            {
                case delay1:delay=delay2;break;
                case delay2:delay=delay3;break;
                case delay3:delay=delay4;break;
                case delay4:delay=delay1;break;
                default:break;
            }
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_d=true;
        }
    }
    if(!inside_delay(x,y))
        in_d=false;
    if(inside_pause(x,y))
    {
        if(e.type==SDL_MOUSEBUTTONDOWN)
        {
            pause=true;
        }
        if(e.type==SDL_MOUSEMOTION)
        {
            in_p=true;
        }
    }
    if(!inside_pause(x,y))
        in_p=false;
    if(inside_hcol(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
           // new_human_colony();
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_h=true;
        }
    }
    if(!inside_hcol(x,y))
        in_h=false;
    if(inside_znest(x,y))
    {
        if(e.type ==  SDL_MOUSEBUTTONDOWN)
        {
            //new_zombie_nest();
        }
        if(e.type== SDL_MOUSEMOTION)
        {
            in_z=true;
        }
    }
    if(!inside_znest(x,y))
        in_z=false;
}

void init ()
{
	SDL_Rect hcpos,znpos,fspos,pause_pos,begin_pos,delay_pos,h_col_pos,z_nest_pos,in_fs_pos,res_pos,back_pos;
	//hcpos.x = h.pos.x;
	//hcpos.y = h.pos.y;
	//SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
	//fspos.x = f.x;
	//fspos.y = f.y;
	//SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
	pause_pos.x=PAUSE_X;
	pause_pos.y=PAUSE_Y;

	begin_pos.x=BEGIN_X;
	begin_pos.y=BEGIN_Y;

	delay_pos.x=DELAY_X;
	delay_pos.y=DELAY_Y;

	h_col_pos.x=H_COL_X;
	h_col_pos.y=H_COL_Y;

	z_nest_pos.x=Z_NEST_X;
	z_nest_pos.y=Z_NEST_Y;

	in_fs_pos.x=FS_X;
	in_fs_pos.y=FS_Y;

	res_pos.x=RESET_X;
	res_pos.y=RESET_Y;

	back_pos.x=BACK_X;
	back_pos.y=BACK_Y;
	/*
	znpos.x = z.pos.x;
	znpos.y = z.pos.y;
	SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
	*/
	background = loadSurface ("img/background.bmp");
	human_colony_image = loadSurface("img/human_colony_image.bmp");
	zombie_nest_image = loadSurface ("img/zombie_nest_image.bmp");

	human_left_image = loadSurface("img/human_left_image.bmp");
	human_right_image = loadSurface("img/human_right_image.bmp");
	human_up_image =  loadSurface("img/human_up_image.bmp");
	human_down_image = loadSurface("img/human_down_image.bmp");

	zombie_left_image = loadSurface("img/zombie_left_image.bmp");
	zombie_down_image = loadSurface("img/zombie_down_image.bmp");
	zombie_up_image = loadSurface("img/zombie_up_image.bmp");
	zombie_right_image = loadSurface("img/zombie_right_image.bmp");

	food_source_image = loadSurface("img/food_source_image.bmp");
    begin_sim_in=loadSurface("img/begin_sim_initial.bmp");
    begin_sim_fn=loadSurface("img/begin_sim_final.bmp");
    pause_in=loadSurface("img/pause_initial.bmp");
    pause_fn=loadSurface("img/pause_final.bmp");
    delay_in=loadSurface("img/change_delay_initial.bmp");
    delay_fn=loadSurface("img/change_delay_final.bmp");
    h_col_in=loadSurface("img/new_human_colony_initial.bmp");
    h_col_fn=loadSurface("img/new_human_colony_final.bmp");
    z_nest_in=loadSurface("img/new_zombie_nest_initial.bmp");
    z_nest_fn=loadSurface("img/new_zombie_nest_final.bmp");
    fs_in=loadSurface("img/new_food_source_initial.bmp");
    fs_fn=loadSurface("img/new_food_source_final.bmp");
    reset_in=loadSurface("img/reset_initial.bmp");
    reset_fn=loadSurface("img/reset_final.bmp");
    back_in=loadSurface("img/back_initial.bmp");
    back_fn=loadSurface("img/back_final.bmp");
	bluedot = loadSurface("img/bluedot.bmp");
	
	
	SDL_Event e;
	
	bool new_quit=false;
	bool sanat=false,satwikk=false,shruti=false,tejashwar=false,grp=false;
	while(!new_quit)
	{
	
		
		SDL_BlitSurface (background, NULL, gsurface, NULL);
		if(!grp)
	    SDL_BlitSurface(begin_sim_in,NULL,gsurface,&begin_pos);
		else SDL_BlitSurface(begin_sim_fn,NULL,gsurface,&begin_pos);
  
   
	       // SDL_BlitSurface(pause_in,NULL,gsurface,&pause_pos);


	       // SDL_BlitSurface(delay_in,NULL,gsurface,&delay_pos);
     
			if(!sanat) SDL_BlitSurface(h_col_in,NULL,gsurface,&h_col_pos);
			else SDL_BlitSurface(h_col_fn,NULL,gsurface,&h_col_pos);
 
		 
			  if(!satwikk)SDL_BlitSurface(z_nest_in,NULL,gsurface,&z_nest_pos);
			  else SDL_BlitSurface(z_nest_fn,NULL,gsurface,&z_nest_pos);
   
		  
			  if(!tejashwar) SDL_BlitSurface(fs_in,NULL,gsurface,&in_fs_pos);
			  else SDL_BlitSurface(fs_fn,NULL,gsurface,&in_fs_pos);
  
   
	       if(!shruti) SDL_BlitSurface(back_in,NULL,gsurface,&back_pos);
		   else SDL_BlitSurface(back_fn,NULL,gsurface,&back_pos);
  
 
			//SDL_BlitSurface(reset_in,NULL,gsurface,&res_pos);
			SDL_UpdateWindowSurface(gwindow);
		while ( SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				new_quit = true;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN )
			{
				int x2,y2;
				SDL_GetMouseState(&x2, &y2);
				if(inside_hcol(x2,y2))
				{
					new_human_colony();
				}
				if(inside_znest(x2,y2))
				{	
					new_zombie_nest();
				}
				if(inside_fs(x2,y2))
				{
					new_food_source();
				}
				if(inside_begin(x2,y2))
				{
					new_quit = true;
				}
				if(inside_back(x2,y2))
				{
					new_quit=true;
					quit=true;
				}
				
			}
			if(e.type == SDL_MOUSEMOTION )
			{
				int x2,y2;
				SDL_GetMouseState(&x2, &y2);
				if(inside_hcol(x2,y2))
				{
					 sanat=true;
				}else sanat=false;
				if(inside_znest(x2,y2))
				{	
					  satwikk=true;
				}else satwikk=false;
				if(inside_fs(x2,y2))
				{
					tejashwar=true;
				}else tejashwar=false;
				if(inside_begin(x2,y2))
				{
					 grp=true;
				}else grp=false;
				if(inside_back(x2,y2))
				{
					shruti=true;
				}else shruti=false;
				
			}
		}
	}
	

}	

	

	
	



SDL_Surface* Load_image(std::string filename)
{
    SDL_Surface*loaded_image=NULL;
    SDL_Surface*optimized_image=NULL;
    loaded_image=loadSurface(filename.c_str());
    if(loaded_image!=NULL)
    {
        SDL_FreeSurface(loaded_image);
        if(optimized_image!=NULL)
        {
            SDL_SetColorKey(optimized_image,SDL_TRUE,SDL_MapRGB(optimized_image->format,0xff,0xff,0xff));
        }
    }else cout<<"Load_image not working";
    return optimized_image;
}


extern "C" int main(int argc, char *argv[])
{
	//srand (time(NULL)); // SEDING RAND

	start_window();


	
	// making the window and setting the surface


    gsurface = SDL_GetWindowSurface (gwindow);

    // loading images
	bool success = true;

	background = loadSurface ("img/background.bmp");
	human_colony_image = loadSurface("img/human_colony_image.bmp");
	zombie_nest_image = loadSurface ("img/zombie_nest_image.bmp");

	human_left_image = loadSurface("img/human_left_image.bmp");
	human_right_image = loadSurface("img/human_right_image.bmp");
	human_up_image =  loadSurface("img/human_up_image.bmp");
	human_down_image = loadSurface("img/human_down_image.bmp");

	zombie_left_image = loadSurface("img/zombie_left_image.bmp");
	zombie_down_image = loadSurface("img/zombie_down_image.bmp");
	zombie_up_image = loadSurface("img/zombie_up_image.bmp");
	zombie_right_image = loadSurface("img/zombie_right_image.bmp");

	food_source_image = loadSurface("img/food_source_image.bmp");
    begin_sim_in=loadSurface("img/begin_sim_initial.bmp");
    begin_sim_fn=loadSurface("img/begin_sim_final.bmp");
    pause_in=loadSurface("img/pause_initial.bmp");
    pause_fn=loadSurface("img/pause_final.bmp");
    delay_in=loadSurface("img/change_delay_initial.bmp");
    delay_fn=loadSurface("img/change_delay_final.bmp");
    h_col_in=loadSurface("img/new_human_colony_initial.bmp");
    h_col_fn=loadSurface("img/new_human_colony_final.bmp");
    z_nest_in=loadSurface("img/new_zombie_nest_initial.bmp");
    z_nest_fn=loadSurface("img/new_zombie_nest_final.bmp");
    fs_in=loadSurface("img/new_food_source_initial.bmp");
    fs_fn=loadSurface("img/new_food_source_final.bmp");
    reset_in=loadSurface("img/reset_initial.bmp");
    reset_fn=loadSurface("img/reset_final.bmp");
    back_in=loadSurface("img/back_initial.bmp");
    back_fn=loadSurface("img/back_final.bmp");
	bluedot = loadSurface("img/bluedot.bmp");

	if  (
            fs_in==NULL||fs_fn==NULL||z_nest_fn==NULL||z_nest_in==NULL||
            h_col_fn==NULL||h_col_in==NULL||delay_fn==NULL||delay_in==NULL||
            begin_sim_in==NULL||begin_sim_fn==NULL||pause_fn==NULL||pause_in==NULL||
            human_down_image == NULL||human_left_image==NULL||human_right_image==NULL||human_up_image==NULL||
            zombie_left_image == NULL||zombie_down_image==NULL||zombie_right_image==NULL||zombie_up_image==NULL||
            human_colony_image == NULL||zombie_nest_image == NULL||background == NULL||food_source_image == NULL||
            reset_in==NULL||reset_fn==NULL||back_in==NULL||back_fn==NULL
        )
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

	SDL_Rect hcpos,znpos,fspos,pause_pos,begin_pos,delay_pos,h_col_pos,z_nest_pos,in_fs_pos,res_pos,back_pos;
	//hcpos.x = h.pos.x;
	//hcpos.y = h.pos.y;
	//SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
	//fspos.x = f.x;
	//fspos.y = f.y;
	//SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
	pause_pos.x=PAUSE_X;
	pause_pos.y=PAUSE_Y;

	begin_pos.x=BEGIN_X;
	begin_pos.y=BEGIN_Y;

	delay_pos.x=DELAY_X;
	delay_pos.y=DELAY_Y;

	h_col_pos.x=H_COL_X;
	h_col_pos.y=H_COL_Y;

	z_nest_pos.x=Z_NEST_X;
	z_nest_pos.y=Z_NEST_Y;

	in_fs_pos.x=FS_X;
	in_fs_pos.y=FS_Y;

	res_pos.x=RESET_X;
	res_pos.y=RESET_Y;

	back_pos.x=BACK_X;
	back_pos.y=BACK_Y;
	/*
	znpos.x = z.pos.x;
	znpos.y = z.pos.y;
	SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
	*/


	/***********************************************************************/

    init();
	init_grid();
	init_human_list();
	init_zombie_list();



	// actually blitting the image
		while (!quit)
		{

            SDL_Event e;
            bool in_res=false,in_back=false,in_pause=false, in_begin=false,in_delay=false, in_h_col=false,in_z_nest=false, in_fs=false;

            bool pause=false,begin_sim=false;

			while ( SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if(e.type==SDL_MOUSEMOTION||e.type==SDL_MOUSEBUTTONDOWN||e.type==SDL_MOUSEBUTTONUP)
				{
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    handleMouseEventMain(e,x,y,in_begin,in_pause,begin_sim,pause,in_delay,in_h_col,in_z_nest,in_fs,in_res,in_back);

				}

			}
			while(pause)
			{
                begin_sim=false;
                SDL_Event e1;
                while(SDL_PollEvent(&e1) != 0)
                {
                    if (e1.type == SDL_QUIT)
                    {
                        quit = true;
                        pause=false;
                    }
                    if(e1.type==SDL_MOUSEMOTION||e1.type==SDL_MOUSEBUTTONDOWN||e1.type==SDL_MOUSEBUTTONUP)
                    {
                        int x1,y1;
                        SDL_GetMouseState(&x1,&y1);
                        handleMouseEventMain(e1,x1,y1,in_begin,in_pause,begin_sim,pause,in_delay,in_h_col,in_z_nest,in_fs,in_res,in_back);
                        if(in_delay)
                            SDL_BlitSurface(delay_fn,NULL,gsurface,&delay_pos);
                        else
                            SDL_BlitSurface(delay_in,NULL,gsurface,&delay_pos);
                        if(in_begin)
                            SDL_BlitSurface(begin_sim_fn,NULL,gsurface,&begin_pos);
                        else
                            SDL_BlitSurface(begin_sim_in,NULL,gsurface,&begin_pos);
                        // if(in_h_col)
                           // SDL_BlitSurface(h_col_fn,NULL,gsurface,&h_col_pos);
                        //else
                          //  SDL_BlitSurface(h_col_in,NULL,gsurface,&h_col_pos);
                        //if(in_z_nest)
                          //  SDL_BlitSurface(z_nest_fn,NULL,gsurface,&z_nest_pos);
                        //else
                          //  SDL_BlitSurface(z_nest_in,NULL,gsurface,&z_nest_pos);
                         //if(in_fs)
                           // SDL_BlitSurface(fs_fn,NULL,gsurface,&in_fs_pos);
                        //else
                          //  SDL_BlitSurface(fs_in,NULL,gsurface,&in_fs_pos);
                         if(in_back)
                            SDL_BlitSurface(back_fn,NULL,gsurface,&back_pos);
                        else
                            SDL_BlitSurface(back_in,NULL,gsurface,&back_pos);
                          if(in_pause)
                            SDL_BlitSurface(pause_fn,NULL,gsurface,&pause_pos);
                        else
                            SDL_BlitSurface(pause_in,NULL,gsurface,&pause_pos);
                        // if(in_res)
                            //SDL_BlitSurface(reset_fn,NULL,gsurface,&res_pos);
                       // else
                            //SDL_BlitSurface(reset_in,NULL,gsurface,&res_pos);

                        if(begin_sim)
                            pause=false;

                        SDL_UpdateWindowSurface(gwindow);

                    }
                }
			}


		    change_state();
			cout << "Something " << endl;


			vector<human>::iterator tempith;

			vector<zombie>::iterator tempitz;
			SDL_BlitSurface (background, NULL, gsurface, NULL);
			if(in_begin)
                SDL_BlitSurface(begin_sim_fn,NULL,gsurface,&begin_pos);
            else
                SDL_BlitSurface(begin_sim_in,NULL,gsurface,&begin_pos);
            if(in_pause)
                SDL_BlitSurface(pause_fn,NULL,gsurface,&pause_pos);
            else
                SDL_BlitSurface(pause_in,NULL,gsurface,&pause_pos);
            if(in_delay)
                SDL_BlitSurface(delay_fn,NULL,gsurface,&delay_pos);
            else
                SDL_BlitSurface(delay_in,NULL,gsurface,&delay_pos);
            //if(in_h_col)
              //  SDL_BlitSurface(h_col_fn,NULL,gsurface,&h_col_pos);
            //else
              //  SDL_BlitSurface(h_col_in,NULL,gsurface,&h_col_pos);
            //if(in_z_nest)
              //  SDL_BlitSurface(z_nest_fn,NULL,gsurface,&z_nest_pos);
            //else
              //  SDL_BlitSurface(z_nest_in,NULL,gsurface,&z_nest_pos);
            //if(in_fs)
              //  SDL_BlitSurface(fs_fn,NULL,gsurface,&in_fs_pos);
            //else
               // SDL_BlitSurface(fs_in,NULL,gsurface,&in_fs_pos);
            if(in_back)
                SDL_BlitSurface(back_fn,NULL,gsurface,&back_pos);
            else
                SDL_BlitSurface(back_in,NULL,gsurface,&back_pos);
           // if(in_res)
               // SDL_BlitSurface(reset_fn,NULL,gsurface,&res_pos);
            //else
               // SDL_BlitSurface(reset_in,NULL,gsurface,&res_pos);

            vector<human_colony>::iterator temp_it_hc;
            vector<zombie_nest>::iterator temp_it_zn;
            vector<food_source>::iterator temp_it_fs;
            //Blitting human colonies
            for (temp_it_hc = Input.human_colonies.begin(); temp_it_hc!= Input.human_colonies.end(); temp_it_hc ++)
            {
                hcpos.x=FIELD_X + temp_it_hc->pos.x;
                hcpos.y=FIELD_Y + temp_it_hc->pos.y;
                SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
            }

            //Blitting Zombie nests
            for (temp_it_zn = Input.zombie_nests.begin(); temp_it_zn!= Input.zombie_nests.end(); temp_it_zn ++)
            {
                znpos.x=FIELD_X + temp_it_zn->pos.x;
                znpos.y=FIELD_Y + temp_it_zn->pos.y;
                SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
			}

			//Blitting Food sources
			for (temp_it_fs = Input.food_sources.begin(); temp_it_fs!= Input.food_sources.end(); temp_it_fs ++)
			{
                fspos.x=FIELD_X + temp_it_fs->x;
                fspos.y=FIELD_Y + temp_it_fs->y;
                SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
			}

			//Blitting humans
			for (tempith = H.begin(); tempith!= H.end(); tempith ++)
			{
				/*
				SDL_Rect temp_pos;
				temp_pos.x = FIELD_X + tempith->last_pos.x;
				temp_pos.y = FIELD_Y + tempith->last_pos.y;

                if((tempith->pos.x-tempith->last_pos.x)>0) //moved right
				SDL_BlitSurface (human_right_image, NULL, gsurface, &temp_pos);

				else if((tempith->pos.x-tempith->last_pos.x)<0) //moved left
				SDL_BlitSurface (human_left_image, NULL, gsurface, &temp_pos);

				else if((tempith->pos.y-tempith->last_pos.y)>0) //moved down
				SDL_BlitSurface (human_down_image, NULL, gsurface, &temp_pos);

				else if((tempith->pos.y-tempith->last_pos.y)<0) //moved up
				SDL_BlitSurface (human_up_image, NULL, gsurface, &temp_pos);

				else cout<<"Human blitting not working well"<<endl;
				*/
				SDL_Rect temp_pos;
				
				temp_pos.x = FIELD_X + tempith->pos.x;
				temp_pos.y = FIELD_Y + tempith->pos.y;
				
				SDL_BlitSurface (bluedot, NULL, gsurface, &temp_pos);
				
				
			}



			//Blitting zombies
			for (tempitz = Z.begin(); tempitz!= Z.end(); tempitz ++)
			{
				SDL_Rect temp_pos;
				temp_pos.x = FIELD_X + tempitz->last_pos.x;
				temp_pos.y = FIELD_Y + tempitz->last_pos.y;

                if((tempitz->pos.x-tempitz->last_pos.x)>0) //moved right
                SDL_BlitSurface (zombie_right_image, NULL, gsurface, &temp_pos);

                else if((tempitz->pos.x-tempitz->last_pos.x)<0) //moved left
                SDL_BlitSurface (zombie_left_image, NULL, gsurface, &temp_pos);

                else if((tempitz->pos.y-tempitz->last_pos.y)>0) //moved down
                SDL_BlitSurface (zombie_down_image, NULL, gsurface, &temp_pos);

                else if((tempitz->pos.y-tempitz->last_pos.y)<0) //moved up
                SDL_BlitSurface (zombie_up_image, NULL, gsurface, &temp_pos);

                else cout<<"Zombie blitting not working well"<<endl;



			}


			SDL_Delay(delay);


			/*
			//SDL_BlitSurface (zombie_nest_image, NULL, gsurface, &znpos);
			SDL_BlitSurface (background, NULL, gsurface, NULL);
			SDL_BlitSurface (human_colony_image, NULL, gsurface, &hcpos);
			SDL_BlitSurface (food_source_image, NULL, gsurface, &fspos);
			*/
		SDL_UpdateWindowSurface(gwindow);
	    }





	// closing the stuff
	SDL_FreeSurface(background);
	background = NULL;
	SDL_FreeSurface(human_colony_image);
	human_colony_image = NULL;
	SDL_FreeSurface(zombie_nest_image);
	zombie_nest_image = NULL;

	SDL_FreeSurface(human_left_image);
	human_left_image = NULL;
	SDL_FreeSurface(human_right_image);
	human_right_image = NULL;
	SDL_FreeSurface(human_up_image);
	human_up_image = NULL;
	SDL_FreeSurface(human_down_image);
	human_down_image = NULL;

	SDL_FreeSurface(zombie_left_image);
	zombie_left_image = NULL;
	SDL_FreeSurface(zombie_up_image);
	zombie_up_image = NULL;
	SDL_FreeSurface(zombie_down_image);
	zombie_down_image = NULL;
	SDL_FreeSurface(zombie_right_image);
	zombie_right_image = NULL;

	SDL_FreeSurface(food_source_image);
	food_source_image = NULL;
	SDL_FreeSurface(begin_sim_in);
	begin_sim_in=NULL;
	SDL_FreeSurface(begin_sim_fn);
	begin_sim_fn=NULL;
	SDL_FreeSurface(pause_in);
	pause_in=NULL;
	SDL_FreeSurface(pause_fn);
	pause_fn=NULL;
    SDL_FreeSurface(delay_fn);
	delay_fn=NULL;
	SDL_FreeSurface(delay_in);
	delay_in=NULL;
    SDL_FreeSurface(reset_fn);
	reset_fn=NULL;
	SDL_FreeSurface(reset_in);
	reset_in=NULL;
    SDL_FreeSurface(back_fn);
	back_fn=NULL;
	SDL_FreeSurface(back_in);
	back_in=NULL;

	SDL_FreeSurface(gsurface);
	gsurface=NULL;

}
