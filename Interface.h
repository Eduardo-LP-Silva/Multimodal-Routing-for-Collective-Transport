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
	GraphViewer *gv;

public:
	
	Interface();
	void CalcRouteMenu();
	void graphMenu();
	void RouteMenu();
	void transportPreferenceMenu();
	void quickestVsShortestMenu();
	void findPointMenu(Vertex *&v);
	void setGraphViewer(GraphViewer *gv);
	void setGraph(Graph *g);
	void createExpGraph();
	void createTestGraph();
};

#endif
