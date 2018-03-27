#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include <string>
#include <set>
#include "GPSCoord.h"

using namespace std;

class Info
{
private:

	string name;
	int ID;
	set<string> routes;
	set<string> lines;
	bool busStation;
	bool trainStation;

public:

	Info();
	Info(int id, string n, bool bs = false, bool ts = false);
	string getName() const;
	int getID() const;
	void setName(string n);
	void setID(int id);
	bool is_busStation() const;
	bool is_trainStation() const;
	void setBusStation(bool bs);
	void setTrainStation(bool ts);
	void addRoute(string r);
	void addLine(string l);
};

#endif