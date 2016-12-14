#include "GeoObject.h"
#include <iostream>
#include <math.h>
#include <cmath>

using std::abs;
using std::cout;
using std::endl;

void Plane::hit(Ray *r, double intersect[3])
{
	double normal[3];
	getNormal(NULL,normal);
	
	double denom = dotProduct(r->getDirection(),normal);
	
	if(denom==0)
	{
		double* source = r->getSource();
		copy(source,intersect);
		return;
	}
	
	double ans[3];
	subtract(center,r->getSource(),ans);
	
	double t = (dotProduct(ans,normal))/denom;
	
	if(t<0)
	{
		double* source = r->getSource();
		copy(source,intersect);
		return;
	}

	multiply(t,r->getDirection(),ans);
	add(ans,r->getSource(),intersect);
	
	double intersect_vector[3];
	double x_vector[3],y_vector[3];
	
	subtract(x_distance_point,center,x_vector);
	subtract(y_distance_point,center,y_vector);
	subtract(intersect,center,intersect_vector);
	
	double x_distance = magnitude(x_vector);
	double y_distance = magnitude(y_vector);
	
	normalize(x_vector,x_vector);
	normalize(y_vector,y_vector);
	
	if(std::abs(dotProduct(intersect_vector,x_vector))>x_distance || std::abs(dotProduct(intersect_vector,y_vector))>y_distance)
	{
		double* source = r->getSource();
		copy(source,intersect);
	}
} 

void Sphere::hit(Ray *r,double intersect[3])
{
	double dir[3];
	
	double ans[3];
	subtract(radius_point,center,ans);
	double radius = magnitude(ans);
	
	subtract(center,r->getSource(),dir);
	//cout << "dir " << dir[0] << " " << dir[1] << " " << dir[2] << endl;
	
	double dist = pow(pow(dir[0],2)+pow(dir[1],2)+pow(dir[2],2),0.5);
	
	double x = pow(pow(dist,2)-pow(dotProduct(dir,r->getDirection()),2),0.5);

	if(x>radius)
	{
		double* source = r->getSource();
		intersect[0] = source[0];
		intersect[1] = source[1];
		intersect[2] = source[2];
		return;
	}
	
	double y = pow(pow(radius,2)-pow(x,2),0.5);
	double d = pow(pow(dist,2)-pow(x,2),0.5);
	
	double intArm[3];
	multiply(d-y,r->getDirection(),intArm);
	add(intArm,r->getSource(),intersect);
	
	if(x==0) 
	{
		cout << "X = 0" << endl;
		cout << "Arm " << (d-y) << endl;
	}
	
	return;
}

Tetrahedron::Tetrahedron(std::string name,double transform[4][4],Material *m): GeoObject(name,transform, m)
{	
	vertexes[0][0] = 1;
	vertexes[0][1] = 0;
	vertexes[0][2] = -1/pow(2,0.5);
	
	vertexes[1][0] = -1;
	vertexes[1][1] = 0;
	vertexes[1][2] = -1/pow(2,0.5);
	
	vertexes[2][0] = 0;
	vertexes[2][1] = 1;
	vertexes[2][2] = 1/pow(2,0.5);
	
	vertexes[3][0] = 0;
	vertexes[3][1] = -1;
	vertexes[3][2] = 1/pow(2,0.5);
	
	
	double ans[3];
	
	mat_mult4x1(transform,vertexes[0],ans);
	copy(ans,vertexes[0]);
	
	mat_mult4x1(transform,vertexes[1],ans);
	copy(ans,vertexes[1]);
	
	mat_mult4x1(transform,vertexes[2],ans);
	copy(ans,vertexes[2]);
	
	mat_mult4x1(transform,vertexes[3],ans);
	copy(ans,vertexes[3]);
	
	
	subtract(center,vertexes[0],normals[0]);
	normalize(normals[0],normals[0]);
	
	subtract(center,vertexes[1],normals[1]);
	normalize(normals[1],normals[1]);
	
	subtract(center,vertexes[2],normals[2]);
	normalize(normals[2],normals[2]);
	
	subtract(center,vertexes[3],normals[3]);
	normalize(normals[3],normals[3]);
}

