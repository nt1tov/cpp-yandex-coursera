#include "test_runner.h"
#include "profile.h"
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
// Напишите реализацию функции, не копируя объекты типа Token
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> res;
  Sentence<Token> sentence;
  bool sentence_flag = false;
  for(auto& token: tokens){
    //cout << token << endl;
    if(token.IsEndSentencePunctuation()){
        sentence_flag = true;
    }
    else if(sentence_flag && !sentence.empty()){
      res.emplace_back(std::move(sentence));
      sentence.clear();
      sentence_flag = false;
    }
    sentence.emplace_back(std::move(token));
  }
  if(!sentence.empty()){
    res.emplace_back(std::move(sentence));
    sentence.clear();
  }
  // for(auto &s: res){
  //   for(auto &w: s){
  //     cout << w << " ";
  //   }
  // }
  return res;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}
// const int TOKENS_COUNT = 1'000'000;

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestSplitting);
//   return 0;
// }
