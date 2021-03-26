#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <deque>

using namespace std;



class InvertedIndex {
public:

  InvertedIndex(){
    docs_count = 0;
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
  InvertedIndex index;
};

/*
AddQuerie вот тут попробуй Synchronized<InvertedIndex> const & index.
Тут for (const pair<int, size_t>& entry - тоже.
и тут vector<pair<size_t, size_t>> InvertedIndex::Lookup переделай чтобы возвращаемый 
тип был const vector<pair<size_t, size_t>>&
*/