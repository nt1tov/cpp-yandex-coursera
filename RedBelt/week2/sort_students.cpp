#include "student.h"
#include "test_runner.h"
//#include "profile.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

//Оптимизируйте эту функцию
// bool Compare(Student first, Student second) {
//   return first.Less(second);
// }

bool Compare(const Student& first, const Student& second) {
  return first.Less(second);
}

// void TestComparison() {
// 	Student newbie {
// 		"Ivan", "Ivanov", {
// 			{"c++", 1.0},
// 			{"algorithms", 3.0}
// 		},
// 		2.0
// 	};

// 	Student cpp_expert {
// 		"Petr", "Petrov", {
// 		{"c++", 9.5},
// 		{"algorithms", 6.0}
// 		},
// 		7.75
// 	};

// 	Student guru {
// 		"Sidor", "Sidorov", {
// 			{"c++", 10.0},
// 			{"algorithms", 10.0}
// 		},
// 		10.0
// 	};
// 	ASSERT(Compare(guru, newbie));
// 	ASSERT(Compare(guru, cpp_expert));
// 	ASSERT(!Compare(newbie, cpp_expert));
// }

// void TestSorting() {
// 	vector<Student> students {
// 		{"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
// 		{"Semen", "Semenov", {{"maths", 4.}}, 4.},
// 		{"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
// 		{"Petr", "Petrov", {{"maths", 3.}}, 3.},
// 		{"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
// 	};
// 	sort(students.begin(), students.end(), Compare);
// 	ASSERT(is_sorted(students.begin(), students.end(),
// 		[](Student first, Student second) {
// 			return first.Less(second);
// 		})
// 	);
// }

// void TestComparisonNew() {
// 	Student newbie {
// 		"Ivan", "Ivanov", {
// 			{"c++", 1.0},
// 			{"algorithms", 3.0}
// 		},
// 		2.0
// 	};

// 	Student cpp_expert {
// 		"Petr", "Petrov", {
// 		{"c++", 9.5},
// 		{"algorithms", 6.0}
// 		},
// 		7.75
// 	};

// 	Student guru {
// 		"Sidor", "Sidorov", {
// 			{"c++", 10.0},
// 			{"algorithms", 10.0}
// 		},
// 		10.0
// 	};
// 	ASSERT(CompareNew(guru, newbie));
// 	ASSERT(CompareNew(guru, cpp_expert));
// 	ASSERT(!CompareNew(newbie, cpp_expert));
// }

// void TestSortingNew() {
// 	vector<Student> students {
// 		{"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
// 		{"Semen", "Semenov", {{"maths", 4.}}, 4.},
// 		{"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
// 		{"Petr", "Petrov", {{"maths", 3.}}, 3.},
// 		{"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
// 	};
// 	sort(students.begin(), students.end(), CompareNew);
// 	ASSERT(is_sorted(students.begin(), students.end(),
// 		[](Student first, Student second) {
// 			return first.Less(second);
// 		})
// 	);
// }
//  #define LARGE_VEC_SIZE 300000
// int main() {
// 	TestRunner tr;
// 	RUN_TEST(tr, TestComparison);
// 	RUN_TEST(tr, TestSorting);

// 	RUN_TEST(tr, TestComparisonNew);
// 	RUN_TEST(tr, TestSortingNew);

// 	{
// 		vector<Student> students {
// 			{"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
// 			{"Semen", "Semenov", {{"maths", 4.}}, 4.},
// 			{"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
// 			{"Petr", "Petrov", {{"maths", 3.}}, 3.},
// 			{"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
// 		};
// 		vector<Student> large_students;
// 		for(auto i = 0; i < LARGE_VEC_SIZE; ++i){
// 			auto r_idx = rand() % 5;
// 			large_students.push_back(students[r_idx]);
// 		}
// 		LOG_DURATION("Compare");
// 		sort(large_students.begin(), large_students.end(), Compare);
// 	}


// 	{
// 		vector<Student> students {
// 			{"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
// 			{"Semen", "Semenov", {{"maths", 4.}}, 4.},
// 			{"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
// 			{"Petr", "Petrov", {{"maths", 3.}}, 3.},
// 			{"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
// 		};
// 		vector<Student> large_students;
// 		for(auto i = 0; i < LARGE_VEC_SIZE; ++i){
// 			auto r_idx = rand() % 5;
// 			large_students.push_back(students[r_idx]);
// 		}
// 		LOG_DURATION("CompareNew");
// 		sort(large_students.begin(), large_students.end(), CompareNew);
// 	}
// 	return 0;
// }