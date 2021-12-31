#include "json/json.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include "API.h"

using namespace std;

int main()
{

	TopologyList testing;
	testing.readJSON("topology.json");
	testing.writeJSON("top1");

	vector<Topology> t = testing.queryTopologies();
	cout << t[0].getID() << endl;

	vector<device> d = t[0].queryDevices();
	cout << d[0].getID() << endl;

	vector<device> d2 = t[0].queryDevicesWithNetlistNode("n1");
	cout << d2[0].getID() << endl;

	testing.deleteTopology("top1");

	return EXIT_SUCCESS;
}
