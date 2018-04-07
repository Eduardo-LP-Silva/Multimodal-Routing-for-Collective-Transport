#ifndef VERTEX_H
#define VERTEX_H

#include "MutablePriorityQueue.h"
#include "Edge.h"

using namespace std;

class Vertex
{
private:
	
	GPSCoord coords;             
	vector<Edge> adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex *path = NULL;
	int queueIndex = 0; 		
	int id;
	bool processing = false;
	bool counting = false;
	bool limitReached = false;
	double time;
	double cost;

public:
	Vertex(GPSCoord c, int ID);
	void addEdge(Vertex *dest, double w, Info i);
	bool operator<(Vertex & vertex) const; 
	GPSCoord getCoords() const;
	vector<Edge> getAdj() const;
	double getDist() const;
	Vertex *getPath() const;
	bool isProcessing() const;
	int getId() const;
	int getIndex() const;
	double getTime() const;
	double getCost() const;
	bool isCounting() const;
	bool isLimitReached() const;
	void setDist(double d);
	void setPath(Vertex *v);
	void setProcessing(bool p);
	void setIndex(int i);
	void setTime(double t);
	void setCost(double c);
	void setCounting(bool c);
	void setLimitReached(bool lr);
	
};

#endif
