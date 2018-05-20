#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <map>
#include "Funcs.h"
#include "Graph.h"
#include "Info.h"

class Interface
{
private:

	Graph graph;
	bool shortest;
	bool test;
	bool best;
	double limit;
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
	void searchMenu(Vertex *&v);
	void listAproximateNames(Vertex *&v, string word);
	int listAproximateNames(Vertex *&v, string word, Graph t_graph);
	void KMPMatcher(Vertex* &v, string pattern);
	void setGraphViewer(GraphViewer *gv);
	void setGraph(Graph *g);
	void createExpGraph();
	void createTestGraph();
	void createSmallTestGraph();
	void testGraphTimes();
	void testListNamesTimes();
	void testKPMTimes();
	int KMPMatcher(Vertex* &v, string pattern, Graph t_graph);
	unsigned int listOptions();
};

#endif
