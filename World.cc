#include "World.h"
#include "image.h"
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

World::World()
{
	ambientLight = new double[3];
	ambientLight[0] = 20;
	ambientLight[1] = 20;
	ambientLight[2] = 20;
	
	// ****************Scene: Light Color********************
	/*
	double* sourceR = new double[3];  
	double* diffuceR = new double[3]; 
	double* specularR = new double[3]; 
	
	sourceR[0] = 6;
	sourceR[1] = -4;
	sourceR[2] = 6;
	
	diffuceR[0] = 0.0;
	diffuceR[1] = 0.0;
	diffuceR[2] = 1.0;
	
	specularR[0] = 0.0;
	specularR[1] = 0.0;
	specularR[2] = 0.3;
	
	Light* lightR = new Light(sourceR,diffuceR,specularR);
	
	double* sourceG = new double[3];  
	double* diffuceG = new double[3]; 
	double* specularG = new double[3]; 
	
	sourceG[0] = 6;
	sourceG[1] = 0;
	sourceG[2] = 6;
	
	diffuceG[0] = 0.0;
	diffuceG[1] = 1.0;
	diffuceG[2] = 0.0;
	
	specularG[0] = 0.0;
	specularG[1] = 0.3;
	specularG[2] = 0.0;
	
	Light* lightG = new Light(sourceG,diffuceG,specularG);
	
	double* sourceB = new double[3];  
	double* diffuceB = new double[3]; 
	double* specularB = new double[3]; 
	
	sourceB[0] = 6;
	sourceB[1] = 4;
	sourceB[2] = 6;
	
	diffuceB[0] = 1.0;
	diffuceB[1] = 0.0;
	diffuceB[2] = 0.0;
	
	specularB[0] = 0.3;
	specularB[1] = 0.0;
	specularB[2] = 0.0;
	
	Light* lightB = new Light(sourceB,diffuceB,specularB);
	
	lights.push_front(lightB);
	lights.push_front(lightR);
	lights.push_front(lightG);
	
	
	double* rd = new double[3];
	double* rs = new double[3];
	
	rd[0] = 200;
	rd[1] = 200;
	rd[2] = 200;
	
	rs[0] = 100;
	rs[1] = 100;
	rs[2] = 100;
	
	double* cd = new double[3];
	double* cs = new double[3];
	
	cd[0] = 100;
	cd[1] = 100;
	cd[2] = 100;
	
	cs[0] = 1;
	cs[1] = 1;
	cs[2] = 1;
	
	Material* red = new Material(rd,rs);
	Material* cyan = new Material(cd,cs);
	
	double* cord = new double[3];
	cord[0] = 0;
	cord[1] = 0;
	cord[2] = 0;
	
	double* normal = new double[3];
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 1;
	
	Plane *p = new Plane(cord,normal,cyan);
	
	double* center = new double[3];
	center[0] = 6;
	center[1] = 0;
	center[2] = 3;
	
	Sphere *s = new Sphere(center,2,red);
	
	obj.push_front(p);
	obj.push_front(s);
	*/
	
	// ***************Scene: Three Objects*****************
	
	double* source = new double[3];  
	double* diffuce = new double[3]; 
	double* specular = new double[3]; 
	
	source[0] = 2;
	source[1] = -2;
	source[2] = 6;
	
	diffuce[0] = 0.7;
	diffuce[1] = 0.7;
	diffuce[2] = 0.7;
	
	specular[0] = 0.3;
	specular[1] = 0.3;
	specular[2] = 0.3;
	
	Light* light = new Light(source,diffuce,specular);
	
	lights.push_front(light);
	
	double* rd = new double[3];
	double* rs = new double[3];
	
	rd[0] = 50;
	rd[1] = 50;
	rd[2] = 200;
	
	rs[0] = 100;
	rs[1] = 100;
	rs[2] = 100;
	
	double* cd = new double[3];
	double* cs = new double[3];
	
	cd[0] = 200;
	cd[1] = 200;
	cd[2] = 50;
	
	cs[0] = 1;
	cs[1] = 1;
	cs[2] = 1;
	
	double* yd = new double[3];
	double* ys = new double[3];
	
	yd[0] = 50;
	yd[1] = 200;
	yd[2] = 200;
	
	ys[0] = 1;
	ys[1] = 1;
	ys[2] = 1;
	
	double* gd = new double[3];
	double* gs = new double[3];
	
	gd[0] = 50;
	gd[1] = 200;
	gd[2] = 50;
	
	gs[0] = 1;
	gs[1] = 1;
	gs[2] = 1;
	
	Material* red = new Material(rd,rs);
	Material* cyan = new Material(cd,cs);
	Material* yellow = new Material(yd,ys);
	Material* green = new Material(gd,gs);
	
	double* cord = new double[3];
	cord[0] = 0;
	cord[1] = 0;
	cord[2] = 0;
	
	double* normal = new double[3];
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 1;
	
	Plane *p = new Plane(cord,normal,cyan);
	
	double* center = new double[3];
	center[0] = 6;
	center[1] = 0;
	center[2] = 3;
	
	Sphere *s = new Sphere(center,1.5,red);
	
	double* center2 = new double[3];
	center2[0] = 6;
	center2[1] = 7;
	center2[2] = 3;
	
	Tetrahedron *t = new Tetrahedron(center2,2,yellow);
	
	double* center3 = new double[3];
	center3[0] = 6;
	center3[1] = -7;
	center3[2] = 3;
	
	Dodecahedron *d = new Dodecahedron(center3,2,green);
	
	obj.push_front(p);
	obj.push_front(s);
	obj.push_front(t);
	obj.push_front(d);
	
}

