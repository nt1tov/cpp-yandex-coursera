#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <utility>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, const Key &k)
{
	if(m.count(k) == 0){
		throw std::runtime_error ("element not found");
	}
	else{
		return m[k];
	}


}

int main()
{
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue

	return 0;
}