#include <iostream>
#include <exception>
#include "GPSCoord.h"

using namespace std;

GPSCoord::GPSCoord()
{

};

GPSCoord::GPSCoord(double l1, double l2, double a)
{
	this.latitude = l1;
	this.longitude = l2;
	this.altitude = a;
}

double GPSCoord::getLatitude()
{
	return this.latitude;
}

double GPSCoord::getLongitude()
{
	return this.longitude;
}

double GPSCoord::getAltitude()
{
	return this.altitude;
}

bool GPSCoord::operator==(GPSCoord  &gps) const
{
	return ((this->latitude == gps2.getLatitude() ) && (this->longitude == gps2.getLongitude() )  && (this->altitude == gps2.getAltitude()));
}

