#include "Interface.h"
#include "GPSCoord.h"

using namespace std;

int main()
{
	Graph<Vertex<GPSCoord>> g = Graph<Vertex<GPSCoord>>();
	GPSCoord gps1 = GPSCoord(799, 189); //Os valores do A.txt est�o num formato estranho, estes valores n�o sei ao que correspondem
	GPSCoord gps2 = GPSCoord(797, 191);
	double weight = 1; //Valor a atribu�r � a dist�ncia/tempo/whatever
	Vertex<GPSCoord> v1 = Vertex<GPSCoord>(gps1, 477);
	Vertex<GPSCoord> v2 = Vertex<GPSCoord>(gps2, 1859);
	Info v1v2 = Info(1, "Rua de Ramalho Ortig�o"); 
	v1.addEdge(&v2, weight, v1v2); //Tomar aten��o ao bool no B.txt que diz se uma rua tem dois sentidos ou n�o. Se tiver adicionar essa edge mas de v2 para v1
	Interface interface = Interface(g);
	interface.RouteMenu();

	return 0;
}