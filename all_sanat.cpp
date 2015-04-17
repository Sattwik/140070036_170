#include"parameters.h"



//Preconditions: vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined

/* PreC: base_pheromone,number_of_colonies, number_of_nests, number_of_food_sources, food_sources already available initialised

NEEDS : <vector> , <math.h>
*/


void init_grid()
{


	// IMP ::have to make a default constructor for node to implement node grid[X][X];


    vector<food_source>::const_iterator it = Input.food_sources.begin();	// traversing food_locations


	for ( int i = 0 ;i < X ; i ++ )
	{
		for (int j = 0; j < X; j++)
		{
			// setting positions
			grid[i][j].pos.x = i;
			grid[i][j].pos.y = j;

            // initialising base pheromone
			for (int k =0; k< Input.number_of_colonies; k++)
			{
				grid[i][j].reg_pheromone[k] = Input.base_pheromone;
				grid[i][j].food_pheromone[k] = Input.base_pheromone;
			}

			// initialising
			// CHANGES !! => sort food_source<>
			if (it != Input.food_sources.end() && it->x == i && it->y == j )
			{
                int fs_size = int(sqrt (it->food_source_area)) / 2;

				for (int l = i - fs_size; l <= i + fs_size ; l++)
				{
					for (int m = j - fs_size; m <= j + fs_size ; m++)
					{
						grid[l][m].food = it->food_per_source_node;
					}
				}
				it ++;
			}

		}
	} // tbv



}

/* PostC :
	->positions assigned.
    ->sets base pheromone.
    ->food amounts assigned in an area around location, amount per area grid is input

*/


/* PreC :
human_colonies (preferably sorted according to position, traversing rows at a time),
number_of_colonies are available
*/

/* Function:
Initialises vector H with various default values
Should be present in begin_simulation ( name change ??) before change_state
*/

/* Includes : <vector>, "parameters.h" */


void init_human_list()
{
	vector<human_colony>::iterator it_human_colonies; // it_human_colonies is an iterator
	// for vector human_colonies in Configure


	for (it_human_colonies = Input.human_colonies.begin(); it_human_colonies != Input.human_colonies.end(); it_human_colonies++)
	{
		for (int i = 0; i <  it_human_colonies->number_of_humans; i++)
		{
			human newh; // NB -> need a default constructor here for human class:D
			newh.pos = it_human_colonies->pos;
			newh.last_pos = it_human_colonies->pos;
			newh.age = 0;
			newh.food = 0.0;


			human_colony &temp(*it_human_colonies);
			newh.colony = &temp;

			newh.dead = false;
			newh.infected = false;
			newh.carrying_food = false;

            grid[newh.pos.x][newh.pos.y].humans_at_posn.push_back(newh);
			H.push_back(newh);

		}
	}




}

/* PostC :
H initialised as follows:
Humans are "grouped" together initially according to colonies
For every human in H,
-> pos = last_pos = posn of respective colony
-> grid points that are colony locations have been seeded with humans_at_posn

// changes to the above????
*/

/* PreC :
zombie_nests (preferably sorted according to position, traversing rows at a time),
number_of_nests are available
*/

/* Function:
Initialises vector Z with various default values
*/

/* Includes : <vector>, "parameters.h" */




void init_zombie_list()
{
	vector<zombie_nest>::iterator it_zombie_nests; // it_zombie_nests is an iterator
	// for vector zombie_nests in Configure


	for (it_zombie_nests = Input.zombie_nests.begin(); it_zombie_nests != Input.zombie_nests.end(); it_zombie_nests++)
	{

		for (int i = 0; i <  it_zombie_nests->number_of_zombies; i++)
		{

			zombie newz; // NB -> need a default constructor here for zombie class:D
			newz.pos = it_zombie_nests->pos; // need a copy ctor here for position
			newz.last_pos = it_zombie_nests->pos;
			position temper(-1,-1);
			newz.chase_pos = temper;


			zombie_nest &temper2= *it_zombie_nests;
			//cout << temper2.pos.x << endl;
			//cout<<endl<<endl<<endl;


			newz.nest = &temper2;
			newz.chasing = false;
			grid[newz.pos.x][newz.pos.y].zombies_at_posn.push_back(newz);
			Z.push_back(newz);
		}
	}

}

