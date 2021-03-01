#include "test_runner.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>
#include <deque>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target);
  std::string_view TranslateForward(string_view source) const;
  string_view TranslateBackward(string_view target) const;

private:
  string_view CreateLocalData(string_view s);
  deque<string> data;
  unordered_map<string_view, string_view> forward_dict;
  unordered_map<string_view, string_view> backward_dict;
};

string_view Translator::CreateLocalData(string_view s){
  for(const auto* map_ptr: {&forward_dict, &forward_dict}){
      auto it = map_ptr->find(s);
      if(it != map_ptr->end()){
        return (*it).first;
      }
  }
  return data.emplace_back(s);
}
void Translator::Add(string_view source, string_view target) {
  source =  CreateLocalData(source);
  target =  CreateLocalData(target);
  forward_dict[source] = target;
  backward_dict[target] = source;
}

string_view Translator::TranslateForward(string_view target) const {
  auto founded_translation = forward_dict.find(target);
  if(founded_translation == forward_dict.end()){
      return string("");
  }
  return forward_dict.at(target);
}
string_view Translator::TranslateBackward(string_view target) const {
  auto founded_translation = backward_dict.find(target);
  if(founded_translation == backward_dict.end()){
      return string("");
  }
  return backward_dict.at(target);
}


void TestSimple() {
  Translator translator;
  translator.Add(*(new string("okno")), *(new string("window")));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

void TestSimple2() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

void TestSimple3() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));
  cout  << translator.TranslateForward("stol") << endl;

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  RUN_TEST(tr, TestSimple2);
  RUN_TEST(tr, TestSimple3);
  return 0;
}
