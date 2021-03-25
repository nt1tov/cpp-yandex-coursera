#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>
#include <utility>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  size_t range_size = range_end - range_begin;
  if(range_size < 2){
    return;
  }
  vector<typename RandomIt::value_type> v(make_move_iterator(range_begin),
                                          make_move_iterator(range_end));
  //cout << v2 << endl;
  MergeSort(v.begin(),
            v.begin() + range_size/3);
  //cout << v << endl;
  MergeSort(v.begin() + range_size/3,
            v.begin() + 2*range_size/3);
  //cout << v << endl;
  MergeSort(v.begin() + 2*range_size/3,
            v.end());
  //cout << v << endl;

  vector<typename RandomIt::value_type> temp;
  merge(
    make_move_iterator(v.begin()),
    make_move_iterator(v.begin() + range_size/3),
    make_move_iterator(v.begin() + range_size/3),
    make_move_iterator(v.begin() + 2*range_size/3),
    back_inserter(temp)
  );
  //cout << "temp=" << temp << endl;
  vector<typename RandomIt::value_type> temp2;
  merge(
    make_move_iterator(temp.begin()),
    make_move_iterator(temp.end()),
    make_move_iterator(v.begin() + 2*range_size/3),
    make_move_iterator(v.end()),
    range_begin
  );

  // for(auto it = range_begin; it != range_end; ++it){
  //   cout << *it << " ";
  // }
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}
void TestIntVector2() {
  vector<int> numbers = {9,8,7,6,5,4,3,2,1};
  MergeSort(begin(numbers), end(numbers));
  //cout << numbers ;
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

class NonCopy{
public:
  explicit NonCopy(int x){
    value = x;
  }
  explicit NonCopy(NonCopy&& other) {
    value = other.value;
  }
  NonCopy(NonCopy&) = delete;
  NonCopy& operator=(const NonCopy&) const = delete;
  void operator=(NonCopy&& other){
    NonCopy tmp(move(other));
    //cout << other.GetValue() << endl;
    value = other.value;
  }
  int GetValue() const{
    return value;
  }
private:
  int value;
};
bool operator<(const NonCopy &lhs, const NonCopy& rhs) {
  return lhs.GetValue() < rhs.GetValue();
}
bool operator==(const NonCopy &lhs, const NonCopy& rhs) {
  return lhs.GetValue() == rhs.GetValue();
}

bool operator<=(const NonCopy &lhs, const NonCopy& rhs) {
  return lhs.GetValue() <= rhs.GetValue();
}
ostream& operator<<(ostream& os, const NonCopy &lhs){
  os << lhs.GetValue();
  return os;
}
void TestNonCopyVector() {
  vector<NonCopy> numbers;
  for(auto i = 9; i>=1; --i){
    numbers.emplace_back(move(i));
  }

  MergeSort(begin(numbers), end(numbers));
  //cout << numbers;
 // sort(begin(numbers), end(numbers));
  //cout << numbers;
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

//9 6 4 7 6 4 4 0 1 5

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestIntVector2);
  RUN_TEST(tr, TestNonCopyVector);
  return 0;
}
