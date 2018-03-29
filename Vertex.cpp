#include "Vertex.h"

using namespace std;

Vertex::Vertex(GPSCoord c, int ID)
{
	coords = c;
	id = ID;
	time = 0;
	dist = 0;
}

/*
* Auxiliary function to add an outgoing edge to a vertex (this),
* with a given destination vertex (d) and edge weight (w).
*/
void Vertex::addEdge(Vertex *d, double w, Info i)
{
	adj.push_back(Edge(d, w, i));
}

bool Vertex::operator<(Vertex & vertex) const
{
	return this->dist < vertex.dist;
}

GPSCoord Vertex::getCoords() const
{
	return this->coords;
}

double Vertex::getDist() const
{
	return this->dist;
}
Vertex *Vertex::getPath() const
{
	return this->path;
}

vector<Edge> Vertex::getAdj() const
{
	return adj;
}

int Vertex::getId() const
{
	return id;
}

int Vertex::getIndex() const
{
	return queueIndex;
}

bool Vertex::isProcessing() const
{
	return processing;
}

void Vertex::setDist(double d)
{
	dist = d;
}

void Vertex::setPath(Vertex *v)
{
	path = v;
}

void Vertex::setProcessing(bool p)
{
	processing = p;
}

void Vertex::setIndex(int i)
{
	queueIndex = i;
}

void Vertex::setTime(double t)
{
	time = t;
}

double Vertex::getTime() const
{
	return time;
}
