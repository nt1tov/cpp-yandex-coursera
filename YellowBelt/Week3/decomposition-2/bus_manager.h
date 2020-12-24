#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

#include "responses.h"

using namespace std;

class BusManager {
    map<string, vector<string>> buses2stop, stops4bus;
public:
    BusManager();

    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;

};