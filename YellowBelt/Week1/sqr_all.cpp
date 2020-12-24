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


template <typename First , typename Second >
pair <First , Second > operator * (const pair <First , Second >& p1 , const pair <First , Second >& p2);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> &p);

template <typename T>
vector<T> Sqr(const vector<T> &v);

template <typename Key, typename Value>
map<Key, Value> Sqr( const map<Key, Value>& m);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> &p);


// Объявляем шаблонные функции

template <typename T>
T Sqr(const T &x)
{
	return x * x;

}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> &p)
{
	First f = Sqr(p.first);
	Second s = Sqr(p.second);
	return {f, s};
}

template <typename T>
vector<T> Sqr(const vector<T> &v) 
{ 
	std::vector<T> sq;
	for(auto &item: v){
		sq.push_back(Sqr(item));
	}
	return sq;
}

template <typename Key, typename Value>
map<Key, Value> Sqr( const map<Key, Value>& m) 
{ 
	map<Key, Value> sq;

	for (auto& [key , value] : m) {
		sq[key] = Sqr(value);
	}
	return sq;

}

int main()
{

	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}