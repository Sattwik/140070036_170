#include"parameters.h"

Configuration::Configuration()   
{/* take input for all members */

number_of_colonies =  1;

ev_rate = 0.999;
delay = 2000;
base_pheromone  = 0; 	
number_of_nests = 1;		
number_of_food_sources = 1;

}
food_source::food_source(): x(0),y(0) {;}
position::position(int x1, int y2 )
	{
		x = x1;
		y = y2;
	}
position::position(position &pos1)
	{
		x = pos1.x;
		y = pos1.y;
	}
position::position()
	{
		x = y = 0;
	}

human_colony::human_colony()  {;}
human_colony::human_colony(const human_colony & colony) 
{
	colony_number = colony.colony_number;
	pos = colony.pos;
	birth_rate = colony.birth_rate;
	number_of_humans = colony.number_of_humans;
	death_age = colony.death_age;
	food_amount = colony.food_amount;
	strength = colony.strength;
	food_max = colony.food_max;
	food_per_new_human = colony.food_per_new_human;
	
	
}


human::human()
{
	;
}

human::human(const human &h)
{
	pos = h.pos;
	last_pos = h.last_pos;
	age = h.age;
	food = h.food;
	colony = h.colony;
	bored = h.bored;
	dead = h.dead;
	infected = h.infected;
	dx = h.dx;
	dy = h.dy;
	foodPher = h.foodPher;
	homePher = h.homePher;
	x = h.x;
	y = h.y;
	WANDER_CHANCE = h.WANDER_CHANCE;
	USE_RATE = h.USE_RATE;
	
}
human::human(vector<human_colony>::iterator colony1)
{
    human_colony &temp = *colony1; // chnaged to a reference otherwise would give a dangling pointer:Sattwik 11.04.15 11.49 pm
	colony = &temp; 
    dead=false;infected=false; bored = 0;
    food=0;age=0;
    pos.x=colony1->pos.x; pos.y=colony1->pos.y; 
	x = pos.x; y = pos.y;
    last_pos.x=pos.x;
	last_pos.y= pos.y;
	dx = random(-1,1);dy = random(-1,1);
	foodPher = 100;
	homePher = 100;
	WANDER_CHANCE = 0.92;
	USE_RATE = 0.95;
	
}



zombie::zombie()
{
	;
}
zombie::zombie( const zombie &z)
{
	pos = z.pos;
	last_pos = z.last_pos;
	//chase_pos = z.chase_pos;
	nest = z.nest;

}
zombie_nest::zombie_nest (const zombie_nest & nest)
{
	pos = nest.pos;
	strength = nest.strength;
	infection_rate = nest.infection_rate;
	number_of_zombies = nest.number_of_zombies;
	chase_radius = nest.chase_radius;
}
zombie_nest::zombie_nest()
{
	pos.x = pos.y = 0;
}


node::node() 
{
	;
}


human::human(human_colony * colony1)
{
    colony=colony1;
    dead=false;infected=false;
    food=0;age=0;
    pos.x=colony1->pos.x; pos.y=colony1->pos.y;
    last_pos.x=pos.x;
	last_pos.y= pos.y;
	
	
}





zombie::zombie(zombie_nest * nest1)
{
    nest=nest1;

	//chase_pos.x = chase_pos.y = -1;;

    pos=(nest1->pos);
    last_pos=(pos);
}

zombie::zombie(zombie &z1)
{
    pos=z1.pos;
    last_pos=z1.last_pos;
	//chase_pos=z1.chase_pos;
	nest=z1.nest;

}
