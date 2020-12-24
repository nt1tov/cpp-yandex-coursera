
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


template <typename T>
void RemoveDuplicates(vector<T>& elements) {

	set<T> buf_set;
	for(auto it = begin(elements); it != end(elements); ++it){
		buf_set.insert(*it);
	}
	elements.assign(begin(buf_set), end(buf_set));
}


int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;
  
  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}

//6 4 7 0 1
//C++ C