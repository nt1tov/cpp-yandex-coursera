
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {

	vector<string> v;
	auto it = begin(s);
	while(it != end(s)){
		auto tmp_it = find(it, end(s), ' ');
		v.push_back(string(it, tmp_it));
		if(tmp_it != end(s))
			it = ++tmp_it;
		else
			break;
	}
	return v;

}


int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}


//4 С/Cpp/Java/Python