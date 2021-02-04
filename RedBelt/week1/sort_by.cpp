#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;



// struct Date {
//   int year, month, day;
// };

// struct Time {
//   int hours, minutes;
// };

// struct AirlineTicket {
//   string from;
//   string to;
//   string airline;
//   Date departure_date;
//   Time departure_time;
//   Date arrival_date;
//   Time arrival_time;
//   int price;
// };


ostream& operator<<(ostream& os, const Date& date){
	os << "{";
	os << "{" <<"day: " << date.day << "}" << ", ";
	os << "{" <<"month: " << date.month << "}" << ", ";
	os << "{" <<"year: " << date.year << "}";
	os << "}";
	return os;
}


ostream& operator<<(ostream& os, const Time& time){
	os << "{";
	os << "{" <<"hours: " << time.hours << "}" << ", ";
	os << "{" <<"minutes: " << time.minutes << "}";
	os << "}";
	return os;
}


ostream& operator<<(ostream& os, const AirlineTicket& ticket){
	os << "{";
	os << "{" <<"from: " << ticket.from << "}" << ", ";
	os << "{" <<"to: " << ticket.to << "}" << ", ";
	os << "{" <<"airline: " << ticket.airline << "}" << ", ";
	os << "{" <<"departure_date: " << ticket.departure_date << "}" << ", ";
	os << "{" <<"departure_time: " << ticket.departure_time << "}" << ", ";
	os << "{" <<"arrival_date: " << ticket.arrival_date << "}" << ", ";
	os << "{" <<"arrival_date: " << ticket.arrival_time << "}" << ", ";
	os << "{" <<"price: " << ticket.price << "}";
	os << "}";
	return os;
}

bool operator<(const Date& lhs, const Date& rhs){
	if(lhs.year != rhs.year){
		return lhs.year < rhs.year;
	}
	else if(lhs.month != rhs.month){
		return lhs.month < rhs.month;
	}
	return lhs.day < rhs.day;
}

bool operator==(const Date& lhs, const Date& rhs){
	if(lhs.year == rhs.year){
		if(lhs.month == rhs.month){
			return lhs.day == rhs.day;
		}
	}
	return false;
}

bool operator<(const Time& lhs, const Time& rhs){
	if(lhs.hours != rhs.hours){
		return lhs.hours < rhs.hours;
	}
	return lhs.minutes < rhs.minutes;
}

bool operator==(const Time& lhs, const Time& rhs){
	if(lhs.hours == rhs.hours){
		return lhs.minutes == rhs.minutes;
	}
	return false;
}

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

#define SORT_BY(field)  																			\
	[](const AirlineTicket& lhs, const AirlineTicket& rhs) {return lhs.field < rhs.field;}																		\


void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
