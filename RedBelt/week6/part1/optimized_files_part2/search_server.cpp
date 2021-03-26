#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(string& line) {
  istringstream words_input((line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }
  index = move(new_index);
}

//iterate oves queriies, check hitcount of query words in documents
void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {

  vector<pair<size_t, size_t>>  docid_counter(index.DocCount(), {0,0});
  for (string current_query; getline(query_input, current_query); ) {
    search_results_output << current_query << ':';
    const auto words = SplitIntoWords((current_query));
    docid_counter.assign(docid_counter.size(), pair<size_t, size_t>(0,0));

    for (const auto& word : words) {
      for (const auto& [docid, hitcount] : index.Lookup(word)) {
        docid_counter[docid].second += hitcount;
        docid_counter[docid].first = docid;
      }
    }

    partial_sort(docid_counter.begin(), Head(docid_counter, 5).end(), docid_counter.end(),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        return make_pair(lhs.second, rhs.first) > make_pair(rhs.second, lhs.first);
      }
    );

    for(auto &[id, hitcount]: Head(docid_counter, 5)){
          if(hitcount != 0){
            search_results_output << " {"
            << "docid: " << id << ", "
            << "hitcount: " << hitcount << '}';
          }
    }
    search_results_output << endl;
  }
}


void InvertedIndex::Add(string&& document) {
  ++docs_count;

  const size_t docid = DocCount() - 1;
  unordered_map<string, size_t> counter;
  for (auto& word : SplitIntoWords((document))) {
    counter[word]++;
  }
  for (auto& [word, count] : counter) {
    index[word].emplace_back(pair{docid, count});
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return index.at(word);
  }
  else {
    return empty_lookup;
  }
}
// UpdateDocumentBase: 971 ms
// AddQueriesStream: 1174 ms