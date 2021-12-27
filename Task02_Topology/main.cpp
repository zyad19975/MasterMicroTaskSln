#include "json/json.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "./jsoncpp.cpp"

using namespace std;

string readFileIntoString(const string &path)
{
	ifstream input_file(path);
	if (!input_file.is_open())
	{
		cerr << "Could not open the file - '"
			 << path << "'" << endl;
		exit(EXIT_FAILURE);
	}
	return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}

int main()
{

	string filename("topology.json");

	string rawJson = readFileIntoString(filename);
	;

	JSONCPP_STRING err;
	Json::Value root;

	Json::Reader reader;
	reader.parse(rawJson, root);
	cout << root << endl;
	return EXIT_SUCCESS;
}
