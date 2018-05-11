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

Graph* addVertexes(string f1, string f2, GraphViewer *gv)
{
	ifstream r1, rd;
	string r1l, r2l, label = ".";
	Graph *g = NULL;
	int pos1, pos2, node_id, pos1_d, pos2_d;
	double lat, longit;
	int lat_redux, longit_redux;

	label.push_back(1);

	r1.open(f1.c_str());

	if (!r1.is_open())
	{
		cout << "Error opening file 1\n";
		return g;
	}

	rd.open(f2.c_str());

	if (!rd.is_open())
	{
		cout << "Error opening file 2\n";
		return g;
	}

	g = new Graph();

	while (getline(r1, r1l) && getline(rd, r2l))
	{
		node_id = extractID(r1l);
		pos1 = r1l.find(';');
		pos1_d = r2l.find(';');
		pos2 = r1l.find(';', pos1 + 1);
		pos2_d = r2l.find(';', pos1_d + 1);
		lat = stod(r1l.substr(pos1 + 1, pos2 - pos1 - 1));
		longit = stod(r1l.substr(pos2 + 1));
		lat_redux = stoi(r2l.substr(pos1_d + 1, pos2_d - pos1_d - 1));
		longit_redux = stoi(r2l.substr(pos2_d + 1));
		g->addVertex(GPSCoord(lat, longit), node_id);
		gv->addNode(node_id, lat_redux - 400, longit_redux - 100);
		gv->setVertexSize(node_id, 5);
		gv->setVertexLabel(node_id, ".");
	}

	r1.close();
	rd.close();

	return g;
} 

