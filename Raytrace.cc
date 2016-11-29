#include <iostream>
#include "World.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	World* w = new World("test");
	cout << "created world" << endl;
	double eye [3] = {-20,0,2};
	
	//w->drawImage("Three_Objects",1920,1080,eye,18,0,0,0);
	
	delete w;
}