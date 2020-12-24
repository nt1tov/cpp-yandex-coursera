#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;



template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
	RandomIt range_end, char prefix) {
	std::string empty_string = "";
	auto find_lambda = [](const std::string &lhs, const std::string &rhs){return lhs[0] < rhs[0];};
	
	std::string tmp = "";
	tmp += prefix;
	auto lhs_iter = lower_bound(range_begin, range_end, tmp, find_lambda);
	auto rhs_iter = upper_bound(range_begin, range_end, tmp, find_lambda);

	// for(auto it = range_begin; it != rhs_iter; ++it)
	// 	cout<<*it<<endl;


	// if(lhs_iter == range_end){
	// 	lhs_iter = range_begin;
	// 	rhs_iter = range_begin;
	// }
	// else{
	// 	--lhs_iter;
	// }
	//std::cout<<tmp<<endl;
	//std::cout<<*lhs_iter<<" "<<*rhs_iter<<std::endl;
	return std::make_pair(lhs_iter, rhs_iter);
}

int main() {
	const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
      cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
  return 0;
}
/*
moscow murmansk
2 2
3 3
*/
