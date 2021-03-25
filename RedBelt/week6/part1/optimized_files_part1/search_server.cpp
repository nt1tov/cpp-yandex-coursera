#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(string line) {
  istringstream words_input(move(line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;
  index.Clear();
  for (string current_document; getline(document_input, current_document); ) {
    index.Add(move(current_document));
  }

  //index = move(new_index);
}

//iterate oves queriies, check hitcount of query words in documents
void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  //docid_count.reserve(index.DocSize());
  vector<size_t> docid_count(index.DocCount(), 0);
  vector<size_t> docid_index(index.DocCount());
  iota(docid_index.begin(), docid_index.end(), 0);
  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);
    auto docid_count_query = docid_count;
    auto docid_index_query = docid_index;

    for (const auto& word : words) {
      for (const auto& [docid, hitcount] : index.Lookup(word)) {
        docid_count_query[docid] += hitcount;
      }
    }

    stable_sort(docid_index_query.begin(), docid_index_query.end(),
      [&docid_count_query](size_t i1, size_t i2) {
        return docid_count_query[i1] > docid_count_query[i2];
      }
    );

    partial_sort(docid_count_query.begin(), Head(docid_count_query, 5).end(), docid_count_query.end(),
      [](size_t lhs, size_t rhs) {
        return lhs > rhs;
      }
    );

    search_results_output << current_query << ':';
    auto top5_hitcount_query = Head(docid_count_query, 5);
    auto top5_docid_query = Head(docid_index_query, 5);

    for(auto it_docid = top5_docid_query.begin(),
        it_hitcount = top5_hitcount_query.begin();
        it_docid != top5_docid_query.end();
        ++it_docid, ++it_hitcount){
          if(*it_hitcount != 0){
            search_results_output << " {"
            << "docid: " << *it_docid << ", "
            << "hitcount: " << *it_hitcount << '}';
          }
    }
    search_results_output << endl;
  }
}

// void InvertedIndex::Add(const string& document) {
//   docs.push_back(document);

//   const size_t docid = docs.size() - 1;
//   for (const auto& word : SplitIntoWords(document)) {
//     index[word].push_back(docid);
//   }
// }

void InvertedIndex::Add(string document) {
  ++docs_count;

  const size_t docid = DocCount() - 1;
  unordered_map<string, size_t> counter;
  for (auto& word : SplitIntoWords(move(document))) {
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
