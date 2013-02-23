//TSP constructor

#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

#define MAX_CITIES 30
#define MAX_DIST 100

struct cityType{
	int x,y;
}cities[MAX_CITIES];

using namespace std;

int main()
{

    ofstream f1;
    f1.open("TSP.txt");
    srand(time(NULL));
    
    
    int city;
    
    for(city =0 ;city<MAX_CITIES; city++)
    {
        cities[city].x = rand()%MAX_DIST;
		
    	cities[city].y = rand()%MAX_DIST;
    
        f1<<cities[city].x<<" "<<cities[city].y<<" "<<std::endl;
    }

    f1.close();

    return 0;

}
