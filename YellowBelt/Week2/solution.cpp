#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

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
        int stop_count;
        is >> stop_count;
        for (auto i = 0; i < stop_count; ++i) {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
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
        os << "No stop";
    }
    else{
        auto i = 0;
        for(auto& item: r.buses){
            os << item;
            if(++i < static_cast<int>(r.buses.size())){
                os << " ";
            }
        }
    }
    return os;
}

struct StopsForBusResponse {
    vector<string> stops;
    map<string, vector<string>> buses2stop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.buses2stop.size() == 0){
        os << "No bus";
    }
    else{
        auto i = 0;
        for(auto& stop: r.stops){
            os << "Stop " << stop << ": ";
            if(r.buses2stop.count(stop) == 0){
                os << "no interchange";
            }
            else{
                for(auto& bus: r.buses2stop.at(stop)){
                    os << " " << bus;
                }
            }
            if(++i < static_cast<int>(r.stops.size())){
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
    if (r.stops4bus.size() == 0) {
        os << "No buses";
    } 
    else {
        auto i = 0;
        for (auto& bus : r.stops4bus) {
            os << "Bus " << bus.first << ":";
            for (auto& stop : bus.second) {
                os << " " << stop;
            }
            if (++i < static_cast<int>(r.stops4bus.size())) {
                os << endl;
            }
        }
    }
    return os;
}

class BusManager {
    map<string, vector<string>> buses2stop, stops4bus;
public:
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
                for (auto& bus_n : GetBusesForStop(stop).buses) {
                    if (bus_n != bus) {
                        res.buses2stop[stop].push_back(bus_n);
                    }
                }
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

    cin >> query_count;

    BusManager bm;
    
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
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
        }
    }

    return 0;
}
