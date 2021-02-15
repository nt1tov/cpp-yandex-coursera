#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
// #include "profile.h"
// #include "test_runner.h"
#include <unordered_map>

using namespace std;

// class ReadingManagerSlow {
// public:
//   ReadingManagerSlow()
//       : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
//         sorted_users_(),
//         user_positions_(MAX_USER_COUNT_ + 1, -1) {}

//   void Read(int user_id, int page_count) {
//     if (user_page_counts_[user_id] == 0) {
//       AddUser(user_id);
//     }
//     user_page_counts_[user_id] = page_count;
//     int& position = user_positions_[user_id];
//     while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
//       SwapUsers(position, position - 1);
//     }
//   }

//   double Cheer(int user_id) const {
//     if (user_page_counts_[user_id] == 0) {
//       return 0;
//     }
//     const int user_count = GetUserCount();
//     if (user_count == 1) {
//       return 1;
//     }
//     const int page_count = user_page_counts_[user_id];
//     int position = user_positions_[user_id];
//     while (position < user_count &&
//       user_page_counts_[sorted_users_[position]] == page_count) {
//       ++position;
//     }
//     if (position == user_count) {
//         return 0;
//     }
//     // По умолчанию деление целочисленное, поэтому
//     // нужно привести числитель к типу double.
//     // Простой способ сделать это — умножить его на 1.0.
//     return (user_count - position) * 1.0 / (user_count - 1);
//   }

// private:
//   // Статическое поле не принадлежит какому-то конкретному
//   // объекту класса. По сути это глобальная переменная,
//   // в данном случае константная.
//   // Будь она публичной, к ней можно было бы обратиться снаружи
//   // следующим образом: ReadingManager::MAX_USER_COUNT.
//   static const int MAX_USER_COUNT_ = 100'000;

//   vector<int> user_page_counts_;
//   vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
//   vector<int> user_positions_; // позиции в векторе sorted_users_

//   int GetUserCount() const {
//     return sorted_users_.size();
//   }
//   void AddUser(int user_id) {
//     sorted_users_.push_back(user_id);
//     user_positions_[user_id] = sorted_users_.size() - 1;
//   }
//   void SwapUsers(int lhs_position, int rhs_position) {
//     const int lhs_id = sorted_users_[lhs_position];
//     const int rhs_id = sorted_users_[rhs_position];
//     swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
//     swap(user_positions_[lhs_id], user_positions_[rhs_id]);
//   }
// };

class ReadingManager {
public:
  ReadingManager()
      :pages_counter_(MAX_PAGES_COUNT_+1, 0){}

  void Read(int user_id, int page_count) {
    if(user_pages_.find(user_id) != user_pages_.end()){
      auto older_page = user_pages_[user_id];
      if(pages_counter_[older_page] > 0){
        --pages_counter_[older_page];
      }
    }
    user_pages_[user_id] = page_count;
    ++pages_counter_[page_count];
  }

  double Cheer(int user_id) const {
    if (user_pages_.find(user_id) == user_pages_.end()) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int user_position = user_pages_.at(user_id);
    int position = 1;
    int lower_users = 0;
    while (position < user_position) {
      lower_users += pages_counter_[position];
      ++position;
    }
    return (lower_users) * 1.0 / (user_count - 1);
  }

private:
  static const int MAX_PAGES_COUNT_ = 1'000;
  unordered_map<int, int> user_pages_;
  vector<int> pages_counter_;   // отсортированы по убыванию количества страниц
 // vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const {
    return user_pages_.size();
  }

};


// void TestSlow(){
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   ReadingManagerSlow manager;

//   stringstream ss;
//   vector<float> res;
//   vector<float> exp = {0, 1, 0, 0.5, 0.5, 1, 0.5 };
//   ss << "CHEER 5\nREAD 1 10\nCHEER 1\nREAD 2 5\nREAD 3 7\nCHEER 2\nCHEER 3\nREAD 3 10\nCHEER 3\nREAD 3 11\nCHEER 3\nCHEER 1\n";
//   int query_count = 12;

//   for (int query_id = 0; query_id < query_count; ++query_id) {
//     string query_type;
//     ss >> query_type;
//     int user_id;
//     ss >> user_id;

//     if (query_type == "READ") {
//       int page_count;
//       ss >> page_count;
//       manager.Read(user_id, page_count);
//     }
//     else if (query_type == "CHEER") {
//       //cout << setprecision(6) << manager.Cheer(user_id) << "\n";
//       res.push_back(manager.Cheer(user_id));
//     }
//   }
//   ASSERT_EQUAL(res, exp);
// }

// void TestFast(){


//   ReadingManager manager;

//   stringstream ss;
//   vector<float> res;
//   vector<float> exp = {0, 1, 0, 0.5, 0.5, 1, 0.5 };
//   ss << "CHEER 5\nREAD 1 10\nCHEER 1\nREAD 2 5\nREAD 3 7\nCHEER 2\nCHEER 3\nREAD 3 10\nCHEER 3\nREAD 3 11\nCHEER 3\nCHEER 1\n";
//   int query_count = 12;

//   for (int query_id = 0; query_id < query_count; ++query_id) {
//     string query_type;
//     ss >> query_type;
//     int user_id;
//     ss >> user_id;

//     if (query_type == "READ") {
//       int page_count;
//       ss >> page_count;
//       manager.Read(user_id, page_count);
//     }
//     else if (query_type == "CHEER") {
//       //cout << setprecision(6) << manager.Cheer(user_id) << "\n";
//       res.push_back(manager.Cheer(user_id));
//     }
//   }
//   ASSERT_EQUAL(res, exp);
//}

//testing main
// int main(){
//   TestRunner tester;
//   RUN_TEST(tester, TestSlow);
//   RUN_TEST(tester, TestFast);

//   {
//     LOG_DURATION("Slow")
//     TestSlow();
//   }

//     {
//     LOG_DURATION("Fast")
//     TestFast();
//   }

// }

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}