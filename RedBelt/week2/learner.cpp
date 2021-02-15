#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cstdlib>

//#include "test_runner.h"
// #include "profile.h"

using namespace std;

// class LearnerOld {
// 	private:
// 	vector<string> dict;

// 	public:
// 	int Learn(const vector<string>& words) {
// 		int newWords = 0;
// 		for (const auto& word : words) {
// 			if (find(dict.begin(), dict.end(), word) == dict.end()) {
// 				++newWords;
// 				dict.push_back(word);
// 			}
// 		}
// 		return newWords;
// 	}

// 	vector<string> KnownWords() {
// 		sort(dict.begin(), dict.end());
// 			dict.erase(unique(dict.begin(), dict.end()), dict.end());
// 			return dict;
// 	}
// };

class Learner {
	private:
	set<string> dict;

	public:
	int Learn(const vector<string>& words) {
		auto old_size = dict.size();
		for (const auto& word : words) {
			dict.insert(word);
		}
		return dict.size() - old_size;
	}

	vector<string> KnownWords() {
		return vector<string>{begin(dict), end(dict)};
	}
};


// #define LARGE_SIZE 30000


// void TestWordsOld(){

// 	vector<string> unique_words = {"crazy", "dirty", "lazy"};
// 	LearnerOld learner;
// 	string line;
// 	stringstream in_stream;
// 	string uniq_word;
// 	for(auto i = 0; i < LARGE_SIZE; ++i){
// 		uniq_word = unique_words[rand() % 3] + static_cast<char>('a' + static_cast<char>((rand() % ('z'-'a'+1))));
// 		in_stream << unique_words[rand() % 3] << " ";
// 	}
// 	vector<vector<string>> words_all;
// 	while (getline(in_stream, line)) {
// 		vector<string> words;
// 		stringstream ss(line);
// 		string word;
// 		while (ss >> word) {
// 			words.push_back(word);
// 		}
// 		words_all.push_back(words);
// 	}

// 	int newWordsCount = 0;
// 	for(const auto& words: words_all){
// 		newWordsCount = learner.Learn(words);
// 	}

// 	vector<string> known_words;
// 	known_words = learner.KnownWords();

// 	ASSERT_EQUAL(newWordsCount, unique_words.size());
// 	ASSERT_EQUAL(known_words, unique_words);
// }


// void TestWordsNew(){

// 	vector<string> unique_words = {"crazy", "dirty", "lazy"};
// 	Learner learner;
// 	string line;
// 	stringstream in_stream;
// 	string uniq_word;
// 	for(auto i = 0; i < LARGE_SIZE; ++i){
// 		uniq_word = unique_words[rand() % 3] + static_cast<char>('a' + static_cast<char>((rand() % ('z'-'a'+1))));
// 		in_stream << unique_words[rand() % 3] << " ";
// 	}
// 	vector<vector<string>> words_all;
// 	while (getline(in_stream, line)) {
// 		vector<string> words;
// 		stringstream ss(line);
// 		string word;
// 		while (ss >> word) {
// 			words.push_back(word);
// 		}
// 		words_all.push_back(words);
// 	}
// 	int newWordsCount = 0;
// 	for(const auto& words: words_all){
// 		newWordsCount = learner.Learn(words);
// 	}

// 	vector<string> known_words;
// 	known_words = learner.KnownWords();
// 	ASSERT_EQUAL(newWordsCount, unique_words.size());
// 	ASSERT_EQUAL(known_words, unique_words);
// }

// string randomizeStr(const size_t size){
// 	string str;
// 	for(auto i = 0; i < size; ++i){
// 		str += static_cast<char>('a' + static_cast<char>((rand() % ('z'-'a'+1))));
// 	}
// 	return str;
// }
// #define WORD_SIZE 5

// vector<vector<string>> generateWords(){
// 	vector<vector<string>> res;

// 	string uniq_word;
// 	vector<string> words;
// 	for(auto i = 0; i < LARGE_SIZE; ++i){
// 		uniq_word = randomizeStr(WORD_SIZE);
// 		words.push_back(uniq_word);

// 	}
// 	res.push_back(words);
// 	return res;
// }

// void RunWordsOld(const vector<vector<string>>& words_all){

//     LearnerOld learner;
//     int newWordsCount = 0;
//     {
//       LOG_DURATION("learner.Learn Old");
//       for(const auto& words: words_all){
//         newWordsCount = learner.Learn(words);
//       }
//     }
// 	cout << "Old Count:" << newWordsCount << endl;
//     vector<string> known_words;
//     {
//       LOG_DURATION("learner.KnownWords old")
//       known_words = learner.KnownWords();
//     }
// }

// void RunWordsNew(const vector<vector<string>>& words_all){

//     Learner learner;


//     int newWordsCount = 0;
//     {
//       LOG_DURATION("learner.Learn New");
//       for(const auto& words: words_all){
//         newWordsCount = learner.Learn(words);
//       }
//     }
// 	cout << "New Count:" << newWordsCount << endl;

//     vector<string> known_words;
//     {
//       LOG_DURATION("learner.KnownWords New")
//       known_words = learner.KnownWords();
//     }
// }

// int main(){
// 	TestRunner tr;
// 	RUN_TEST(tr, TestWordsOld);
// 	RUN_TEST(tr, TestWordsNew);

// 	auto data = generateWords();
// 	RunWordsOld(data);
// 	RunWordsNew(data);
// 	return 0;
// }

// // Old Count:29961
// // learner.Learn Old: 27598 ms
// // learner.KnownWords old: 47 ms

// // New Count:29961
// // learner.Learn New: 69 ms
// // learner.KnownWords New: 2 ms