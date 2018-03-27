#include "GPSCoord.h"

using namespace std;

GPSCoord::GPSCoord(){}

GPSCoord::GPSCoord(double l1, double l2)
{
	latitude = l1;
	longitude = l2;
}

double GPSCoord::getLatitude()
{
	return latitude;
}

double GPSCoord::getLongitude()
{
	return longitude;
}

bool GPSCoord::operator==(GPSCoord  &gps) const
{
	return this->latitude == gps.getLatitude() && this->longitude == gps.getLongitude();
}

