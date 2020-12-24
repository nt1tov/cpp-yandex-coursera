#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

int main()
{
	int n;
	std::cin>>n;
	long long  sum = 0;
	std::vector<long long> temp;
	for(auto i = 0; i < n; ++i){
		auto tmp = 0;
		std::cin>>tmp;
		sum += tmp;
		temp.push_back(tmp);
	}
	long long average = sum / n;
	std::vector<long long> temp_over_avg;
	for(size_t i = 0; i < temp.size(); ++i){
		if(temp[i] > average)
			temp_over_avg.push_back(i);
	}

	std::cout<<temp_over_avg.size()<<std::endl;
	for(auto &t: temp_over_avg)
		std::cout<<t<<" ";


	return 0;
}