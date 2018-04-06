#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "Vertex.h"
#include "graphviewer.h"
#include <cfloat>
#include <climits> // to work on linux

using namespace std;

#define INF INT_MAX

class Graph
{
private:

	vector<Vertex *> vertexSet;    // vertex set
	GraphViewer *gv;

public:

	Graph(); //simple default graph

	Vertex *findVertex(const int ID) const;
	Vertex *findVertexByEdge(const string name) const;
	bool addVertex(const GPSCoord c, const int ID);
	bool addVertex(Vertex *v);
	bool addEdge(const int &IDsourc, const int &IDdest, Info I, double w);
	bool addEdgeDIS(const int &IDsourc, const int &IDdest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;
	void dijkstraShortestPathOriginal(const int &IDorigin);
	void dijkstraShortestPath(const int &IDorigin, const string ft, double limit);
	void dijkstraShortestTime(const int &IDorigin, const string ft, double limit);
	void setGraphViewer(GraphViewer *gv);
	vector<Vertex*> getPath(const int &IDorigin, const int &IDdest) const;
};



#endif /* GRAPH_H_ */
