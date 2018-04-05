#include "Interface.h"
#include "GPSCoord.h"
#include <sstream>

using namespace std;

/* 100M
GraphViewer* initiateGraphV()
{
	ifstream inFile;
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->defineEdgeCurved(false);
	gv->defineVertexSize(100);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	//Ler o ficheiro nos.txt
	inFile.open("A.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	string line;

	long id = 0;
	double X = 0;
	double Y = 0;

	double Xadd;
	double Yadd;
	long i = 0;

	string dummy;

	dummy.push_back(1); // The given program does not accept space nor empty string for a label so I had to be creative...

	while (getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> id;

		getline(linestream, data, ';');  // read up-to the first ; (discard 😉.
		linestream >> X;
		getline(linestream, data, ';');  // read up-to the first ; (discard 😉.
		linestream >> Y;

		if (i == 0) 		//Sets the first point as the origin of the map
		{					//
			Xadd = -X;		//
			Yadd = -Y;		//
		}					//
							//
		X += Xadd;			//
		Y += Yadd;			//

		X = X * 1350000;		//Since the give program only accepts integer coordinates some shady techniques are applied.
		Y = Y * 1000000;		//X is multiplied more than Y because the proportions were a bit off.

		swap(X, Y);			//Rotates 90ª counter-clockwise
		Y *= -1;

		// cout << X << ", " << Y << "\n";

		gv->addNode(id, X, Y);

		gv->setVertexLabel(id, dummy);

		i++;
	}

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("C.txt");

	if (!inFile) 
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	long long idAresta = 0;
	long long idNoOrigem = 0;
	long long idNoDestino = 0;
	i = 0;

	while (std::getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ;
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ;
		linestream >> idNoDestino;

		gv->addEdge(i, idNoOrigem, idNoDestino, EdgeType::UNDIRECTED);

		gv->setEdgeThickness(i, 8);

		i++;
	}

	inFile.close();

	gv->rearrange();

	return gv;
}*/

int main()
{
	Interface inter = Interface();
	inter.graphMenu();

	/*
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
	cout << endl; */
	
	return 0;
}
