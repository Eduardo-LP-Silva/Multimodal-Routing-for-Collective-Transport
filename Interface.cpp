#include "Interface.h"

using namespace std;

Interface::Interface(Graph<Vertex<GPSCoord>> g)
{
	graph = g;
}

void Interface::RouteMenu()	
{
	int opt = 0;

	system("cls");

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
				CalcRouteMenu();
				break;

			case 2:
				break;
		}
	}
}

void Interface::CalcRouteMenu()
{
	int opt = 0;
	string origin, destination;

	cin.clear();
	cin.ignore(1000, '\n');

	cout << "Origin: ";
	getline(cin, origin);
	
	cout << endl << endl << "Destination: ";
	getline(cin, destination);

	while (opt != 3)
	{
		cout << "+---------------------------+\n"
			<< "| 1 - Transport Preferences |\n"
			<< "+---------------------------+\n"
			<< "| 2 - Spending Limit        |\n"
			<< "+---------------------------+\n"
			<< "| 3 - Exit                  |\n"
			<< "+---------------------------+\n" << endl;

		cin >> opt;

		InvalidInput(3, opt);

		switch (opt)
		{
			case 1:

				break;

			case 2:

				break;

			case 3:
				break;
		}

	}
}
