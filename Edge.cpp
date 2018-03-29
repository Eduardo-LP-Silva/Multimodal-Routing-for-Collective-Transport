#include "Edge.h"

#define BUS_V 14.24
#define WALK_V 5
#define TRAIN_V 40

using namespace std;

Edge::Edge(Vertex *d, double w, Info i)
{
	dest = d;
	weight = w;
	info = i;

	if (i.is_busStation())
		time = w / BUS_V;
	else
		if (i.is_trainStation())
			time = w / TRAIN_V;
		else
			time = w / WALK_V;
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
