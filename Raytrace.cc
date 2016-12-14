#include <iostream>
#include <stdlib.h>
#include "World.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	
	cout << argc << endl;
	
	if(argc == 5)
	{
		World* w = new World(argv[1]);
		cout << "created world" << endl;
	
		w->drawImage(argv[3],argv[2],strtol(argv[4],NULL,10));
		
		delete w;
	}
	else
		cout << "ERROR: Not enough input arguments. Must be in the order: file name, camera name, output image name, image width in pixels\n";
	
}