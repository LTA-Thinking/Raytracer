#include "VectorHelpers.h"
#include "GeoObject.h"
#include "ClrFileOperations.h"
#include <string>

list<Material*> materials;
list<GeoObject*> obj;
list<Light*> lights;
list<Camera*> cameras;

list<Material*>::iterator materials_it;
list<GeoObject*>::iterator obj_it;
list<Light*>::iterator lights_it;
list<Camera*>::iterator cameras_it;

double ambientLight[3];

int saveCheck = 0;

string getString()
{
	string input = "";
	char c;
	scanf("%c",&c);
	if(c==' ' || c=='\n')
		scanf("%c",&c);
	
	while(c!=' ' && c!='\n')
	{
		input += c;
		scanf("%c",&c);
	}
	
	return input;
}

void listAll()
{
	printf("\nMaterials:\n");
	
	for(materials_it = materials.begin(); materials_it != materials.end(); materials_it++)
	{
		printf("\t%s\n",(*materials_it)->getName().c_str());
		
		double *color = (*materials_it)->getDiffuse();
		printf("\t\tDiffuse: (%f,%f,%f)\n",color[0],color[1],color[2]);
		
		color = (*materials_it)->getSpecular();
		printf("\t\tSpecular: (%f,%f,%f)\n",color[0],color[1],color[2]);
	}
	
	printf("\nLights:\n");
	
	for(lights_it = lights.begin(); lights_it != lights.end(); lights_it++)
	{
		printf("\t%s\n",(*lights_it)->getName().c_str());
		
		double *color = (*lights_it)->getSource();
		printf("\t\tSource: (%f,%f,%f)\n",color[0],color[1],color[2]);
		
		color = (*lights_it)->getDiffuce();
		printf("\t\tDiffuse: (%f,%f,%f)\n",color[0],color[1],color[2]);
		
		color = (*lights_it)->getSpecular();
		printf("\t\tSpecular: (%f,%f,%f)\n",color[0],color[1],color[2]);
	}
	
	printf("\nCameras:\n");
	
	for(cameras_it = cameras.begin(); cameras_it != cameras.end(); cameras_it++)
	{
		printf("\t%s\n",(*cameras_it)->getName().c_str());
		
		double *transform = (*cameras_it)->getTransform0();
		printf("\t\tTransform:\n");
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*cameras_it)->getTransform1();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*cameras_it)->getTransform2();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*cameras_it)->getTransform3();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		
		double value = (*cameras_it)->getWidth();
		printf("\t\tWidth: %f\n",value);
		
		value = (*cameras_it)->getHeight();
		printf("\t\tHeight: %f\n",value);
		
		value = (*cameras_it)->getAngle();
		printf("\t\tAngle: %f\n",value);
	}
	
	printf("\nObjects:\n");
	
	for(obj_it = obj.begin(); obj_it != obj.end(); obj_it++)
	{
		printf("\t%s\n",(*obj_it)->getName().c_str());
		
		printf("\t\t%s\n",(*obj_it)->getType().c_str());
		
		double *transform = (*obj_it)->getTransform0();
		printf("\t\tTransform:\n");
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*obj_it)->getTransform1();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*obj_it)->getTransform2();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
		transform = (*obj_it)->getTransform3();
		printf("\t\t\t(%f,%f,%f,%f)\n",transform[0],transform[1],transform[2],transform[3]);
	}
}

void deleteItem(string name)
{	
	for(materials_it = materials.begin(); materials_it != materials.end(); materials_it++)
	{
		if((*materials_it)->getName() == name)
		{
			materials.erase(materials_it);
			return;
		}
	}
	
	for(lights_it = lights.begin(); lights_it != lights.end(); lights_it++)
	{
		if((*lights_it)->getName() == name)
		{
			lights.erase(lights_it);
			return;
		}
	}
	
	for(cameras_it = cameras.begin(); cameras_it != cameras.end(); cameras_it++)
	{
		if((*cameras_it)->getName() == name)
		{
			cameras.erase(cameras_it);
			return;
		}
	}
	
	for(obj_it = obj.begin(); obj_it != obj.end(); obj_it++)
	{
		if((*obj_it)->getName() == name)
		{
			obj.erase(obj_it);
			return;
		}
	}
	
	printf("Can't find an item with that name.\n");
}

