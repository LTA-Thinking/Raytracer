#include "World.h"
#include "ClrFileOperations.h"
#include "image.h"
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

World::World(std::string path)
{
		loadClrFileForRaytrace(path,&materials,&obj,&lights,&cameras,ambientLight);
}

void World::drawImage(std::string image_name, std::string camera_name, int widthPixels) 
{
	cout << "starting image" << endl;
	
	Camera *main_camera;
	
	for(camera_it = cameras.begin(); camera_it!=cameras.end(); camera_it++)
	{
		if((*camera_it)->getName() == camera_name)
		{
			main_camera = *camera_it;
			break;
		}
	}
	
	for(obj_it = obj.begin();obj_it != obj.end();obj_it++)
	{
		printf("%s %s \n",(*obj_it)->getName().c_str(),(*obj_it)->getMaterial()->getName().c_str());
	}
		
	printf("%d %d %d %d \n",materials.size(),lights.size(),cameras.size(),obj.size());
	
	int heightPixels = (main_camera->getHeight()*widthPixels)/main_camera->getWidth();
	
	Image output(heightPixels,widthPixels,3);
	Ray *ray;
	
	double cen[3];
	copy(main_camera->getCenter(),cen);
	
	double eye[3];
	
	double direction[3];
	main_camera->getDirection(direction);	
	
	double distance = main_camera->getWidth()/(2*tan(main_camera->getAngle()/2));
	
	double eye_dir[3];
	
	copy(direction,eye_dir);
	multiply(-distance,eye_dir,eye_dir);
	add(cen,eye_dir,eye);
	
	printf("eye %f %f %f \n",eye[0],eye[1],eye[2]);
	cout << "starting to find pixels " << output.getRows() << " " << output.getCols() << endl;
	
	for (int i = 0; i < output.getRows(); i++) 
	{
		for(int j = 0; j < output.getCols(); j++) 
		{
			
			double cord [3];
			main_camera->screenCoordinate((double)i/widthPixels,(double)j/heightPixels,cord);
			
			double dir[3];
			subtract(cord,eye,dir);

			//printf("cord %f %f %f\n",cord[0],cord[1],cord[2]);
			//printf("dir %f %f %f\n",dir[0],dir[1],dir[2]);
			
			ray = new Ray(eye,dir);
			unsigned char pixel[3];
			
			raytrace(ray,pixel);
			
			output.putPixel(i,j,2,pixel[2]);
			output.putPixel(i,j,1,pixel[1]);
			output.putPixel(i,j,0,pixel[0]);
		}
	}
	
	cout << "found pixels" << endl;
	
	image_name.append(".png");
	output.write_png(image_name);
	
	cout << "Created Image";
}

void World::raytrace(Ray* ray, unsigned char pixel[3])
{
	double minDist = 100000;
	double finalPoint[3];
	GeoObject* hitObject;
	
	
	for(obj_it = obj.begin(); obj_it!=obj.end(); obj_it++)
	{
		double point[3];
		double ans[3];
		
		(*obj_it)->hit(ray,point);
		
		subtract(point,ray->getSource(),ans);
		
		double dist = magnitude(ans);
		
		if(dist>0 && dist<minDist)
		{
			minDist = dist;
			hitObject = *obj_it;
			
			finalPoint[0] = point[0];
			finalPoint[1] = point[1];
			finalPoint[2] = point[2];
		}
	}
	
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
		
		Material* mat = hitObject->getMaterial();
		double* m_diffuse = mat->getDiffuse();
		double* m_specular = mat->getSpecular();
		
		double normal[3];
		hitObject->getNormal(finalPoint,normal);
		normalize(normal,normal);
		
		int i=0;
		
		for(light_it = lights.begin();light_it != lights.end();light_it++)
		{
			double* l_diffuse = (*light_it)->getDiffuce();
			double* l_specular = (*light_it)->getSpecular();
			
			double lightVector[3];
			subtract((*light_it)->getSource(),finalPoint,lightVector);
			
			double distance = magnitude(lightVector);
			normalize(lightVector,lightVector);
			
			Ray* r = new Ray(finalPoint,lightVector);
			bool blocked = false;
			
			for(obj_it = obj.begin(); obj_it!=obj.end(); obj_it++)
			{
				if(hitObject!=*obj_it)
				{
					double point[3];
					double ans[3];
				
					(*obj_it)->hit(r,point);
					
					subtract(point,r->getSource(),ans);
					
					double dist = magnitude(ans);
					
					normalize(ans,ans);
					
					double dot = (dotProduct(ans,lightVector)); 

					if(dist>0 && dist<distance && dotProduct(ans,lightVector)>0)
					{
						blocked = true;
						break;
					}
				}
			}
			
			if(!blocked)
			{
				double ref[3];
				multiply(2*dotProduct(lightVector,normal),normal,ref);
				subtract(ref,lightVector,ref);
				normalize(ref,ref);
				
				double view[3];
				subtract(ray->getSource(),finalPoint,view);
				normalize(view,view);
				
				double specCom = pow(std::max(0.0,dotProduct(ref,view)),SPECULAR_EXP);
				double difCom = std::max(0.0,dotProduct(normal,lightVector));
				
				tot_l_d[0] += l_diffuse[0]*difCom;
				tot_l_d[1] += l_diffuse[1]*difCom;
				tot_l_d[2] += l_diffuse[2]*difCom;
				
				tot_l_s[0] += l_specular[0]*specCom;
				tot_l_s[1] += l_specular[1]*specCom;
				tot_l_s[2] += l_specular[2]*specCom;
			}
			
			delete r;
		}
		
		pixel[0] = static_cast<unsigned char>(255*std::min(1.0,(ambientLight[0]+m_diffuse[0]*tot_l_d[0]+m_specular[0]*tot_l_s[0])));
		pixel[1] = static_cast<unsigned char>(255*std::min(1.0,(ambientLight[1]+m_diffuse[1]*tot_l_d[1]+m_specular[1]*tot_l_s[1])));
		pixel[2] = static_cast<unsigned char>(255*std::min(1.0,(ambientLight[2]+m_diffuse[2]*tot_l_d[2]+m_specular[2]*tot_l_s[2])));
	}
	else
	{
		pixel[0] = static_cast<unsigned char>(255*ambientLight[0]);
		pixel[1] = static_cast<unsigned char>(255*ambientLight[1]);
		pixel[2] = static_cast<unsigned char>(255*ambientLight[2]);
	}
}