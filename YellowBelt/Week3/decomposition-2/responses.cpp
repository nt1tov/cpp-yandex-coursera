#include "responses.h"
#include "bus_manager.h"
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