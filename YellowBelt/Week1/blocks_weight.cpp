
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
 
using namespace std;

int main()
{
	size_t count, density;
	cin>>count>>density;
	size_t sum_weight = 0;
	for(size_t i = 0; i < count; ++i){
		size_t w, h, d;
		cin>>w>>h>>d;
		sum_weight += density * w * h * d;
	}
	cout<<sum_weight;


	return 0;
}