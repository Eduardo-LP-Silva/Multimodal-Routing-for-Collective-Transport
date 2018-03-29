#include "Interface.h"
#include "GPSCoord.h"

using namespace std;

int main()
{
	//Graph *g = addVertexes("A.txt");
	//addEdges(g, "B.txt", "C.txt");
	Graph* g = new Graph();
	//Interface interface = Interface(*test_graph);
	//interface.RouteMenu();

	GPSCoord gps1 = GPSCoord(10, 1);
	GPSCoord gps2 = GPSCoord(12, 2);
	GPSCoord gps3 = GPSCoord(8, 2);
	GPSCoord gps4 = GPSCoord(8, 4);
	

	g->addVertex(gps1, 1);
	g->addVertex(gps3, 3);
	g->addVertex(gps4, 4);
	g->addVertex(gps2, 2);

	g->addEdge(1, 2, Info(12, "Edge entre 1 e 2"), calcDistance(gps1, gps2));
	g->addEdge(1, 3, Info(13, "Edge entre 1 e 3"), calcDistance(gps1, gps3));
	g->addEdge(3, 4, Info(34, "Edge entre 3 e 4"), calcDistance(gps3, gps4));
	g->addEdge(2, 4, Info(24, "Edge entre 2 e 4 - Metro", false, true), calcDistance(gps2, gps4));

	g->dijkstraShortestPath(1);
	cout << "Shortest path between 1 and 4: ";
	showPath(g->getPath(1, 4));
	cout << endl;

	cout << "Shortest time between 1 and 4: ";
	g->dijkstraShortestTime(1);
	showPath(g->getPath(1,4));
	cout << endl;
	
	return 0;
}
