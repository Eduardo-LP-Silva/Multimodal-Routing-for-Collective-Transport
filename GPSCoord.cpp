#include "GPSCoord.h"

using namespace std;

GPSCoord::GPSCoord(){}

GPSCoord::GPSCoord(double l1, double l2, double a)
{
	latitude = l1;
	longitude = l2;
	altitude = a;
}

double GPSCoord::getLatitude()
{
	return latitude;
}

double GPSCoord::getLongitude()
{
	return longitude;
}

double GPSCoord::getAltitude()
{
	return altitude;
}

bool GPSCoord::operator==(GPSCoord  &gps) const
{
	return this->latitude == gps.getLatitude() && this->longitude == gps.getLongitude() && this->altitude == gps.getAltitude();
}

