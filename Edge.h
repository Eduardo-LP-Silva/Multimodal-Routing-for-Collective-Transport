#ifndef EDGE_H
#define EDGE_H

#include "Info.h"

class Vertex;

class Edge
{
private:

	Vertex * dest;      // destination vertex
	double weight;         // edge weight
	Info info;

public:

	Edge(Vertex *d, double w, Info i);
	double getWeight() const;
	Vertex* getDest() const;
};

#endif
