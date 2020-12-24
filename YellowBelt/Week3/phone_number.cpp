#include <string>
#include "phone_number.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
using namespace std;



PhoneNumber::PhoneNumber(const string &international_number) {
		string str = international_number;
		if(international_number[0] != '+' || international_number.find('-') == string::npos ||
			international_number.find(' ') != string::npos)
			throw invalid_argument(international_number);
		if(international_number.substr(international_number.find("-") + 1).find('-') == string::npos)
			throw invalid_argument(international_number);
		
		int i = 0;
		while(international_number[i] != '-'){
			++i;
		}


		cerr << international_number.find("-") << endl;
		int buf_idx = i + 1;
		country_code_ = international_number.substr(1, i-1);
		i++;
		int count  = 0;
		while(international_number[i] != '-'){
			++i;
			count++;
		}
		city_code_ = international_number.substr(buf_idx, count);
		local_number_ = international_number.substr(buf_idx + 1 + count);

		if(country_code_.size() == 0 ||city_code_.size() == 0 ||local_number_.size() == 0 )
			throw invalid_argument(international_number);


}

string PhoneNumber::GetCountryCode() const {
		return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	stringstream os;
	os << "+" <<country_code_<<"-"<<city_code_<<"-"<<local_number_;
	return (os.str());
	
}


// int main() {
// 	PhoneNumber num("+7-8-9");
// 	cout << num.GetCountryCode() <<endl;
// 	cout << num.GetCityCode() <<endl;
// 	cout << num.GetLocalNumber() <<endl;
// 	cout << num.GetInternationalNumber() <<endl;
// 	return 0;
// }

  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
