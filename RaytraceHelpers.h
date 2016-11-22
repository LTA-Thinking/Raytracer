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

	Ray(double[] s,double[] d)
	{
		source[0] = s[0];
		source[1] = s[1];
		source[2] = s[2];
		direction[0] = d[0];
		direction[1] = d[1];
		direction[2] = d[2];
		
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

	Material(double* d,double* s) 
	{
		diffuse[0] = d[0];
		diffuse[1] = d[1];
		diffuse[2] = d[2];
		
		specular[0] = s[0];
		specular[1] = s[1];
		specular[2] = s[2];
	}
	
	Material(Material *m)
	{
		double *d = m->getDiffuse();
		double *s = m->getSpecular();
		
		diffuse[0] = d[0];
		diffuse[1] = d[1];
		diffuse[2] = d[2];
		
		specular[0] = s[0];
		specular[1] = s[1];
		specular[2] = s[2];
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
		
	Light(double[] s,double[] d,double[] spe)
	{
		source[0] = s[0];
		source[1] = s[1];
		source[2] = s[2];
		
		diffuse[0] = d[0];
		diffuse[1] = d[1];
		diffuse[2] = d[2];
		
		specular[0] = spe[0];
		specular[1] = spe[1];
		specular[2] = spe[2];
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
	
	Camera(double[] cord,double angle,int w,int h,double p,double y,double r)
	{
		center[0] = cord[0];
		center[1] = cord[1];
		center[2] = cord[2];
		
		view_angle = angle;
		width = w;
		height = h;
		pitch = p;
		yaw = y;
		roll = r;
	}

private:
	
	double center[3];
	double view_angle,width,height,pitch,yaw,roll;
	
};