void World::drawImage(std::string name, int width, int height, double eye [], double distance, double pitch, double yaw, double roll) 
{
	cout << "starting image" << endl;
		
	Image output(height,width,3);
	Ray *ray;
	
	double direction[3];

	/*double Rx [3][3] = {{1,0,0},{0,cos(roll),-sin(roll)},{0,sin(roll),cos(roll)}};
	double Ry [3][3] = {{cos(pitch),0,sin(pitch)},{0,1,0},{-sin(pitch),0,cos(pitch)}};
	double Rz [3][3] = {{cos(yaw),-sin(yaw),0},{sin(yaw),cos(yaw),0},{0,0,1}};
	
	double temp[3][3];
	double R [3][3]; 
	
	mat_mult3x3(Rz,Ry,temp);
	mat_mult3x3(temp,Rx,R);*/
	
	direction[0] = 1;//R[0][2];
	direction[1] = 0;//R[1][2];
	direction[2] = 0;//R[2][2];
	
	//double R_inv [3][3];
	//transpose3(R,R_inv);
	
	
	double cen [3];
	multiply(distance,direction,cen);
	add(cen,eye,cen);
	
	cout << "starting to find pixels" << endl;
	
	for (int i = 0; i < output.getRows(); i++) 
	{
		for(int j = 0; j < output.getCols(); j++) 
		{
			
			double disHigh = (i-(double)(height/2.0))*pixel_to_unit;
			double disAcross = (j-(double)(width/2.0))*pixel_to_unit;
			double cord [3] = {disAcross,disHigh,0};
			
			//double temp2[3];
			//mat_mult3x1(R_inv,cord,temp2);
			
			cord[0] = cen[0];//temp2[0];
			cord[1] = cen[1]+disAcross;//temp2[1];
			cord[2] = cen[2]+disHigh;//temp2[2];
			
			double* dir = new double[3]; 
			subtract(cord,eye,dir);
			
			ray = new Ray(eye,dir);
			unsigned char* pixel = new unsigned char[3];
			
			//cout << "High: " << disHigh << "   Across: " << disAcross << endl;
			//cout << "Dir: " << dir[0] << " " << dir[1] << " " << dir[2] << endl;
			
			raytrace(ray,pixel);
			
			output.putPixel(i,j,2,pixel[2]);
			output.putPixel(i,j,1,pixel[1]);
			output.putPixel(i,j,0,pixel[0]);
			
			delete [] pixel;
			delete [] dir;
		}
	}
	
	cout << "found pixels" << endl;
	
	name.append(".png");
	output.write_png(name);
	
	cout << "Created Image";
}

