#include "Interface.h"

using namespace std;

Interface::Interface()
{
	shortest = false;
	favTransport = "";
	origin = NULL;
	dest = NULL;
	limit = 1000;
	test = false;
}

void Interface::graphMenu()
{
	int opt;

	cout
		<< "+------------------------------------+\n"
		<< "| Choose a graph                     |\n"
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
		test = false;
		createExpGraph();
		break;

	case 2:
		test = true;
		createTestGraph();
		graph.setTest(true);
		break;

	default:
		break;
	}

	RouteMenu();
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
		cout
			<< "+------------------------------+\n"
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
				findPointMenu(origin);

				if (origin == NULL)
					continue;

				findPointMenu(dest);

				if (dest == NULL)
					continue;

				quickestVsShortestMenu();

				break;

			case 2:
				break;
		}
	}
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
	limit = INF;
	favTransport = "";

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

				if(test)
					showPath(graph.getPath(origin->getId(), dest->getId()), gv, false);
				else
					showPath(graph.getPath(origin->getId(), dest->getId()), gv, true);

			case 4:
				break;
		}

	}
}

void Interface::transportPreferenceMenu()
{
	int opt = 0;
	
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
	gv = new GraphViewer(900, 900, false);

	gv->defineEdgeCurved(false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexColor("yellow");

	graph.setGraphViewer(gv);

	GPSCoord trindadeGPS(900, 170); //1
	GPSCoord aliadosGPS(751, 243); //2
	GPSCoord SBentoGPS(746, 255); //3
	GPSCoord ReitoriaGPS(750, 222); //4
	GPSCoord ClerigosGPS(770, 240); //5
	GPSCoord PSPGPS(1000, 277); //6
	GPSCoord rivoliGPS(1000, 218); //7
	GPSCoord CamaraGPS(980, 191); //8
	GPSCoord CasaGPS(789, 170); //9
	GPSCoord CMVGPS(100,200); //10
	GPSCoord gps11(450, 250);
	GPSCoord gps12(500, 230);
	GPSCoord gps13(550, 207);
	GPSCoord gps14(600, 213);
	GPSCoord gps15(750, 215);

	Vertex *v1 = new Vertex(trindadeGPS, 1);
	Vertex *v2 = new Vertex(aliadosGPS, 2);
	Vertex *v3 = new Vertex(SBentoGPS, 3);
	Vertex *v4 = new Vertex(ReitoriaGPS, 4);
	Vertex *v5 = new Vertex(ClerigosGPS, 5);
	Vertex *v6 = new Vertex(PSPGPS, 6);
	Vertex *v7 = new Vertex(rivoliGPS, 7);
	Vertex *v8 = new Vertex(CamaraGPS, 8);
	Vertex *v9 = new Vertex(CasaGPS, 9);
	Vertex *v10 = new Vertex(CMVGPS,10);
	Vertex *v11 = new Vertex(gps11, 11);
	Vertex *v12 = new Vertex(gps12, 12);
	Vertex *v13 = new Vertex(gps13, 13);
	Vertex *v14 = new Vertex(gps14, 14);
	Vertex *v15 = new Vertex(gps15, 15);

	Info TAL(1, "1-2", false, true); // METRO 1-2
	Info ASB(2, "2-3", false, true); // METRO 2-3
	Info SBPSP(3, "3-6", false, true); // METRO 3-6
	Info TREI(4, "1-4", false, false); // PE 1-4
	Info REIRI(5, "4-7", false, false); // PE 4-7
	Info RICAM(6, "7-8", false, false); // PE 7-8
	Info REISB(8, "4-3", true, false); // BUS 4-3
	Info RISB(9, "7-6", true, false); // BUS 7-6
	Info SBCAM(10, "3-8", true, false); // BUS 3-8
	Info ALCA(11, "9-15", false, false); // PE 9-15
	Info CACLE(12, "9-5", true, false); // BUS 9-5
	Info SBCLE(13, "3-5", false, false); // PE 3-5
	Info CLEPSP(14, "5-6", false, false); // PE 5-6
	Info TRIMCAM(15, "1-8", false, false); // PE 1-8
	Info CMV(16, "CMV-3", false, true); // METRO CMV-3
	Info i17(17, "10-11", false, false); //PE 10-11
	Info i18(18, "11-12", true, false); //BUS 11-12
	Info i19(19, "12-13", true, false); //BUS 12-13
	Info i20(20, "13-14", false, false); //PE 13-14
	Info i21(21, "14-15", false, false); //PE 14-15
	Info i22(22, "15-4", false, false); //PE 15-4
	Info i23(23, "10-13", false, false); //PE 10-13
	Info i24(24, "1-9", false, false); //PE 1-9


	graph.addVertex(v1);
	graph.addVertex(v2);
	graph.addVertex(v3);
	graph.addVertex(v4);
	graph.addVertex(v5);
	graph.addVertex(v6);
	graph.addVertex(v7);
	graph.addVertex(v8);
	graph.addVertex(v9);
	graph.addVertex(v10);
	graph.addVertex(v11);
	graph.addVertex(v12);
	graph.addVertex(v13);
	graph.addVertex(v14);
	graph.addVertex(v15);
	
	for(Vertex *v: graph.getVertexSet())
	for (unsigned int i = 1; i < graph.getVertexSet().size(); i++)
	{
		gv->addNode(v->getId(), (int) (v->getCoords().getLatitude() - 500), (int) v->getCoords().getLongitude());
		gv->setVertexSize(v->getId(), 20);
		gv->setVertexLabel(v->getId(), to_string(v->getId()));
	}

	graph.addEdge(v1->getId(), v2->getId(), TAL, calcDistanceSimplified(trindadeGPS, aliadosGPS)); // 1-2
	graph.addEdge(v2->getId(), v1->getId(), TAL, calcDistanceSimplified(trindadeGPS, aliadosGPS));

	gv->addEdge(TAL.getID(), v1->getId(), v2->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(TAL.getID(), 3);
	gv->setEdgeColor(TAL.getID(), GREEN);

	graph.addEdge(v1->getId(), v4->getId(), TREI, calcDistanceSimplified(trindadeGPS, ReitoriaGPS)); // 1-4
	graph.addEdge(v4->getId(), v1->getId(), TREI, calcDistanceSimplified(trindadeGPS, ReitoriaGPS)); // 4-1

	gv->addEdge(TREI.getID(), v1->getId(), v4->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(TREI.getID(), 3);
	gv->setEdgeColor(TREI.getID(), RED);


	graph.addEdge(v2->getId(), v3->getId(), ASB, calcDistanceSimplified(aliadosGPS, SBentoGPS));  // 2-3
	graph.addEdge(v3->getId(), v2->getId(), ASB, calcDistanceSimplified(aliadosGPS, SBentoGPS));

	gv->addEdge(ASB.getID(), v2->getId(), v3->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(ASB.getID(), 3);
	gv->setEdgeColor(ASB.getID(), GREEN);

	graph.addEdge(v15->getId(), v9->getId(), ALCA, calcDistanceSimplified(aliadosGPS, CasaGPS)); // 2 -9
	graph.addEdge(v9->getId(), v15->getId(), ALCA, calcDistanceSimplified(aliadosGPS, CasaGPS)); 

	gv->addEdge(ALCA.getID(), v15->getId(), v9->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(ALCA.getID(), 3);
	gv->setEdgeColor(ALCA.getID(), RED);

	graph.addEdge(v5->getId(), v3->getId(), SBCLE, calcDistanceSimplified(SBentoGPS, ClerigosGPS)); // 5-3
	graph.addEdge(v3->getId(), v5->getId(), SBCLE, calcDistanceSimplified(SBentoGPS, ClerigosGPS)); // 3-5

	gv->addEdge(SBCLE.getID(), v5->getId(), v3->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(SBCLE.getID(), 3);
	gv->setEdgeColor(SBCLE.getID(), RED);

	graph.addEdge(v3->getId(), v6->getId(), SBPSP, calcDistanceSimplified(SBentoGPS, PSPGPS)); // 3-6
	graph.addEdge(v6->getId(), v3->getId(), SBPSP, calcDistanceSimplified(SBentoGPS, PSPGPS));

	gv->addEdge(SBPSP.getID(), v3->getId(), v6->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(SBPSP.getID(), 3);
	gv->setEdgeColor(SBPSP.getID(), GREEN);

	graph.addEdge(v9->getId(), v5->getId(), CACLE, calcDistanceSimplified(CasaGPS, ClerigosGPS)); // 9-5

	gv->addEdge(CACLE.getID(), v9->getId(), v5->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(CACLE.getID(), 3);
	gv->setEdgeColor(CACLE.getID(), BLUE);

	graph.addEdge(v5->getId(), v6->getId(), CLEPSP, calcDistanceSimplified(ClerigosGPS, PSPGPS)); // 5-6
	graph.addEdge(v6->getId(), v5->getId(), CLEPSP, calcDistanceSimplified(ClerigosGPS, PSPGPS)); // 6-5

	gv->addEdge(CLEPSP.getID(), v5->getId(), v6->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(CLEPSP.getID(), 3);
	gv->setEdgeColor(CLEPSP.getID(), RED);

	graph.addEdge(v4->getId(), v3->getId(), REISB, calcDistanceSimplified(ReitoriaGPS, SBentoGPS)); // 4 -3
	graph.addEdge(v3->getId(), v4->getId(), REISB, calcDistanceSimplified(ReitoriaGPS, SBentoGPS));

	gv->addEdge(REISB.getID(), v4->getId(), v3->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(REISB.getID(), 3);
	gv->setEdgeColor(REISB.getID(), BLUE);

	graph.addEdge(v4->getId(), v7->getId(), REIRI, calcDistanceSimplified(ReitoriaGPS, rivoliGPS)); // 4-7
	graph.addEdge(v7->getId(), v4->getId(), REIRI, calcDistanceSimplified(ReitoriaGPS, rivoliGPS)); // 7-4

	gv->addEdge(REIRI.getID(), v4->getId(), v7->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(REIRI.getID(), 3);
	gv->setEdgeColor(REIRI.getID(), RED);

	graph.addEdge(v7->getId(), v8->getId(), RICAM, calcDistanceSimplified(rivoliGPS, CamaraGPS)); // 7-8
	graph.addEdge(v8->getId(), v7->getId(), RICAM, calcDistanceSimplified(rivoliGPS, CamaraGPS)); // 8-7

	gv->addEdge(RICAM.getID(), v7->getId(), v8->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(RICAM.getID(), 3);
	gv->setEdgeColor(RICAM.getID(), RED);

	graph.addEdge(v7->getId(), v6->getId(), RISB, calcDistanceSimplified(rivoliGPS, PSPGPS)); // 7-6

	gv->addEdge(RISB.getID(), v7->getId(), v6->getId(), EdgeType::DIRECTED);
	gv->setEdgeThickness(RISB.getID(), 3);
	gv->setEdgeColor(RISB.getID(), BLUE);

	graph.addEdge(v1->getId(), v8->getId(), TRIMCAM, calcDistanceSimplified(trindadeGPS, CamaraGPS)); // 1-8
	graph.addEdge(v8->getId(), v1->getId(), TRIMCAM, calcDistanceSimplified(trindadeGPS, CamaraGPS));

	gv->addEdge(TRIMCAM.getID(), v1->getId(), v8->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(TRIMCAM.getID(), 3);
	gv->setEdgeColor(TRIMCAM.getID(), RED);

	graph.addEdge(v10->getId(), v3->getId(), CMV, calcDistanceSimplified(CMVGPS, SBentoGPS));  // 10-3
	graph.addEdge(v3->getId(), v10->getId(), CMV, calcDistanceSimplified(CMVGPS, SBentoGPS));

	gv->addEdge(CMV.getID(), v10->getId(), v3->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(CMV.getID(), 3);
	gv->setEdgeColor(CMV.getID(), GREEN);

	graph.addEdge(v10->getId(), v11->getId(), i17, calcDistanceSimplified(CMVGPS, gps11)); //10-11
	graph.addEdge(v11->getId(), v10->getId(), i17, calcDistanceSimplified(CMVGPS, gps11));

	gv->addEdge(i17.getID(), v10->getId(), v11->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i17.getID(), 3);
	gv->setEdgeColor(i17.getID(), RED);

	graph.addEdge(v11->getId(), v12->getId(), i18, calcDistanceSimplified(gps11, gps12)); //11-12
	graph.addEdge(v12->getId(), v11->getId(), i18, calcDistanceSimplified(gps11, gps12));

	gv->addEdge(i18.getID(), v11->getId(), v12->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i18.getID(), 3);
	gv->setEdgeColor(i18.getID(), BLUE);

	graph.addEdge(v12->getId(), v13->getId(), i19, calcDistanceSimplified(gps12, gps13)); //12-13
	graph.addEdge(v13->getId(), v12->getId(), i19, calcDistanceSimplified(gps12, gps13));

	gv->addEdge(i19.getID(), v12->getId(), v13->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i19.getID(), 3);
	gv->setEdgeColor(i19.getID(), BLUE);

	graph.addEdge(v13->getId(), v14->getId(), i20, calcDistanceSimplified(gps13, gps14)); //13-14
	graph.addEdge(v14->getId(), v13->getId(), i20, calcDistanceSimplified(gps13, gps14));

	gv->addEdge(i20.getID(), v13->getId(), v14->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i20.getID(), 3);
	gv->setEdgeColor(i20.getID(), RED);

	graph.addEdge(v14->getId(), v15->getId(), i21, calcDistanceSimplified(gps14, gps15)); //14-15
	graph.addEdge(v15->getId(), v14->getId(), i21, calcDistanceSimplified(gps14, gps15));

	gv->addEdge(i21.getID(), v14->getId(), v15->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i21.getID(), 3);
	gv->setEdgeColor(i21.getID(), RED);

	graph.addEdge(v15->getId(), v4->getId(), i22, calcDistanceSimplified(gps15, ReitoriaGPS)); //15-4
	graph.addEdge(v4->getId(), v15->getId(), i22, calcDistanceSimplified(gps15, ReitoriaGPS));

	gv->addEdge(i22.getID(), v15->getId(), v4->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i22.getID(), 3);
	gv->setEdgeColor(i22.getID(), RED); 

	graph.addEdge(v10->getId(), v13->getId(), i23, calcDistanceSimplified(CMVGPS, gps13)); //10-13
	graph.addEdge(v13->getId(), v10->getId(), i23, calcDistanceSimplified(CMVGPS, gps13));

	gv->addEdge(i23.getID(), v13->getId(), v10->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i23.getID(), 3);
	gv->setEdgeColor(i23.getID(), RED);

	graph.addEdge(v1->getId(), v9->getId(), i24, calcDistanceSimplified(trindadeGPS, CasaGPS)); //1-9
	graph.addEdge(v9->getId(), v1->getId(), i24, calcDistanceSimplified(trindadeGPS, CasaGPS));

	gv->addEdge(i24.getID(), v1->getId(), v9->getId(), EdgeType::UNDIRECTED);
	gv->setEdgeThickness(i24.getID(), 3);
	gv->setEdgeColor(i24.getID(), RED);



}
