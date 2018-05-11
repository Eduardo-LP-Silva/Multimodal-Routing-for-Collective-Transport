#include "Edge.h"

//Km/h

#define BUS_V 14.24
#define WALK_V 5.0
#define TRAIN_V 40.0
#define AVRG_WAITING_TIME 2

using namespace std;

Edge::Edge(Vertex *d, double w, Info i)
{
	dest = d;
	weight = w;
	info = i;

	//Minutes

	if (i.is_busStation())
		time = (w / BUS_V) * 60 + AVRG_WAITING_TIME;
	else
		if (i.is_trainStation())
			time = (w / TRAIN_V) * 60 + AVRG_WAITING_TIME;
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

Info Edge::getInfo() const
{
	return info;
}

void Edge::setWeight(double w)
{
	weight = w;
}

double Edge::getPrice()
{
	if (this->getInfo().is_busStation() || this->getInfo().is_trainStation())
		return (getTime() / 60) * 1.20;
	else
		return 0;
}

bool Edge::operator==(const Edge &e2)
{
	return this->info.getID() == e2.info.getID();
}
