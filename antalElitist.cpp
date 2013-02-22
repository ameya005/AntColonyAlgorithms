// Ant al - elitist systems
//Ant algorithms for Travelling salesman Problem

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <fstream>
//#include <cv.h>
//#include <highgui.h>

#define MAX_CITIES 30
#define MAX_DIST 100
#define MAX_TOUR (MAX_CITIES * MAX_DIST)
#define MAX_ANTS 30

using namespace std;

//Initial Definiton of the problem
struct cityType{
	int x,y;
};

struct antType{
	
	int curCity, nextCity, pathIndex;
	int tabu[MAX_CITIES];
	int path[MAX_CITIES];
	double tourLength;
};

//Ant algorithm problem parameters

#define ALPHA 1.0
#define BETA 5.0 //This parameter raises the weight of distance over pheromone
#define RHO 0.5 //Evapouration rate
#define QVAL 100
#define MAX_TOURS 20
#define MAX_TIME (MAX_TOURS * MAX_CITIES)
#define INIT_PHER (1.0/MAX_CITIES)
#define E_ACO 1.0

//runtime Structures and global variables

cityType cities[MAX_CITIES];
antType ants[MAX_ANTS];

double dist[MAX_CITIES][MAX_CITIES];

double phero[MAX_CITIES][MAX_CITIES];

double best=(double)MAX_TOUR;
int bestIndex;

//function init() - initializes the entire graph

void init()
{
	int from,to,ant;
    ifstream f1;
    
    f1.open("TSP.txt");
	
	//creating cities
	
	for(from = 0; from < MAX_CITIES; from++)
	{
		//randomly place cities
		/*
		cities[from].x = rand()%MAX_DIST;
		
		cities[from].y = rand()%MAX_DIST;
        */
        f1>>cities[from].x;
        f1>>cities[from].y;

        cout<<cities[from].x<<" "<<cities[from].y<<endl;
		//printf("\n %d %d",cities[from].x, cities[from].y);
		for(to=0;to<MAX_CITIES;to++)
		{
			dist[from][to] = 0.0;
			phero[from][to] = INIT_PHER;
		}
	}
	
	//computing distance
	
	for(from = 0; from < MAX_CITIES; from++)
	{
		for( to =0; to < MAX_CITIES; to++)
		{
			if(to!=from && dist[from][to]==0.0)
			{
				int xd = pow( abs(cities[from].x - cities[to].x), 2);
				int yd = pow( abs(cities[from].y - cities[to].y), 2);
				
				dist[from][to] = sqrt(xd + yd);
				dist[to][from] = dist[from][to];
				
			}
		}
	}
	
	
	//initializing the ANTs
	
	to = 0;
	for( ant = 0; ant < MAX_ANTS; ant++)
	{
		if(to == MAX_CITIES)
			to=0;
		
		ants[ant].curCity = to++;
		
		for(from = 0; from < MAX_CITIES; from++)
		{
			ants[ant].tabu[from] = 0;
			ants[ant].path[from] = -1;
		}
		
		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0;
		
		//loading first city into tabu list
		
		ants[ant].tabu[ants[ant].curCity] =1;
		
	}
}

//reinitialize all ants and redistribute them
void restartAnts()
{
	int ant,i,to=0;
	
	for(ant = 0; ant<MAX_ANTS; ant++)
	{
		if(ants[ant].tourLength < best)
		{
			best = ants[ant].tourLength;
			bestIndex = ant;
		}
		
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0.0;
		
		for(i=0;i<MAX_CITIES;i++)
		{
			ants[ant].tabu[i] = 0;
			ants[ant].path[i] = -1;
		}
		
		if(to == MAX_CITIES)
			to=0;
			
		ants[ant].curCity = to++;
		
		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		
		ants[ant].tabu[ants[ant].curCity] = 1;
	}
}

