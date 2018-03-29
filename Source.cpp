#include "Interface.h"
#include "GPSCoord.h"

using namespace std;

int main()
{

	//Graph *g = addVertexes("A.txt");
	//addEdges(g, "B.txt", "C.txt");
	Graph* test_graph = new Graph();
	Interface interface = Interface(*test_graph);
	interface.RouteMenu(); 

	return 0;
}
