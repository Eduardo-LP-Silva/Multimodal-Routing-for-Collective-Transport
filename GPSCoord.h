#ifndef GPSCoord_H
#define GPSCoord_H

#include <iostream>
#include <exception>

class GPSCoord
{
	double latitude;
	double longitude;
	double altitude;

public:

	GPSCoord();
	GPSCoord(double l1, double l2, double a);
	double getLatitude();
	double getLongitude();
	double getAltitude();
	bool operator==(GPSCoord  &gps) const;

};
