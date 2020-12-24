#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;



template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
	RandomIt range_end, const std::string &prefix) {

	auto find_lambda_lower = [](const std::string &lhs, const std::string &rhs){
        auto left_sub = lhs.substr(0, rhs.length());

        return left_sub < rhs;
    };
	
    auto find_lambda_upper = [](const std::string &lhs, const std::string &rhs){
        auto right_sub = rhs.substr(0, lhs.length());
       
        return lhs < right_sub;
    };

	auto lhs_iter = lower_bound(range_begin, range_end, prefix, find_lambda_lower);
	auto rhs_iter = upper_bound(range_begin, range_end, prefix, find_lambda_upper);

	return std::make_pair(lhs_iter, rhs_iter);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
/*
moscow motovilikha
2 2
3 3
*/
