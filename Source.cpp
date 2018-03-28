#include "Interface.h"
#include "GPSCoord.h"

using namespace std;

int main()
{
	Graph *g = addVertexes("A.txt");
	addEdges(g, "B.txt", "C.txt");
	Interface interface = Interface(*g);
	interface.RouteMenu(); 

	return 0;
}