void Tetrahedron::hit(Ray *r, double *intersect)
{
	double beta, gamma, t, det, bottom, minDis = 100000;
	double* s = r->getSource();
	double* d = r->getDirection();
	
	double v[3][3];
	
	for(int i=0;i<4;i++)
	{
		v[0][0] = s[0]-vertexes[i][0];
		v[0][1] = vertexes[(i+2)%4][0]-vertexes[i][0];
		v[0][2] = -d[0];
		
		v[1][0] = s[1]-vertexes[i][1];
		v[1][1] = vertexes[(i+2)%4][1]-vertexes[i][1];
		v[1][2] = -d[1];
		
		v[2][0] = s[2]-vertexes[i][2];
		v[2][1] = vertexes[(i+2)%4][2]-vertexes[i][2];
		v[2][2] = -d[2];
		
		det = determinant3(v);
		
		v[0][0] = vertexes[(i+1)%4][0]-vertexes[i][0];
		v[1][0] = vertexes[(i+1)%4][1]-vertexes[i][1];
		v[2][0] = vertexes[(i+1)%4][2]-vertexes[i][2];
		
		bottom = determinant3(v);
		
		beta = det/bottom;
		
		v[0][1] = s[0]-vertexes[i][0];
		v[1][1] = s[1]-vertexes[i][1];
		v[2][1] = s[2]-vertexes[i][2];
		
		gamma = determinant3(v)/bottom;
		
		v[0][1] = vertexes[(i+2)%4][0]-vertexes[i][0];
		v[1][1] = vertexes[(i+2)%4][1]-vertexes[i][1];
		v[2][1] = vertexes[(i+2)%4][2]-vertexes[i][2];
		
		v[0][2] = s[0]-vertexes[i][0];
		v[1][2] = s[1]-vertexes[i][1];
		v[2][2] = s[2]-vertexes[i][2];
		
		t = determinant3(v)/bottom;
		
		if(beta>=0 && gamma>=0 && beta+gamma<=1 && t<minDis)
		{
			minDis = t;
			intersect[0] = vertexes[i][0]+beta*(vertexes[(i+1)%4][0]-vertexes[i][0])+gamma*(vertexes[(i+2)%4][0]-vertexes[i][0]);
			intersect[1] = vertexes[i][1]+beta*(vertexes[(i+1)%4][1]-vertexes[i][1])+gamma*(vertexes[(i+2)%4][1]-vertexes[i][1]);
			intersect[2] = vertexes[i][2]+beta*(vertexes[(i+1)%4][2]-vertexes[i][2])+gamma*(vertexes[(i+2)%4][2]-vertexes[i][2]);
		}
	}
	
	if(minDis==100000)
	{
		intersect[0] = s[0];
		intersect[1] = s[1];
		intersect[2] = s[2];
	}
}

void Tetrahedron::getNormal(double *loc, double *ans)
{
	double beta, gamma, z;
		
	for(int i=0;i<4;i++)
	{
		gamma = (loc[1]-vertexes[i][1]-(loc[0]-vertexes[i][0])*(vertexes[(i+1)%4][1]-vertexes[i][1])/(vertexes[(i+1)%4][0]-vertexes[i][0]))/(vertexes[(i+2)%4][1]-vertexes[i][1]-(vertexes[(i+2)%4][0]-vertexes[i][0])*(vertexes[(i+1)%4][1]-vertexes[i][1])/(vertexes[(i+1)%4][0]-vertexes[i][0]));
	
		beta = (loc[0]-vertexes[i][0]-gamma*(vertexes[(i+2)%4][0]-vertexes[i][0]))/(vertexes[(i+1)%4][0]-vertexes[i][0]);
	
		z = vertexes[i][2]+beta*(vertexes[(i+1)%4][2]-vertexes[i][2])+gamma*(vertexes[(i+2)%4][2]-vertexes[i][2]);
	
		// check z verses loc[2]
		if(abs(z-loc[2])<0.01)
		{
			ans[0] = normals[(i+3)%4][0];
			ans[1] = normals[(i+3)%4][1];
			ans[2] = normals[(i+3)%4][2];
		
			return;
		}
	}
	
	ans[0] = 0;
	ans[1] = 0;
	ans[2] = 0;
}