void edit(string name,double transform[4][4],int append)
{
	
	for(obj_it = obj.begin(); obj_it != obj.end(); obj_it++)
	{
		if((*obj_it)->getName() == name)
		{
			if(append == 1)
				(*obj_it)->appendTransform(transform);
			else
				(*obj_it)->setTransform(transform);
			
			return;
		}
	}
	
	for(cameras_it = cameras.begin(); cameras_it != cameras.end(); cameras_it++)
	{
		if((*cameras_it)->getName() == name)
		{
			if(append == 1)
				(*cameras_it)->appendTransform(transform);
			else
				(*cameras_it)->setTransform(transform);
			return;
		}
	}
	
	printf("Can't find item with that name.\n");
}

void newObject(string type,string name,string mat_name,double transform[4][4])
{
	Material *mat = NULL;
	for(materials_it = materials.begin(); materials_it != materials.end(); materials_it++)
	{
		if((*materials_it)->getName() == mat_name)
		{
			mat = (*materials_it);
			break;
		}
	}
	
	if(mat == NULL)
	{
		printf("Material not found\n");
	}
	
	if(type =="sphere")
	{
		Sphere *s = new Sphere(name,transform,mat);
		obj.push_back(s);
	}
	else if(type == "plane")
	{
		Plane *s = new Plane(name,transform,mat);
		obj.push_back(s);
	}
	else if(type == "tetrahedron")
	{
		Tetrahedron *s = new Tetrahedron(name,transform,mat);
		obj.push_back(s);
	}
	else if(type == "dodecahedron")
	{
		Dodecahedron *s = new Dodecahedron(name,transform,mat);
		obj.push_back(s);
	}
	else
	{
		printf("Unrecognized shape\n");
	}
}

void newLight()
{
	
}