unsigned char* World::raytrace(Ray* ray, unsigned char* pixel)
{
	//cout << "starting raytrace" << endl;
		
	double minDist = 100000;
	double *point,*finalPoint = new double[3];
	GeoObject* hitObject;
	
	
	for(it = obj.begin(); it!=obj.end(); it++)
	{
		point = new double[3];
		double* ans = new double[3];
		
		(*it)->hit(ray,point);
		
		subtract(point,ray->getSource(),ans);
		
		double dist = magnitude(ans);
		
		if(dist>0 && dist<minDist)
		{
			minDist = dist;
			hitObject = *it;
			
			finalPoint[0] = point[0];
			finalPoint[1] = point[1];
			finalPoint[2] = point[2];
		}
		
		delete [] point;
		delete [] ans;
	}
	
	//cout << "found intersect" << endl;
	
	if(minDist<100000)
	{
		double tot_l_d[3];
		double tot_l_s[3];
		
		tot_l_d[0] = 0;
		tot_l_d[1] = 0;
		tot_l_d[2] = 0;
		
		tot_l_s[0] = 0;
		tot_l_s[1] = 0;
		tot_l_s[2] = 0;
		//cout << "finding intersect info" << endl;
		//bool colored = false;
		
		Material* mat = hitObject->getMaterial();
		double* m_diffuse = mat->getDiffuse();
		double* m_specular = mat->getSpecular();
		
		double* normal = new double[3];
		hitObject->getNormal(finalPoint,normal);
		normalize(normal,normal);
		
		int i=0;
		
		for(lit = lights.begin();lit != lights.end();lit++)
		{
			double* l_diffuse = (*lit)->getDiffuse();
			double* l_specular = (*lit)->getSpecular();
			
			double* lightVector = new double[3];
			subtract((*lit)->getSource(),finalPoint,lightVector);
			
			double distance = magnitude(lightVector);
			normalize(lightVector,lightVector);
			
			Ray* r = new Ray(finalPoint,lightVector);
			bool blocked = false;
			
			for(it = obj.begin(); it!=obj.end(); it++)
			{
				if(hitObject!=*it)
				{
					point = new double[3];
					double* ans = new double[3];
				
					(*it)->hit(r,point);
					
					subtract(point,r->getSource(),ans);
					
					double dist = magnitude(ans);
					
					normalize(ans,ans);
					
					double dot = (dotProduct(ans,lightVector)); 

					if(dist>0 && dist<distance && dotProduct(ans,lightVector)>0)
					{
						blocked = true;
						delete [] point;
						delete [] ans;
						break;
					}
					
					delete [] point;
					delete [] ans;
				}
			}
			
			//double dot = dotProduct(normal,lightVector);
			//cout << dot << endl;
			
			if(!blocked)
			{
				double* ref = new double[3];
				multiply(2*dotProduct(lightVector,normal),normal,ref);
				subtract(ref,lightVector,ref);
				normalize(ref,ref);
				
				double* view = new double[3];
				subtract(ray->getSource(),finalPoint,view);
				normalize(view,view);
				
				double specCom = pow(std::max(0.0,dotProduct(ref,view)),specular_ex);
				double difCom = std::max(0.0,dotProduct(normal,lightVector));
				
				//cout << "SpecCom " << specCom << endl;
				
				//cout << "DifCom " << difCom << endl;
				
				tot_l_d[0] += l_diffuse[0]*difCom;
				tot_l_d[1] += l_diffuse[1]*difCom;
				tot_l_d[2] += l_diffuse[2]*difCom;
				
				tot_l_s[0] += l_specular[0]*specCom;
				tot_l_s[1] += l_specular[1]*specCom;
				tot_l_s[2] += l_specular[2]*specCom;
				//colored = true;
				
				//cout << "Light for " << i << " " << tot_l_d[0] << " " << tot_l_d[1] << " " << tot_l_d[2] << endl;
				//i++;
			}
			
			delete [] lightVector;
			delete r;
		}
		
		delete [] normal;
		
		pixel[0] = static_cast<unsigned char>(std::min(255.0,(ambientLight[0]+m_diffuse[0]*tot_l_d[0]+m_specular[0]*tot_l_s[0])));
		pixel[1] = static_cast<unsigned char>(std::min(255.0,(ambientLight[1]+m_diffuse[1]*tot_l_d[1]+m_specular[1]*tot_l_s[1])));
		pixel[2] = static_cast<unsigned char>(std::min(255.0,(ambientLight[2]+m_diffuse[2]*tot_l_d[2]+m_specular[2]*tot_l_s[2])));
		//if(!colored)
		//{
			
		//}
		
	}
	else
	{
		pixel[0] = static_cast<unsigned char>(ambientLight[0]);
		pixel[1] = static_cast<unsigned char>(ambientLight[1]);
		pixel[2] = static_cast<unsigned char>(ambientLight[2]);
	}
	
	delete [] finalPoint;
}