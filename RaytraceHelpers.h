#include "VectorHelpers.h"
/*
	This file contains classes that are used to hold information on common objects used in raytracing.
	
	-RB Johnson, 10/5/2016
*/

/*
	The Ray class holds information on rays. It contains a ray's source point and direction vector. 
	It has two methods for getting the values of these properties.
*/
class Ray 
{
public:

	Ray(double s[3],double d[3])
	{
		copy(s,source);
		copy(d,direction);
		
		normalize(direction,direction);
	}
	
	double* getSource() {return source;}
	double* getDirection() {return direction;}
	
private:

	double source[3];
	double direction[3];

};

/*
	The Material class holds information on the materials of objects. It has the diffuse and specular components for the three color bands, RGB.
	It has two getter methods to get the values of these properties.
*/
class Material 
{
public:

	Material(double d[3],double s[3]) 
	{
		copy(d,diffuse);
		copy(s,specular);
	}
	
	Material(Material *m)
	{
		double *d = m->getDiffuse();
		double *s = m->getSpecular();
		
		copy(d,diffuse);
		copu(s,specular);
	}
	
	double* getDiffuse() {return diffuse;}
	double* getSpecular() {return specular;}
	
private:
	
	double diffuse[3];
	double specular[3];
	
};

/*
	The Light class holds information on lighting objects. It has the diffuse and specular components for the three color bands, RGB, that the light emits as well as the source point of the light.
	It has three getter methods to get the values of these properties.
*/
class Light
{
public:
		
	Light(double s[4],double d[3],double spe[3])
	{
		copy(s,source);
		
		copy(d,diffuse);
		copy(spe,specular);
	}
	
	double* getSource() {return source;}
	
	double* getDiffuse() {return diffuce;}
	
	double* getSpecular() {return specular;}
		
private :
	
	double source[3];
	double diffuce[3];
	double specular[3];
	
};

class Camera
{
public:
	
	Camera(double cord[4],double angle,int w,int h,double p,double y,double r)
	{
		copy(cord,center);
		
		view_angle = angle;
		width = w;
		height = h;
		pitch = p;
		yaw = y;
		roll = r;
	}

private:
	
	double center[4];
	double view_angle,width,height,pitch,yaw,roll;
	
};