int parseCommand(string input)
{
	printf("Parsing command %s\n",input.c_str());
	
	if(input == "h" || input == "help")
	{
		printf("Here are a list of commands:\n");
		printf("\t-n/new: Creates a new item in the scene.\n");
		printf("\t-e/edit: Changes the transform matrix of an item.\n");
		printf("\t-d/delete: Deletes an item from the scene.\n");
		printf("\t-l/list: Lists all items in the scene.\n");
		printf("\t-a/ambient: Sets the ambient light level for the scene.\n");
		printf("\t-o/open: Opens a new scene.\n");
		printf("\t-s/save: Saves the current scene.\n");
		printf("\t-h/help: Shows this help text.\n");
		printf("\t-q/quit: Quits the editor.\n");
	}
	else if(input == "n" || input == "new")
	{
		saveCheck = 1;
		
		printf("Enter type of new item: (l,m,c,o) ");
		string type = getString();
		
		if(type == "l" || type == "light")
		{
			printf("New Light\n");
			
			printf("Enter name: ");
			string name = getString();
			
			double source[3],diffuce[3],specular[3];
			
			printf("Enter location: ");
			scanf("%lf %lf %lf",&source[0],&source[1],&source[2]);
			
			printf("Enter diffuse coeffs: ");
			scanf("%lf %lf %lf",&diffuce[0],&diffuce[1],&diffuce[2]);
			
			printf("Enter specular coeffs: ");
			scanf("%lf %lf %lf",&specular[0],&specular[1],&specular[2]);
			
			Light *light = new Light(name,source,diffuce,specular);
			lights.push_back(light);
		}
		else if(type == "m" || type == "material")
		{
			printf("New Material\n");
			
			printf("Enter name: ");
			string name = getString();
			
			double ambient[3],diffuce[3],specular[3];
			
			printf("Enter ambient coeffs: ");
			scanf("%lf %lf %lf",&ambient[0],&ambient[1],&ambient[2]);
			
			printf("Enter diffuse coeffs: ");
			scanf("%lf %lf %lf",&diffuce[0],&diffuce[1],&diffuce[2]);
			
			printf("Enter specular coeffs: ");
			scanf("%lf %lf %lf",&specular[0],&specular[1],&specular[2]);
			
			Material *mat = new Material(name,ambient,diffuce,specular);
			materials.push_back(mat);
		}
		else if(type == "c" || type == "camera")
		{
			printf("New Camera\n");
			
			printf("Enter name: ");
			string name = getString();
			
			double angle;
			int width,height;
			
			printf("Enter angle of view: ");
			scanf("%lf",&angle);
			
			printf("Enter width: ");
			scanf("%d",&width);
			
			printf("Enter height: ");
			scanf("%d",&height);
			
			printf("Enter transformation");
			double transform[4][4];
			for(int i=0;i<16;i++)
			{
				scanf("%lf",&transform[i/4][i%4]);
			}
			
			Camera *cam = new Camera(name,transform,angle,width,height);
			cameras.push_back(cam);
		}
		else if(type == "o" || type == "object")
		{	
			printf("New Object\n");
			
			printf("Enter name: ");
			string name = getString();
			
			printf("Enter type: ");
			string type = getString();
			
			printf("Enter material's name: ");
			string mat_name = getString();
			
			printf("Enter transform: ");
			double transform[4][4];
			for(int i=0;i<16;i++)
			{
				scanf("%lf",&transform[i/4][i%4]);
			}
			
			newObject(type,name,mat_name,transform);
		}
		else
		{
			printf("Unrecognized type");
		}
	}
	else if(input == "e" || input == "edit")
	{
		saveCheck = 1;
		
		printf("Enter name of item to be edited: ");
		string name = getString();
		
		printf("Append or replace: (a,r) ");
		string type = getString();
		int append = 0;
		if(type == "append" || type == "a")
			append = 1;
		
		printf("Enter transform: ");
		double transform[4][4];
		for(int i=0;i<16;i++)
		{
			scanf("%lf",&transform[i/4][i%4]);
		}
		
		edit(name,transform,append);
	}
	else if(input == "d" || input == "delete")
	{
		saveCheck = 1;
		
		printf("Enter name of item to be deleted: ");
		string name = getString();
		
		deleteItem(name);
	}
	else if(input == "l" || input == "list")
	{
		listAll();
	}
	else if(input == "o" || input == "open")
	{
		if(saveCheck == 1)
		{
			printf("Load without saving current work? (y/n) ");
			char check;
			scanf("%c",&check);
			if(check == 'n')
				return 0;
		}
		
		printf("Enter file path: ");
		string file_name = getString();
		
		loadClrFile(file_name,&materials,&obj,&lights,&cameras,ambientLight);
	}
	else if(input == "s" || input == "save")
	{
		saveCheck = 0;
		
		printf("Enter file name: ");
		string file_name = getString();
		
		printf("Enter author's name: ");
		string author = getString();
		
		saveClrFile(file_name,author,"Scene 1",&materials,&obj,&lights,&cameras,ambientLight);
	}
	else if(input == "q" || input == "quit")
	{
		if(saveCheck == 0)
			return 1;
		else
		{
			printf("Exit without saving? (y/n) ");
			char check;
			scanf("%c",&check);
			if(check == 'y')
				return 1;
		}
	}
	else if(input == "a" || input == "ambient")
	{
		printf("Enter the ambient light levels for the scene: ");
		scanf("%lf %lf %lf",&ambientLight[0],&ambientLight[1],&ambientLight[2]);
	}
	else
	{
		printf("Unknown command\n");
	}
	
	return 0;
}

int main(int argc, char** argv)
{
	ambientLight[0] = 0.0;
	ambientLight[1] = 0.0;
	ambientLight[2] = 0.0;
	
	int command;
	string input;
	printf("Welcome to the CLR file editor. Created by RB Johnson. For help use the command help.\n");
	
	while(true)
	{
		printf(">> ");
		input = getString();
		//printf("%s\n",input.c_str());
		command = parseCommand(input);
		
		if(command == 1)
			break;
	}
}