Dodecahedron::Dodecahedron(std::string name,double transform[4][4],Material *m): GeoObject(name,transform, m)
{
	double phi = (1+pow(5,0.5))/2;	
	
	vertexes[0][0] = 1;
	vertexes[0][1] = 1;
	vertexes[0][2] = 1;
	
	vertexes[1][0] = -1;
	vertexes[1][1] = 1;
	vertexes[1][2] = 1;
	
	vertexes[2][0] = 1;
	vertexes[2][1] = -1;
	vertexes[2][2] = 1;
	
	vertexes[3][0] = -1;
	vertexes[3][1] = -1;
	vertexes[3][2] = 1;
	
	vertexes[4][0] = 1;
	vertexes[4][1] = 1;
	vertexes[4][2] = -1;
	
	vertexes[5][0] = -1;
	vertexes[5][1] = 1;
	vertexes[5][2] = -1;
	
	vertexes[6][0] = 1;
	vertexes[6][1] = -1;
	vertexes[6][2] = -1;
	
	vertexes[7][0] = -1;
	vertexes[7][1] = -1;
	vertexes[7][2] = -1;
	
	vertexes[8][0] = 0;
	vertexes[8][1] = 1/phi;
	vertexes[8][2] = phi;
	
	vertexes[9][0] = 0;
	vertexes[9][1] = -1/phi;
	vertexes[9][2] = phi;
	
	vertexes[10][0] = 0;
	vertexes[10][1] = 1/phi;
	vertexes[10][2] = -phi;
	
	vertexes[11][0] = 0;
	vertexes[11][1] = -1/phi;
	vertexes[11][2] = -phi;
	
	vertexes[12][0] = 1/phi;
	vertexes[12][1] = phi;
	vertexes[12][2] = 0;
	
	vertexes[13][0] = -1/phi;
	vertexes[13][1] = phi;
	vertexes[13][2] = 0;
	
	vertexes[14][0] = 1/phi;
	vertexes[14][1] = -phi;
	vertexes[14][2] = 0;
	
	vertexes[15][0] = -1/phi;
	vertexes[15][1] = -phi;
	vertexes[15][2] = 0;
	
	vertexes[16][0] = phi;
	vertexes[16][1] = 0;
	vertexes[16][2] = 1/phi;
	
	vertexes[17][0] = phi;
	vertexes[17][1] = 0;
	vertexes[17][2] = -1/phi;
	
	vertexes[18][0] = -phi;
	vertexes[18][1] = 0;
	vertexes[18][2] = 1/phi;
	
	vertexes[19][0] = -phi;
	vertexes[19][1] = 0;
	vertexes[19][2] = -1/phi;
	
	double ans[3];
	for(int i=0;i<20;i++)
	{
		mat_mult4x1(transform,vertexes[i],ans);
		copy(ans,vertexes[i]);
	}
	
	faces[0][0] = 0;
	faces[0][1] = 12;
	faces[0][2] = 13;
	faces[0][3] = 1;
	faces[0][4] = 8;
	
	faces[1][0] = 0;
	faces[1][1] = 12;
	faces[1][2] = 4;
	faces[1][3] = 17;
	faces[1][4] = 16;
	
	faces[2][0] = 4;
	faces[2][1] = 12;
	faces[2][2] = 13;
	faces[2][3] = 5;
	faces[2][4] = 10;
	
	faces[3][0] = 1;
	faces[3][1] = 13;
	faces[3][2] = 5;
	faces[3][3] = 19;
	faces[3][4] = 18;
	
	faces[4][0] = 14;
	faces[4][1] = 15;
	faces[4][2] = 3;
	faces[4][3] = 9;
	faces[4][4] = 2;
	
	faces[5][0] = 0;
	faces[5][1] = 8;
	faces[5][2] = 9;
	faces[5][3] = 2;
	faces[5][4] = 16;
	
	faces[6][0] = 1;
	faces[6][1] = 8;
	faces[6][2] = 9;
	faces[6][3] = 3;
	faces[6][4] = 18;
	
	faces[7][0] = 2;
	faces[7][1] = 16;
	faces[7][2] = 17;
	faces[7][3] = 6;
	faces[7][4] = 14;
	
	faces[8][0] = 7;
	faces[8][1] = 19;
	faces[8][2] = 18;
	faces[8][3] = 3;
	faces[8][4] = 15;
	
	faces[9][0] = 6;
	faces[9][1] = 11;
	faces[9][2] = 7;
	faces[9][3] = 15;
	faces[9][4] = 14;
	
	faces[10][0] = 10;
	faces[10][1] = 11;
	faces[10][2] = 7;
	faces[10][3] = 19;
	faces[10][4] = 5;
	
	faces[11][0] = 10;
	faces[11][1] = 11;
	faces[11][2] = 6;
	faces[11][3] = 17;
	faces[11][4] = 4;
	
	for(int i=0;i<12;i++)
	{
		double vec1[3],vec2[3];
		
		subtract(vertexes[faces[i][1]],vertexes[faces[i][0]],vec1);
		subtract(vertexes[faces[i][2]],vertexes[faces[i][0]],vec2);
		
		crossProduct3(vec1,vec2,normals[i]);
		
		subtract(vertexes[faces[i][0]],center,vec1);
		
		normalize(normals[i],normals[i]);
		normalize(vec1,vec1);
		
		if(dotProduct(vec1,normals[i])<0)
		{
			normals[i][0] = -normals[i][0];
			normals[i][1] = -normals[i][1];
			normals[i][2] = -normals[i][2];
		}
	}
}

