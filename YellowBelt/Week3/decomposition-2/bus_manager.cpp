#include "bus_manager.h"
#include "responses.h"


BusManager::BusManager() {
    buses2stop.clear();
    stops4bus.clear();
}
void BusManager::AddBus(const string& bus, const vector<string>& stops) {      
    for (const string &stop: stops) {
        stops4bus[bus].push_back(stop);
        buses2stop[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse res;
    if(buses2stop.count(stop) > 0 ){
        res.buses = buses2stop.at(stop);
    }
    return res;

}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse res;
    if(stops4bus.count(bus) > 0){
        for (auto& stop : stops4bus.at(bus)) {
            res.stops.push_back(stop);
            res.buses2stop[stop] = GetBusesForStop(stop).buses;
            res.this_bus = bus;
        }
    }
    return res;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse res;
    res.stops4bus = stops4bus;
    return res;
}

