#include <iostream>
#include <string>
#include "Funcs.h"
#include "Interface.h"
#include "GPSCoord.h"

class VertexInfo
{
private:

	string name;
	GPSCoord gps;
	int ID;

public:

	VertexInfo();
	VertexInfo(string n, GPSCoord g, int id);
	string getName();
	GPSCoord getGPSCoord();
	int getID();
	void setName(string n);
	void setGPS(GPSCoord g);
	void setID(int id);

};