/* PostC :
Z initialised as follows:
Zombies are "grouped" together initially according to nests
For every zombie in Z,
-> pos = last_pos = posn of respective nest
-> chase_pos = (-1,-1) ; NB -> by convention, this means zombie is NOT in chase mode
-> chasing = false
-> grid points that are nest locations have been seeded with zombies_at_posn

// cahnges to the above????
*/

/**********************************************************************************************************************/



int decide(float a, float b, float c, float d)
{


	/*
	a = max(a,0.0001);
	b = max(b,0.0001);
	c = max(c,0.0001);
	d = max(d,0.0001);
	*/
	///

    float new_ph = (rand()%10000)/10000.0; // this works -> sattwik 11.04.15 , 11:44 pm

    if(new_ph<(a/(a+b+c+d)))
        return 0;  //Left
    if(new_ph>=(a/(a+b+c+d)) && new_ph<((a+b)/(a+b+c+d)))
        return 1;  //Up
     if(new_ph>=((a+b)/(a+b+c+d)) && new_ph<((a+b+c)/(a+b+c+d)))
        return 2;  //Right
     if(new_ph>=((a+b+c)/(a+b+c+d)))
        return 3;  //Down
}
void moving(zombie &z, node n)
{

    vector<zombie>::iterator it_moving=grid[z.pos.x][z.pos.y].zombies_at_posn.begin();

    for(; it_moving!=grid[z.pos.x][z.pos.y].zombies_at_posn.end();it_moving++)  //Condition for end of vector zombies_at_posn   // Changed !!!
    {

        if(z==*it_moving)
        {
            vector<zombie>::iterator temp = grid[z.pos.x][z.pos.y].zombies_at_posn.erase(it_moving);
            break;
        }
        //it_moving++;
    }

    n.zombies_at_posn.push_back(z);
    z.pos.x=n.pos.x; z.pos.y=n.pos.y;



}
void zombie::chase()
{
    if(chasing)
    {
        int decision;
        if(fabs(pos.x-chase_pos.x)>fabs(pos.y-chase_pos.y))
        {
            if(pos.x-chase_pos.x>0)
                decision=0; // pos.x--
            else decision=2; // pos.x++
        }
        else
        {
            if(pos.y-chase_pos.y>0)
                decision=1; // pos.y--
            else decision=3; // pos.y++
        }

        switch(decision)
        {
            case 0:moving(*this,grid[pos.x-1][pos.y]); break;
            case 1:moving(*this,grid[pos.x][pos.y-1]); break;
            case 2:moving(*this,grid[pos.x+1][pos.y]); break;
            case 3:moving(*this,grid[pos.x][pos.y+1]); break;
        }
    }

    check_human();

    if(chasing)
    {
        int decision;
        if(fabs(pos.x-chase_pos.x)>fabs(pos.y-chase_pos.y))
        {
            if(pos.x-chase_pos.x>0)
                decision=0; // pos.x--
            else decision=2; // pos.x++
        }
        else
        {
            if(pos.y-chase_pos.y>0)
                decision=1; // pos.y--
            else decision=3; // pos.y++
        }

        switch(decision)
        {
            case 0:moving(*this,grid[pos.x-1][pos.y]); break;
            case 1:moving(*this,grid[pos.x][pos.y-1]); break;
            case 2:moving(*this,grid[pos.x+1][pos.y]); break;
            case 3:moving(*this,grid[pos.x][pos.y+1]); break;
        }
    }
}

// Postconditions: Zombie moves two positions if it does not encounter human in first one


//Preconditions: vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined


void zombie::check_human()
{
    bool human_is_not_there=false;
    human_is_not_there=grid[pos.x][pos.y].humans_at_posn.empty();

    if(!human_is_not_there)
    {
        vector<human>::iterator it_moving=grid[pos.x][pos.y].humans_at_posn.begin();
        (this)->encounter_human(*it_moving);
    }
}

//Postcondition: Calls encounter human if human is there

//Preconditions: vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined



