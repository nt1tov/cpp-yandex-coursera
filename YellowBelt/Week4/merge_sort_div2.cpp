#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end - range_begin < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto left_iter1 = elements.begin();
	auto right_iter2 = elements.end();
	auto left_iter2 = left_iter1 + (right_iter2 - left_iter1)/2;
	auto right_iter1 = left_iter1 +  (right_iter2 - left_iter1)/2;
	MergeSort(left_iter1, left_iter2);
	MergeSort(right_iter1, right_iter2);
	std::merge(left_iter1, left_iter2, right_iter1, right_iter2, range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl; //0 1 4 4 4 6 6 7
  return 0;
}
