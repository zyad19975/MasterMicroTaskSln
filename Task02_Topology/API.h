#include <json/json.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#ifndef API_H
#define API_H

class device
{
private:
    string DeviceID;
    string DeviceType;
    Json::Value DeviceProperties;
    Json::Value DeviceNetlist;
    Json::Value Raw;

public:
    device(Json::Value DeviceRaw);
    string getID();
    string getType();
    bool IsConnectedToNode(string Node);
    Json::Value getJson();
};

class Topology
{
private:
    string topology_id;
    vector<device> devices;
    Json::Value Raw;

public:
    Topology(string file_path);
    vector<device> queryDevices();
    vector<device> queryDevicesWithNetlistNode(string NetlistNodeID);
    string getID();
    Json::Value getJson();
};


class TopologyList
{
private:
    vector<Topology> list;

public:
    TopologyList();
    void readJSON(string file_path);
    void writeJSON(string TopologyID);
    vector<Topology> queryTopologies();
    void deleteTopology(string TopologyID);
};
#endif