void zombie::die()
{
    nest->number_of_zombies--;
    vector<zombie>::iterator it_moving=grid[pos.x][pos.y].zombies_at_posn.begin();

	// from posn
	for(;it_moving != grid[pos.x][pos.y].zombies_at_posn.end(); it_moving++ )
    {
        if(*this == *it_moving)
        {
            vector<zombie>::iterator temp = grid[pos.x][pos.y].zombies_at_posn.erase(it_moving);
            break;
        }

    }

	// from main list
	vector<zombie>::iterator it_zombie1=it_zombie;
    it_zombie=Z.erase(it_zombie1);

	/*
	if (it_zombie!=Z.begin())
	{
	    it_zombie--;
    }
	*/

}

//Postcondition: Kills the zombie and increments it_zombie and removes the zombie from the node


int decide(float a, float b)
{
    //srand (time(NULL));
    float new_ph = (rand()%10000)/10000.0;
    if(new_ph<(a/(a+b)))
        return 0;  //a wins
    else return 1; //b wins
}

void zombie::encounter_human(human h)
{
    cout << "Encountered !" << endl;
    chasing=false;

    if(decide(nest->strength, h.colony->strength)==1)
    {
        if(decide(nest->infection_rate, h.colony->strength)==1)
        {
            die();
        }
        else
        {
            h.infect(*this);
            die();
        }
    }
    else
    {
        if(decide(nest->strength, nest->infection_rate)==1)
        {
            h.infect(*this);
        }
        else
        {
            h.die();
        }
    }
}

// Postcondition: it_zombie may be increased


void zombie::move()
{
	 position temp_last_pos=last_pos;
	 last_pos =  pos;

     if(chasing)
     {
        chase();

     }
     else
     {

         int new_pos_x[4],new_pos_y[4];
         if(pos.x!=0)
             {
                 new_pos_x[0]=pos.x-1;
                 new_pos_y[0]=pos.y;
             }
         else
             {
                 new_pos_x[0]=-1;
                 new_pos_y[0]=-1;
             }

         if(pos.x!=X-1)
             {
                 new_pos_x[2]=pos.x+1;
                 new_pos_y[2]=pos.y;
             }
         else
             {
                 new_pos_x[2]=-1;
                 new_pos_y[2]=-1;
             }
         if(pos.y!=0)
             {
                 new_pos_x[3]=pos.x;
                 new_pos_y[3]=pos.y-1;
             }
         else
             {
                 new_pos_x[3]=-1;
                 new_pos_y[3]=-1;
             }

         if(pos.y!=X-1)
             {
                 new_pos_x[1]=pos.x;
                 new_pos_y[1]=pos.y+1;
             }
         else
             {
                 new_pos_x[1]=-1;
                 new_pos_y[1]=-1;
             }

		int mark=-1;

		for(int i=0;i<4;i++)
		{
			if(new_pos_x[i]==temp_last_pos.x && new_pos_y[i]==temp_last_pos.y)
			//if(new_pos_x[i]== 2*pos.x - temp_last_pos.x && new_pos_y[i]== 2*pos.y -temp_last_pos.y)
			{

				new_pos_x[i]=-1; new_pos_y[i]=-1; //mark=i;

			}
			if(new_pos_x[i]== 2*pos.x - temp_last_pos.x && new_pos_y[i]== 2*pos.y -temp_last_pos.y)
			{
				mark=i;
			}
		}


		float a0 = 	(new_pos_x[0]!=-1 && new_pos_y[0]!=-1)?1.0:0; // might affect logic

		float a1 =  (new_pos_x[1]!=-1 && new_pos_y[1]!=-1)?1.0:0;

		float a2 =  (new_pos_x[2]!=-1 && new_pos_y[2]!=-1)?1.0:0;

		float a3 =  (new_pos_x[3]!=-1 && new_pos_y[3]!=-1)?1.0:0;



		switch(mark)
		{
			case 0:a0=10.0; break;
			case 1:a1=10.0; break;
			case 2:a2=10.0; break;
			case 3:a3=10.0; break;
			default: ;
		}


		int decision = decide( a0,a1,a2,a3);



        switch(decision)
        {
            case 0: moving(*this,grid[pos.x-1][pos.y]); break;
            case 1: moving(*this,grid[pos.x][pos.y+1]); break;
            case 2: moving(*this,grid[pos.x+1][pos.y]); break;
            case 3: moving(*this,grid[pos.x][pos.y-1]); break;
        }


     }




}
// Postconditions: zombie removed from present node and addded to next node.

