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
			


			if (it != Input.food_sources.end() && it->x == i && it->y == j )
			{
                int fs_size = int(sqrt(it->food_source_area));
				//int leftextentl = (i - fs_size < 0)?0:i - fs_size;
				int rightextentl = (i + fs_size  > X-1)?X-1:i + fs_size;
				//int upextentm = (j - fs_size < 0)?0:j - fs_size;
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
void init_grid2()
{
	

	// IMP ::have to make a default constructor for node to implement node grid[X][X];
	
	
    vector<food_source>::const_iterator it = Input.food_sources.begin();	// traversing food_locations


	for ( int i = 0 ;i < X ; i ++ )
	{
		for (int j = 0; j < X; j++)
		{
			// setting positions
			

			if (it != Input.food_sources.end() && it->x == i && it->y == j )
			{
                int fs_size = int(sqrt(it->food_source_area));
				//int leftextentl = (i - fs_size < 0)?0:i - fs_size;
				int rightextentl = (i + fs_size  > X-1)?X-1:i + fs_size;
				//int upextentm = (j - fs_size < 0)?0:j - fs_size;
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
			newh.bored = 0;
			newh.homePher = 100; newh.foodPher = 100;
			newh.x = newh.pos.x; newh.y = newh.pos.y;
			newh.dx = random(-1,1);
			newh.dy = random(-1,1);
			//cout << "initially" << newh.dx << " " << newh.dy << endl;
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
			//position temper(-1,-1);
			//newz.chase_pos = temper;
			
			
			zombie_nest &temper2= *it_zombie_nests;
			//cout << temper2.pos.x << endl;
			//cout<<endl<<endl<<endl;


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
	
    float new_ph = random(1); // this works -> sattwik 11.04.15 , 11:44 pm
 
    if(new_ph<(a/(a+b+c+d)))
        return 0;  //Left
    if(new_ph>=(a/(a+b+c+d)) && new_ph<((a+b)/(a+b+c+d)))
        return 1;  //Up
     if(new_ph>=((a+b)/(a+b+c+d)) && new_ph<((a+b+c)/(a+b+c+d)))
        return 2;  //Right
     if(new_ph>=((a+b+c)/(a+b+c+d)))
        return 3;  //Down
}

void moving(zombie &z, node &n)
{

    vector<zombie>::iterator it_moving=grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.begin();

    for(; it_moving!=grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.end();it_moving++)  //Condition for end of vector zombies_at_posn   // Changed !!!
    {

        if(z==*it_moving)
        {
            grid[z.last_pos.x][z.last_pos.y].zombies_at_posn.erase(it_moving);
            break;
        }
        //it_moving++;
    }

    n.zombies_at_posn.push_back(z);
    z.pos.x=n.pos.x; z.pos.y=n.pos.y;



}

/*
void zombie::check_human()
{
    bool human_is_not_there=true;
    //human_is_not_there=grid[pos.x][pos.y].humans_at_posn.empty();
	int i, j;

	int leftextenti = (pos.x - nest->chase_radius < 0)?0:pos.x - nest->chase_radius;
	int rightextenti = (pos.x + nest->chase_radius > X-1)?X-1:pos.x + nest->chase_radius;
	int upextentj = (pos.y - nest->chase_radius < 0)?0:pos.y - nest->chase_radius;
	int downextentj = (pos.y + nest->chase_radius > X-1)?X-1:pos.y + nest->chase_radius;
	
	bool breaking = false;
	for ( i = leftextenti ; i <= rightextenti; i++)
	{
		for ( j = upextentj; j <= downextentj ; j++)
		{
			human_is_not_there = grid[i][j].humans_at_posn.empty();

			if( !human_is_not_there )
			{	
		        vector<human>::iterator it_moving=grid[i][j].humans_at_posn.begin(); 

		        encounter_human(*it_moving); 
				//encounter_human(grid[i][j].humans_at_posn[0]);
				breaking = true;
				
				break;
			}
			if(breaking == true)
				break;
		}
	}
}

*/
void zombie::die()
{
	cout << "in zombie die " << endl;
    nest->number_of_zombies--;
    vector<zombie>::iterator it_moving=grid[pos.x][pos.y].zombies_at_posn.begin();
    
	//cout << "bool "<<grid[pos.x][pos.y].zombies_at_posn.empty() << endl;
	// from posn
	for(;it_moving != grid[pos.x][pos.y].zombies_at_posn.end(); it_moving++ )
    {
		cout << "in for loop in zombie die" << endl;
        if(*this == *it_moving)
        {
			grid[pos.x][pos.y].zombies_at_posn.erase(it_moving);
            break;
        }

    }
    
	cout << "After for loop in zombie die"<< endl;
	// from main list
	
	
	vector<zombie>::iterator it_zombie1=Z.begin();
	for (; it_zombie1 != Z.end(); it_zombie1 ++)
	{
		cout << "Inside main list for loop inside zombie die "<< endl;
		if(*it_zombie1 == *this)
			{	
				it_zombie = Z.erase(it_zombie1);
				break;
			}
		
		
	}


	
	cout << "returning from zombie die " << endl;
	
}




int decide(float a, float b)
{
    //srand (time(NULL));
	

    float new_ph = random(1);

    if(new_ph<(a/(a+b)))
        return 0;  //a wins
    else return 1; //b wins
}
/*
void zombie::encounter_human(human h)
{
    cout << "Encountered !" << endl;


	
    if(decide(nest->strength, h.colony->strength)==1)
    {
		
        if(decide(nest->infection_rate, h.colony->strength)==1)
        {
			cout << "case 1" << endl;
            die();
        }
        else
        {
			cout << "case 2" << endl;
            zombie temp = *this;
			die();
			h.infect(temp);
            
        }
    }
    else
    {
        if(decide(nest->strength, nest->infection_rate)==1)
        {
			cout << "case 3" << endl;
            h.infect(*this);
        }
        else
        {
			cout << "case 4 " << endl;
            h.die();
        }
    }
}
*/
// Postcondition: it_zombie may be increased


void zombie::move()
{
	 position temp_last_pos=last_pos;
	 last_pos =  pos;

     //if(chasing)
     //{
       // chase();

     //}
     //else
     //{
         
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

		
    // }

	 


}
// Postconditions: zombie removed from present node and addded to next node.

//Preconditions: vector<human> H, vector<zombie> Z and vector<zombie_colony> zombie_colonies defined

int distance(position a, position b)
{
    return fabs(a.x-b.x)+fabs(a.y-b.y);
} 
/*
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
                chase_pos=(distance(pos,chase_pos)>distance(pos,temp_chase_pos))?temp_chase_pos:chase_pos;
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
*/
/**********************************************************************************************************************/



void human::aging()
{
    age++;
    if(age>=colony->death_age)
	{
		
	    die();	
	}
	
	
}

//Postcondition: Increases the age of the human and kills it if it is too old




void human::die()
{
	cout << "In human die " << endl;
    colony->number_of_humans--;
    vector<human>::iterator it_moving=grid[pos.x][pos.y].humans_at_posn.begin();

	// erasing from posn
	for (; it_moving != grid[pos.x][pos.y].humans_at_posn.end(); it_moving++)  //Condition for end of vector humans_at_posn
    {
		cout << "Inside for loop in human  die" << endl;
        if(*this == *it_moving)
        {
			
            vector<human>::iterator temp = grid[pos.x][pos.y].humans_at_posn.erase(it_moving);

            break;
        }
       
    }
	
	cout << "Outside for loop in human die" << endl;
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
	cout << "Returning from human die" << endl;

}

//Postcondition: Kills the human and and increments it_human
/*

void human::infect(zombie infecting_zombie)
{
	cout << "In human infect" << endl;
	cout << "human position in infect" << pos.x << " " << pos.y << endl;
    zombie new_z = infecting_zombie; 
	new_z.pos = pos;
	
	cout << "new zombie position in infect " << new_z.pos.x << " " << new_z.pos.y << endl;
    Z.push_back(new_z);
	
    die();
	cout << "After infect's die " << endl;
}
*/


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


void moving(human &h, node &n)
{
	
    vector<human>::iterator it_moving=grid[h.last_pos.x][h.last_pos.y].humans_at_posn.begin();
	//cout << "last pos " << h.last_pos.x << "  " << h.last_pos.y << endl;
	cout << "current pos " << h.pos.x << " " << h.pos.y << endl;
    for(; it_moving != grid[h.last_pos.x][h.last_pos.y].humans_at_posn.end();it_moving++)  //Condition for end of vector humans_at_posn
    {
		cout << " posns of hhuman at posn " << it_moving->pos.x << " " << it_human->pos.y << endl;
		cout << endl << endl;
			cout << "int position " << it_moving->pos.x << " " << it_moving->pos.y << " VS " << h.pos.x << " " << h.pos.y << endl;
			//cout << "float position " << it_moving->x << " " << it_moving->y << " VS " << h.x << " " << h.y << endl;
			cout << "dx dy " <<  h.dx << " " << h.dy << " VS " << it_moving->dx << " " << it_moving->dy << endl;
			//cout << "last position " << h.last_pos.x << " " << h.last_pos.y << " VS " << it_moving->last_pos.x << " " << it_moving->last_pos.y << endl;
			cout << "colony number " << h.colony->colony_number <<  " VS " << it_moving->colony->colony_number << endl;
			cout << "food " << h.food << " VS " << it_moving->food << endl;
			//cout << "age" << h.age << " VS " << it_moving->age << endl;
			cout << "dead " << h.dead << " VS " << it_moving->dead << endl;
			cout << "infected " << h.infected << " VS " << it_moving->infected << endl;
			cout << "bored " << h.bored << " VS " << it_moving->bored << endl;
			//cout << "foodPher "<< h.foodPher << " VS " << it_moving->foodPher << endl;
			//cout << "homePher " << h.homePher << " VS " << it_moving->foodPher << endl;
        if(h==*it_moving)
        {	
			cout << "In " << endl;
            grid[h.last_pos.x][h.last_pos.y].humans_at_posn.erase(it_moving);
            break;
        }
        //it_moving++;
    }
   
    h.pos.x=n.pos.x; h.pos.y=n.pos.y;
	human temph = h;
	temph.last_pos = h.last_pos;
	 n.humans_at_posn.push_back(h);
}
void human::move()                 // Change move to something else (Reserved word)
{
	

    if (random(1) > WANDER_CHANCE) {dx += random(-1, 1);}
    if (random(1) > WANDER_CHANCE) {dy += random(-1, 1);}
    if (random(1) > .99) bored += floor(random(15));
	

	cout << "after random " << endl;

	if (bored > 0)
		bored --;

	else if (food != 0)
	{	
		
        vector<int> direction = getStrongestreg(pos.x, pos.y);
		
		/*
		cout << "lokking for home " << endl;
		cout << direction[0] << endl;
		cout << direction[1] << endl;
		*/
        
		dx += direction[0] * random(1.5);
        dy += direction[1] * random(1.5);				
		

	}
	else 
	{
        vector<int> direction = getStrongestfood(pos.x, pos.y);
		
		/*
		cout << "Looking for food " << endl;
		cout << direction[0] << endl;
		cout << direction[1] << endl;
		*/
        dx += direction[0] * random(1.5);
        dy += direction[1] * random(1.5);
	}
	cout << "after get strongest " << endl;
	
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
	
	cout << "before " << tempposx << " " << tempposy << endl;
	
	
	moving(*this, grid[tempposx][tempposy]);
   
	cout << "after " << pos.x << " " << pos.y << endl;


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
				cout << "Spawned" << endl;
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
				cout << "Spawned" << endl;

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
			//it_zombie->scan();

                it_zombie->move();
				
				
    			//it_zombie->check_human();
			    bool human_is_not_there=true;
			    //human_is_not_there=grid[pos.x][pos.y].humans_at_posn.empty();
				

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
						        
								
								/*else
						        {
									cout << "case 2" << endl;

									//it_moving->infect(temp);
									vector<human>::iterator it;
									for(it = H.begin(); it != H.end(); it++)
									{
										if (*it == *it_moving)
										{
			
											//it_human = H.erase(it);
											break; // Sattwik : inserted this -> somehow (maybe) got rid of strange segfault  -> 11.04.15 , 11:33 pm
										}
		
									}
									
								    zombie new_z = *it_zombie; 
									new_z.pos = it->pos;
									new_z.last_pos = it->last_pos;
									
								    Z.push_back(new_z);
								    it->die();
																		
									//grid[i][j].humans_at_posn.erase(it_moving);
								    it_zombie->die();
									cout << "After infect's die " << endl;
            					
						        }
								*/
						    }
						    else
						    {	/*
						        if(decide(it_zombie->nest->strength, it_zombie->nest->infection_rate)==1)
						        {
									cout << "case 3" << endl;
						            //it_moving->infect(*it_zombie);
									vector<human>::iterator it;
									for(it = H.begin(); it != H.end(); it++)
									{
										if (*it == *it_moving)
										{
			
											//it_human = H.erase(it);
											break; // Sattwik : inserted this -> somehow (maybe) got rid of strange segfault  -> 11.04.15 , 11:33 pm
										}
		
									}
									
								    zombie new_z = *it_zombie; 
									new_z.pos = it->pos;
									new_z.last_pos = it->last_pos;
									
								    Z.push_back(new_z);
								    it_human = H.erase(it);
									
																		
									//grid[i][j].humans_at_posn.erase(it_moving);
						        }*/
						        if(decide( it_zombie->nest->infection_rate,it_zombie->nest->strength)==1)
								//else
						        {
									cout << "case 4 " << endl;
									vector<human>::iterator it;
	
									//erasing from H
									for(it = H.begin(); it != H.end(); it++)
									{
										/*
										cout << endl << endl;
											cout << "int position " << it->pos.x << " " << it->pos.y << " VS " << it_moving->pos.x << " " << it_moving->pos.y << endl;
											cout << "float position " << it->x << " " << it->y << " VS " << it_moving->x << " " << it_moving->y << endl;
											cout << "dx dy " <<  it->dx << " " << it->dy << " VS " << it_moving->dx << " " << it_moving->dy << endl;
											cout << "last position " << it->last_pos.x << " " << it->last_pos.y << " VS " << it_moving->last_pos.x << " " << it_moving->last_pos.y << endl;
											cout << "colony number " << it->colony->colony_number <<  " VS " << it_moving->colony->colony_number << endl;
											cout << "food " << it->food << " VS " << it_moving->food << endl;
											cout << "age" << it->age << " VS " << it_moving->age << endl;
											cout << "dead " << it->dead << " VS " << it_moving->dead << endl;
											cout << "infected " << it->infected << " VS " << it_moving->infected << endl;
											cout << "bored " << it->bored << " VS " << it_moving->bored;
											cout << "foodPher "<< it->foodPher << " VS " << it_moving->foodPher << endl;
											cout << "homePher " << it->homePher << " VS " << it_moving->foodPher << endl;
										*/
										
										if (*it == *it_moving)
										{
											
											cout << "here " << endl;
											
											it_human = H.erase(it);
											break; // Sattwik : inserted this -> somehow (maybe) got rid of strange segfault  -> 11.04.15 , 11:33 pm
										}
		
									}
									
									grid[i][j].humans_at_posn.erase(it_moving);
						        }
						    }
							//encounter_human(grid[i][j].humans_at_posn[0]);
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
		cout << "In betwwen " << endl;

        for (it_human = H.begin(); it_human!=H.end(); )
		{   
			vector<human>::iterator tempith = it_human;
			
			cout << "before move " <<endl;
	   		it_human->move();
			cout << "after move" << endl;
			//cout << it_human->food << endl;
			if (it_human->food != 0) 
			{

	  	        if (it_human->pos.x > it_human->colony->pos.x-10 && it_human->pos.x < it_human->colony->pos.x+10 
					&& it_human->pos.y > it_human->colony->pos.y-10 && it_human->pos.y < it_human->colony->pos.y+10) 
	  			{
	  	          // Close enough to home
				  //cout << "dropped" << endl;
		          it_human->colony->food_amount  += it_human->food; 
				  
				  it_human->food=0;
	  	          
				  it_human->homePher = 100;
	  	        }
				
			}
			
    	    else if(grid[it_human->pos.x][it_human->pos.y].food != 0) 
    		{
				/*
  			  cout << "found " <<  grid[it_human->pos.x][it_human->pos.y].food << endl;
			  cout << "but " << it_human->colony->food_max << endl;
			  cout << "bool " << (grid[it_human->pos.x][it_human->pos.y].food >= it_human->colony->food_max);
			  */
			  
			  
		 	  if(grid[it_human->pos.x][it_human->pos.y].food >= it_human->colony->food_max)
		 	     {

		             it_human->food = it_human->colony->food_max;
		             grid[it_human->pos.x][it_human->pos.y].food -= it_human->food;
		         }
		 	  else
		 	     {

					 //cout << it_human->food << endl;
 		 	         it_human->food = it_human->food + grid[it_human->pos.x][it_human->pos.y].food;
					 //cout << grid[it_human->pos.x][it_human->pos.y].food << endl;
					 //cout << it_human->food << endl;
		              grid[it_human->pos.x][it_human->pos.y].food=0;
		 	     }
    	      it_human->foodPher = 100;
			  //cout << "food with human " << it_human->food << endl;
    	    }
			
		
			it_human->aging();

			if(it_human == tempith && it_human != H.end()) // if you don't check for H.end() , gives segfault
				it_human++;

		}
		
		
		//cout << "Number of humans  " << H.size() << endl;
		//cout << "Number of zombies " << Z.size() << endl;
		update_pheromone();
		//cout << "simtime " << sim_time <<endl; 
		sim_time++;

		
}

/**********************************************************************************************************************/
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
			
			/*
			vector<human>::iterator ith= grid[i][j].humans_at_posn.begin();
			for (;ith != grid[i][j].humans_at_posn.end(); ith++)
			{
				ith-> age++;
			}
			*/
		}
	}
	

}        

/**********************************************************************************************************************/


