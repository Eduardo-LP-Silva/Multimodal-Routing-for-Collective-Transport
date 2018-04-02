#include "Funcs.h"

using namespace std;

void InvalidInput(int n_op, int &op)
{
	while (cin.fail() || (op < 1 || op > n_op))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "Invalid option! Please try again\n" << endl;
		cin >> op;
	}
}

int extractID(string line)
{
	int pos = line.find(';');
	
	return stoi(line.substr(0, pos));
}

Graph* addVertexes(string f1)
{
	ifstream r1;
	string r1l;
	Graph *g = NULL;
	int pos1, pos2, node_id;
	double lat, longit;

	r1.open(f1.c_str());

	if (!r1.is_open())
	{
		cout << "Error opening file 1\n";
		return g;
	}

	g = new Graph();

	while (getline(r1, r1l))
	{
		node_id = extractID(r1l);
		pos1 = r1l.find(';');
		pos2 = r1l.find(';', pos1);
		lat = stod(r1l.substr(pos1 + 1, pos2 - pos1 - 1));
		longit = stod(r1l.substr(pos2 + 1));
		g->addVertex(GPSCoord(lat, longit), node_id);
	}

	r1.close();

	return g;
} 

void addEdges(Graph *g, string f2, string f3)
{
	ifstream r2, r3;
	string r2l, r3l, s_name, route, line;
	int street_id2, street_id1, originID, destID;
	int pos1_1, pos1_2;
	bool bothWays = false, no_name = false;
	Info *i;

	r2.open(f2.c_str());

	if(!r2.is_open())
	{
		cout << "Error in opening file 2";
		return;
	}

	r3.open(f3.c_str());

	if (!r3.is_open())
	{
		cout << "Error in opening file 3";
		return;
	}

	while (getline(r2, r2l) && getline(r3, r3l))
	{
		bothWays = false;
		no_name = false;
		street_id1 = extractID(r2l);
		street_id2 = extractID(r3l);

		if(street_id1 != street_id2)
			while(street_id1 > street_id2)
			{
				pos1_1 = r3l.find(';');
				pos1_2 = r3l.find(';', pos1_1 + 1);

				originID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));

				pos1_1 = pos1_2;
				pos1_2 = r3l.find(';', pos1_1);

				destID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));
				
				i = new Info(street_id2, "Path No " + to_string(street_id2));

				g->addEdge(originID, destID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
				getline(r3, r3l);
				street_id2 = extractID(r3l);
			}
			
		pos1_1 = r2l.find(';');
		
		if (r2l.at(pos1_1 + 1) == ';')
		{
			s_name = street_id1;
			pos1_2 = pos1_1 + 1;
			no_name = true;
		}
		else
		{
			pos1_2 = r2l.find(';', pos1_1 + 1);
			s_name = r2l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1);
		}

		if (r2l.at(pos1_2 + 1) == 'T')
		{
			bothWays = true;
			pos1_1 = pos1_2 + 5;
		}
		else
			pos1_1 = pos1_2 + 6;

		i = new Info(street_id1, s_name);

		if (r2l.at(pos1_1 + 1) != ';')
			if (r2l.at(r2l.length() - 1) == 's')
			{
				i->setBusStation(true);

				if (no_name)
					i->setName("Bus");
			}
			else
				if (r2l.at(r2l.length() - 1) == 'm')
				{
					i->setTrainStation(true);

					if (no_name)
						i->setName("Subway");
				}

		pos1_1 = r3l.find(';');
		pos1_2 = r3l.find(';', pos1_1 + 1);

		originID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));

		pos1_1 = pos1_2;
		pos1_2 = r3l.find(';', pos1_1);

		destID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));

		g->addEdge(originID, destID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));

		if (bothWays)
			g->addEdge(destID, originID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
	}

	r2.close();
	r3.close();
}

double toRad(double deg) 
{
	return deg * M_PI / 180;
}

double toDeg(double rad) 
{
	return rad * 180 / M_PI;
}

double calcDistance(GPSCoord gps1, GPSCoord gps2)
{
	double lat1r, lon1r, lat2r, lon2r, u, v;
	double res;

	lat1r = toRad(gps1.getLatitude());
	lon1r = toRad(gps1.getLongitude());
	lat2r = toRad(gps2.getLatitude());
	lon2r = toRad(gps2.getLongitude());
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);

	res = 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

	return res;
}

void showPath(vector<Vertex*> v)
{
	unsigned int i;

	for (i = 0; i < v.size() - 1; i++)
	{
		cout << v.at(i)->getId() << endl 
			<< "|" << endl 
			<< "V" << endl;

		for (unsigned int j = 0; j < v.at(i)->getAdj().size(); j++)
			if (v.at(i)->getAdj().at(j).getDest()->getId() == v.at(i + 1)->getId())
			{
				cout << v.at(i)->getAdj().at(j).getInfo().getName() << endl
					<< "|";

				if (v.at(i)->getAdj().at(j).getInfo().is_busStation())
					cout << " Bus";
				else
					if (v.at(i)->getAdj().at(j).getInfo().is_trainStation())
						cout << "Subway";

				if(v.at(i)->getAdj().at(j).getTime() >= 1)
					cout << fixed << setprecision(0) <<  " (" << v.at(i)->getAdj().at(j).getTime() << " minutes)" << endl;
				else
					cout << fixed << setprecision(0) << " (" << v.at(i)->getAdj().at(j).getTime() * 60 << " seconds)" << endl;

				cout << "V" << endl;
			}
	}

	cout << v.at(i)->getId() << endl;
}
