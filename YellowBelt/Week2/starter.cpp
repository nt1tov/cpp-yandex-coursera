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
     if (operation_code == "NEW_BUS") {
      q.type = QueryType::NewBus;
      is >> q.bus;
      int stop_count;
      is >> stop_count;
      for (auto i = 0; i < stop_count; ++i) {
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
        int i = 0;
        for(auto& item: r.buses){
            os << item;
            if(++i < r.buses.size()){
                os << " ";
            }
        }
    }
    return os;
}

struct StopsForBusResponse {
    vector<string> stops;
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.buses_to_stops.size() == 0){
        os << "No bus";
    }
    else{
        int i = 0;
        for(auto& stop: stops){
            os << "Stop: " << stop << ": ";
            if(r.buses_to_stops.count(stop) == 0){
                os << "no interchange";
            }
            else{
                for(auto& bus: r.buses_to_stops.at(stop)){
                    os << " " << bus;
                }
            }
            if(++i < r.stops.size()){
                os << endl;
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map <string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.stops_to_buses.size() == 0) {
        os << "No buses";
    } 
    else {
        int i = 0;
        for (auto& bus : r.stops_to_buses) {
            os << "Bus " << bus.first << ":";
            for (auto& stop : bus.second) {
                os << " " << stop;
            }
            if (++i < r.stops_to_buses.size()) {
                os << endl;
            }
        }
    }
    return os;
}

class BusManager {
  map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      buses_to_stops[bus] = stops;
      stops.resize(stop_count);
      for (string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
      }

    // Реализуйте этот метод
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
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
