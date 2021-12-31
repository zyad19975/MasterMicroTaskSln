# Task 02 Topology

| Class Name   | Member Functions  | Description                                                                        | return value         |
| ------------ | ----------------- | ---------------------------------------------------------------------------------- | -------------------- |
| TopologyList | readJSON()        | this function takes a path to a json file and save it in the vector class topology | void                 |
|              | writeJSON()       | Takes a Topology id and find it in the topology list then writes it to a json file | void                 |
|              | queryTopologies() | returns all the topologies in the list                                             | vector of topologies |
|              | deleteTopology()  | takes a Topology id and delet it from the list                                     | void                 |

| Class Name | Member Functions              | Description                                                                                          | return value      |
| ---------- | ----------------------------- | ---------------------------------------------------------------------------------------------------- | ----------------- |
| Topology   | Topology()                    | class constructor this function takes a path to a json file and save it in the vector class topology | void              |
|            | queryDevices()                | return all the devices in this topology                                                              | vector of devices |
|            | queryDevicesWithNetlistNode() | returns all the devices connected to given netlist                                                   | vector of devices |

| Class Name | Member Functions    | Description                                           | return value |
| ---------- | ------------------- | ----------------------------------------------------- | ------------ |
| Device     | device()            | class constructor this function takes a json variable | void         |
|            | IsConnectedToNode() | check if the node is connected to this devices or not | bool         |

## you can use this API simpliy by creating an object of TopologyList and use all the internal functions

#

# Example

```cpp
//creating object of TopologyList class caled testing
    TopologyList testing;
//read json file caled toplogy.json
	testing.readJSON("topology.json");

//search testing for a topology called top1 and write it into a file
	testing.writeJSON("top1");

//return all the topologies in testing
	vector<Topology> t = testing.queryTopologies();

//print the id of the first topology
	cout << t[0].getID() << endl;

//return all the devices in topolgy t[0]
	vector<device> d = t[0].queryDevices();
	cout << d[0].getID() << endl;

//find all the devices that conected to node n1
	vector<device> d2 = t[0].queryDevicesWithNetlistNode("n1");
	cout << d2[0].getID() << endl;

//delete topolgy top1 from topologyList
	testing.deleteTopology("top1");

```
