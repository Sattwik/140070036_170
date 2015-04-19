#include"parameters.h"



// This file contains most of the functions required to implement the algorithm (ACO)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//

/* PreC: base_pheromone,number_of_colonies, number_of_nests, number_of_food_sources, food_sources already available initialised
		 vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined
*/


void init_grid()
{
	

	
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
			

			//initialising food
			if (it != Input.food_sources.end() && it->x == i && it->y == j )
			{
                int fs_size = int(sqrt(it->food_source_area));

				int rightextentl = (i + fs_size  > X-1)?X-1:i + fs_size;

				int downextentm = (j + fs_size > X-1)?X-1:j + fs_size;
				
				for (int l = i ; l <= rightextentl ; l++)
				{
					for (int m = j ; m <= downextentm ; m++)
					{
						grid[l][m].food = it->food_per_source_node;
					}
				}
				it ++;
			}
					
		}
	} 
	

	
}


/* PostC : 
	->positions assigned.
    ->sets base pheromone.
    ->food amounts assigned in an area around location, amount per area grid is input

*/
/**********************************************************************************************************************************************************************************/


/*PreC: Input.food_sources is defined */

void init_grid2()
{
	

	
	
	
    vector<food_source>::const_iterator it = Input.food_sources.begin();	// traversing food_locations


	for ( int i = 0 ;i < X ; i ++ )
	{
		for (int j = 0; j < X; j++)
		{

			// initialising food

			if (it != Input.food_sources.end() && it->x == i && it->y == j )
			{
                int fs_size = int(sqrt(it->food_source_area));

				int rightextentl = (i + fs_size  > X-1)?X-1:i + fs_size;

				int downextentm = (j + fs_size > X-1)?X-1:j + fs_size;
				
				for (int l = i ; l <= rightextentl ; l++)
				{
					for (int m = j ; m <= downextentm ; m++)
					{
						grid[l][m].food = it->food_per_source_node;
					}
				}
				it ++;
			}
					
		}
	} 
	

	
}
/*PostC : Initialises grid points with food only before the beginning of simulation*/

/**********************************************************************************************************************************************************************************/
/* PreC : 
Input.human_colonies,
number_of_colonies are available
*/

/* Function: 
Initialises vector H with various default values
Should be present in main() before change_state
*/



