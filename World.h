#include "GeoObject.h"
#include <list>
#include <string>

using std::list;

/* 
	The World class is what holds the information of all the objects and lights in the scene. All objects are difined in the World constructor. 
	There are two methods:
		drawImage - Creates an image from the scene. It takes information about where the camera is located, how it is oriented, and what the final picture should be called.
		raytrace - Traces the path of a single ray, and returns the color of the pixel the ray passes through. Takes as arguments the ray to be traced and an array to put the information about the pixel in.	
		
	-RB Johnson, 10/5/2016
*/

class World 
{

public:
	
	World();
	
	// width and height in pixels, eye is the location of the eye, distance is the distance between the eye and the draw plate, theta is the rotation around the z axis, phi is the rotation around the xy plane, and alpha is the local rotation around it's center point.
	void drawImage(std::string name, int width, int height, double eye [], double distance, double pitch, double yaw, double roll);
	
	unsigned char* raytrace(Ray* ray,unsigned char* pixel);
	
	~World()
	{
			for (it = obj.begin(); it!=obj.end(); it++) {
				delete *it;
			}
			
			for (lit = lights.begin(); lit!=lights.end(); lit++) {
				delete *lit;
			}
			
			delete [] ambientLight;
	}
private:
	
	list<GeoObject*> obj;
	list<GeoObject*>::iterator it;
	
	list<Light*> lights;
	list<Light*>::iterator lit;
	
	// 3 element array with the ambient light for the world between 0-255
	// 0 is blue, 1 is green, 2 is red
	double* ambientLight;
	
	static const int specular_ex = 100;
	static const double pixel_to_unit = 0.01; // ratio of pixel size to in world units
};