#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
/*
enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
*/
bool map_cmp(const map<Lang, string> &lhs, const map<Lang, string> &rhs)
{

	if(lhs != rhs)
		return false;
	for(auto l = lhs.begin(), r = rhs.begin(); l != lhs.end(), r != rhs.end(); ++l, ++r){
		//cout<<l->second <<" " << r->second << endl;
		if(l->second != r->second)
			return false;
	}
	return true;
}

auto getRank(const Region &reg)
{
	return tie(reg.std_name, reg.parent_std_name, reg.population);
}

bool cmpRegion(const Region &lhs, const Region &rhs)
{
	return (getRank(lhs) == getRank(rhs) 
		&& (map_cmp(lhs.names,rhs.names)));
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	if (regions.size() == 0)
		return  0;
	int max_count = 1;
	set<int> copy_indexes{};
	for(size_t i = 0; i < regions.size(); ++i){
		if(copy_indexes.find(i) != copy_indexes.end())
			continue;
		auto count = 1;
		for(size_t j = i + 1; j < regions.size(); ++j){
			if(cmpRegion(regions[j], regions[i])){
				++count;
				copy_indexes.insert(j);
			}
		}
		if(count > max_count)
			max_count = count;
	}

	return max_count;
}



int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;
  
  return 0;
}