//Preconditions: vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined

int distance(position a, position b)
{
    return fabs(a.x-b.x)+fabs(a.y-b.y);
}
void zombie::scan()
{
    bool human_is_there=false;
    position temp_chase_pos(int(max(pos.x - nest->chase_radius,0)),int(max(pos.y-nest->chase_radius,0))); // typecasted arguments to prevent argument clash : Sattwik 11.04.15 11.55 pm

    while(temp_chase_pos.y < X && temp_chase_pos.y<=pos.y +nest->chase_radius)
    {
        while(temp_chase_pos.x < X && temp_chase_pos.x<=pos.x + nest->	chase_radius)
        {
            bool human_is_not_there=false;
            human_is_not_there=grid[temp_chase_pos.x][temp_chase_pos.y].humans_at_posn.empty();
            if(!human_is_not_there)
            {
                human_is_there=true;  //To be or not to be?? LOL :D
                chase_pos=(::distance(pos,chase_pos)>::distance(pos,temp_chase_pos))?temp_chase_pos:chase_pos;
            }
            temp_chase_pos.x++;
        }
        temp_chase_pos.y++;
    }
    if (human_is_there)
    {
        chasing = true;
    }
}

/**********************************************************************************************************************/



void human::aging()
{
    age++;
    if(age>=colony->death_age)
	{


	    die();

		/*
		if (it_human != H.begin())
				{
					it_human--;
				}
		*/
	}


}

//Postcondition: Increases the age of the human and kills it if it is too old


void human::carry_food()
{

	 if(grid[pos.x][pos.y].food >= colony->food_max)
	     {
            food = colony->food_max;
            grid[pos.x][pos.y].food = grid[pos.x][pos.y].food - food;
         }
	 else
	     {
	         food = food + grid[pos.x][pos.y].food;
             grid[pos.x][pos.y].food=0;
	     }
     carrying_food=true;
}

//Postcondition: If human is at a food source, it picks up food


void human::deposit_food()
{

    if((pos.x <= colony->pos.x + Input.extent) && (pos.x >= colony->pos.x - Input.extent) && (pos.y <= colony->pos.y + Input.extent) && (pos.y >= colony->pos.x - Input.extent))
    {
        colony->food_amount = colony->food_amount + food;
        food=0;
    }
    carrying_food=false;
}

//Postcondition: If the human is at a colony, it deposits all its food


//Precondition: Execute after carry_food()

void human::die()
{
    colony->number_of_humans--;
    vector<human>::iterator it_moving=grid[pos.x][pos.y].humans_at_posn.begin();

	// erasing from posn
	for (; it_moving != grid[pos.x][pos.y].humans_at_posn.end(); it_moving++)  //Condition for end of vector humans_at_posn
    {
        if(*this == *it_moving)
        {

            vector<human>::iterator temp = grid[pos.x][pos.y].humans_at_posn.erase(it_moving);

            break;
        }

    }


    vector<human>::iterator it;

	//erasing from H
	for(it = H.begin(); it != H.end(); it++)
	{
		if (*it == *this)
		{

			it_human = H.erase(it);
			break; // Sattwik : inserted this -> somehow (maybe) got rid of strange segfault  -> 11.04.15 , 11:33 pm
		}

	}


}

//Postcondition: Kills the human and and increments it_human


void human::infect(zombie infecting_zombie)
{
    zombie new_z(infecting_zombie);
    Z.push_back(new_z);
    die();
}

//Postcondition: The human is deleted and a zombie with parameters same as original zombie takes its place




