#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Funcs.h"
#include "Graph.h"
#include "Info.h"

class Interface
{
private:

	Graph<Vertex<GPSCoord>> graph;

public:
	
	Interface(Graph<Vertex<GPSCoord>> g);
	void CalcRouteMenu();
	void RouteMenu();
};



#endif
