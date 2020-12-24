#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;


enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};


struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    q.stops.clear();
    q.bus.clear();
    q.stop.clear();


    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;

        int stop_count = 0;
        is >> stop_count;

        q.stops.resize(stop_count);
        for (auto &stop: q.stops) {
            is >> stop;
        }
    } 
    else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } 
    else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } 
    else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    } 
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.size() == 0){
        os << "No stop" << endl;
    }
    else{
        for(auto& item: r.buses){
            os << item << " ";
        }
        os << endl; 
    }
   
    return os;
}

struct StopsForBusResponse {
    string this_bus;
    vector<string> stops;
    map<string, vector<string>> buses2stop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.buses2stop.empty()){
        os << "No bus" << endl;
    }
    else{
        for(auto& stop: r.stops){
            os << "Stop " << stop << ": ";
            if(r.buses2stop.at(stop).size() == 1){
                os << "no interchange" << endl;
            }
            else{
                for(const auto& bus: r.buses2stop.at(stop)){
                    if(bus != r.this_bus)
                        os << bus << " ";
                }
                os << endl;
            }
            
        }
    }
    return os;
}

struct AllBusesResponse {
    map <string, vector<string>> stops4bus;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.stops4bus.empty()) {
        os << "No buses" << endl;;
    } 
    else {
        for (const auto& bus : r.stops4bus) {
            os << "Bus " << bus.first << ": ";
            for (const auto& stop : bus.second) {
                os  << stop  << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
    map<string, vector<string>> buses2stop, stops4bus;
public:
    BusManager() {
        buses2stop.clear();
        stops4bus.clear();
    }
    void AddBus(const string& bus, const vector<string>& stops) {      
        for (const string &stop: stops) {
            stops4bus[bus].push_back(stop);
            buses2stop[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse res;
        if(buses2stop.count(stop) > 0 ){
            res.buses = buses2stop.at(stop);
        }
        return res;

    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse res;
        res.stops4bus = stops4bus;
        return res;
    }

};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    ifstream inf("input.txt");
    inf >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        inf >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
            default:
                throw -1;
        }
    }

    return 0;
}
