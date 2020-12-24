#include <iostream>
#include <map>
#include <ostream>
#include <random>
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

/*
int GetDistinctRealRootCount(double a, double b, double c) {
    if(a == 0){
      if(b == 0)
        return 0;
      return 1;
    }
    else if(b == 0){
      if(c == 0)
        return 1;
      if(c < 0 )
        return 2;
      return 0;

    }
    else if(b*b - 4*a*c < 0){
        return 0;
    }
    else if(b*b - 4*a*c == 0){
        return 1;
    }
    else {
        return 2;
    }
}
*/
void CheckConstant()
{
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "has no roots when a = 0 b = 0 c = 1");
    AssertEqual(GetDistinctRealRootCount(0, 0, -199999999), 0, "has no roots when a = 0 b = 0 c = -1999999999");
    AssertEqual(GetDistinctRealRootCount(0, 0, -199999999), 0, "has no roots when a = 0 b = 0 c = 0");
}

void CheckLinear() {
    AssertEqual(GetDistinctRealRootCount(0, 100000, 0), 1, "1 root when a = 0 b = 100000 c = 0");
    AssertEqual(GetDistinctRealRootCount(0, 2, 100), 1, "1 root when a = 0 b = 2 c = 100");
    AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "1 root when a = 0 b = 1 c = 1");
}

void CheckNoRoots() {
  AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
    "x^2+1 = 0 has 0 real roots.");
  AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
    "x^2+3x+4 = 0 has 0 real roots.");
  AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
    "x^2-2x+10 = 0 has 0 real roots.");
}

void CheckOneRoot() {
    mt19937 gen;
    uniform_real_distribution<> unif(-10, 10);
    for(auto i = 0; i < 100; ++i){
      const auto x = unif(gen);
      const auto p = x + x;
      const auto q = x * x;

      AssertEqual(GetDistinctRealRootCount(1, p, q), 1, "x^2* + " + to_string(p) + " + x*" + to_string(q));
    }
        
}

void CheckRootCount() {
    mt19937 gen;
    uniform_real_distribution<> unif(-10, 10);
    for(auto i = 0; i < 100; ++i){
      const auto a = unif(gen);
      const auto b = unif(gen);
      const auto c = unif(gen);

      auto count = GetDistinctRealRootCount(a, b, c);
      Assert(count >= 0 && count <= 2,
      "Quadratic equation has only 0, 1 or 2 real roots.");
    }
        
}

int main() {
  TestRunner runner;
  runner.RunTest(CheckLinear, "linear eq where a = 0 , bx + c = 0");
  runner.RunTest(CheckConstant, "const eq where a = 0 , b = 0, c != 0");
  runner.RunTest(CheckNoRoots, "no roots eq ");
  runner.RunTest(CheckOneRoot, "one root eq ");
  runner.RunTest(CheckRootCount, "count roots eq ");


  // добавьте сюда свои тесты
  return 0;
}

