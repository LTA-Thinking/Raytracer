#include "GeoObject.h"
#include "ClrFileOperations.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

string substring(string s,int start,int end)
{
	return s.substr(start,end-start);
}

string substring(string s,int start)
{
	return s.substr(start);
}

string dtos(double d) // Thanks to stackoverflow use Adam Rosenfield for this code
{
	std::ostringstream sstream;
	sstream << d;
	string varAsString = sstream.str();
	
	return varAsString;
}

void loadClrFile(string filePath,list<Material*> *materials,list<GeoObject*> *objects,list<Light*> *lights,list<Camera*> *cameras,double ambientLight[3])
{
	//*******************************CHANGE THIS*******************************
	ambientLight[0] = 0.2;
	ambientLight[1] = 0.2;
	ambientLight[2] = 0.2;
	//************************************************************************
	
	string line;
	ifstream clrFile(filePath);
	int line_num = 0;
	
	if(clrFile.is_open())
	{
		string tag,mode = "";
		int tag_start;
		while( getline(clrFile,line))
		{
			line_num++;
			if((tag_start = line.find("<"))!=-1)
			{
				if(line.find("/") == tag_start+1)
					continue;
				
				int carot = line.find(">",tag_start);
				tag = substring(line,tag_start+1,carot);
				if(tag.find(' ')!=-1)
				{
					tag = substring(tag,0,tag.find(' '));
				}
				
				if(tag == "material")
				{
					//cout << "Loading material\n";
					
					double ambient[3],diffuse[3],specular[3];
					string name;
					
					for(int i=0;i<4;i++)
					{
						line_num++;
						if(!getline(clrFile,line) || (tag_start = line.find("<"))==-1)
						{
							cout << "ERROR: Bad Material " << line_num << "\n";
						}
						int carot = line.find(">",tag_start);
						tag = substring(line,tag_start+1,carot);
						if(tag.find(' ')!=-1)
						{
							tag = substring(tag,0,tag.find(' '));
						}
						
						//cout << "Mat tag = " << tag << "\n";
						
						if(tag == "color")
						{
							string id = substring(line,line.find("id=",tag_start)+4,line.find(">")-1);
							string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
							
							if(id == "ambient")
							{
								ambient[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								ambient[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								ambient[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
							else if(id == "diffuse")
							{
								diffuse[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								diffuse[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								diffuse[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
							else if(id == "specular")
							{
								specular[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								specular[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								specular[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
						}
						else if(tag == "string")
						{
							name = substring(line,line.find(">")+1,line.find("<",line.find(">")));
						}
					}
					
					Material *mat = new Material(name,ambient,diffuse,specular);
					
					materials->push_back(mat);
					
					//cout << name << "\n";
				}
				else if(tag == "light")
				{
					//cout << "Loading light\n";
					
					double location[3],diffuse[3],specular[3];
					string name;
					
					for(int i=0;i<4;i++)
					{
						line_num++;
						if(!getline(clrFile,line) || (tag_start = line.find("<"))==-1)
						{
							cout << "ERROR: Bad Light " << line_num << "\n";
						}
						int carot = line.find(">",tag_start);
						tag = substring(line,tag_start+1,carot);
						if(tag.find(' ')!=-1)
						{
							tag = substring(tag,0,tag.find(' '));
						}
						
						//cout << "Lit tag = " << tag << "\n";
						
						if(tag == "color")
						{
							string id = substring(line,line.find("id=",tag_start)+4,line.find(">")-1);
							string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
							
							if(id == "diffuse")
							{
								//printf("diffuse %s %s %s \n",line.c_str(),content.c_str(),substring(content,1,content.find(" ",1)).c_str());
								diffuse[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								diffuse[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								diffuse[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
							else if(id == "specular")
							{
								specular[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								specular[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								specular[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
						}
						else if(tag == "vec3")
						{
							string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
							
							location[0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							content = substring(content,content.find(" ",1));
							location[1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							content = substring(content,content.find(" ",1));
							location[2] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
						}
						else if(tag == "string")
						{
							name = substring(line,line.find(">")+1,line.find("<",line.find(">")));
						}
					}
					
					Light *lit = new Light(name,location,diffuse,specular);
					lights->push_back(lit);
					
					//cout << name << "\n";
				}
				else if(tag == "camera") 
				{
					//cout << "Loading camera\n";
					
					double transform[4][4];
					double angle,width,height;
					string name;
					
					for(int i=0;i<5;i++)
					{
						line_num++;
						
						if(!getline(clrFile,line) || (tag_start = line.find("<"))==-1)
						{
							cout << "ERROR: Bad Camera " << line_num << "\n";
						}
						int carot = line.find(">",tag_start);
						tag = substring(line,tag_start+1,carot);
						if(tag.find(' ')!=-1)
						{
							tag = substring(tag,0,tag.find(' '));
						}
						
						//cout << "Cam tag = " << tag << "\n";
						
						if(tag[0] == '/')
						{
							i--;
							continue;
						}
						
						if(tag == "float")
						{
							string id = substring(line,line.find("id=",tag_start)+4,line.find(">")-1);
							string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
							
							if(id == "angle")
							{
								angle = strtod(content.c_str(),NULL);
							}
							else if(id == "width")
							{
								width = strtod(content.c_str(),NULL);
							}
							else if(id == "height")
							{
								height = strtod(content.c_str(),NULL);
							}
						}
						else if(tag == "mat4")
						{
							for(int k=0;k<4;k++)
							{
								line_num++;
								if(!getline(clrFile,line) && (tag_start = line.find("<"))==-1)
								{
									cout << "ERROR: Bad Matrix " << line_num << "\n";
								}
								
								string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
								
								transform[k][0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][2]  = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][3]  = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
						}
						else if(tag == "string")
						{
							name = substring(line,line.find(">")+1,line.find("<",line.find(">")));
						}
					}
					
					Camera *cam = new Camera(name,transform,angle,width,height);
					cameras->push_back(cam);
					
					//printf("%s %f %f \n",name,width,height);
				}
				else if(tag == "object")
				{
					//cout << "Loading object\n";
					
					string name,type,mat_name;
					double  transform[4][4];
					
					for(int i=0;i<4;i++)
					{
						line_num++;
						if(!getline(clrFile,line) || (tag_start = line.find("<"))==-1)
						{
							cout << "ERROR: Bad Object " << line_num << "\n";
						}
						int carot = line.find(">",tag_start);
						tag = substring(line,tag_start+1,carot);
						if(tag.find(' ')!=-1)
						{
							tag = substring(tag,0,tag.find(' '));
						}
						
						//cout << "Obj tag = " << tag << "\n";
						
						if(tag[0] == '/')
						{
							i--;
							continue;
						}
						
						if(tag == "string")
						{
							string id = substring(line,line.find("id=",tag_start)+4,line.find(">")-1);
							string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
							
							if(id == "name")
							{
								name = content;
							}
							else if(id == "type")
							{
								type = content;
							}
							else if(id == "material_name")
							{
								mat_name = content;
							}
						}
						else if(tag == "mat4")
						{
							for(int k=0;k<4;k++)
							{
								line_num++;
								if(!getline(clrFile,line) && (tag_start = line.find("<"))==-1)
								{
									cout << "ERROR: Bad Matrix " << line_num << "\n";
								}
								
								string content = substring(line,line.find(">")+1,line.find("<",line.find(">")));
								
								transform[k][0] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][1] = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][2]  = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
								content = substring(content,content.find(" ",1));
								transform[k][3]  = strtod(substring(content,1,content.find(" ",1)).c_str(),NULL);
							}
						}
					}
					
					Material *mat;
					list<Material*>::iterator mat_it;
					
					for(mat_it = materials->begin(); mat_it != materials->end(); mat_it++)
					{
						if((*mat_it)->getName() == mat_name)
						{
							mat = (*mat_it);
							break;
						}
					}
					
					cout << name << " " << type << " " << mat_name << " " << mat->getName() << "\n";
					
					if(type == "ELLIPSE")
					{
						Sphere *sph = new Sphere(name,transform,mat);
						objects->push_back(sph);
					}
					else if(type == "TETRAHEDRON")
					{
						Tetrahedron *tet = new Tetrahedron(name,transform,mat);
						objects->push_back(tet);
					}
					else if(type == "PLANE")
					{
						Plane *pla = new Plane(name,transform,mat);
						objects->push_back(pla);
					}
					else if(type == "DODECAHEDRON")
					{
						Dodecahedron *dod = new Dodecahedron(name,transform,mat);
						objects->push_back(dod);
					}
				}
			}
		}
		clrFile.close();
	}
	else
		cout << "Error opening file\n";
}

void saveClrFile(string filePath,string author,string scene_name,list<Material*> *materials,list<GeoObject*> *objects,list<Light*> *lights,list<Camera*> *cameras,double ambientLight[3])
{	
	filePath += ".clr";
	
	ofstream file;
	file.open(filePath);
	
	file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	file << "<CLEAR version='0.1'>\n";
	file << "/t<file_information>\n";
	file << "\t\t<author>" << author << "</author>\n";
	file << "\t\t<authoring_tool> CLEAR File Editor </authoring_tool>\n";
	file << "\t\t<created></created>\n";
	file << "\t\t<modified></modified>\n";
	file << "\t</file_information>\n";
	
	file << "\t<scene>\n";
	file << "\t\t<string id='name'> " << scene_name << "</string>\n";
	file << "\t\t<color id='ambient'> " << dtos(ambientLight[0]) << " " << dtos(ambientLight[1]) << " " << dtos(ambientLight[2]) << " </color>\n";
	file << "\t\t<assets>\n";
	
	list<Material*>::iterator mat_it;
	for(mat_it = materials->begin(); mat_it != materials->end(); mat_it++)
	{
		file << "\t\t\t<material>\n";
		file << "\t\t\t\t<string id='name'>" << (*mat_it)->getName().c_str() << "</string>\n";
		
		double *color = (*mat_it)->getAmbient();
		file << "\t\t\t\t<color id='ambient'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </color>/n";
		color = (*mat_it)->getDiffuse();
		file << "\t\t\t\t<color id='ambient'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </color>/n";
		color = (*mat_it)->getSpecular();
		file << "\t\t\t\t<color id='ambient'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </color>/n";
		
		file << "\t\t\t</material>\n";
	}
	
	list<Light*>::iterator light_it;
	for(light_it = lights->begin(); light_it != lights->end(); light_it++)
	{
		file << "\t\t\t<light>\n";
		file << "\t\t\t\t<string id='name'>" << (*light_it)->getName().c_str() << "</string>\n";
		
		double *color = (*light_it)->getSource();
		file << "\t\t\t\t<vec3 id='location'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </vec3>/n";
		color = (*light_it)->getDiffuce();
		file << "\t\t\t\t<color id='ambient'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </color>/n";
		color = (*light_it)->getSpecular();
		file << "\t\t\t\t<color id='ambient'> " << dtos(color[0]) << " " << dtos(color[1]) << " " << dtos(color[2]) << " </color>/n";
		
		file << "\t\t\t</light>\n";
	}
	
	list<Camera*>::iterator camera_it;
	for(camera_it = cameras->begin(); camera_it != cameras->end(); camera_it++)
	{
		file << "\t\t\t<camera>\n";
		file << "\t\t\t\t<string id='name'>" << (*camera_it)->getName().c_str() << "</string>\n";
		
		file << "\t\t\t\t<mat4 id='transform'>\n";
		double *transform = (*camera_it)->getTransform0();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*camera_it)->getTransform1();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*camera_it)->getTransform2();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*camera_it)->getTransform3();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		file << "\t\t\t\t</mat4>\n";
		
		file << "\t\t\t\t<float id='angle'> " << dtos((*camera_it)->getAngle()) << " </float>\n";
		file << "\t\t\t\t<float id='width'> " << dtos((*camera_it)->getWidth()) << " </float>\n";
		file << "\t\t\t\t<float id='height'> " << dtos((*camera_it)->getHeight()) << " </float>\n";
		
		file << "\t\t\t</camera>\n";
	}
	
	file << "\t\t</assets>\n";
	file << "\t\t<entities>\n";
	
	list<GeoObject*>::iterator obj_it;
	for(obj_it = objects->begin(); obj_it != objects->end(); obj_it++)
	{
		file << "\t\t\t<object>\n";
		file << "\t\t\t\t<string id='name'>" << (*obj_it)->getName().c_str() << "</string>\n";
		file << "\t\t\t\t<string id='type'>" << (*obj_it)->getType().c_str() << "</string>\n";
		file << "\t\t\t\t<string id='material_name'>" << (*obj_it)->getMaterial()->getName().c_str() << "</string>\n";
		
		file << "\t\t\t\t<mat4 id='transform'>\n";
		double *transform = (*obj_it)->getTransform0();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*obj_it)->getTransform1();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*obj_it)->getTransform2();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		transform = (*obj_it)->getTransform3();
		file << "\t\t\t\t\t<vec4> " << dtos(transform[0]) << " " << dtos(transform[1]) << " " << dtos(transform[2]) << " " << dtos(transform[3]) << " </vec4>\n";
		file << "\t\t\t\t</mat4>\n";
		
		file << "\t\t\t</object>\n";
	}
	
	file << "\t\t</entities>\n";
	file << "\t</scene>\n";
	file << "</CLEAR>\n";
	
	file.close();
}