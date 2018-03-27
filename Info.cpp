#include "Info.h"

using namespace std;

Info::Info(){}

Info::Info(int id, string n, bool bs, bool ts)
{
	name = n;
	ID = id;
	busStation = bs;
	trainStation = ts;
	lines = set<string>();
	routes = set<string>();
}

string Info::getName() const
{
	return name;
}

int Info::getID() const
{
	return ID;
}

void Info::setName(string n)
{
	name = n;
}

void Info::setID(int id)
{
	ID = id;
}

bool Info::is_busStation() const
{
	return busStation;
}

bool Info::is_trainStation() const
{
	return trainStation;
}

void Info::setBusStation(bool bs)
{
	busStation = bs;
}

void Info::setTrainStation(bool ts)
{
	trainStation = ts;
}

void Info::addRoute(string r)
{
	routes.insert(r);
}

void Info::addLine(string l)
{
	lines.insert(l);
}