void moving(human &h, node n)
{
    vector<human>::iterator it_moving=grid[h.pos.x][h.pos.y].humans_at_posn.begin();
    for(; it_moving != grid[h.pos.x][h.pos.y].humans_at_posn.end();it_moving++)  //Condition for end of vector humans_at_posn
    {
        if(h==*it_moving)
        {
            vector<human>::iterator temp = grid[h.pos.x][h.pos.y].humans_at_posn.erase(it_moving);
            break;
        }
        //it_moving++;
    }
    n.humans_at_posn.push_back(h);
    h.pos.x=n.pos.x; h.pos.y=n.pos.y;
}
void human::move()                 // Change move to something else (Reserved word)
{

    position temp_last_move(last_pos);
    last_pos.x=pos.x; last_pos.y=pos.y;



    int new_pos_x[4],new_pos_y[4];
    if(pos.x!=0)
        {
            new_pos_x[0]=pos.x-1;
            new_pos_y[0]=pos.y;
        }
    else
        {
            new_pos_x[0]=-1;
            new_pos_y[0]=-1;
        }

    if(pos.x!=X-1)
        {
            new_pos_x[2]=pos.x+1;
            new_pos_y[2]=pos.y;
        }
    else
        {
            new_pos_x[2]=-1;
            new_pos_y[2]=-1;
        }
    if(pos.y!=0)
        {
            new_pos_x[3]=pos.x;
            new_pos_y[3]=pos.y-1;
        }
    else
        {
            new_pos_x[3]=-1;
            new_pos_y[3]=-1;
        }

    if(pos.y!=X-1)
        {
            new_pos_x[1]=pos.x;
            new_pos_y[1]=pos.y+1;
        }
    else
        {
            new_pos_x[1]=-1;
            new_pos_y[1]=-1;
        }


		int mark=-1;
    if( pos!=colony->pos &&  grid[pos.x][pos.y].food == 0 && food < colony->food_max  )
    {

		for(int i=0;i<4;i++)
        {
            if(new_pos_x[i]==temp_last_move.x && new_pos_y[i]==temp_last_move.y)
            {
				new_pos_x[i]=-1;
                new_pos_y[i]=-1;
            }
			if(new_pos_x[i]==2*pos.x-temp_last_move.x && new_pos_y[i]==2*pos.y-temp_last_move.y)
			{
				mark=i;
			}
        }
    }


	if (food == 0)
	{
		float a1 = (new_pos_x[0]!=-1 && new_pos_y[0]!=-1)?max((grid[new_pos_x[0]][new_pos_y[0]].food_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;


		float a2 = (new_pos_x[1]!=-1 && new_pos_y[1]!=-1)?max((grid[new_pos_x[1]][new_pos_y[1]].food_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;

		float a3 = (new_pos_x[2]!=-1 && new_pos_y[2]!=-1)?max((grid[new_pos_x[2]][new_pos_y[2]].food_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;

		float a4 = (new_pos_x[3]!=-1 && new_pos_y[3]!=-1)?max((grid[new_pos_x[3]][new_pos_y[3]].food_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;


	    switch(mark)
		{
			case 0:a1=a1*5;break;
			case 1:a2=a2*5;break;
			case 2:a3=a3*5;break;
			case 3:a4=a4*5;break;
			default: break;
		}
		int decision = decide( a1 ,a2 ,a3 ,a4);



	    switch(decision)
	    {
	    case 0:moving(*this,grid[pos.x-1][pos.y]); break;
	    case 1:moving(*this,grid[pos.x][pos.y+1]); break;
	    case 2:moving(*this,grid[pos.x+1][pos.y]); break;
	    case 3:moving(*this,grid[pos.x][pos.y-1]); break;
	    }
    	grid[pos.x][pos.y].reg_pheromone[colony->colony_number]=grid[pos.x][pos.y].reg_pheromone[colony->colony_number]+colony->reg_pheromone_inc;
	}




	if (food != 0 )
	{
		float a1 = (new_pos_x[0]!=-1 && new_pos_y[0]!=-1)?max((grid[new_pos_x[0]][new_pos_y[0]].reg_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;


		float a2 = (new_pos_x[1]!=-1 && new_pos_y[1]!=-1)?max((grid[new_pos_x[1]][new_pos_y[1]].reg_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;

		float a3 = (new_pos_x[2]!=-1 && new_pos_y[2]!=-1)?max((grid[new_pos_x[2]][new_pos_y[2]].reg_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;

		float a4 = (new_pos_x[3]!=-1 && new_pos_y[3]!=-1)?max((grid[new_pos_x[3]][new_pos_y[3]].reg_pheromone[it_human->colony->colony_number]-Input.reference_pheromone),Input.base_pheromone):0;


	    int decision = decide( a1 ,a2 ,a3 ,a4);

	    switch(mark)
		{
			case 0:a1=a1*5;break;
			case 1:a2=a2*5;break;
			case 2:a3=a3*5;break;
			case 3:a4=a4*5;break;
			default: break;
		}

	    switch(decision)
	    {
	    case 0:moving(*this,grid[pos.x-1][pos.y]); break;
	    case 1:moving(*this,grid[pos.x][pos.y+1]); break;
	    case 2:moving(*this,grid[pos.x+1][pos.y]); break;
	    case 3:moving(*this,grid[pos.x][pos.y-1]); break;
	    }
    	grid[pos.x][pos.y].food_pheromone[colony->colony_number]=grid[pos.x][pos.y].food_pheromone[colony->colony_number]+colony->food_pheromone_inc;

	}


}

//Postcondition: The human will move to a position decided as per pheromone levels (value of humans_at_posn at current node and next node is modified)
//               Human does not turn back unless it is at the colony or its food equals its maximum capacity to carry food


//Precondition : not much
void spawn_new_humans()  //spawns new humans if enough food is available
{

    it_human_colony = Input.human_colonies.begin();

    for(;it_human_colony!=Input.human_colonies.end();it_human_colony++)
	{
        if(it_human_colony->food_amount > it_human_colony->birth_rate * it_human_colony->food_per_new_human)
		{
            for(int i=1; i<=it_human_colony->birth_rate; i++)
            {
                human new_human(it_human_colony);
                H.push_back(new_human);
            }
            it_human_colony->number_of_humans += it_human_colony->birth_rate;
            it_human_colony->food_amount -= (it_human_colony->birth_rate * it_human_colony->food_per_new_human);
        }
        else
		{
            while(it_human_colony->food_amount > 0)
			{
                human new_human(it_human_colony);
                H.push_back(new_human);

                it_human_colony->number_of_humans++;
                it_human_colony->food_amount -= it_human_colony->food_per_new_human;
            }
        }
    }

	return;
}
//Postcondition: New humans pushed back according to certain conditions
// Sattwik  11/05/ 14 : should work


//General Precondition: All functions running under change_state loop. A member of H is being called in one iteration
/**********************************************************************************************************************/

void change_state()
{



    spawn_new_humans();


        for (it_zombie = Z.begin(); it_zombie!=Z.end(); )
		{


			vector<zombie>::iterator tempitz = it_zombie;
                it_zombie->scan();

                it_zombie->move();


                it_zombie->check_human();

				if ( it_zombie == tempitz && it_zombie!= Z.end())
					it_zombie++;
				// if first guy dies, second guy gets skipped!!!

		}


        for (it_human = H.begin(); it_human!=H.end(); )
		{
			vector<human>::iterator tempith = it_human;
			if ( grid[it_human->pos.x][it_human->pos.y].food > 0 ) it_human->carry_food();
   			if ( (it_human->pos.x <= it_human->colony->pos.x + Input.extent) && (it_human->pos.x >= it_human->colony->pos.x - Input.extent) && (it_human->pos.y <= it_human->colony->pos.y + Input.extent) && (it_human->pos.y >= it_human->colony->pos.x - Input.extent)  )
			{
				if ( it_human-> food!=0)
				it_human->deposit_food();
			}

	   		it_human->move();

			it_human->aging();

			if(it_human == tempith && it_human != H.end()) // if you don't check for H.end() , gives segfault
				it_human++;

		}
		update_pheromone();
		sim_time++;


}

/**********************************************************************************************************************/
void update_pheromone()
{


	Input.reference_pheromone += Input.ev_rate;


}

/**********************************************************************************************************************/


