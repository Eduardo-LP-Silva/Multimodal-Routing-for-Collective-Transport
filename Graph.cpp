#include "Graph.h"

using namespace std;

Graph::Graph(){}

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

Vertex* Graph::findVertexByEdge(const string name) const
{
	for (Vertex* v : vertexSet)
		for (Edge e : v->getAdj())
			if (e.getInfo().getName() == name)
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

bool Graph::addVertex(Vertex *v)
{
	if (findVertex(v->getId()) != NULL)
		return false;

	vertexSet.push_back(v);

	return true;
}

/*
* Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* Returns true if successful, and false if the source or destination vertex does not exist.
*/

bool Graph::addEdge(const int &IDsourc, const int &IDdest, Info I, double w)
{
	auto v1 = findVertex(IDsourc);
	auto v2 = findVertex(IDdest);

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

void Graph::setGraphViewer(GraphViewer *gv)
{
	this->gv = gv;
} 

void Graph::dijkstraShortestPath(const int &IDorigin, const string ft, double limit)
{
	MutablePriorityQueue<Vertex> qe;
	Vertex *v2;
	double walk_penalty = 10;
	double time_passed = 0;
	double distance_to_add = 0;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->getId() == IDorigin)
		{
			vertexSet.at(i)->setDist(0);
			qe.insert(vertexSet.at(i));
			gv->setVertexColor(IDorigin, BLUE);
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
			/*if (!e.getInfo().is_busStation() && !e.getInfo().is_trainStation())
			{
				distance_to_add = walk_penalty;
				//e.setWeight(e.getWeight() + walk_penalty);
				walk_penalty += 2;
			}
			else
				distance_to_add = 0;*/

			if (ft != "")
				if (e.getInfo().is_busStation() && ft == "Bus")
					e.setWeight(e.getWeight() / 2);
				else
					if(e.getInfo().is_trainStation() && ft == "Train")
						e.setWeight(e.getWeight() / 2);

			if (e.getDest()->getDist() > v2->getDist() + e.getWeight())
			{
				time_passed += e.getTime();
				limit -= (e.getTime() + time_passed) / 60 * 1.20;
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

void Graph::dijkstraShortestTime(const int &IDorigin, const string ft, double limit)
{
	MutablePriorityQueue<Vertex> qe;
	Vertex *v2;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->getId() == IDorigin)
		{
			vertexSet.at(i)->setTime(0);
			qe.insert(vertexSet.at(i));
		}
		else
			vertexSet.at(i)->setTime(INF);

		vertexSet.at(i)->setPath(NULL);
	}

	while (!qe.empty())
	{
		v2 = qe.extractMin();
		v2->setProcessing(false);

		for (Edge e : v2->getAdj())
		{
			if (e.getDest()->getTime() > v2->getTime() + e.getTime())
			{
				e.getDest()->setTime(v2->getTime() + e.getTime());
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

vector<Vertex*> Graph::getPath(const int &IDorigin, const int &IDdest) const
{
	vector<Vertex*> res;
	Vertex *v = findVertex(IDdest);

	while (1)
	{
		res.insert(res.begin(), v);

		if (v->getPath() == NULL)
			break;
		else
			v = v->getPath();
	}

	return res;
}
