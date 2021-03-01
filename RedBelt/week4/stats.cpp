#include "stats.h"
#include <iostream>

using namespace std;


HttpRequest ParseRequest(string_view line){
    HttpRequest req;
    line = line.substr(line.find_first_not_of(' '));
    line = line.substr(0, line.find_last_not_of(' ')+1);
    //cout <<"|"<< line <<"|" << endl;
    auto method_end_pos = line.find(" ");
    req.method = line.substr(0, method_end_pos);
    auto sub_line = line.substr(method_end_pos+1);
    auto uri_end_pos = sub_line.find(" ");
    req.uri = sub_line.substr(0, uri_end_pos);
    req.protocol = sub_line.substr(uri_end_pos+1);
    return req;
}
Stats::Stats():
    known_uris{"/", "/order", "/product", "/basket", "/help"},
    known_methods{"GET", "POST", "PUT", "DELETE"},
    uri_stats{
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0}
    },
    method_stats{
        {"GET", 0},
        {"POST", 0},
        {"PUT", 0},
        {"DELETE", 0},
        {"UNKNOWN", 0}
    }
{}

void Stats::AddMethod(string_view method){
    if(known_methods.find(method) != known_methods.end()){
        method_stats[method]++;
    }
    else{
         method_stats["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri){
    if(known_uris.find(uri) != known_uris.end()){
        uri_stats[uri]++;
    }
    else{
        uri_stats["unknown"]++;
    }
}

const map<string_view, int>& Stats::GetMethodStats() const{
    return method_stats;
}
const map<string_view, int>& Stats::GetUriStats() const{
    return uri_stats;
}