void addEdges(Graph *g, string f2, string f3, GraphViewer *gv)
{
	ifstream r2, r3;
	string r2l, r3l, rdl, s_name, route, line;
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
				pos1_2 = r3l.find(';', pos1_1 + 1);

				destID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));
				
				i = new Info(street_id2, "Path No " + to_string(street_id2));

				if (g->findVertex(originID) == NULL || g->findVertex(destID) == NULL)
					continue;

				g->addEdge(originID, destID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
				
				g->addEdge(destID, originID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));

				gv->addEdge(street_id2, originID, destID, EdgeType::UNDIRECTED);
				gv->setEdgeThickness(street_id2, 3);
				gv->setEdgeColor(street_id2, RED);
				
				getline(r3, r3l);
				street_id2 = extractID(r3l);
			}
			
		pos1_1 = r2l.find(';');
		
		if (r2l.at(pos1_1 + 1) == ';')
		{
			s_name = "Path No " + to_string(street_id1);
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
			}
			else
				if (r2l.at(r2l.length() - 1) == 'm')
				{
					i->setTrainStation(true);
				}

		pos1_1 = r3l.find(';');
		pos1_2 = r3l.find(';', pos1_1 + 1);

		originID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));

		pos1_1 = pos1_2;
		pos1_2 = r3l.find(';', pos1_1);

		destID = stoi(r3l.substr(pos1_1 + 1, pos1_2 - pos1_1 - 1));

		if (i->is_trainStation())
		{
			Vertex *v = g->findVertex(originID), *v2 = g->findVertex(destID);

			if (v != NULL && v2 != NULL)
			{
				v->setConectionToTrain(true);
				v2->setConectionToTrain(true);
			}
		}

		if (g->findVertex(originID) == NULL || g->findVertex(destID) == NULL)
			continue;

		g->addEdge(originID, destID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
		
		if(i->is_busStation())
		{ 
			gv->addEdge(street_id1, originID, destID, EdgeType::UNDIRECTED);
			gv->setEdgeThickness(street_id1, 3);
			gv->setEdgeColor(street_id1, BLUE);
			g->addEdge(destID, originID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
		}
		else
			if(i->is_trainStation())	
			{
				gv->addEdge(street_id1, originID, destID, EdgeType::UNDIRECTED);
				gv->setEdgeThickness(street_id1, 3);
				gv->setEdgeColor(street_id1, GREEN);
				g->addEdge(destID, originID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
			}
			else
			{
				gv->addEdge(street_id1, originID, destID, EdgeType::UNDIRECTED);
				gv->setEdgeThickness(street_id1, 3);
				gv->setEdgeColor(street_id1, RED);
				g->addEdge(destID, originID, *i, calcDistance(g->findVertex(originID)->getCoords(), g->findVertex(destID)->getCoords()));
			}	
	}

	r2.close();
	r3.close();

	gv->rearrange();

	addStationstoGraph(g, gv, street_id1);
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

	return res; //Km
}

double calcDistanceSimplified(GPSCoord gps1, GPSCoord gps2)
{
	return sqrt(pow(gps1.getLatitude() - gps2.getLatitude(), 2) + pow(gps1.getLongitude() - gps2.getLongitude(), 2)) / 1000;
}

void showPath(vector<Vertex*> v, GraphViewer *gv, bool increaseSize)
{
	unsigned int i, j;
	double sector_time = 0;
	string last_sector = "", current_sector = "";

	for (i = 0; i < v.size() - 1; i++)
	{
		if (increaseSize)
			gv->setVertexSize(v.at(i)->getId(), 15);

		if(i != 0)
			gv->setVertexColor(v.at(i)->getId(), GREEN);
		else
			if(increaseSize)
				gv->setVertexSize(v.at(i)->getId(), 20);

		for (j = 0; j < v.at(i)->getAdj().size(); j++)
			if (v.at(i)->getAdj().at(j).getDest()->getId() == v.at(i + 1)->getId())
			{
				if (v.at(i)->getAdj().at(j).getInfo().is_busStation())
				{
					current_sector = "Bus";
				}
				else
					if (v.at(i)->getAdj().at(j).getInfo().is_trainStation())
					{
						current_sector = "Subway";
					}
					else
					{
						current_sector = "Walk";
					}

				if (i != 0 && current_sector != last_sector)
				{
					if (sector_time >= 1)
						cout << fixed << setprecision(0) << " (" << sector_time << " minutes)" << endl;
					else
						cout << fixed << setprecision(0) << " (" << sector_time * 60 << " seconds)" << endl;

					sector_time = v.at(i)->getAdj().at(j).getTime();
				}
				else
					sector_time += v.at(i)->getAdj().at(j).getTime();

				cout << endl << v.at(i)->getAdj().at(j).getInfo().getName() << endl << endl
					<< "| " << current_sector << endl << "V";

				last_sector = current_sector;
			}
	}

	if (increaseSize)
		gv->setVertexSize(v.at(i)->getId(), 20);

	gv->setVertexColor(v.at(i)->getId(), BLACK);

	cout << endl << "Destination";

	if (sector_time >= 1)
		cout << fixed << setprecision(0) << " (" << sector_time << " minutes)" << endl;
	else
		cout << fixed << setprecision(0) << " (" << sector_time * 60 << " seconds)\n" << endl;
}

void addStationstoGraph(Graph *graph, GraphViewer *gv, int lastEdge)
{
	if (&graph == NULL || gv == NULL)
		return;

	double d;

	for (Vertex *v : graph->getVertexSet())
		if (v->isConectedToTrain())
			for (Vertex *v2 : graph->getVertexSet())
			if(!v2->isConectedToTrain())
			{
				d = calcDistance(v->getCoords(), v2->getCoords());

				if(d <= 0.025)
				{
					graph->addEdge(v->getId(), v2->getId(), Info(lastEdge++, "Path number" + to_string(lastEdge)), d);
					graph->addEdge(v2->getId(), v->getId(), Info(lastEdge, "Path number" + to_string(lastEdge)), d);

					gv->setEdgeThickness(lastEdge, 3);
					gv->addEdge(lastEdge, v->getId(), v2->getId(), EdgeType::UNDIRECTED);
					gv->setEdgeColor(lastEdge, RED);
				}

			}
}

int getEditingDistance(string word, string pattern)
{
	vector<vector<int>> D(word.length() + 1, vector<int>(pattern.length() + 1, 100));
	int operations[3];
	unsigned int j, i;


	//Initialization

	for (i = 0; i <= word.length(); i++)
		D.at(i).at(0) = i;

	for (j = 0; j <= pattern.length(); j++)
		D.at(0).at(j) = j;

	//Recurrence

	unsigned int subs_penalty = 0, delete_penalty = 0, min = 0;

	for (i = 1; i <= word.length(); i++)
		for (j = 1; j <= pattern.length(); j++)
			if (word.at(i - 1) == pattern.at(j - 1))
				D.at(i).at(j) = D.at(i - 1).at(j - 1);
			else
			{
				operations[0] = D.at(i - 1).at(j - 1); //Subsitution
				operations[1] = D.at(i - 1).at(j); //Insertion
				operations[2] = D.at(i).at(j - 1); //Elimination

				min = *min_element(operations, operations + 3);
				D.at(i).at(j) = 1 + min;

				if (min == D.at(i - 1).at(j - 1))
					subs_penalty += 10;
				else
					if (min == D.at(i).at(j - 1))
						delete_penalty += 2;
			}

	//Finalization

	/*
	for (i = 0; i <= word.length(); i++)
	{
		for (j = 0; j <= word.length(); j++)
			cout << D.at(i).at(j) << "|";

		cout << endl;
	} */

	if (subs_penalty / 10 >= pattern.length())
		subs_penalty *= 2;
	else
		if (subs_penalty / 10 < 3)
			subs_penalty = 0;

	return D[word.length()][pattern.length()] + subs_penalty + delete_penalty;
}

bool sortEdgesByED(pair<Edge, int> p1, pair<Edge, int> p2)
{
	return p1.second < p2.second;
}





