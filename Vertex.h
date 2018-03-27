#ifndef VERTEX_H
#define VERTEX_H

#include "MutablePriorityQueue.h"
#include "Edge.h"

using namespace std;

template <class T>
class Vertex
{
private:
	
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		
	int id;
	bool processing = false;

public:
	Vertex(T in);
	Vertex(T in, int ID);
	void addEdge(Vertex<T> *dest, double w, Info i);
	bool operator<(Vertex<T> & vertex) const; 
	T getInfo() const;
	vector<Edge<T>> getAdj() const;
	double getDist() const;
	Vertex *getPath() const;
	
};

template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

template <class T>
Vertex<T>::Vertex(T in, int ID)
{
	info = in;
	id = ID;
}

/*
* Auxiliary function to add an outgoing edge to a vertex (this),
* with a given destination vertex (d) and edge weight (w).
*/
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, Info i)
{
	adj.push_back(Edge<T>(d, w, i));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const
{
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const
{
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const
{
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const
{
	return this->path;
}

template <class T>
vector<Edge<T>> Vertex<T>::getAdj() const
{
	return adj;
}

#endif
