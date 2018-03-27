#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "Vertex.h"

using namespace std;

#define INF std::numeric_limits<double>::max()

template <class T>
class Graph 
{
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	void dijkstraShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;
};

template <class T>
int Graph<T>::getNumVertex() const
{
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const
{
	return vertexSet;
}

/*
* Auxiliary function to find a vertex with a given content.
*/
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const
{
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
*  Adds a vertex with a given content or info (in) to a graph (this).
*  Returns true if successful, and false if a vertex with that content already exists.
*/
template <class T>
bool Graph<T>::addVertex(const T &in)
{
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
* Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* Returns true if successful, and false if the source or destination vertex does not exist.
*/
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w)
{
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);

	if (v1 == NULL || v2 == NULL)
		return false;

	v1->addEdge(v2, w);

	return true;
}

/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin)
{
	MutablePriorityQueue<Vertex<T>> qe;
	Vertex<T> *v2;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->info == origin)
		{
			vertexSet.at(i)->dist = 0;
			qe.insert(vertexSet.at(i));
		}
		else
			vertexSet.at(i)->dist = INF;

		vertexSet.at(i)->path = NULL;
	}

	while (!qe.empty())
	{
		v2 = qe.extractMin();
		v2->processing = false;

		for (Edge<T> e : v2->getAdj())
		{
			if (e.dest->dist > v2->dist + e.weight)
			{
				e.dest->dist = v2->dist + e.weight;
				e.dest->path = v2;

				if (!e.dest->processing)
				{
					e.dest->processing = true;
					qe.insert(e.dest);
				}
				else
					qe.decreaseKey(e.dest);
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const
{
	vector<T> res;
	Vertex<T> *v = findVertex(dest);

	while (1)
	{
		res.insert(res.begin(), v->info);

		if (v->path == NULL)
			break;
		else
			v = v->path;
	}

	return res;
}

#endif /* GRAPH_H_ */
