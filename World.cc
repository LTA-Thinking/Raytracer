#include "World.h"
#include "image.h"
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

World::World(std::string path)
{
		// load scene data from file
}

void World::drawImage(std::string image_name, std::string camera_name) 
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