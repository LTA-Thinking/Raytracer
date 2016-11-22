#include "RaytraceHelpers.h"
#include "VectorHelpers.h"

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

	virtual GeoObject(double transform[4][4],Material *m)
	{
		mat = new Material(m);
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				transformation[i][j] = transform[i][j];
			}
		}
		
		center[0] = 0;
		center[1] = 0;
		center[2] = 0;
		center[3] = 1;
	}

	double* getCenter() { return center; }
	
	virtual void hit(Ray* r,double* intersect) {}

	virtual void getNormal(double* loc,double* ans) {} 
	
	Material* getMaterial() { return mat;}
	
	~GeoObject()
	{
		delete mat;
	}
	
protected:
	
	double center[3];
	double transformation[4][4];
	Material *mat;
	
};


/*
	The Plane object is a subclass of GeoObject. It represents a flat plane
*/
class Plane : public GeoObject
{
public:
	
	Plane(double transform[4][4],Material *m): GeoObject(transform, m)
	{
		normal_point[0] = 0;
		normal_point[1] = 0;
		normal_point[2] = 1;
		
		x_distance_point[0] = 1;
		x_distance_point[1] = 0;
		x_distance_point[2] = 0;
		
		y_distance_point[0] = 0;
		y_distance_point[1] = 1;
		y_distance_point[2] = 0;
		
		double ans[3];
		
		mat_mult4x1(transform,center,ans);
		copy(ans,center);
		
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
		subtract(normal_point,center_point,ans);
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
	
	Sphere(double transform[4][4],Material *m): GeoObject(transform, m)
	{
		
	}
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans) 
	{
		subtract(loc,center,ans);
		normalize(ans,ans);
	}
	
private:

	double radius;
};

/*
	The Tetrahedron class is a subclass of GeoObject. It represents a regular four faced polyhedron with triangular faces.
*/
class Tetrahedron: public GeoObject
{
public:
	
	Tetrahedron(double transform[4][4],Material *m): GeoObject(transform, m);
	
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
	
	Dodecahedron(double transform[4][4],Material *m): GeoObject(transform, m);
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans);
	
private:
	
	double vertexes[20][3];
	double normals[12][3];
	int faces[12][5];
	double length;	
};

