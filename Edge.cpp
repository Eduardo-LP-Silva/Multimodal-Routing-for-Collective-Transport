#include "Edge.h"

using namespace std;

Edge::Edge(Vertex *d, double w, Info i)
{
	dest = d;
	weight = w;
	info = i;
}

double Edge::getWeight() const
{
	return weight;
}

Vertex* Edge::getDest() const
{
	return dest;
}