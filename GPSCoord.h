#ifndef GPSCOORD_H
#define GPSCOORD_H

class GPSCoord
{
private:

	double latitude;
	double longitude;

public:

	GPSCoord();
	GPSCoord(double l1, double l2);
	double getLatitude();
	double getLongitude();
	bool operator==(GPSCoord  &gps) const;
};

#endif
