#include <iostream>
#include <string>
#include "VertexInfo.h"

using namespace std;

VertexInfo::VertexInfo(){}

VertexInfo::VertexInfo(string n, GPSCoord g, int id)
{
	name = n;
	gps = g;
	ID = id;
}

string VertexInfo::getName()
{
	return name;
}

GPSCoord VertexInfo::getGPSCoord()
{
	return gps;
}

int VertexInfo::getID()
{
	return ID;
}

void VertexInfo::setName(string n)
{
	name = n;
}

void VertexInfo::setGPS(GPSCoord g)
{
    gps = g;
}

void VertexInfo::setID(int id)
{
	ID = id;
}

