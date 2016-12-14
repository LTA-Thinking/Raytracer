#include <string>
#include <list>

using namespace std;

string substring(string s,int start,int end);

string substring(string s,int start);

void loadClrFileForRaytrace(string filePath,list<Material*> *materials,list<GeoObject*> *objects,list<Light*> *lights,list<Camera*> *cameras,double ambientLight[3]);
