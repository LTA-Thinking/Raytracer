#include "VectorHelpers.h"
#include <string>
#include <iostream>
#include <cstdio>
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

	Material(std::string n,double a[3],double d[3],double s[3]) 
	{
		name = n;
		copy(a,ambient);
		copy(d,diffuse);
		copy(s,specular);
	}
	
	Material(Material *m)
	{
		name = m->getName();
		double *a = m->getAmbient();
		double *d = m->getDiffuse();
		double *s = m->getSpecular();
		
		copy(a,ambient);
		copy(d,diffuse);
		copy(s,specular);
	}
	
	std::string getName(){return name;}
	double* getAmbient(){return ambient;}
	double* getDiffuse() {return diffuse;}
	double* getSpecular() {return specular;}
	
private:
	
	double ambient[3];
	double diffuse[3];
	double specular[3];
	std::string name;
	
};

/*
	The Light class holds information on lighting objects. It has the diffuse and specular components for the three color bands, RGB, that the light emits as well as the source point of the light.
	It has three getter methods to get the values of these properties.
*/
class Light
{
public:
		
	Light(std::string n,double s[3],double d[3],double spe[3])
	{
		name = n;
		copy(s,source);		
		copy(d,diffuce);
		copy(spe,specular);
	}
	
	std::string getName(){return name;}
	double* getSource() {return source;}
	double* getDiffuce() {return diffuce;}
	double* getSpecular() {return specular;}
		
private :
	
	std::string name;
	double source[3];
	double diffuce[3];
	double specular[3];
	
};

class Camera
{
public:
	// change this to use a normal transform matrix, or a direction vector
	Camera(std::string n,double t[4][4],double angle,int w,int h)
	{
		name = n;
		
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				transform[i][j] = t[i][j];
			}
		}
		
		center[0] = 0;
		center[1] = 0;
		center[2] = 0;
		
		double ans[3];
		mat_mult4x1(transform,center,ans);
		copy(ans,center);
		
		view_angle = angle;
		width = w;
		height = h;
	}
	
	std::string getName(){return name;}
	double getAngle(){return view_angle;}
	double getWidth(){return width;}
	double getHeight(){return height;}
	double* getCenter(){return center;}
	
	void getDirection(double ans[3])
	{
		double dir[3] = {0,0,1};
		mat_mult4x1(transform,dir,ans);
	}
	
	void screenCoordinate(double percent_width,double percent_height,double cords[3])
	{
		//printf("Screen Cord %f %f\n",percent_width,percent_height);
		cords[0] = width*(percent_width-0.5);
		cords[1] = height*(percent_height-0.5);
		cords[2] = 0;
		//printf("%f %f %f\n",cords[0],cords[1],cords[2]);
		double ans[3];
		mat_mult4x1(transform,cords,ans);
		copy(ans,cords);
		//printf("%f %f %f\n",cords[0],cords[1],cords[2]);
	}

private:
	
	std::string name;
	double center[3];
	double transform[4][4];
	double view_angle,width,height;
	
};