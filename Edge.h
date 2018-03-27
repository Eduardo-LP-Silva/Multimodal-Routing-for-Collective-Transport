#ifndef EDGE_H
#define EDGE_H

#include "Info.h"

template <class Vertex> class Vertex;

template <class T>
class Edge
{
private:

	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
	Info info;

public:

	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, double w, Info i);
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w) : dest(d), weight(w) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, Info i)
{
	dest = d;
	weight = w;
	info = i;
}

#endif
