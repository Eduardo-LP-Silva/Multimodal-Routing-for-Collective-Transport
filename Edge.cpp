#include "Edge.h"

//Km/h

#define BUS_V 14.24
#define WALK_V 5.0
#define TRAIN_V 40.0

using namespace std;

Edge::Edge(Vertex *d, double w, Info i)
{
	dest = d;
	weight = w;
	info = i;

	//Minutes

	if (i.is_busStation())
		time = (w / BUS_V) * 60;
	else
		if (i.is_trainStation())
			time = (w / TRAIN_V) * 60;
		else
			time = (w / WALK_V) * 60;
}

double Edge::getWeight() const
{
	return weight;
}

Vertex* Edge::getDest() const
{
	return dest;
}

double Edge::getTime() const
{
	return time;
}

void Edge::setInfo(Info i)
{
	info = i;
}

Info Edge::getInfo()
{
	return info;
}

void Edge::setWeight(double w)
{
	weight = w;
}
