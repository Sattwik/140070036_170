#include"parameters.h"
/*

position::position(int x1,int y2)
{
    x=x1; y=y2;
}
*/
Configuration::Configuration()
{/* take input for all members */

number_of_colonies =  0;
reference_pheromone = 0;
ev_rate = 0;
delay = 2000;
base_pheromone  = 0.002;
number_of_nests = 0;
number_of_food_sources = 0;
extent = 20;
}
food_source::food_source(){
    x=0;
    y=0;
    food_per_source_node=0;
    food_source_area=0;
}
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

human_colony::human_colony() {
    colony_number=0;
    birth_rate=0;
    number_of_humans=0;
    death_age=0;
    food_amount=0;
    strength=0;
    food_max=0;
    food_per_new_human=0;
    reg_pheromone_inc=0;
    food_pheromone_inc=0;
}
human_colony::human_colony(const human_colony & colony) : colony_number(0)
{
	pos = colony.pos;
	birth_rate = colony.birth_rate;
	number_of_humans = colony.number_of_humans;
	death_age = colony.death_age;
	food_amount = colony.food_amount;
	strength = colony.strength;
	food_max = colony.food_max;
	food_per_new_human = colony.food_per_new_human;
	reg_pheromone_inc = colony.reg_pheromone_inc;
	food_pheromone_inc = colony.food_pheromone_inc;

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

	dead = h.dead;
	infected = h.infected;
	carrying_food = h.carrying_food;

}
human::human(vector<human_colony>::iterator colony1)
{
    human_colony &temp = *colony1; // chnaged to a reference otherwise would give a dangling pointer:Sattwik 11.04.15 11.49 pm
	colony = &temp;
    dead=false;infected=false;carrying_food=false;
    food=0;age=0;
    pos.x=colony1->pos.x; pos.y=colony1->pos.y;
    last_pos.x=pos.x;
	last_pos.y= pos.y;
}



zombie::zombie()
{
	;
}
zombie::zombie( const zombie &z)
{
	pos = z.pos;
	last_pos = z.last_pos;
	chase_pos = z.chase_pos;
	nest = z.nest;
	chasing = z.chasing;
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
	strength=0;
	infection_rate=0;
	number_of_zombies=0;
	chase_radius=0;
}


node::node()
{
	;
}


human::human(human_colony * colony1)
{
    colony=colony1;
    dead=false;infected=false;carrying_food=false;
    food=0;age=0;
    pos.x=colony1->pos.x; pos.y=colony1->pos.y;
    last_pos.x=pos.x;
	last_pos.y= pos.y;
}





zombie::zombie(zombie_nest * nest1)
{
    nest=nest1;

	chase_pos.x = chase_pos.y = -1;;
    chasing=false;
    pos=(nest1->pos);
    last_pos=(pos);
}

zombie::zombie(zombie &z1)
{
    pos=z1.pos;
    last_pos=z1.last_pos;
	chase_pos=z1.chase_pos;
	nest=z1.nest;
	chasing=false;
}
