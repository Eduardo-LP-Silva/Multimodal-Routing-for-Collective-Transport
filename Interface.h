#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Funcs.h"
#include "Graph.h"
#include "Info.h"

class Interface
{
private:

	Graph graph;

public:
	
	Interface(Graph g);
	void CalcRouteMenu();
	void RouteMenu();
};



#endif
