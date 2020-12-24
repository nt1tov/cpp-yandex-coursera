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

bool IsPalindrom(const string& str) {
    if(str.size() <= 1)
        return true;
    for(auto i = 0; i < static_cast<int>(str.size()) / 2 + 1; ++i){
        if(str[i] != str[str.size() - 1 - i])
            return false;
    }
    return true;
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}


void CheckLength() {

    AssertEqual(IsPalindrom(""), true, "empty str is palindrome");
    AssertEqual(IsPalindrom(" "), true, "1 space str is palindrome");
    AssertEqual(IsPalindrom("a"), true, "1 char str is palindrome");
    AssertEqual(IsPalindrom("ab"), false, "ab str is not palindrome");
}

void CheckEvenness() {

    AssertEqual(IsPalindrom("abba"), true, "abba str is palindrome");
    AssertEqual(IsPalindrom("aba"), true, "aba space str is  palindrome");
    AssertEqual(IsPalindrom("aabcaa"), false, "aabcaa char str is not palindrome");
    AssertEqual(IsPalindrom("aac"), false, "aac str is not palindrome");
}

void CheckCompEnd() {

    AssertEqual(IsPalindrom("abcddcba"), true, "abcddcba str is palindrome");
    AssertEqual(IsPalindrom("abcdcba"), true, "abcdcba space str is  palindrome");
    AssertEqual(IsPalindrom("abcdcbb"), false, "abcdcbb char str is not palindrome");
    AssertEqual(IsPalindrom("bbcdcba"), false, "aac str is not palindrome");
}

void CheckSpaces() {

    AssertEqual(IsPalindrom("abcd dcba"), true, "abcd dcba str is palindrome");
    AssertEqual(IsPalindrom("abc d cba"), true, "abc d cba space str is palindrome");
    AssertEqual(IsPalindrom("abcd  cba"), false, "abcd  cba char str is not palindrome");
    AssertEqual(IsPalindrom("abcddcb a"), false, "abcddcb a str is not palindrome");
    AssertEqual(IsPalindrom(" abcdcba "), true, " abcdcba  a str is  palindrome");
    AssertEqual(IsPalindrom(" abcdcba"), false, " abcdcba  a str is not  palindrome");
    AssertEqual(IsPalindrom("abcdcba "), false, "abcdcba  a str is not  palindrome");
}

void CheckExamples() {

    AssertEqual(IsPalindrom("madam"), true, "madam str is palindrome");
    AssertEqual(IsPalindrom("level"), true, "level space str is  palindrome");
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "wasitacaroracatisaw char str is palindrome");
}
int main() {
  TestRunner runner;
  runner.RunTest(CheckLength, "check 0-1 length palindrome");
  runner.RunTest(CheckEvenness, "check even or odd size of str");
  runner.RunTest(CheckCompEnd, "check end of comprasion");
  runner.RunTest(CheckSpaces, "check spaces");
  runner.RunTest(CheckExamples, "check examples");


  // добавьте сюда свои тесты
  return 0;
}
