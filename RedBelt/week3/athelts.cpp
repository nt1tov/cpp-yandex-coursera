#include <iostream>
#include <list>

#include "test_runner.h"
#include "profile.h"



using namespace std;



const size_t MAX_COUNT = 100000;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    list<int> query;
    int query_count;
    cin >> query_count;
    vector<list<int>::iterator> positions(MAX_COUNT, query.end());
    for(auto i = 0; i < query_count; ++i){
        int a, b;
        cin >> a >> b;
        positions[a] = query.insert(positions[b], a);

    }

    for(const auto& node: query){
        cout << node << endl;
    }
}
