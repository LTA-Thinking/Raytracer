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

	GeoObject(std::string name, std::string t, double trans[4][4], double max, Material *m);

	double* getCenter() { return center; }
	
	virtual void hit(Ray* r,double intersect[3]) {}

	virtual void getNormal(double loc[3],double ans[3]) {} 
	
	virtual void setTransform(double t[4][4]) 
	{
		copy4x4(t,transform);
		
		double ans[3];
		
		mat_mult4x1(transform,base_center,ans);
		copy(ans,center);
		
		mat_mult4x1(transform,base_max,ans);
		copy(ans,max_radius);
	}
	
	void appendTransform(double t[4][4])
	{
		double ans[4][4];
		mat_mult4x4(t,transform,ans);
		
		setTransform(ans);
	}
	
	int couldHit(Ray* r);
	
	Material* getMaterial() { return mat;}
	
	std::string getName() {return obj_name;}
	
	std::string getType() {return type;}
	
	double* getTransform0(){return transform[0];}
	double* getTransform1(){return transform[1];}
	double* getTransform2(){return transform[2];}
	double* getTransform3(){return transform[3];}
	
	~GeoObject()
	{
		delete mat;
	}
	
protected:
	
	double base_max[3];
	double max_radius[3];
	
	double base_center[3];
	double center[3];
	
	double transform[4][4];
	Material *mat;
	std::string obj_name;
	std::string type;
	
};


/*
	The Plane object is a subclass of GeoObject. It represents a flat plane
*/
class Plane : public GeoObject
{
public:
	
	Plane(std::string name,double transform[4][4],Material *m): GeoObject(name,"PLANE",transform, 1, m)
	{
		base_normal_point[0] = 0.0;
		base_normal_point[1] = 0.0;
		base_normal_point[2] = 1.0;
		
		base_x_point[0] = 1.0;
		base_x_point[1] = 0.0;
		base_x_point[2] = 0.0;
		
		base_y_point[0] = 0.0;
		base_y_point[1] = 1.0;
		base_y_point[2] = 0.0;
		
		double ans[3];
		
		mat_mult4x1(transform,base_normal_point,ans);
		copy(ans,normal_point);
		
		mat_mult4x1(transform,base_x_point,ans);
		copy(ans,x_distance_point);
		
		mat_mult4x1(transform,base_y_point,ans);
		copy(ans,y_distance_point);
	}
	
	void hit(Ray* r,double* intersect);
	
	void getNormal(double* loc,double* ans) 
	{
		subtract(normal_point,center,ans);
		normalize(ans,ans);
	}
	
	void setTransform(double t[4][4])
	{
		GeoObject::setTransform(t);
			
		double ans[3];
		
		mat_mult4x1(transform,base_normal_point,ans);
		copy(ans,normal_point);
		
		mat_mult4x1(transform,base_x_point,ans);
		copy(ans,x_distance_point);
		
		mat_mult4x1(transform,base_y_point,ans);
		copy(ans,y_distance_point);
	}
	
private:
	
	double base_normal_point[3];
	double base_x_point[3];
	double base_y_point[3];
	
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
	
	Sphere(std::string name,double transform[4][4],Material *m): GeoObject(name,"ELLIPSE",transform, 1, m)
	{
		base_radius[0] = 0.0;
		base_radius[1] = 0.0;
		base_radius[2] = 1.0;
		
		double ans[3];
		mat_mult4x1(transform,base_radius,ans);
		copy(ans,radius_point);
	}
	
	void hit(Ray* r,double intersect[3]);
	
	void getNormal(double loc[3],double ans[3]) 
	{
		subtract(loc,center,ans);
		normalize(ans,ans);
	}
	
	void setTransform(double t[4][4])
	{
		GeoObject::setTransform(t);
		
		double ans[3];
		
		mat_mult4x1(transform,base_radius,ans);
		copy(ans,radius_point);
		
	}
	
private:

	double base_radius[3];
	double radius_point[3];
};

/*
	The Tetrahedron class is a subclass of GeoObject. It represents a regular four faced polyhedron with triangular faces.
*/
class Tetrahedron: public GeoObject
{
public:
	
	Tetrahedron(std::string name,double transform[4][4],Material *m);
	
	void hit(Ray* r,double intersect[3]);
	
	void getNormal(double loc[3],double ans[3]);
	
	void setTransform(double t[4][4]);
	
private:
	
	double base_vertexes[4][3];
	
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
	
	void setTransform(double t[4][4]);
	
private:
	
	double base_vertexes[20][3];
	
	double vertexes[20][3];
	double normals[12][3];
	int faces[12][5];
	double length;	
};

