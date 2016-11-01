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

	Ray(double ex,double ey,double ez,double dx,double dy,double dz)
	{
		source = new double[3];
		direction = new double[3];
		source[0] = ex;
		source[1] = ey;
		source[2] = ez;
		direction[0] = dx;
		direction[1] = dy;
		direction[2] = dz;
		
		normalize(direction,direction);
	}
	
	Ray(double e[3],double d[3]) 
	{
		source = e;
		direction = d;
		
		normalize(direction,direction);
	}
	
	double* getSource() {return source;}
	double* getDirection() {return direction;}
	
	~Ray() {
		delete [] source;
		delete [] direction;
	}
	
private:

	double* source;
	double* direction;

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
		diffuse = d;
		specular = s;
	}
	
	double* getDiffuse() {return diffuse;}
	double* getSpecular() {return specular;}
	
	~Material()
	{
		delete [] diffuse;
		delete [] specular;
	}
	
private:
	
	double* diffuse;
	double* specular;
	
};

/*
	The Light class holds information on lighting objects. It has the diffuse and specular components for the three color bands, RGB, that the light emits as well as the source point of the light.
	It has three getter methods to get the values of these properties.
*/
class Light
{
public:
		
	Light(double* s,double* dif,double* spe)
	{
		source = s;
		diffuce = dif;
		specular = spe;
	}
	
	double* getSource() {return source;}
	
	double* getDiffuse() {return diffuce;}
	
	double* getSpecular() {return specular;}
	
	~Light()
	{
		delete [] source;
		delete [] diffuce;
		delete [] specular;
	}
		
private :
	
	double* source;
	double* diffuce;
	double* specular;
	
};