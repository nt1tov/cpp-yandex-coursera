#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// enum class Gender {
//   FEMALE,
//   MALE
// };

// struct Person {
//   int age;  // возраст
//   Gender gender;  // пол
//   bool is_employed;  // имеет ли работу
// };




// // Это пример функции, его не нужно отправлять вместе с функцией PrintStats
// template <typename InputIt>
// int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
// 	if (range_begin == range_end) {
// 		return 0;
// 	}
// 	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
// 	auto middle = begin(range_copy) + range_copy.size() / 2;
// 	nth_element(
// 		begin(range_copy), middle, end(range_copy),
// 		[](const Person& lhs, const Person& rhs) {
// 			return lhs.age < rhs.age;
// 		}
// 	);
// 	return middle->age;
// }

void PrintStats(vector<Person> persons) {

	ostringstream os;
	int age = -1;
	age = ComputeMedianAge(begin(persons), end(persons));
	os << "Median age = " << age << endl;

	auto it = partition(begin(persons), end(persons),  
		[](const Person &p) { return p.gender == Gender::FEMALE; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for females = " << age << endl;

	it = partition(begin(persons), end(persons), 
		[](const Person &p) { return p.gender == Gender::MALE; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for males = " << age << endl;

	it = partition(begin(persons), end(persons), 
		[](const Person &p) { return p.gender == Gender::FEMALE && p.is_employed; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for employed females = " << age << endl;

	it = partition(begin(persons), end(persons), 
		[](const Person &p) { return p.gender == Gender::FEMALE && !p.is_employed; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for unemployed females = " << age << endl;

	it = partition(begin(persons), end(persons), 
		[](const Person &p) { return p.gender == Gender::MALE && p.is_employed; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for employed males = " << age << endl;

	it = partition(begin(persons), end(persons), 
		[](const Person &p) { return p.gender == Gender::MALE && !p.is_employed; });
	age = ComputeMedianAge(begin(persons), it);
	os << "Median age for unemployed males = " << age << endl;

	cout<<os.str();

}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}

// Median age = 40
// Median age for females = 40
// Median age for males = 55
// Median age for employed females = 40
// Median age for unemployed females = 80
// Median age for employed males = 55
// Median age for unemployed males = 78