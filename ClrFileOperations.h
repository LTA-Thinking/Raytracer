#include <string>
#include <list>

using namespace std;

string substring(string s,int start,int end);

string substring(string s,int start);

string dtos(double d);

void loadClrFile(string filePath,list<Material*> *materials,list<GeoObject*> *objects,list<Light*> *lights,list<Camera*> *cameras,double ambientLight[3]);

void saveClrFile(string filePath,string author,string scene_name,list<Material*> *materials,list<GeoObject*> *objects,list<Light*> *lights,list<Camera*> *cameras,double ambientLight[3]);