//#include "ClrFileOperations.h"
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
	
	World(std::string path);
	
	// width and height in pixels, eye is the location of the eye, distance is the distance between the eye and the draw plate, theta is the rotation around the z axis, phi is the rotation around the xy plane, and alpha is the local rotation around it's center point.
	void drawImage(std::string image_name, std::string camera_name, int widthPixels);
	
	void raytrace(Ray* ray,unsigned char pixel[3]);
	
	~World()
	{
			for (materials_it = materials.begin(); materials_it!=materials.end(); materials_it++) {
				delete *materials_it;
			}
			
			for (obj_it = obj.begin(); obj_it!=obj.end(); obj_it++) {
				delete *obj_it;
			}
			
			for (light_it = lights.begin(); light_it!=lights.end(); light_it++) {
				delete *light_it;
			}
			
			for(camera_it = cameras.begin(); camera_it!=cameras.end(); camera_it++)
			{
				delete *camera_it;
			}
	}
private:
	
	list<Material*> materials;
	list<Material*>::iterator materials_it;
	
	list<GeoObject*> obj;
	list<GeoObject*>::iterator obj_it;
	
	list<Light*> lights;
	list<Light*>::iterator light_it;
	
	list<Camera*> cameras;
	list<Camera*>::iterator camera_it;
	
	// 3 element array with the ambient light for the world between 0-255
	// 0 is blue, 1 is green, 2 is red
	double ambientLight[3];
	
	static const int SPECULAR_EXP = 100;
};