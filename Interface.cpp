#include "Interface.h"

using namespace std;

Interface::Interface()
{
	shortest = false;
	favTransport = "";
	origin = NULL;
	dest = NULL;
	limit = 1000;
}

void Interface::RouteMenu()
{
	int opt = 0;

	//system("cls");
	origin = NULL;
	dest = NULL;
	favTransport = "";
	shortest = false;
	limit = 0;

	while (opt != 2)
	{
		cout << "+------------------------------+\n"
			<< "| Collective Transport Routing |\n"
			<< "+------------------------------+\n"
			<< "| 1 - Calculate Rout           |\n"
			<< "+------------------------------+\n"
			<< "| 2 - Exit                     |\n"
			<< "+------------------------------+\n" << endl;

		cin >> opt;

		InvalidInput(2, opt);

		switch (opt)
		{
			case 1:
				graphMenu();
				
				break;

			case 2:
				break;
		}
	}
}

void Interface::graphMenu()
{
	int opt;

	cout
		<< "+------------------------------------+\n"
		<< "| 1 - Experimental Graph (Real Data) |\n"
		<< "+------------------------------------+\n"
		<< "| 2 - Custom Test Graph              |\n"
		<< "+------------------------------------+\n"
		<< "| 3 - Go back                        |\n"
		<< "+------------------------------------+\n" << endl;

	cin >> opt;

	InvalidInput(3, opt);

	switch (opt)
	{
		case 1:
			createExpGraph();
			break;

		case 2:
			createTestGraph();
			break;

		default:
			break;
	}

	findPointMenu(origin);

	if (origin == NULL)
		return;

	findPointMenu(dest);

	if (dest == NULL)
		return;

	quickestVsShortestMenu();
}

void Interface::findPointMenu(Vertex* &v)
{
	int opt = 0, id;
	string ori;

	cout << "+--------------------+\n";

	if (v == origin)
		cout << "| Origin             |\n";
	else
		cout << "| Destination        |\n";

	cout
		<< "+--------------------+\n"
		<< "| 1 - By Street name |\n"
		<< "+--------------------+\n"
		<< "| 2 - By ID          |\n"
		<< "+--------------------+\n"
		<< "| 3 - Go Back        |\n"
		<< "+--------------------+\n" << endl;

	cin >> opt;

	InvalidInput(3, opt);

	switch (opt)
	{
		case 1:
				
			cin.clear();
			cin.ignore(1000, '\n');
			getline(cin, ori);
			v = graph.findVertexByEdge(ori);
		
			if (v == NULL)
			{
				cout << "Street not found\n" << endl;
				return;
			}

			break;

		case 2:

			cin >> id;

			v = graph.findVertex(id);

			if (v == NULL)
			{
				cout << "Point not found\n" << endl;
				return;
			}

		case 3:
			break;
	}
}

void Interface::quickestVsShortestMenu()
{
	int opt = 0;
	shortest = false;

	cout
		<< "+-------------------+\n"
		<< "| 1 - Shortest Path |\n"
		<< "+-------------------+\n"
		<< "| 2 - Quickest Path |\n"
		<< "+-------------------+\n" << endl;

	cin >> opt;

	InvalidInput(2, opt);

	switch (opt)
	{
	case 1:
		shortest = true;
		break;

	case 2:
		break;

	case 3:
		break;
	}

	CalcRouteMenu();
}

void Interface::CalcRouteMenu()
{
	int opt = 0;
	limit = 1000; //Meh... I don't know...

	while (opt != 3)
	{
		cout
			<< "+---------------------------+\n"
			<< "| 1 - Transport Preferences |\n"
			<< "+---------------------------+\n"
			<< "| 2 - Spending Limit        |\n"
			<< "+---------------------------+\n"
			<< "| 3 - Calculate             |\n"
			<< "+---------------------------+\n"
			<< "| 4 - Go Back               |\n"
			<< "+---------------------------+\n" << endl;

		cin >> opt;

		InvalidInput(4, opt);

		switch (opt)
		{
			case 1:
				transportPreferenceMenu();
				break;

			case 2:
				cin >> limit;

				if (limit < 0)
				{
					cout << "Invalid Number\n" << endl;
					limit = 0;
				}

				break;

			case 3:

				if (shortest)
					graph.dijkstraShortestPath(origin->getId(), favTransport, limit);
				else
					graph.dijkstraShortestTime(origin->getId(), favTransport, limit);

				showPath(graph.getPath(origin->getId(), dest->getId()), gv);

			case 4:
				break;
		}

	}
}