void Dodecahedron::hit(Ray* r,double intersect[3])
{
	double beta, gamma, t, det, bottom, minDis = 100000;
	double* s = r->getSource();
	double* d = r->getDirection();
	
	double v[3][3];
	
	for(int i=0;i<12;i++)
	{
		for(int j=1;j<4;j++)
		{
			// i+2 = j, i+1 = j+1
			v[0][0] = s[0]-vertexes[faces[i][0]][0];
			v[0][1] = vertexes[faces[i][j]][0]-vertexes[faces[i][0]][0];
			v[0][2] = -d[0];
			
			v[1][0] = s[1]-vertexes[faces[i][0]][1];
			v[1][1] = vertexes[faces[i][j]][1]-vertexes[faces[i][0]][1];
			v[1][2] = -d[1];
			
			v[2][0] = s[2]-vertexes[faces[i][0]][2];
			v[2][1] = vertexes[faces[i][j]][2]-vertexes[faces[i][0]][2];
			v[2][2] = -d[2];
			
			det = determinant3(v);
			
			v[0][0] = vertexes[faces[i][j+1]][0]-vertexes[faces[i][0]][0];
			v[1][0] = vertexes[faces[i][j+1]][1]-vertexes[faces[i][0]][1];
			v[2][0] = vertexes[faces[i][j+1]][2]-vertexes[faces[i][0]][2];
			
			bottom = determinant3(v);
			
			beta = det/bottom;
			
			v[0][1] = s[0]-vertexes[faces[i][0]][0];
			v[1][1] = s[1]-vertexes[faces[i][0]][1];
			v[2][1] = s[2]-vertexes[faces[i][0]][2];
			
			gamma = determinant3(v)/bottom;
			
			v[0][1] = vertexes[faces[i][j]][0]-vertexes[faces[i][0]][0];
			v[1][1] = vertexes[faces[i][j]][1]-vertexes[faces[i][0]][1];
			v[2][1] = vertexes[faces[i][j]][2]-vertexes[faces[i][0]][2];
			
			v[0][2] = s[0]-vertexes[faces[i][0]][0];
			v[1][2] = s[1]-vertexes[faces[i][0]][1];
			v[2][2] = s[2]-vertexes[faces[i][0]][2];
			
			t = determinant3(v)/bottom;
			
			if(beta>=0 && gamma>=0 && beta+gamma<=1 && t<minDis)
			{
				minDis = t;
				intersect[0] = vertexes[faces[i][0]][0]+beta*(vertexes[faces[i][j+1]][0]-vertexes[faces[i][0]][0])+gamma*(vertexes[faces[i][j]][0]-vertexes[faces[i][0]][0]);
				intersect[1] = vertexes[faces[i][0]][1]+beta*(vertexes[faces[i][j+1]][1]-vertexes[faces[i][0]][1])+gamma*(vertexes[faces[i][j]][1]-vertexes[faces[i][0]][1]);
				intersect[2] = vertexes[faces[i][0]][2]+beta*(vertexes[faces[i][j+1]][2]-vertexes[faces[i][0]][2])+gamma*(vertexes[faces[i][j]][2]-vertexes[faces[i][0]][2]);
			}
		}
	}
	
	if(minDis==100000)
	{
		intersect[0] = s[0];
		intersect[1] = s[1];
		intersect[2] = s[2];
	}
}

void Dodecahedron::getNormal(double loc[3], double ans[3])
{
	double dis;
		
	for(int i=0;i<12;i++)
	{
		dis = abs(normals[i][0]*(vertexes[faces[i][0]][0]-loc[0])+normals[i][1]*(vertexes[faces[i][0]][1]-loc[1])+normals[i][2]*(vertexes[faces[i][0]][2]-loc[2]))/pow(pow(normals[i][0],2)+pow(normals[i][1],2)+pow(normals[i][2],2),0.5);
		
		if(dis<0.01)
		{
			ans[0] = normals[i][0];
			ans[1] = normals[i][1];
			ans[2] = normals[i][2];
			
			return;
		}
	}
	
	ans[0] = 0;
	ans[1] = 0;
	ans[2] = 0;
}