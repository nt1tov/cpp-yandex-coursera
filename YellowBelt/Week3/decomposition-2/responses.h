#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>


using namespace std;

struct BusesForStopResponse {
    vector<string> buses;
};

struct StopsForBusResponse {
    string this_bus;
    vector<string> stops;
    map<string, vector<string>> buses2stop;
};

struct AllBusesResponse {
    map <string, vector<string>> stops4bus;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);