double antProduct(int from, int to)
{
	return(( pow( phero[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA)));
}

int selectNextCity( int ant )
{
	int from, to;
	double denom = 0.0;
	
	from=ants[ant].curCity;
	
	for(to=0;to<MAX_CITIES;to++)
	{
		if(ants[ant].tabu[to] == 0)
		{
			denom += antProduct( from, to );
		}
	}
	
	assert(denom != 0.0);
	
	do
	{
		double p;
		to++;
		
		if(to >= MAX_CITIES)
			to=0;
		if(ants[ant].tabu[to] == 0)
		{
			p = antProduct(from,to)/denom;
			
			//printf("\n%lf %lf", (double)rand()/RAND_MAX,p);
			double x = ((double)rand()/RAND_MAX); 
			if(x < p)
			{
				//printf("%lf %lf Yo!",p,x);
			
				break;
			}
		}
	}while(1);
	
	return to;
}
	
int simulateAnts()
{
	int k;
	int moving = 0;
	
	for(k=0; k<MAX_ANTS; k++)
	{
		//checking if there are any more cities to visit
		
		if( ants[k].pathIndex < MAX_CITIES )
		{
			ants[k].nextCity = selectNextCity(k);
			ants[k].tabu[ants[k].nextCity] = 1;
			ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;
			
			ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];
			
			//handle last case->last city to first
			
			if(ants[k].pathIndex == MAX_CITIES)
			{
				ants[k].tourLength += dist[ants[k].path[MAX_CITIES -1]][ants[k].path[0]];
			}
			
			ants[k].curCity = ants[k].nextCity;
			moving++;
			
		}
	}
	
	return moving;
}

//Updating trails

void updateTrails()
{
	int from,to,i,ant,flag = 0,k;
	
	//Pheromone Evaporation
	
	for(from=0; from<MAX_CITIES;from++)
	{
		for(to=0;to<MAX_CITIES;to++)
		{
			if(from!=to)
			{
				phero[from][to] *=( 1.0 - RHO);
				
				if(phero[from][to]<0.0)
				{
					phero[from][to] = INIT_PHER;
				}
			}
		}
	}
	
	//Add new pheromone to the trails
	
	for(ant=0;ant<MAX_ANTS;ant++)
	{
		for(i=0;i<MAX_CITIES;i++)
		{	
			if( i < MAX_CITIES-1 )
			{
				from = ants[ant].path[i];
				to = ants[ant].path[i+1];
			}
			else
			{
				from = ants[ant].path[i];
				to = ants[ant].path[0];
			}
			for(k=0;k<MAX_CITIES;k++)
            {
                if(from == ants[bestIndex].path[k] && to==ants[bestIndex].path[k+1])
                    flag = 1;
            } 
            if(flag == 1)
            {
			    phero[from][to] += (QVAL/ ants[ant].tourLength) + (QVAL/ best ) ; //Elitist updation
			    phero[to][from] = phero[from][to];
			}
            else
            {
                phero[from][to] += (QVAL/ ants[ant].tourLength) ;
			    phero[to][from] = phero[from][to];
            }
		}
	}
	
	for (from=0; from < MAX_CITIES;from++)
	{
		for( to=0; to<MAX_CITIES; to++)
		{
			phero[from][to] *= RHO;
		}
	}
	
}

void emitDataFile(int bestIndex)
{
	ofstream f1;
	f1.open("Data_elitist.txt");
	antType antBest;
	antBest = ants[bestIndex];
	//f1<<antBest.curCity<<" "<<antBest.tourLength<<"\n";
	int i;
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<antBest.path[i]<<" ";
	}
	
	f1.close();
	
	f1.open("city_data_elitist.txt");
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<cities[i].x<<" "<<cities[i].y<<"\n";
	}
	f1.close();
	
}
	


int main()
{
    int curTime = 0;

    cout<<"ACO- Elitist";
	cout<<"MaxTime="<<MAX_TIME;
	
	srand(time(NULL));
	
	init();
	
	while( curTime++ < MAX_TIME)
	{
		if( simulateAnts() == 0)
		{
			updateTrails();
			
			if(curTime != MAX_TIME)
				restartAnts();
				
			cout<<"\n Time is "<<curTime<<"("<<best<<")";
			
		}
	}
	
	cout<<"\nACO-E: Best tour = "<<best<<endl<<endl<<endl;
	
	emitDataFile(bestIndex);
	
	return 0;
}
	
				
	


		
			
	  
		
	 

 