void init_human_list()
{

	vector<human_colony>::iterator it_human_colonies; // it_human_colonies is an iterator
	// for vector human_colonies in Configure
	

	for (it_human_colonies = Input.human_colonies.begin(); it_human_colonies != Input.human_colonies.end(); it_human_colonies++)
	{
		for (int i = 0; i <  it_human_colonies->number_of_humans; i++)
		{
			human newh; 
			newh.pos = it_human_colonies->pos; 
			newh.last_pos = it_human_colonies->pos; 
			newh.age = 0;
			newh.food = 0.0;
			newh.bored = 0;
			newh.homePher = 100; newh.foodPher = 100;
			newh.x = newh.pos.x; newh.y = newh.pos.y;
			newh.dx = random(-1,1);
			newh.dy = random(-1,1);

			human_colony &temp(*it_human_colonies);
			newh.colony = &temp;
			newh.WANDER_CHANCE = 0.92; newh.USE_RATE = 0.95;
			
			newh.dead = false;
			newh.infected = false;

						
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
-> initial dx, dy = random number between -1 to 1 to ensure spread of humans
*/
/**********************************************************************************************************************************************************************************/

/* PreC : 
zombie_nests ,
number_of_nests are available
*/

/* Function: 
Initialises vector Z with various default values
*/


void init_zombie_list()
{

	vector<zombie_nest>::iterator it_zombie_nests; // it_zombie_nests is an iterator
	// for vector zombie_nests in Configure
	
	
	for (it_zombie_nests = Input.zombie_nests.begin(); it_zombie_nests != Input.zombie_nests.end(); it_zombie_nests++)
	{
		
		for (int i = 0; i <  it_zombie_nests->number_of_zombies; i++)
		{

			zombie newz; 
			newz.pos = it_zombie_nests->pos;
			newz.last_pos = it_zombie_nests->pos; 
			
			
			zombie_nest &temper2= *it_zombie_nests;
			

			newz.nest = &temper2;
			
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

-> grid points that are nest locations have been seeded with zombies_at_posn
*/

/**********************************************************************************************************************************************************************************/

/*PreC: a,b,c,d represent pher values */
int decide(float a, float b, float c, float d)
{
	
	
	
    float new_ph = random(1); 
 
    if(new_ph<(a/(a+b+c+d)))
        return 0;  //Left
    if(new_ph>=(a/(a+b+c+d)) && new_ph<((a+b)/(a+b+c+d)))
        return 1;  //Up
     if(new_ph>=((a+b)/(a+b+c+d)) && new_ph<((a+b+c)/(a+b+c+d)))
        return 2;  //Right
     if(new_ph>=((a+b+c)/(a+b+c+d)))
        return 3;  //Down
}
/*PostC : returns decision based on probability */

/**********************************************************************************************************************************************************************************/


/*PreC : z is the zombie to be moved, n is the node to which it has to be moved, both have to be valid members of Z and grid[X][X]*/
void moving(zombie &z, node &n)
{

    vector<zombie>::iterator it_moving=grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.begin();

	// deleting from last_pos
    for(; it_moving!=grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.end();it_moving++)  //Condition for end of vector zombies_at_posn   
    {

        if(z==*it_moving)
        {
            grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.erase(it_moving);
            break;
        }

    }

	//changing current pos
    n.zombies_at_posn.push_back(z);
    z.pos.x=n.pos.x; z.pos.y=n.pos.y;



}
/*PostC : zombie's position changed accordingly and zombies_at_posn at last_pos does not contain this particular zombie anymore*/

/**********************************************************************************************************************************************************************************/

/* PreC : being called when a zombie is killed by a human*/
void zombie::die()
{

    nest->number_of_zombies--;
    vector<zombie>::iterator it_moving=grid[pos.x][pos.y].zombies_at_posn.begin();
    

	// from posn
	for(;it_moving != grid[pos.x][pos.y].zombies_at_posn.end(); it_moving++ )
    {

        if(*this == *it_moving)
        {
			grid[pos.x][pos.y].zombies_at_posn.erase(it_moving);
            break;
        }

    }
    

	// from main list
	
	
	vector<zombie>::iterator it_zombie1=Z.begin();
	for (; it_zombie1 != Z.end(); it_zombie1 ++)
	{

		if(*it_zombie1 == *this)
			{	
				it_zombie = Z.erase(it_zombie1);
				break;
			}
		
		
	}


	

	
}
/*PostC : removes zombie from Z and zombies_at_posn at pos*/

/**********************************************************************************************************************************************************************************/

/*PreC : a,b represent fight parameters*/ 
int decide(float a, float b)
{
    //srand (time(NULL));
	

    float new_ph = random(1);

    if(new_ph<(a/(a+b)))
        return 0;  //a wins
    else return 1; //b wins
}
/*PostC :  returns decision based on probability*/

/**********************************************************************************************************************************************************************************/


/* PreC : assuming zombie calling is from Z*/


void zombie::move()
{
	 position temp_last_pos=last_pos;
	 last_pos =  pos;
   
	 // to prevent back movememnt
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
			
			{

				new_pos_x[i]=-1; new_pos_y[i]=-1; 
				
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
		
		//to promote forward movememnt
		
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
/*PostC : Zombie moved according to probability , see moving for details*/

/**********************************************************************************************************************************************************************************/

/*PreC :  a,b are valid*/
int distance(position a, position b)
{
    return fabs(a.x-b.x)+fabs(a.y-b.y);
} 
/*PostC: returns "distance " between two position*/



/**********************************************************************************************************************************************************************************/


// PreC: human calling is from H
void human::aging()
{
    age++;
    if(age>=colony->death_age)
	{
		
	    die();	
	}
	
	
}

//Postcondition: Increases the age of the human and kills it if it is too old


/**********************************************************************************************************************************************************************************/

/* PreC : being called from aging or zombie killing a human*/ 
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
			break; 
		}
		
	}


}

//Postcondition: Kills the human and and increments it_human

/**********************************************************************************************************************************************************************************/

/* PreC :  posx, posy are current positions*/

vector<int> human::getStrongestreg(int posx, int posy) 
{
  float compare = 0;
  float strongestVal = 0;
  vector<int> strongest;
  
  strongest.push_back(0);
  strongest.push_back(0);

 
  compare = grid[posx][posy-1].reg_pheromone[colony->colony_number]; // up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 0;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
  
  
  
  compare = grid[posx-1][posy].reg_pheromone[colony->colony_number]; // left
  if (compare > strongestVal) 
  {
	
	  strongest.at(0) = -1;
	
	  strongest.at(1) = 0;
    strongestVal = compare;
  }
  
  compare = grid[posx+1][posy].reg_pheromone[colony->colony_number]; // right
  if (compare > strongestVal) 
  {
	  
	  strongest.at(0) = 1;
	  
	  strongest.at(1) = 0;
    strongestVal = compare;
  }
  
  
  
  compare = grid[posx][posy+1].reg_pheromone[colony->colony_number]; // down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 0;
	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  compare = grid[posx+1][posy+1].reg_pheromone[colony->colony_number]; // right down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 1;

	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  compare = grid[posx+1][posy-1].reg_pheromone[colony->colony_number]; // right up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 1;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
	
  compare = grid[posx-1][posy+1].reg_pheromone[colony->colony_number]; // left down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = -1;

	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  compare = grid[posx-1][posy-1].reg_pheromone[colony->colony_number]; // left up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = -1;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
  
  return strongest;
}
/* PostC : returns vector<int> for direction in which home pheromone's strongest */

/**********************************************************************************************************************************************************************************/

/*PreC : see previous*/ 
vector<int> human::getStrongestfood(int posx, int posy) 
{
  float compare = 0;
  float strongestVal = 0;
  vector<int> strongest;
  
  strongest.push_back(0);
  strongest.push_back(0);

 
  compare = grid[posx][posy-1].food_pheromone[colony->colony_number]; // up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 0;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
  compare = grid[posx-1][posy-1].food_pheromone[colony->colony_number]; // left up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = -1;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
  
  
  compare = grid[posx-1][posy].food_pheromone[colony->colony_number]; // left
  if (compare > strongestVal) 
  {
	
	  strongest.at(0) = -1;
	
	  strongest.at(1) = 0;
    strongestVal = compare;
  }
  compare = grid[posx-1][posy+1].food_pheromone[colony->colony_number]; // left down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = -1;

	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  compare = grid[posx+1][posy].food_pheromone[colony->colony_number]; // right
  if (compare > strongestVal) 
  {
	  
	  strongest.at(0) = 1;
	  
	  strongest.at(1) = 0;
    strongestVal = compare;
  }
  compare = grid[posx+1][posy-1].food_pheromone[colony->colony_number]; // right up
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 1;

	  strongest.at(1) = -1;
    strongestVal = compare;
  }
  
  compare = grid[posx+1][posy+1].food_pheromone[colony->colony_number]; // right down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 1;

	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  compare = grid[posx][posy+1].food_pheromone[colony->colony_number]; // down
  if (compare > strongestVal) 
  {

	  strongest.at(0) = 0;
	  strongest.at(1) = 1;
    strongestVal = compare;
  }
  
  

  return strongest;
}
/*PostC : same as getStrongestreg() except this one is for food pher*/
/**********************************************************************************************************************************************************************************/

/*PreC : similar to moving(zombie &z, node & n)*/
void moving(human &h, node &n)
{
	
    vector<human>::iterator it_moving=grid[h.last_pos.x][h.last_pos.y].humans_at_posn.begin();


    for(; it_moving != grid[h.last_pos.x][h.last_pos.y].humans_at_posn.end();it_moving++)  //Condition for end of vector humans_at_posn
    {
				

        if(h==*it_moving)
        {	

            grid[h.last_pos.x][h.last_pos.y].humans_at_posn.erase(it_moving);
            break;
        }

    }
   
    h.pos.x=n.pos.x; h.pos.y=n.pos.y;
	human temph = h;
	temph.last_pos = h.last_pos;
	 n.humans_at_posn.push_back(h);
}
/* PostC : similar to moving(zombie &z, node & n)*/ 
/**********************************************************************************************************************************************************************************/


/* PreC : assuming being called by a human from H */
void human::move()                
{
	

    if (random(1) > WANDER_CHANCE) {dx += random(-1, 1);}
    if (random(1) > WANDER_CHANCE) {dy += random(-1, 1);}
    if (random(1) > .99) bored += floor(random(15));
	



	if (bored > 0)
		bored --;

	else if (food != 0)
	{	
		
        vector<int> direction = getStrongestreg(pos.x, pos.y);
		
		
        
		dx += direction[0] * random(1.5);
        dy += direction[1] * random(1.5);				
		

	}
	else 
	{
        vector<int> direction = getStrongestfood(pos.x, pos.y);
		
		
        dx += direction[0] * random(1.5);
        dy += direction[1] * random(1.5);
	}

	
    if (x<2) dx = 1;
    if (x>::X-2) dx = -1;
    if (y<2) dy = 1;
    if (y>::X-2) dy = -1;
	
    dx = min(dx, 1);
    dx = max(dx, -1);
    dy = min(dy, 1);
    dy = max(dy, -1);
	
    x += dx;
    y += dy;
   	int tempposx = floor(x);
    int tempposy = floor(y); // actual positions
	

	
	
	moving(*this, grid[tempposx][tempposy]);
   



	if (last_pos.x != tempposx || last_pos.y != tempposy) 
  	{
      // Leave trails
      if (food != 0) 
    {
        // Leave food pheromone trail
        foodPher = foodPher * USE_RATE;
		if(foodPher > grid[tempposx][tempposy].food_pheromone[colony->colony_number])
			grid[tempposx][tempposy].food_pheromone[colony->colony_number] = foodPher;
		


      }
      else
      {
        // Leave home pheromone trail
        homePher = homePher * USE_RATE;
		if (homePher > grid[tempposx][tempposy].reg_pheromone[colony->colony_number])
        	grid[tempposx][tempposy].reg_pheromone[colony->colony_number] = homePher;
		


      }
    }

    last_pos.x = tempposx;
    last_pos.y = tempposy;
	
	

}

//Postcondition: The human will move to a position decided as per pheromone levels (value of humans_at_posn at current node and next node is modified)

/**********************************************************************************************************************************************************************************/

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


/**********************************************************************************************************************************************************************************/

//Precondition: All functions running under change_state loop. A member of H,Z each is being called in one iteration

void change_state()
{
        
	

	spawn_new_humans();


        for (it_zombie = Z.begin(); it_zombie!=Z.end(); )
		{
		    

			vector<zombie>::iterator tempitz = it_zombie;


                it_zombie->move();
				
				

			    bool human_is_not_there=true;

				

				int leftextenti = (it_zombie->pos.x - it_zombie->nest->chase_radius < 0)?0:it_zombie->pos.x - it_zombie->nest->chase_radius;
				int rightextenti = (it_zombie->pos.x + it_zombie->nest->chase_radius > X-1)?X-1:it_zombie->pos.x + it_zombie->nest->chase_radius;
				int upextentj = (it_zombie->pos.y - it_zombie->nest->chase_radius < 0)?0:it_zombie->pos.y - it_zombie->nest->chase_radius;
				int downextentj = (it_zombie->pos.y + it_zombie->nest->chase_radius > X-1)?X-1:it_zombie->pos.y + it_zombie->nest->chase_radius;
	
				bool breaking = false;
				for ( int i = leftextenti ; i <= rightextenti; i++)
				{
					for ( int j = upextentj; j <= downextentj ; j++)
					{
						human_is_not_there = grid[i][j].humans_at_posn.empty();

						if( !human_is_not_there )
						{	
					        vector<human>::iterator it_moving=grid[i][j].humans_at_posn.begin(); 

						    
							 	
						    if(decide(it_zombie->nest->strength, it_moving->colony->strength)==1)
						    {
		
						        if(decide(it_zombie->nest->infection_rate, it_moving->colony->strength)==1)
						        {
									cout << "case 1" << endl;
						            it_zombie->die();
						        }
						        
								
						    }
						    else
						    {	
						        if(decide( it_zombie->nest->infection_rate,it_zombie->nest->strength)==1)

						        {
									cout << "case 4 " << endl;
									vector<human>::iterator it;
	
									//erasing from H
									for(it = H.begin(); it != H.end(); it++)
									{
										
										if (*it == *it_moving)
										{
											
											cout << "here " << endl;
											
											it_human = H.erase(it);
											break; 
										}
		
									}
									
									grid[i][j].humans_at_posn.erase(it_moving);
						        }
						    }

							breaking = true;
				
							break;
						}
						if(breaking == true)
							break;
					}
				}
				


				if ( it_zombie == tempitz && it_zombie!= Z.end())
					it_zombie++;

				
		}


        for (it_human = H.begin(); it_human!=H.end(); )
		{   
			vector<human>::iterator tempith = it_human;
			

	   		it_human->move();


			if (it_human->food != 0) 
			{

	  	        if (it_human->pos.x > it_human->colony->pos.x-10 && it_human->pos.x < it_human->colony->pos.x+10 
					&& it_human->pos.y > it_human->colony->pos.y-10 && it_human->pos.y < it_human->colony->pos.y+10) 
	  			{
	  	          
		          it_human->colony->food_amount  += it_human->food; 
				  
				  it_human->food=0;
	  	          
				  it_human->homePher = 100;
	  	        }
				
			}
			
    	    else if(grid[it_human->pos.x][it_human->pos.y].food != 0) 
    		{
				
			  
			  
		 	  if(grid[it_human->pos.x][it_human->pos.y].food >= it_human->colony->food_max)
		 	     {

		             it_human->food = it_human->colony->food_max;
		             grid[it_human->pos.x][it_human->pos.y].food -= it_human->food;
		         }
		 	  else
		 	     {


 		 	         it_human->food = it_human->food + grid[it_human->pos.x][it_human->pos.y].food;


		              grid[it_human->pos.x][it_human->pos.y].food=0;
		 	     }
    	      it_human->foodPher = 100;

    	    }
			
		
			it_human->aging();

			if(it_human == tempith && it_human != H.end()) 
				it_human++;

		}
		
		


		update_pheromone();

		sim_time++;

		
}

/* PostC :  positions, food values, pheromone values changed according to ACO*/
/**********************************************************************************************************************************************************************************/

/* PreC : evaporates pheromone */
void update_pheromone()
{
    

	for (int i = 0; i<X ; i++ )
	{
		for (int j  =0 ;j <X ; j++)
		{
			for ( int c = 0; c < Input.number_of_colonies; c++ )
			{

					grid[i][j].reg_pheromone[c] *= Input.ev_rate;

					grid[i][j].food_pheromone[c] *= Input.ev_rate;
				
			}
			
			
		}
	}
	

}        
/*PostC : pheromone evaporated from each grid position */
/**********************************************************************************************************************/


