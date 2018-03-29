#include "Graph.h"

using namespace std;

Graph::Graph(){

	GPSCoord gp(2.0, 2.0);

	this->addVertex(gp, 0);
	this->addVertex(gp, 1);
	this->addVertex(gp, 2);
	this->addVertex(gp, 3);
	this->addVertex(gp, 4);
	this->addVertex(gp, 5);

	this->addEdgeDIS(0, 1, 10);
	this->addEdgeDIS(0, 2, 20);

	this->addEdgeDIS(2, 3, 20);
	this->addEdgeDIS(2, 4, 33);

	this->addEdgeDIS(1, 3, 50);
	this->addEdgeDIS(1, 4, 10);

	this->addEdgeDIS(3, 4, 20);
	this->addEdgeDIS(3, 5, 2);

	this->addEdgeDIS(4, 5, 1);
}

int Graph::getNumVertex() const
{
	return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const
{
	return vertexSet;
}

/*
* Auxiliary function to find a vertex with a given content.
*/

Vertex * Graph::findVertex(const int ID) const
{
	for (auto v : vertexSet)
		if (v->getId() == ID)
			return v;

	return NULL;
}

/*
*  Adds a vertex with a given content or info (in) to a graph (this).
*  Returns true if successful, and false if a vertex with that content already exists.
*/

bool Graph::addVertex(const GPSCoord c, const int ID)
{
	if (findVertex(ID) != NULL)
		return false;
	vertexSet.push_back(new Vertex(c, ID));
	return true;
}

/*
* Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* Returns true if successful, and false if the source or destination vertex does not exist.
*/

bool Graph::addEdge(const int &IDsourc, const int &IDdest, Info I, double w = 1)
{
	auto v1 = findVertex(IDsourc);
	auto v2 = findVertex(IDdest);

	if(w != 1)
		w = sqrt(pow(v1->getCoords().getLatitude() - v2->getCoords().getLatitude(), 2)
			+ pow(v1->getCoords().getLongitude() - v2->getCoords().getLongitude(), 2));

	if (v1 == NULL || v2 == NULL)
		return false;

	v1->addEdge(v2, w, I);

	return true;
}

bool Graph::addEdgeDIS(const int &IDsourc, const int &IDdest, double w)
{
	auto v1 = findVertex(IDsourc);
	auto v2 = findVertex(IDdest);

	if (v1 == NULL || v2 == NULL)
		return false;

	v1->addEdge(v2, w, Info());

	return true;
}

/**************** Single Source Shortest Path algorithms ************/
//Para fazer para o tempo temos de substituir o setDist por uma funcao chamada setTime
void Graph::dijkstraShortestPath(const int &IDorigin)
{
	MutablePriorityQueue<Vertex> qe;
	Vertex *v2;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->getId() == IDorigin)
		{
			vertexSet.at(i)->setDist(0);
			qe.insert(vertexSet.at(i));
		}
		else
			vertexSet.at(i)->setDist(INF);

		vertexSet.at(i)->setPath(NULL);
	}

	while (!qe.empty())
	{
		v2 = qe.extractMin();
		v2->setProcessing(false);

		for (Edge e : v2->getAdj())
		{
			if (e.getDest()->getDist() > v2->getDist() + e.getWeight())
			{
				e.getDest()->setDist(v2->getDist() + e.getWeight());
				e.getDest()->setPath(v2);

				if (!e.getDest()->isProcessing())
				{
					e.getDest()->setProcessing(true);
					qe.insert(e.getDest());
				}
				else
					qe.decreaseKey(e.getDest());
			}
		}
	}
}

void Graph::dijkstraShortestTime(const int &IDorigin)
{
	MutablePriorityQueue<Vertex> qe;
	Vertex *v2;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->getId() == IDorigin)
		{
			vertexSet.at(i)->setDist(0);
			qe.insert(vertexSet.at(i));
		}
		else
			vertexSet.at(i)->setDist(INF);

		vertexSet.at(i)->setPath(NULL);
	}

	while (!qe.empty())
	{
		v2 = qe.extractMin();
		v2->setProcessing(false);

		for (Edge e : v2->getAdj())
		{
			if (e.getDest()->getDist() > v2->getDist() + e.getTime())
			{
				e.getDest()->setDist(v2->getDist() + e.getTime());
				e.getDest()->setPath(v2);

				if (!e.getDest()->isProcessing())
				{
					e.getDest()->setProcessing(true);
					qe.insert(e.getDest());
				}
				else
					qe.decreaseKey(e.getDest());
			}
		}
	}
}

vector<int> Graph::getPath(const int &IDorigin, const int &IDdest) const
{
	vector<int> res;
	Vertex *v = findVertex(IDdest);

	while (1)
	{
		res.insert(res.begin(), v->getId());

		if (v->getPath() == NULL)
			break;
		else
			v = v->getPath();
	}

	return res;
}
