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
	bool shortest;
	int limit;
	string favTransport;
	Vertex *origin, *dest;

public:
	
	Interface(Graph g);
	void CalcRouteMenu();
	void RouteMenu();
	void transportPreferenceMenu();
	void quickestVsShortestMenu();
	void findPointMenu(Vertex *&v);
};

#endif
