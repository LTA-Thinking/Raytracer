#include "RaytraceHelpers.h"
#include "VectorHelpers.h"
#include <string>

/*
	This file has information on GeoObject and its subclasses. 
	
	-RB Johnson, 10/5/2016
*/

/*
	The GeoObject class is the super class to all the objects used by the raytracer. 
	It has two methods and two virtual methods:
		getCenter - Returns an array of doubles corisponding to the center of the object.
		getMaterial - Returns a pointer to a Material object defining the material of the object.
		
		hit - A virtual method. It takes a pointer to a Ray object and an array of doubles. The array should be filled by the method with the point where the ray intersects the object. If it doesn't intersect the array should be filled with the source location of the ray.
		getNormal - A virtual method. It takes two arrays of doubles. The first array should be a point on the object. The method should then fill the second array with a vector that is normal to the object at the specified point
		
*/
class GeoObject 
{
public:

	GeoObject(std::string name, double transform[4][4],Material *m)
	{
		mat = new Material(m);
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				transformation[i][j] = transform[i][j];
			}
		}
		
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		
		double ans[3];
		mat_mult4x1(transform,center,ans);
		copy(ans,center);
		obj_name = name;
	}

	double* getCenter() { return center; }
	
	virtual void hit(Ray* r,double intersect[3]) {}

	virtual void getNormal(double loc[3],double ans[3]) {} 
	
	Material* getMaterial() { return mat;}
	
	std::string getName() {return obj_name;}
	
	~GeoObject()
	{
		delete mat;
	}
	
protected:
	
	double center[3];
	double transformation[4][4];
	Material *mat;
	std::string obj_name;
	
};


/*
	The Plane object is a subclass of GeoObject. It represents a flat plane
*/
class Plane : public GeoObject
{
public:
	
	Plane(std::string name,double transform[4][4],Material *m): GeoObject(name,transform, m)
	{
		normal_point[0] = 0.0;
		normal_point[1] = 0.0;
		normal_point[2] = 1.0;
		
		x_distance_point[0] = 1.0;
		x_distance_point[1] = 0.0;
		x_distance_point[2] = 0.0;
		
		y_distance_point[0] = 0.0;
		y_distance_point[1] = 1.0;
		y_distance_point[2] = 0.0;
		
		double ans[3];
		
		mat_mult4x1(transform,normal_point,ans);
		copy(ans,normal_point);
		
		mat_mult4x1(transform,x_distance_point,ans);
		copy(ans,x_distance_point);
		
		mat_mult4x1(transform,y_distance_point,ans);
		copy(ans,y_distance_point);
	}
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans) 
	{
		subtract(normal_point,center,ans);
		normalize(ans,ans);
	}
	
private:
	
	double normal_point[3];
	double x_distance_point[3];
	double y_distance_point[3];
};

/*
	The Sphere class is a subclass of GeoObject. It represents a sphere.
*/
class Sphere: public GeoObject
{
public:
	
	Sphere(std::string name,double transform[4][4],Material *m): GeoObject(name,transform, m)
	{
		radius_point[0] = 0.0;
		radius_point[1] = 0.0;
		radius_point[2] = 1.0;
		
		double ans[3];
		mat_mult4x1(transform,radius_point,ans);
		copy(ans,radius_point);
	}
	
	void hit(Ray* r,double intersect[3]);
	
	void getNormal(double loc[3],double ans[3]) 
	{
		subtract(loc,center,ans);
		normalize(ans,ans);
	}
	
private:

	double radius_point[3];
};

/*
	The Tetrahedron class is a subclass of GeoObject. It represents a regular four faced polyhedron with triangular faces.
*/
class Tetrahedron: public GeoObject
{
public:
	
	Tetrahedron(std::string name,double transform[4][4],Material *m);
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans);
	
private:
	
	double vertexes[4][3];
	double normals[4][3];
	double length;
};

/*
	The Dodecahedron class is a subclass of GeoObject. It represents a regular twelve faced polyhedron with pentagonal faces.
*/
class Dodecahedron: public GeoObject
{
public:
	
	Dodecahedron(std::string name,double transform[4][4],Material *m);
	
	void hit(Ray* r,double intersect[3]);
	
	void getNormal(double loc[3],double ans[3]);
	
private:
	
	double vertexes[20][3];
	double normals[12][3];
	int faces[12][5];
	double length;	
};

