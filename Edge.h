#ifndef EDGE_H
#define EDGE_H

#include "Info.h"

class Vertex;

class Edge
{
private:

	Vertex * dest;      // destination vertex
	double weight;      // edge weight
	double time;
	Info info;

public:

	Edge(Vertex *d, double w, Info i);
	double getWeight() const;
	Vertex* getDest() const;
	double getTime() const;
	Info getInfo() const;
	void setInfo(Info i);
	void setWeight(double w);
	double getPrice();
	bool operator==(const Edge &e2);
	
};

#endif
