#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
using namespace std;

void SingleThreadSum(
      const vector<vector<int>>& matrix,
      vector<int64_t>& res,
      size_t threads_count,
      size_t thread_num
){
  // cout << "thread_num: " << thread_num << endl;
  auto slice_len = matrix.size() / threads_count;
  // cout << "slice_len: " << slice_len << endl;
  auto start_row = slice_len * thread_num;
  auto end_row = (thread_num != threads_count-1) ? start_row+slice_len : matrix.size();
    // cout << "start_row: " << start_row << endl;
    // cout << "end_row: " << end_row << endl;
  for(auto row = start_row; row < end_row; row++){
    for(auto col = 0; col < matrix[row].size(); ++col){
      res[thread_num] += matrix[row][col];
    }
  }
  // cout <<"res: "<< res[thread_num] << endl;
}

void CalculateMatrixRowSum(
      const vector<vector<int>>& matrix,
      vector<int64_t>& res,
      size_t threads_count
){
  vector<future<void>> futures;
  for(auto thread_num = 0; thread_num <  threads_count; thread_num++){
    futures.push_back(async([&matrix, &res, threads_count, thread_num]{
          SingleThreadSum(matrix, res, threads_count, thread_num);
        }));
  }
  // for(auto thread_num = 0; thread_num <  threads_count; thread_num++){
  //   futures[thread_num].get();
  // }
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix){
  size_t threads_count = std::min<size_t>(10, matrix.size());
  vector<int64_t> res_vec(threads_count, 0);
  CalculateMatrixRowSum(matrix, res_vec, threads_count);
  int64_t res = 0;
  for(auto &row_sum: res_vec){
    res += row_sum;
  }
  return res;
}


void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestCalculateMatrixSum5() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
    {17, 18, 19, 20}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 210);
}

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestCalculateMatrixSum);
//   RUN_TEST(tr, TestCalculateMatrixSum5);
//   vector<vector<int>> matrix(20001);
//   for(auto i = 0; i < matrix.size(); ++i){
//     matrix[i] = vector<int>(20001);
//   }
//   CalculateMatrixSum(matrix);
//   return 0;
// }
