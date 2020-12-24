#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


// // если имя неизвестно, возвращает пустую строку
// string FindNameByYear(const map<int, string>& names, int year) {
//   string name;  // изначально имя неизвестно
//
//   // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
//   for (const auto& item : names) {
//     // если очередной год не больше данного, обновляем имя
//     if (item.first <= year) {
//       name = item.second;
//     } else {
//       // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
//       break;
//     }
//   }
//
//   return name;
// }

// class Person {
// public:
//   void ChangeFirstName(int year, const string& first_name) {
//     first_names[year] = first_name;
//   }
//   void ChangeLastName(int year, const string& last_name) {
//     last_names[year] = last_name;
//   }
//   string GetFullName(int year) {
//     // получаем имя и фамилию по состоянию на год year
//     const string first_name = FindNameByYear(first_names, year);
//     const string last_name = FindNameByYear(last_names, year);
//
//     // если и имя, и фамилия неизвестны
//     if (first_name.empty() && last_name.empty()) {
//       return "Incognito";
//
//     // если неизвестно только имя
//     } else if (first_name.empty()) {
//       return last_name + " with unknown first name";
//
//     // если неизвестна только фамилия
//     } else if (last_name.empty()) {
//       return first_name + " with unknown last name";
//
//     // если известны и имя, и фамилия
//     } else {
//       return first_name + " " + last_name;
//     }
//   }
//
// private:
//   map<int, string> first_names;
//   map<int, string> last_names;
// };


void TestChangeFirstName()
{

{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeFirstName(1967, "Sergei");
    person.ChangeFirstName(1968, "Dasha");
    map<int, string> tests = {
                {1900, "Incognito"},
                {1965, "Polina with unknown last name"},
                {1966, "Polina with unknown last name"},
                {1967, "Sergei with unknown last name" },
                {1969, "Dasha with unknown last name" }
    };
    for (int year : {1900, 1965, 1966, 1967}) {
        stringstream ss;
        ss << "First name in " << year << " must be " <<  tests[year] ;
        AssertEqual(person.GetFullName(year), tests[year], ss.str());
    }
  }

}


void TestChangeLastName()
{



    {
        Person person;

        person.ChangeLastName(1965, "Strauss");
        person.ChangeLastName(1967, "Euler");
        person.ChangeLastName(1968, "Newton");
        map<int, string> tests = {
                    {1900, "Incognito"},
                    {1965, "Strauss with unknown first name"},
                    {1966, "Strauss with unknown first name"},
                    {1967, "Euler with unknown first name" },
                    {1969, "Newton with unknown first name" }
        };
        for (int year : {1900, 1965, 1966, 1967}) {
            stringstream ss;
            ss << "Last name in " << year << " must be " <<  tests[year] ;
            AssertEqual(person.GetFullName(year), tests[year], ss.str());
        }
    }

}

void TestGetFullName()
{

    {
        Person person;

        map<int, string> tests = {
                    {1900, "Incognito"},
                    {1965, "Incognito"},
                    {1966, "Incognito"},
                    {1967, "Incognito" },
                    {1969, "Incognito" }
        };
        for (int year : {1900, 1965, 1966, 1967}) {
            stringstream ss;
            ss << "Full name in " << year << "must be " <<  tests[year] ;
            AssertEqual(person.GetFullName(year), tests[year], ss.str());
        }
    }
    {
        Person person;
        person.ChangeFirstName(1964, "Iogann");
        person.ChangeLastName(1965, "Strauss");
        person.ChangeLastName(1967, "Euler");
        person.ChangeLastName(1968, "Newton");
        person.ChangeFirstName(1968, "Isac");
        map<int, string> tests = {
                    {1900, "Incognito"},
                    {1964, "Iogann with unknown last name"},
                    {1965, "Iogann Strauss"},
                    {1966, "Iogann Strauss"},
                    {1967, "Iogann Euler" },
                    {1969, "Isac Newton" }
        };
        for (int year : {1900, 1964, 1965, 1966, 1967, 1969}) {
            stringstream ss;
            ss << "Full name in " << year << "must be " <<  tests[year] ;
            AssertEqual(person.GetFullName(year), tests[year], ss.str());
        }
    }

}


int main() {
  TestRunner runner;
  runner.RunTest(TestChangeFirstName, "firstname test");

  runner.RunTest(TestChangeLastName, "secondname test");

  runner.RunTest(TestGetFullName, "fullname test");
  // добавьте сюда свои тесты
  return 0;
}
