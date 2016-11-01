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
	
	virtual double* hit(Ray* r,double* intersect) { 	return intersect; }

	virtual double* getNormal(double* loc,double* ans) { return ans; } 
	
	Material* getMaterial() { return mat;}
	
protected:
	
	double *center;
	Material *mat;
	
};


/*
	The Plane object is a subclass of GeoObject. It represents a flat plane
*/
class Plane : public GeoObject
{
public:
	
	Plane(double* cord,double* n,Material* m)
	{
		mat = m;
		normal = new double[3];
		normalize(n,normal);
		center = cord;
		
		delete [] n;
	}
	
	double* hit(Ray* r,double* intersect);
	
	double* getNormal(double* loc,double* ans) 
	{
		ans[0] = normal[0];
		ans[1] = normal[1];
		ans[2] = normal[2];
		
		return ans;
	}
	
	~Plane()
	{
		delete [] center;
		delete mat;
		delete [] normal;
	}
	
private:
	
	double* normal;
};

/*
	The Sphere class is a subclass of GeoObject. It represents a sphere.
*/
class Sphere: public GeoObject
{
public:
	
	Sphere(double* cen,double r,Material* m)
	{
		center = cen;
		radius = r;
		mat = m;
	}
	
	double* hit(Ray* r,double* intersect);
	
	double* getNormal(double* loc,double* ans) 
	{
		subtract(loc,center,ans);
		normalize(ans,ans);
		
		return ans;
	}
	
	~Sphere()
	{
		delete [] center;
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
	
	Tetrahedron(double* cen,double l,Material* m);
	
	double* hit(Ray* r,double* intersect);
	
	double* getNormal(double* loc,double* ans);
	
	~Tetrahedron()
	{
		delete [] vertexes[0];
		delete [] vertexes[1];
		delete [] vertexes[2];
		delete [] vertexes[3];
		delete [] vertexes;
		delete [] normals[0];
		delete [] normals[1];
		delete [] normals[2];
		delete [] normals[3];
		delete [] normals;
		delete [] center;
		delete mat;
	}
	
private:
	
	double** vertexes;
	double** normals;
	double length;
};

/*
	The Dodecahedron class is a subclass of GeoObject. It represents a regular twelve faced polyhedron with pentagonal faces.
*/
class Dodecahedron: public GeoObject
{
public:
	
	Dodecahedron(double* cen,double l,Material* m);
	
	double* hit(Ray* r,double* intersect);
	
	double* getNormal(double* loc,double* ans);
	
	~Dodecahedron()
	{
		for(int i=0;i<20;i++)
		{
			delete [] vertexes[i];
		}
		for(int i=0;i<12;i++)
		{
			delete [] faces[i];
			delete [] normals[i];
		}
		delete [] vertexes;
		delete [] faces;
		delete [] normals;
		delete [] center;
		delete mat;
	}
	
private:
	
	double** vertexes;
	double** normals;
	int** faces;
	double length;	
};

