#include "Graph.h"

using namespace std;

Graph::Graph()
{
	test = false;
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

void Graph::dijkstraShortestPathOriginal(const int &IDorigin)
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

void Graph::dijkstraShortestPath(const int &IDorigin, const string ft, double limit)
{
	MutablePriorityQueue<Vertex> qe;
	Vertex *v2;
	double walk_penalty = 0;
	double time_passed = 0;
	double distance_to_add = 0;
	
	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet.at(i)->getId() == IDorigin)
		{
			vertexSet.at(i)->setDist(0);
			vertexSet.at(i)->setTimeCount(0);
			qe.insert(vertexSet.at(i));
			gv->setVertexColor(IDorigin, BLUE);
			vertexSet.at(i)->setProcessing(true);
		}
		else
			{
				vertexSet.at(i)->setDist(INF);
				vertexSet.at(i)->setTimeCount(0);
				gv->setVertexColor(vertexSet.at(i)->getId(), YELLOW);
				vertexSet.at(i)->setProcessing(false);
			}
			
		vertexSet.at(i)->setPath(NULL);
		vertexSet.at(i)->setCost(0);
		vertexSet.at(i)->setCounting(false);
		

		if(!test)
			gv->setVertexSize(vertexSet.at(i)->getId(), 5);
	}

	while (!qe.empty())
	{
		v2 = qe.extractMin();
		v2->setProcessing(false);

		for (Edge e : v2->getAdj())
		{
			distance_to_add = e.getWeight();
			walk_penalty = 0;

			if (!e.getInfo().is_busStation() && !e.getInfo().is_trainStation())
			{
				walk_penalty = e.getWeight();
				distance_to_add += walk_penalty;
			}
			else
				if (v2->isLimitReached())
				{
					e.getDest()->setLimitReached(true);
					continue;
				}
				else
					if(!v2->isCounting())
					{
						v2->setCounting(true);
						v2->setTimeCount(0);
						v2->setCost(v2->getCost() + 1.20);
					}

			if (ft != "")
				if (e.getInfo().is_busStation() && ft == "Bus")
					distance_to_add /= 2;
				else
					if(e.getInfo().is_trainStation() && ft == "Train")
						distance_to_add /= 2;

			if (v2->getCost() > limit)
				if(!v2->isLimitReached())
				{
					v2->setCost(0);
					v2->setCounting(false);
					v2->setLimitReached(true);
					e.getDest()->setLimitReached(true);
					continue;
				}

			if (e.getDest()->getDist() > v2->getDist() + distance_to_add)
			{
				if (v2->isCounting())
					if ((v2->getTimeCount() + e.getTime()) / 60 > 1)
						v2->setCounting(false);
					else
					{
						e.getDest()->setTimeCount(v2->getTimeCount() + e.getTime());
						//e.getDest()->setCounting(true);
					}

				//e.getDest()->setTimeCount(v2->getTimeCount() + e.getTime());
				e.getDest()->setDist(v2->getDist() + distance_to_add);
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

void Graph::setTest(bool t)
{
	test = t;
}

bool Graph::isTest() const
{
	return test;
}
