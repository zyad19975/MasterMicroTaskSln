#include "API.h"
using namespace std;

Topology::Topology(string file_path)
{
    ifstream input_file(file_path);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << file_path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string rawJson = string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    Json::Value TopologyJson;
    Json::Reader reader;
    reader.parse(rawJson, TopologyJson);
    topology_id = TopologyJson["id"].asString();
    for (int i = 0; i < TopologyJson["components"].size(); i++)
    {
        device temp(TopologyJson["components"][i]);
        devices.push_back(temp);
    }
    Raw = TopologyJson;
}
string Topology::getID()
{
    return topology_id;
}

vector<device> Topology::queryDevices()
{
    return devices;
}
vector<device> Topology::queryDevicesWithNetlistNode(string NetlistNodeID)
{
    vector<device> connectedDevices;
    for (int i = 0; i < devices.size(); i++)
    {
        if (devices[i].IsConnectedToNode(NetlistNodeID))
        {
            connectedDevices.push_back(devices[i]);
        }
    }
    return connectedDevices;
}
Json::Value Topology::getJson()
{
    return Raw;
}

//################# Device Functions ####################
device::device(Json::Value DeviceRaw)
{
    Raw = DeviceRaw;
    DeviceID = DeviceRaw["id"].asString();;
    DeviceType = DeviceRaw["type"].asString();;
    DeviceNetlist = DeviceRaw["netlist"];
    vector<string> members = DeviceRaw.getMemberNames();
    for (int i = 0 ; i < members.size(); i++)
        if (members[i] == "id" || members[i] == "netlist" || members[i] == "type")
        {
            continue;
        }
        else
        {
            DeviceProperties = DeviceRaw[members[i]];
        }
}

string device::getID()
{
    return DeviceID;
}
string device::getType()
{
    return DeviceType;
}
bool device::IsConnectedToNode(string Node)
{
    vector<string> members = DeviceNetlist.getMemberNames();
    for (int i = 0 ; i < members.size(); i++)
    {
        if (DeviceNetlist[members[i]] == Node)
        {
            return true;
        }
    }
    return false;
}
Json::Value device::getJson()
{
    return Raw;
}

//################## TopologyList ##################
TopologyList::TopologyList()
{ //empty function to generate empty TopologyList
}
void TopologyList::readJSON(string file_path)
{
    Topology temp(file_path);
    list.push_back(temp);
}
vector<Topology> TopologyList::queryTopologies()
{
    return list;
}
void TopologyList::deleteTopology(string TopologyID)
{
    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++,i++)
    {
        if (list[i].getID() == TopologyID)
        {
            list.erase(it);
            return;
        }
    }
}
void TopologyList::writeJSON(string TopologyID)
{
    for (int i = 0 ; i < list.size(); i++)
    {
        if (list[i].getID() == TopologyID)
        {
            string filename = list[i].getID();
            filename.append(".json");
            Json::Value temp = list[i].getJson();
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, temp);
            std::ofstream out(filename);
            out << json_file;
            out.close();
            return;
        }
    }
}