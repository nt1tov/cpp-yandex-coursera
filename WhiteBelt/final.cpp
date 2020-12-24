#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <vector>


using namespace std;

class Date {
private:
        int day, year, month;
public:
        Date();
        Date(int year, int month, int day);
        int GetYear() const;
        int GetMonth() const;
        int GetDay() const;
};
Date::Date()
{
        this->day = 1;
        this->month = 1;
        this->year = 0;
}
Date::Date(int year, int month, int day)
{
        this->day = day;
        this->month = month;
        this->year = year;
}
int Date::GetDay() const
{
        return day;
}

int Date::GetMonth() const
{
        return month;
}

int Date::GetYear() const
{
        return year;
}


class Database {
private:
        map<Date, set<string> > DB;
public:
        void AddEvent(const Date& date, const string& event);
        bool DeleteEvent(const Date& date, const string& event);
        int  DeleteDate(const Date& date);
        void Find(const Date& date) const;
        void PrintData() const;
};

bool operator==(const Date& lhs, const Date& rhs)
{
        return ( (lhs.GetYear() == rhs.GetYear()) 
                && (lhs.GetMonth() == rhs.GetMonth()) 
                && (lhs.GetDay() == rhs.GetDay()));
}
bool operator<(const Date& lhs, const Date& rhs)
{
        if (lhs.GetYear() != rhs.GetYear()) {
                return lhs.GetYear() < rhs.GetYear();
        }
        else {
                if (lhs.GetMonth() != rhs.GetMonth()) {
                        return lhs.GetMonth() < rhs.GetMonth();
                }
                else {
                        return lhs.GetDay() < rhs.GetDay();
                }
        }

}

ostream& operator<<(ostream& stream, const Date& date) {
        stream << fixed << setfill('0');
        stream << setw(4) << date.GetYear() << "-";
        stream << setw(2) << date.GetMonth() << "-";
        stream << setw(2) << date.GetDay();
        return stream;
}
Date ParseDate(const string& data)
{
        Date date;
        int day = 0;
        int month = 0;
        int year = 0;

        istringstream input(data);
        input >> year;
        if(year < 0 || year > 9999){
                throw runtime_error("Wrong date format: " + data);
        }
        else{
                input.ignore(1);
                input >> month;

                if(input.peek() != '-'){
                        throw runtime_error("Wrong date format: " + data);
                }
                else{
                        input.ignore(1);
                        input >> day;
                        if (input.peek() != EOF) {
                                throw runtime_error("Wrong date format: " + data);
                        }
                        if (month < 1 || month > 12) {
                                throw invalid_argument("Month value is invalid: " + to_string(month));
                        }
                        if (day < 1 || day > 31) {
                                throw invalid_argument("Day value is invalid: " + to_string(day));
                        }
                        return date = { year, month, day };
                }
                
        }
        return date;
}
void Database::AddEvent(const Date& new_date, const string& new_event)
{
        bool date_not_empty = 0, event_found = 0;
        for (auto& date: DB){
                if(date.first == new_date){
                        for(auto& event : date.second){
                                if(event == new_event){
                                        event_found = 1;
                                }  
                        }
                        if(event_found == 0){
                                date.second.insert(new_event);
                                date_not_empty = 1;
                        }
                        
                }
        }
        if(date_not_empty == 0){
                DB[new_date].insert(new_event);
        }
}

bool Database::DeleteEvent(const Date& del_date, const string& del_event)
{
        bool f = 0;
        for(auto& date: DB){
                if(date.first == del_date){
                        for(const auto& event: date.second){
                                if(event == del_event){
                                        date.second.erase(event);
                                        f = 1;
                                }
                                if(date.second.size() == 0){
                                        DB.erase(date.first);
                                        return f;
                                }
                        }
                        return f;
                }
        }
        return f;

}
int  Database::DeleteDate(const Date& del_date)
{
        int i = 0;
        //cout<<"delete date started"<<endl;
        for(const auto& date: DB){
                if(date.first == del_date){
                        i = date.second.size();
                        DB.erase(date.first);
                        return i;
                }
        }
        return i;
        //cout<<"delete date successfully"<<endl;
}

void  Database::PrintData() const
{
        for(const auto& date: DB){
                for(auto& event: date.second)
                        cout<<date.first<<" "<<event<<endl;
        }
}

void Database::Find(const Date& find_date) const
{
        for(const auto& date: DB){
                if(date.first == find_date){
                        for(const auto& ev: date.second){
                                cout<<ev<<endl;
                        }
                }
        }

}
int main() {
        Database db;
        string command;
        try{
                while (getline(cin, command)) {// Считайте команды с потока ввода и обработайте каждую
                        istringstream input(command);
                        string cmd = "";
                        input >> cmd;
                        if(cmd == "Add"){
                                string date = "";
                                string event;
                                input >> date >> event;
                                Date new_date = ParseDate(date);
                                if (event.size() != 0) {
                                        db.AddEvent(new_date, event);
                                }
                                else{
                                        throw runtime_error("Wrong date format:");
                                }
                        }
                        else if(cmd == "Find"){
                                string date = "";
                                input >> date;
                                Date new_date = ParseDate(date);
                                db.Find(new_date);
                        }
                        else if(cmd == "Del"){
                                string date = "";
                                input >> date;
                                Date new_date = ParseDate(date);
                                if (input.peek() != EOF) {
                                        string event;
                                        input >> event;
                                        bool k = db.DeleteEvent(new_date, event);
                                        if (k == true) {
                                                cout << "Deleted successfully" << endl;
                                        }
                                        else {
                                                cout << "Event not found" << endl;
                                        }
                                }
                                else {
                                        int num = db.DeleteDate(new_date);
                                        cout << "Deleted " << num << " events" << endl;
                                }
                        }
                        else if(cmd == "Print"){
                                db.PrintData();
                       }
                      else{
                                if(cmd.size() == 0){
                                      continue;
                               }
                               throw runtime_error("Unknown command: " + cmd);
                       }

                }
        }
        catch(exception& ex){
                cout << ex.what();
        }

  return 0;
}