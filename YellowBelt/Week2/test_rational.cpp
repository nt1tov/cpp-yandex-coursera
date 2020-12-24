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

// int gcd( int a,  int b) {
//
//     while(a  != 0 && b != 0){
//         if(a >= b)
//             a = a % b;
//         else
//             b = b % a;
//     }
//     return std::max(a, b);
// }

// class Rational {
//     int num, denom;
// public:
//   // Вы можете вставлять сюда различные реализации,
//   // чтобы проверить, что ваши тесты пропускают корректный код
//   // и ловят некорректный
//
//   Rational(){num = 0; denom = 1; }
//   Rational(int numerator, int denominator) {
//       if(numerator == 0){
//           num = 0;
//           denom = 1;
//       }
//       else{
//           int divisor = gcd(std::abs(numerator), std::abs(denominator));
//           if(!divisor){
//             divisor = 1;
//           }
//
//           num = numerator / divisor;
//           denom = denominator / divisor;
//
//           if(num < 0 && denom < 0){
//               num = -num;
//               denom = -denom;
//           }
//           else if(denom < 0){
//               num = -num;
//               denom = -denom;
//           }
//
//
//
//       }
//   }

//   int Numerator() const {
//       return num;
//   }
//
//   int Denominator() const {
//       return denom;
//   }
// };

void TestDefaultConstructor() {

    Rational number;
    AssertEqual(number.Numerator(), 0, " constructor should make Numerator 0");
    AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
}

void TestReduction() {
    {
        Rational number{1, 1};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }
    {
        Rational number{15, 25};
        AssertEqual(number.Numerator(), 3, " constructor should make Numerator 3");
        AssertEqual(number.Denominator(), 5, " constructor should make Denominator 5");
    }

    {
        Rational number{100, 101};
        AssertEqual(number.Numerator(), 100, " constructor should make Numerator 100");
        AssertEqual(number.Denominator(), 101, " constructor should make Denominator 101");
    }


    {
        Rational number{13, 117};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 9, " constructor should make Denominator 9");
    }

    {
        Rational number{1234, 1234};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

}

void TestSign() {
    {
        Rational number{1, -1};
        AssertEqual(number.Numerator(), -1, " constructor should make Numerator -1");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

    {
        Rational number{-1, -1};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

    {
        Rational number{-1, 1};
        AssertEqual(number.Numerator(), -1, " constructor should make Numerator -1");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

    {
        Rational number{-5, 25};
        AssertEqual(number.Numerator(), -1, " constructor should make Numerator -1");
        AssertEqual(number.Denominator(), 5, " constructor should make Denominator 5");
    }

    {
        Rational number{-5, -25};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 5, " constructor should make Denominator 5");
    }

    {
        Rational number{5, -25};
        AssertEqual(number.Numerator(), -1, " constructor should make Numerator -1");
        AssertEqual(number.Denominator(), 5, " constructor should make Denominator 5");
    }

    {
        Rational number{-5, -25};
        AssertEqual(number.Numerator(), 1, " constructor should make Numerator 1");
        AssertEqual(number.Denominator(), 5, " constructor should make Denominator 5");
    }
}

void TestZeroNumerator() {
    {
        Rational number{0, 1};
        AssertEqual(number.Numerator(), 0, " constructor should make Numerator 0");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

    {
        Rational number{0, 123};
        AssertEqual(number.Numerator(), 0, " constructor should make Numerator 0");
        AssertEqual(number.Denominator(), 1, " constructor should make Denominator 1");
    }

}
int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "test default constructor frac must be 0 / 1");
  runner.RunTest(TestReduction, "test frection reduction");
  runner.RunTest(TestSign, "test frection sign");
  runner.RunTest(TestZeroNumerator, "test zero numerator reduction");
  // добавьте сюда свои тесты
  return 0;
}
