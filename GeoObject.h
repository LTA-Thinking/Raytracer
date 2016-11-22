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

	double* getCenter() { return center; }
	
	virtual void hit(Ray* r,double* intersect) {}

	virtual void getNormal(double* loc,double* ans) {} 
	
	Material* getMaterial() { return mat;}
	
protected:
	
	double center[3];
	Material *mat;
	
};


/*
	The Plane object is a subclass of GeoObject. It represents a flat plane
*/
class Plane : public GeoObject
{
public:
	
	Plane(double[] cord,double[] n,Material* m)
	{
		mat = new Material(m);
		normalize(n,normal);
		center[0] = cord[0];
		center[1] = cord[1];
		center[2] = cord[2];
		
	}
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans) 
	{
		ans[0] = normal[0];
		ans[1] = normal[1];
		ans[2] = normal[2];
	}
	
	~Plane()
	{
		delete mat;
	}
	
private:
	
	double normal[3];
};

/*
	The Sphere class is a subclass of GeoObject. It represents a sphere.
*/
class Sphere: public GeoObject
{
public:
	
	Sphere(double[] cord,double r,Material* m)
	{
		radius = r;
		mat = new Material(m);
		center[0] = cord[0];
		center[1] = cord[1];
		center[2] = cord[2];
	}
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans) 
	{
		subtract(loc,center,ans);
		normalize(ans,ans);
	}
	
	~Sphere()
	{
		delete mat;
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
	
	Tetrahedron(double[] cord,double l,Material* m);
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans);
	
	~Tetrahedron()
	{
		delete mat;
	}
	
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
	
	Dodecahedron(double[] cen,double l,Material* m);
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans);
	
	~Dodecahedron()
	{
		delete mat;
	}
	
private:
	
	double vertexes[20][3];
	double normals[12][3];
	int faces[12][5];
	double length;	
};

