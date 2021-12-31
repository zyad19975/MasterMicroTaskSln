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
}
