#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {

	if(numbers.begin() == numbers.end())
		return numbers.end();
	auto it = find_if(numbers.begin(), numbers.end(), [&](int x){return x >= border;});
	if(it == numbers.end() )
		it = prev(numbers.end());
	return it;

}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел



int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
/*
1 4 4 6 6
1
*/