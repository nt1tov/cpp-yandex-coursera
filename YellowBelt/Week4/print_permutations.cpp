#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;



int main() {

	int n;
	cin >> n;

	std::vector<int> v;
	for(auto i = n; i >= 1; --i)
		v.push_back(i);

	do {
    	for(const auto &el: v)
    		cout<<el<<" ";
    	cout<<endl;
  	} while (prev_permutation(begin(v), end(v)));

	return 0;
}