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

class Graph 
{
	vector<Vertex *> vertexSet;    // vertex set

public:

	Graph(); //simple default graph 

	Vertex *findVertex(const int ID) const;
	Vertex *findVertexByEdge(const string name) const;
	bool addVertex(const GPSCoord c, const int ID);
	bool addEdge(const int &IDsourc, const int &IDdest, Info I, double w);
	bool addEdgeDIS(const int &IDsourc, const int &IDdest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;
	void dijkstraShortestPath(const int &IDorigin, const string ft, double limit);
	void dijkstraShortestTime(const int &IDorigin, const string ft, double limit);
	vector<Vertex*> getPath(const int &IDorigin, const int &IDdest) const;
};



#endif /* GRAPH_H_ */
