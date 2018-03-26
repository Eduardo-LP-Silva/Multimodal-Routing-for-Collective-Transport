#include <iostream>
#include <string>
#include "VertexInfo.h"

using namespace std;

VertexInfo::VertexInfo()
{

}

VertexInfo::VertexInfo(string n, GPSCoord g, int id)
{
	this.name = n;
	this.gps = g;
	this.ID = id;
}

string VertexInfo::getName()
{
	return this.name;
}

GPSCoord VertexInfo::getGPSCoord()
{
	return this.gps;
}

int VertexInfo::getID()
{
	return this.ID;
}

void VertexInfo::setName(string n)
{
	this.name = n;
}

void VertexInfo::setGPS(GPSCoord g)
{
    this.gps = gps;
}

void VertexInfo::setID(int id)
{
	this.ID = id;
}

