#include "Interface.h"
#include "GPSCoord.h"

using namespace std;

int main()
{
	Graph *g = addVertexes("A.txt");
	Vertex *v1 = g->findVertex(477), *v2 = g->findVertex(1859);
	addEdges(g, "B.txt", "C.txt");
	

	/*
	if (v1 == NULL)
	{
		GPSCoord gps1 = GPSCoord(799, 189); //Os valores do A.txt est�o num formato estranho, estes valores n�o sei ao que correspondem
		v1 = new Vertex(gps1, 477);
	}

	if (v2 == NULL)
	{
		GPSCoord gps2 = GPSCoord(797, 191);
		v2 = new Vertex(gps2, 1859);
	}
	
	
	double weight = 1; //Valor a atribu�r � a dist�ncia/tempo/whatever
	Info v1v2 = Info(1, "Rua de Ramalho Ortig�o"); 
	v1->addEdge(v2, weight, v1v2); //Tomar aten��o ao bool no B.txt que diz se uma rua tem dois sentidos ou n�o. Se tiver adicionar essa edge mas de v2 para v1
	Interface interface = Interface(g);
	interface.RouteMenu(); */

	return 0;
}
