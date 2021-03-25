#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <vector>
#include <future>
#include <functional>

using namespace std;

template <typename Iterator>
class Part {
public:
  Part(Iterator begin, Iterator end):
    part_begin(begin),
    part_end(end)
  {
  }
  Iterator begin() const {
    return part_begin;
  }
  Iterator end() const{
    return part_end;
  }
private:
  Iterator part_begin, part_end;
};

template<typename Iterator>
class Partitioner{
public:
  Partitioner(Iterator _begin, Iterator _end, size_t part_size){
    auto container_size = std::distance(_begin, _end);
    auto it = _begin;
    auto next_iter = it;
    while(it != _end){
      if(std::distance(it, _end) >= part_size){
        next_iter = next(it, part_size);
      }
      else{
        next_iter = _end;
      }
      parts.emplace_back(Part{it, next_iter});
      it = next_iter;
    }
  }

  auto begin() const{
    return parts.begin();
  }

  auto end() const{
    return parts.end();
  }

  size_t size() const{
    return parts.size();
  }

private:
  vector<Part<Iterator>> parts;
};

template<typename Container>
auto CreatePartitioner(Container& c, size_t part_size){
  return Partitioner(c.begin(), c.end(), part_size);
}

struct Stats {
  map<string, int> word_frequences;
  void operator += (const Stats& other){
    for(auto &[key, value]: other.word_frequences){
      word_frequences[key] += value;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats result;
  auto pos = 0;
  auto next_pos = 0;
  while(pos != line.size()-1){
    if(line[pos] != ' '){
      next_pos = line.find_first_of(' ', pos);
      if(next_pos == string::npos){
        next_pos = line.size();
      }
      auto word = line.substr(pos, next_pos-pos);
      if(key_words.find(word) != key_words.end()){
        result.word_frequences[word]++;
      }
    }
    pos = line.find_first_not_of(' ', next_pos);
    if(pos == string::npos){
      break;
    }
  }
  return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

template<typename ContainerOfStrings>
Stats ExploreKeyWordsThread (
  const set<string>& key_words,
  ContainerOfStrings input
) {
  Stats result;
  for (auto line: input ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<string> lines;
    Stats res;
    for(string line; getline(input, line);){
      lines.push_back(move(line));
    }
    auto partitioner = CreatePartitioner(lines, 2000);
    // for(auto part: partitioner){
    //     for(auto it = part.begin(); it != part.end(); it = next(it)){
    //       cout << *it << endl;
    //     }
    //   }

    vector<future<Stats>> futures;
    futures.reserve(5);
    if(partitioner.size() > 1){
      for(auto part: partitioner){
        futures.push_back(
          async(
            ExploreKeyWordsThread<Part<typename vector<string>::iterator>>,
            ref(key_words),
            move(part)
          ));
      }
      for (auto& f : futures) {
        res += f.get();
      }
    }
    else{
      res += ExploreKeyWordsThread(key_words, move(*partitioner.begin()));
    }

    return res;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  {

    stringstream ss;
    vector<string> lines;
    lines.reserve(5);
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
    lines.emplace_back("this new yangle service really rocks\n");
    lines.emplace_back("It sucks when yangle isn't available\n");
    lines.emplace_back("10 reasons why yangle is the best IT company\n");
    lines.emplace_back("yangle rocks others suck\n");
    lines.emplace_back("Goondex really sucks, but yangle rocks. Use yangle\n");
    for(auto i = 0; i < 10000; i++){
      ss << lines[i % 5];
    }
    LOG_DURATION("LoadTest");
    const auto stats = ExploreKeyWords(key_words, ss);
  }
}