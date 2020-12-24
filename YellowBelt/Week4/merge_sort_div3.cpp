#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end - range_begin < 3)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto left_iter1 = range_begin;
	auto left_iter2 = left_iter1 + (range_end - range_begin)/3;



	auto middle_iter1 = left_iter2;
	auto middle_iter2 = middle_iter1 + (range_end - range_begin)/3;

	auto right_iter1 = middle_iter2;
	auto right_iter2 = range_end;

	MergeSort(left_iter1, left_iter2);
	MergeSort(middle_iter1, middle_iter2);
	MergeSort(right_iter1, right_iter2);

	vector<typename RandomIt::value_type> tmp_vector;
	std::merge(left_iter1, left_iter2, middle_iter1, middle_iter2, std::back_inserter(tmp_vector));
	std::merge(tmp_vector.begin(), tmp_vector.end(), right_iter1, right_iter2, range_begin);
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
