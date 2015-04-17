#include<iostream>
#include<vector>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<random>
using namespace std;

//general parameters
extern long long int sim_time;
extern const int X;

class human;
class human_colony;
class zombie;
class zombie_nest;

/************************************************************************/

struct food_source{

	int x;
    int y;
	int food_source_area; // NBB -> this has to be a perfect square of the form (2n+1)^2!!
	int food_per_source_node; // NBB -> this has to be a positive integer
	
	food_source();
	
	
};
/************************************************************************/
//position co-ordinates
struct position{
    int x;
    int y;
    
	bool operator==(position p)
		{
			if ( x == p.x && y == p.y ) return true;
			
			else return false;
		}
	bool operator!=(position p)
	{
		if (*this == p) return false;
		else return true;
	}
	position(int x1, int y2 );
	position(position &pos1);
	position();


};

/************************************************************************/
class human_colony{
	public:
    position pos;
	int colony_number;
	
	int birth_rate,number_of_humans,death_age;
	float food_amount,strength,food_max,food_per_new_human;
	

	human_colony();
	human_colony(const human_colony & colony);
	
};
void spawn_new_humans();
/************************************************************************/
class human{
	public:
    position pos,last_pos;
	
	int dx, dy;
	int age; int bored;
	float food;
	float x,y;
	float foodPher, homePher;
	//vector<human_colony>::iterator colony;
	
	human_colony * colony;
	bool dead,infected;
	//human(vector<human_colony>::iterator colony1);
	
	float WANDER_CHANCE, USE_RATE;
	
	bool operator==(human &h)
	{
		if (h.pos == pos && h.dx == dx && h.dy == dy   && h.colony == colony 
			&& h.food == food  && h.dead == dead && h.infected == infected &&  h.bored==bored)
			return true;
		else return false;
		
	}
	
	// member functions
	
	
	void aging();
	void die();
	void carry_food();
	void deposit_food();
	void move();
	void infect(zombie infecting_zombie);	
	vector<int> getStrongestreg(int _x, int _y) ;
	vector<int> getStrongestfood(int _x, int _y) ;
	human(human_colony *  colony1);
	human();
	human(const human &h);
	human(vector<human_colony>::iterator colony1);
};

/************************************************************************/
class zombie{
	public:
	position pos,last_pos;
	//position chase_pos;
	//vector<zombie_nest>::iterator nest;
	zombie_nest * nest;


	//zombie(	vector<zombie_nest>::iterator nest1);
	
	
	// member functions
	
	void die();
	//void scan();
	void move();
	//void chase();
	void encounter_human(human h);
	void check_human();
    
	// operators
	
	bool operator==(zombie z)
	{
		if (z.pos == pos && z.last_pos == last_pos &&  z.nest == nest)
			return true;
		else return false;
		
	}
	zombie(	zombie_nest * nest1);
	zombie(zombie &z1);
	zombie();
	zombie( const zombie &z);


};




/************************************************************************/



class zombie_nest{
	public:
	position pos;
	float strength,infection_rate;
	int number_of_zombies,chase_radius;
	zombie_nest (const zombie_nest & nest);
	zombie_nest();
	
};


/************************************************************************/

class Configuration // made this to facilitate and encapsulate input methods and data members
{

    public : // because even though they are constant, they have to be acessible to other non-member / non-friend functions

	int number_of_colonies,  number_of_nests, number_of_food_sources;

	double base_pheromone, delay, ev_rate;

	vector<food_source> food_sources;

	vector<human_colony> human_colonies;

	vector<zombie_nest> zombie_nests;
    Configuration();

	


} ;
extern Configuration Input;
/************************************************************************/
//grid definition parameters


class node{
	public:
	position pos;
	
	float reg_pheromone[10], food_pheromone[10],food; // have to figure out how to use a var length as a const length here
	
	

	vector<human> humans_at_posn;
	vector<zombie> zombies_at_posn;
    node();
};
extern node grid[490][490];


/***********************************************************************/
extern vector<human>::iterator it_human;
extern vector<human_colony>::iterator it_human_colony;

extern vector<zombie>::iterator it_zombie;
extern vector<zombie_nest>::iterator it_zombie_nest;

extern vector<human> H;
extern vector<zombie> Z;
/***********************************************************************/


void update_pheromone();
void change_state();
void spawn_new_humans();



void moving(human &h, node &n);



int distance(position a, position b);

int decide(float a, float b);

void moving(zombie &z, node &n);

float max(float a,float b);
float min(float a, float b);

void init_zombie_list();
void init_human_list();
void init_grid();
void init_grid2();
int decide(float a, float b, float c, float d);
float random(double n);
float random(double n1, double n2);
float random(double n1, double n2);
int random (int n1, int n2);
float min(float a, float b);
float max(float a, float b);

//Graphics Declarations

extern SDL_Window *gwindow;
void help_window(bool &qq);
void start_window();
void human_colony_input(human_colony &hc);
void food_source_input(food_source &fs);
void zombie_nest_input(zombie_nest &zn);

extern bool quit;



