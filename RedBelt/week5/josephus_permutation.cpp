#include "test_runner.h"

#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <list>
using namespace std;

template <typename RandomIt>
void MakeJosephusPermutationCopy(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(first, last);
  size_t cur_pos = 0;
  while (!pool.empty()) {
    *(first++) = pool[cur_pos];
    pool.erase(pool.begin() + cur_pos);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool;
  auto it = first;
  while(it != last){
    pool.push_back(move(*it));
    ++it;
  }
  auto cur_pos_iter = pool.begin();
  auto next_pos_iter = pool.begin();
  size_t cur_pos = 0;
  size_t next_pos = 0;

  while (!pool.empty()) {
    *(first++) = std::move(*cur_pos_iter);
    auto next_it = pool.end();
    if(cur_pos_iter == pool.end()){
      next_it = pool.begin();
    }
    else{
      next_it = next(cur_pos_iter);
    }
    pool.erase(cur_pos_iter);
    if (pool.empty()) {
      break;
    }
    auto old_pos = cur_pos;
    cur_pos = (cur_pos + step_size - 1) % pool.size();
    if((old_pos + step_size - 1) >= pool.size()){
        cur_pos_iter = next(pool.begin(), cur_pos);
    }
    else{
        if(next_it == pool.end()){
            next_it = pool.begin();
        }
        cur_pos_iter = next(next_it, step_size-1);
    }
  }
}


vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;

  NoncopyableInt(int value) : value(value) {}

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

struct CopyableInt {
  int value;

  CopyableInt(int value) : value(value) {}

  CopyableInt(const CopyableInt&) = default;
  CopyableInt& operator=(const CopyableInt&) = default;

  CopyableInt(CopyableInt&&) = default;
  CopyableInt& operator=(CopyableInt&&) = delete;
};

bool operator == (const CopyableInt& lhs, const CopyableInt& rhs) {
  return lhs.value == rhs.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

const int LENGTH = 10'000'00;
const int STEP = 77;
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestIntVector);
//   RUN_TEST(tr, TestAvoidsCopying);
//  // return 0;
//   {
//     vector<CopyableInt> numbers;
//     for(auto i = 0; i < LENGTH; ++i){
//       numbers.push_back({i});
//     }
//     LOG_DURATION("load test copy");
//     MakeJosephusPermutationCopy(begin(numbers), end(numbers), STEP);
//   }


//     {
//     vector<NoncopyableInt> numbers;
//     for(auto i = 0; i < LENGTH; ++i){
//       numbers.push_back({i});
//     }
//     LOG_DURATION("load test move");
//     MakeJosephusPermutation(begin(numbers), end(numbers), STEP);
//   }
//   return 0;
// }