void Interface::transportPreferenceMenu()
{
	int opt = 0;

	while (opt != 3)
	{
		favTransport = "";

		cout
			<< "+------------+\n"
			<< "| 1 - Train  |\n"
			<< "+------------+\n"
			<< "| 2- Bus     |\n"
			<< "+------------+\n"
			<< "| 3- Go Back |\n"
			<< "+------------+\n" << endl;

		cin >> opt;

		InvalidInput(3, opt);

		switch (opt)
		{
			case 1:
				favTransport = "Train";
				break;

			case 2:
				favTransport = "Bus";
				break;

			case 3:
				return;
		}

	}
}

void Interface::setGraphViewer(GraphViewer *gv)
{
	this->gv = gv;
}

void Interface::setGraph(Graph *g)
{
	graph = *g;
}

void Interface::createExpGraph()
{
	gv = new GraphViewer(600, 600, false);

	gv->defineEdgeCurved(false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexColor("yellow");

	graph = *addVertexes("A.txt", "D.txt", gv);
	graph.setGraphViewer(gv);
	addEdges(&graph, "B.txt", "C.txt", gv);
}

void Interface::createTestGraph()
{
	graph = Graph();
	gv = new GraphViewer(600, 600, false);

	gv->defineEdgeCurved(false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexColor("yellow");

	GPSCoord trindadeGPS(41.15239, -8.60928);
	GPSCoord aliadosGPS(41.14879, -8.61128);
	GPSCoord SBentoGPS(41.14534, -8.61098);
	GPSCoord ReitoriaGPS(41.14648, -8.61558);
	GPSCoord ClerigosGPS(41.14581, -8.61402);
	GPSCoord PSPGPS(41.14357, -8.60877);
	GPSCoord rivoliGPS(41.14778, -8.60989);
	GPSCoord CamaraGPS(41.14994, -8.61044);
	GPSCoord CasaGPS(41.15881, -8.63081);

	Vertex *v1 = new Vertex(trindadeGPS, 1);
	Vertex *v2 = new Vertex(aliadosGPS, 2);
	Vertex *v3 = new Vertex(SBentoGPS, 3);
	Vertex *v4 = new Vertex(ReitoriaGPS, 4);
	Vertex *v5 = new Vertex(ClerigosGPS, 5);
	Vertex *v6 = new Vertex(PSPGPS, 6);
	Vertex *v7 = new Vertex(rivoliGPS, 7);
	Vertex *v8 = new Vertex(CamaraGPS, 8);
	Vertex *v9 = new Vertex(CasaGPS, 8);

	Info TAL(1, "1-2", false, true); // METRO 1-2
	Info ASB(2, "2-3", false, true); // METRO 2-3
	Info SBPSP(3, "3-6", false, true); // METRO 3-6
	Info TREI(4, "1-4", false, false); // PE 1-4
	Info REIRI(5, "4-7", false, false); // PE 4-7
	Info RICAM(6, "7-8", false, false); // PE 7-8
	Info CAMPSP(7, "8-6", false, false); // PE 8-6
	Info REISB(8, "4-3", true, false); // BUS 4-3
	Info RISB(9, "7-3", true, false); // BUS 7-3
	Info SBCAM(10, "3-8", true, false); // BUS 3-8
	Info ALCA(11, "2-9", false, false); // PE 2-9
	Info CACLE(12, "9-5", true, false); // BUS 9-5
	Info SBCLE(13, "3-5", true, false); // PE 3-5
	Info CLEPSP(14, "5-6", false, false); // PE 5-6

	graph.addVertex(v1);
	graph.addVertex(v2);
	graph.addVertex(v3);
	graph.addVertex(v4);
	graph.addVertex(v5);
	graph.addVertex(v6);
	graph.addVertex(v7);
	graph.addVertex(v8);

	int x_origin = -graph.getVertexSet().at(0)->getCoords().getLatitude(), 
		y_origin = -graph.getVertexSet().at(0)->getCoords().getLongitude();

	gv->addNode(graph.getVertexSet().at(0)->getId(), 0, 0);

	for (unsigned int i = 1; i < graph.getVertexSet().size(); i++)
	{
		Vertex *v = graph.getVertexSet().at(i);

		gv->addNode(v->getId(), (v->getCoords().getLatitude() + x_origin) * 1350000, 
			(v->getCoords().getLongitude() + y_origin) * 1000000);
		gv->setVertexSize(v->getId(), 1);
		gv->setVertexLabel(v->getId(), ".");
	}

	graph.addEdge(v1->getId(), v2->getId(), TAL, calcDistance(trindadeGPS, aliadosGPS)); // 1-2

	gv->addEdge(TAL.getID(), v1->getId(), v2->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(TAL.getID(), 3);
	gv->setEdgeColor(TAL.getID(), GREEN);

	graph.addEdge(v1->getId(), v4->getId(), TREI, calcDistance(trindadeGPS, ReitoriaGPS)); // 1-4
	graph.addEdge(v4->getId(), v1->getId(), TREI, calcDistance(trindadeGPS, ReitoriaGPS)); // 4-1

	gv->addEdge(TREI.getID(), v1->getId(), v4->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(TREI.getID(), 3);
	gv->setEdgeColor(TREI.getID(), RED);


	graph.addEdge(v2->getId(), v3->getId(), ASB, calcDistance(aliadosGPS, SBentoGPS));  // 2-3

	gv->addEdge(ASB.getID(), v2->getId(), v3->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(ASB.getID(), 3);
	gv->setEdgeColor(ASB.getID(), GREEN);

	graph.addEdge(v2->getId(), v9->getId(), ALCA, calcDistance(aliadosGPS, CasaGPS)); // 2 -9
	graph.addEdge(v9->getId(), v2->getId(), ALCA, calcDistance(aliadosGPS, CasaGPS)); // 9-2

	gv->addEdge(ALCA.getID(), v2->getId(), v9->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(ALCA.getID(), 3);
	gv->setEdgeColor(ALCA.getID(), RED);

	graph.addEdge(v5->getId(), v3->getId(), SBCLE, calcDistance(SBentoGPS, ClerigosGPS)); // 5-3
	graph.addEdge(v3->getId(), v5->getId(), SBCLE, calcDistance(SBentoGPS, ClerigosGPS)); // 3-5

	gv->addEdge(SBCLE.getID(), v5->getId(), v3->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(SBCLE.getID(), 3);
	gv->setEdgeColor(TAL.getID(), RED);

	graph.addEdge(v3->getId(), v6->getId(), SBPSP, calcDistance(SBentoGPS, PSPGPS)); // 3-6

	gv->addEdge(SBPSP.getID(), v3->getId(), v6->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(SBPSP.getID(), 3);
	gv->setEdgeColor(SBPSP.getID(), GREEN);

	graph.addEdge(v9->getId(), v5->getId(), CACLE, calcDistance(CasaGPS, ClerigosGPS)); // 9-5

	gv->addEdge(CACLE.getID(), v9->getId(), v5->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(CACLE.getID(), 3);
	gv->setEdgeColor(CACLE.getID(), BLUE);

	graph.addEdge(v5->getId(), v6->getId(), CLEPSP, calcDistance(ClerigosGPS, PSPGPS)); // 5-6
	graph.addEdge(v6->getId(), v5->getId(), CLEPSP, calcDistance(ClerigosGPS, PSPGPS)); // 6-5

	gv->addEdge(CLEPSP.getID(), v5->getId(), v6->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(CLEPSP.getID(), 3);
	gv->setEdgeColor(CLEPSP.getID(), RED);

	graph.addEdge(v4->getId(), v3->getId(), REISB, calcDistance(ReitoriaGPS, SBentoGPS)); // 4 -3

	gv->addEdge(REISB.getID(), v4->getId(), v3->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(REISB.getID(), 3);
	gv->setEdgeColor(REISB.getID(), BLUE);

	graph.addEdge(v4->getId(), v7->getId(), REIRI, calcDistance(ReitoriaGPS, rivoliGPS)); // 4-7
	graph.addEdge(v7->getId(), v4->getId(), REIRI, calcDistance(ReitoriaGPS, rivoliGPS)); // 7-4

	gv->addEdge(REIRI.getID(), v4->getId(), v7->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(REIRI.getID(), 3);
	gv->setEdgeColor(REIRI.getID(), RED);

	graph.addEdge(v7->getId(), v8->getId(), RICAM, calcDistance(rivoliGPS, CamaraGPS)); // 7-8
	graph.addEdge(v8->getId(), v7->getId(), RICAM, calcDistance(rivoliGPS, CamaraGPS)); // 8-7

	gv->addEdge(RICAM.getID(), v7->getId(), v8->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(RICAM.getID(), 3);
	gv->setEdgeColor(RICAM.getID(), RED);

	graph.addEdge(v8->getId(), v6->getId(), CAMPSP, calcDistance(CamaraGPS, PSPGPS)); // 8-6
	graph.addEdge(v6->getId(), v8->getId(), CAMPSP, calcDistance(CamaraGPS, PSPGPS)); // 6-8

	gv->addEdge(CAMPSP.getID(), v7->getId(), v8->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(CAMPSP.getID(), 3);
	gv->setEdgeColor(CAMPSP.getID(), RED);

	graph.addEdge(v7->getId(), v3->getId(), RISB, calcDistance(rivoliGPS, SBentoGPS)); // 7-3

	gv->addEdge(RISB.getID(), v7->getId(), v3->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(RISB.getID(), 3);
	gv->setEdgeColor(RISB.getID(), BLUE);
}


