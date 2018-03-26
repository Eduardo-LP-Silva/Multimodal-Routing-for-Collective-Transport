#ifndef GPSCOORD_H
#define GPSCOORD_H

#include <iostream>
#include <exception>

class GPSCoord
{
private:

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

#endif
