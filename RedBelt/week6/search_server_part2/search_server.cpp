#include "search_server.h"
#include "iterator_range.h"



vector<string> SplitIntoWords(string&& line) {
  istringstream words_input(move(line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void UpdateBaseThread(Synchronized<InvertedIndex>&  index, istream& document_input) {
  if(index.GetAccess().ref_to_value.DocCount() == 0){
    auto index_acc = index.GetAccess();
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document); ) {
      new_index.Add(move(current_document));
    }
    swap(index_acc.ref_to_value, new_index);
  }
  else{
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document); ) {
      new_index.Add(move(current_document));
    }
    swap(index.GetAccess().ref_to_value, new_index);
  }

}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  _server_futures.push_back(async(UpdateBaseThread, ref(_index), ref(document_input)));
  if(_first_update == true){
    _first_update = false;
    _server_futures.back().get();
  }
}

//iterate oves queriies, check hitcount of query words in documents
//template<typename Iterator>
// void ThreadQuery(
//   Synchronized<InvertedIndex>& index,
//   Part<vector<string>::iterator> batch,
//   string& search_result_str
//   ){
//   stringstream search_results_output;
//   vector<pair<size_t, size_t>>  docid_counter(index.GetAccess().ref_to_value.DocCount(), {0,0});
//   for (auto& query: batch) {
//     search_results_output << query << ':';
//     const auto words = SplitIntoWords(move(query));
//     docid_counter.assign(docid_counter.size(), pair<size_t, size_t>(0,0));

//     for (const auto& word : words) {
//       for (const auto& [docid, hitcount] : index.GetAccess().ref_to_value.Lookup(word)) {
//         docid_counter[docid].second += hitcount;
//         docid_counter[docid].first = docid;
//       }
//     }

//     partial_sort(docid_counter.begin(), Head(docid_counter, 5).end(), docid_counter.end(),
//       [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
//         return make_pair(lhs.second, rhs.first) > make_pair(rhs.second, lhs.first);
//       }
//     );

//     for(auto &[id, hitcount]: Head(docid_counter, 5)){
//           if(hitcount != 0){
//             search_results_output << " {"
//             << "docid: " << id << ", "
//             << "hitcount: " << hitcount << '}';
//           }
//     }
//     search_results_output << endl;
//   }
//   search_result_str = move(search_results_output.str());
// }

// void SearchServer::AddQueriesStream(
//   istream& query_input, ostream& search_results_output
// ) {

//   vector<string> queries;
//   for(string current_query; getline(query_input, current_query);){
//     queries.push_back(move(current_query));
//   }
//   vector<string> res(queries.size());
//   auto fsize = max<size_t>(1, queries.size()/6);
//   auto qbatches = CreatePartitioner(queries, fsize);
//   {
//     vector<future<void>> futures;
//     futures.reserve(fsize);
//     auto i = 0;
//     for(auto &qbatch : qbatches){
//       futures.push_back(async(ThreadQuery, ref(index), (qbatch), ref(res[i])));
//       ++i;
//     }
//   }
//   for(auto i = 0; i < res.size(); ++i){
//     search_results_output << res[i];
//   }
// }

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    _server_futures.push_back(
      async(
            [&query_input, &search_results_output, this]{
              vector<pair<size_t, size_t>>  docid_counter(_index.GetAccess().ref_to_value.DocCount(), {0,0});
              for (string current_query; getline(query_input, current_query); ) {
                search_results_output << current_query << ':';
                const auto words = SplitIntoWords(move(current_query));
                docid_counter.assign(docid_counter.size(), pair<size_t, size_t>(0,0));

                for (const auto& word : words) {
                  for (const auto& [docid, hitcount] : _index.GetAccess().ref_to_value.Lookup(word)) {
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
      )
    );
}


void InvertedIndex::Add(string&& document) {
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
// UpdateDocumentBase: 971 ms
// AddQueriesStream: 1174 ms