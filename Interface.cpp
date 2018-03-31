#include "Interface.h"

using namespace std;

Interface::Interface(Graph g)
{
	graph = g;
	shortest = false;
	favTransport = "";
	origin = NULL;
	dest = NULL;
	limit = 0;
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
	limit = 0;

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
					graph.dijkstraShortestPath(origin->getId());
				else
					graph.dijkstraShortestTime(origin->getId());

				showPath(graph.getPath(origin->getId(), dest->getId()));

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


