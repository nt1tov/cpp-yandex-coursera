#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

using namespace std;
template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T()):
    value(move(initial))
  {
  }

  struct Access {
    lock_guard<mutex> g;
    T& ref_to_value;
  };

  Access GetAccess(){
    return Access{lock_guard(m), value};
  }
private:
  T value;
  mutex m;
};

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

class InvertedIndex {
public:

  InvertedIndex(){
    docs_count = 0;
  }

  InvertedIndex(InvertedIndex&& other){
    swap(index, other.index);
    docs_count = other.docs_count;
  }
  void operator=(InvertedIndex&& other){
    //cout << "move assignment" << endl;
    //index = move(other.index);
    swap(index, other.index);
    docs_count = other.docs_count;
  }
  //void Add(const string& document);
  void Add(string&& document);
  const vector<pair<size_t, size_t>>& Lookup(const string& word) const;

  // const string& GetDocument(size_t id) const {
  //   return docs[id];
  // }

  size_t DocCount() const{
    return docs_count;
  }

  void Clear(){
    index.clear();
    docs_count = 0;
  }

inline static vector<pair<size_t, size_t>> empty_lookup = {{}};

private:
  unordered_map<string, vector<pair<size_t, size_t>>> index;
  size_t docs_count;
};


class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> _index;
  bool _first_update = true;
  vector<future<void>> _server_futures;
};


