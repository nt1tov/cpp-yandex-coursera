#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "test_runner.h"
#include "profile.h"
#include <ctime>

using namespace std;

#define LARGE_SIZE 100000

//map<int, vector<int>> in original

struct Query{
	string type;
	int start;
	int finish;
};

Query gen_random_query(const int range){
	//srand(time(0));
	Query q;
	vector<string> types = {"ADD", "GO"};
	q.type = types[rand() % 2];
	int randval1 = rand();
	int randval2 = rand();
	int rand_sgn1 = rand();
	int rand_sgn2 = rand();
	q.start =  (randval1 % range) * ((rand_sgn1 % 2 == 0)? 1 : -1);
	q.finish = (randval2 % range) * ((rand_sgn2 % 2 == 0)? 1 : -1);
	return q;
}

vector<Query> generate_queries(const size_t& size){
	vector<Query> q = {
		{"ADD", -2, 5},
		{"ADD", 10, 4},
		{"ADD", 5, 8},
		{"GO", 4, 10},
		{"GO", 4, -2},
		{"GO", 5, 0},
		{"GO", 4, 100}
	};
	vector<Query> res;
	for(auto i = 0; i < size; ++i){
		auto rnd_q = gen_random_query(999'999'999);
		res.push_back(rnd_q);
		//cout <<"{ "<<rnd_q.type<<" "<<rnd_q.start<<" "<<" "<< rnd_q.finish << " }" << endl;
	}
	return res;
}

class RouteManagerSlow {
public:
	//Time Complexity --  Amortized O(1)
	void AddRoute(int start, int finish) {
		reachable_lists_[start].push_back(finish);
		reachable_lists_[finish].push_back(start);
	}
	//Time Complexity -- O(N)
	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}

		const vector<int>& reachable_stations = reachable_lists_.at(start);
		if (!reachable_stations.empty()) { //O(1)
			result = min( // O(N)
				result,
				abs(finish - *min_element(
					begin(reachable_stations), end(reachable_stations),
					[finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
				))
			);
		}
		return result;
	}
private:
	map<int, vector<int>> reachable_lists_;
};

// Used  map<int, set<int>> data structure
class RouteManager {
public:
	//Time Complexity -- O(logN) -- tradeoff
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}
	//Time Complexity -- O(logN) -- speadup
	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}
		//
		const set<int>& reachable_stations = reachable_lists_.at(start); // O(logN)


		const auto higher_iter = reachable_stations.lower_bound(finish); //O(logN)
		int near_higher, near_lower;
		//cout << "hello" << endl;
		if(higher_iter != reachable_stations.end() ){
			//cout << "hello" << endl;
			near_higher = *higher_iter;
			result = min(result, abs(finish - near_higher));
		}
		if( higher_iter != reachable_stations.begin()){
			auto near_lower = *(prev(higher_iter));
			result = min(result, abs(finish - near_lower));
		}


		return result;
	}
private:
	map<int, set<int>> reachable_lists_;
};



void TestSlow(){
	vector<Query> q = {
		{"ADD", -2, 5},
		{"ADD", 10, 4},
		{"ADD", 5, 8},
		{"GO", 4, 10},
		{"GO", 4, -2},
		{"GO", 5, 0},
		{"GO", 4, 100}
	};
	RouteManagerSlow routes;
	vector<int> expected = {0, 6, 2, 90};
	vector<int> res;
	for (int query_id = 0; query_id < q.size(); ++query_id) {
		string query_type = q[query_id].type;
		int start = q[query_id].start;
		int finish = q[query_id].finish;

		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			auto r =  routes.FindNearestFinish(start, finish);
			res.push_back(r);
		}
	}
	ASSERT_EQUAL(res, expected);
}

void TestFast(){

	RouteManager routes;
	RouteManagerSlow routes_slow;
	vector<int> res;
	vector<int> expected;
	auto q = generate_queries(LARGE_SIZE);
	for (int query_id = 0; query_id < q.size(); ++query_id) {
		string query_type = q[query_id].type;
		int start = q[query_id].start;
		int finish = q[query_id].finish;

		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
			routes_slow.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			auto r =  routes.FindNearestFinish(start, finish);
			auto rexp =  routes_slow.FindNearestFinish(start, finish);
			res.push_back(r);
			expected.push_back(rexp);
		}
	}
	ASSERT_EQUAL(res, expected);
}

void RunSlow(const vector<Query>& q){
	RouteManagerSlow routes;
	for (int query_id = 0; query_id < q.size(); ++query_id) {
		string query_type = q[query_id].type;
		int start = q[query_id].start;
		int finish = q[query_id].finish;

		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			auto r =  routes.FindNearestFinish(start, finish);
		}
	}
}

void RunFast(const vector<Query>& q){
	RouteManager routes;
	for (int query_id = 0; query_id < q.size(); ++query_id) {
		string query_type = q[query_id].type;
		int start = q[query_id].start;
		int finish = q[query_id].finish;

		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			auto r =  routes.FindNearestFinish(start, finish);
		}
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSlow);
	RUN_TEST(tr, TestFast);
	auto queries = generate_queries(LARGE_SIZE);
	{
		LOG_DURATION("Slow");
		RunSlow(queries);
	}
	{
		LOG_DURATION("Fast");
		RunFast(queries);
	}
	return 0;
}



// int main() {
//   RouteManager routes;

//   int query_count;
//   cin >> query_count;

//   for (int query_id = 0; query_id < query_count; ++query_id) {
//     string query_type;
//     cin >> query_type;
//     int start, finish;
//     cin >> start >> finish;
//     if (query_type == "ADD") {
//       routes.AddRoute(start, finish);
//     } else if (query_type == "GO") {
//       cout << routes.FindNearestFinish(start, finish) << "\n";
//     }
//   }

//   return 0;
// }