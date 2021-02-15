#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <deque>
#include <unordered_map>

// #include "profile.h"
//#include "test_runner.h"

using namespace std;

struct ClientStamp{
    long long time;
    string hotel;
    int id;
    int count;
};

class BookManager{
public:
    BookManager(){}

    //вывести количество различных клиентов, бронировавших номера в отеле hotel_name за последние сутки.
    int GetClients(const string& hotel) const{
        if(hotel_day_clients_.find(hotel) == hotel_day_clients_.end()){
            return 0;
        }
        return hotel_day_clients_.at(hotel);
    }

    //вывести количество номеров, забронированных за последние сутки в отеле hotel
    int GetRooms(const string& hotel) const{
        if(hotel_day_rooms_.find(hotel) == hotel_day_rooms_.end()){
            return 0;
        }
        return hotel_day_rooms_.at(hotel);
    }


    void Book(const long long& t, const string& hotel, const int& cid, const int& room_cnt){
        CleanPeriod(t);
        clients_q_.emplace_front(ClientStamp{t, hotel, cid, room_cnt});
        if(clients_hotels_[cid].find(hotel) == clients_hotels_[cid].end()){
            ++hotel_day_clients_[hotel];
        }
        ++clients_hotels_[cid][hotel];
        hotel_day_rooms_[hotel] += room_cnt;
    }
private:
    void CleanPeriod(const long long& t){
        while(!clients_q_.empty() && (abs (t - clients_q_.back().time) >= DAYTIME_PERIOD_SEC)){
            auto tmp = clients_q_.back();
            clients_q_.pop_back();
            if(clients_hotels_[tmp.id][tmp.hotel] > 1){
                --clients_hotels_[tmp.id][tmp.hotel];
            }
            else{
                clients_hotels_[tmp.id].erase(tmp.hotel);
                hotel_day_clients_[tmp.hotel]--;
            }
            hotel_day_rooms_[tmp.hotel] -= tmp.count;
        }
    }
   // unordered_map<int, int> unique_day_clients_;
    unordered_map<int, unordered_map<string, int>> clients_hotels_;

    deque<ClientStamp> clients_q_;
    unordered_map<string, int> hotel_day_clients_;
    unordered_map<string, int> hotel_day_rooms_;

    static const int MAX_ROOM_COUNT = 1000;
    static const int MAX_CLIENT_COUNT = 1'000'000'000;
    static const long long DAYTIME_PERIOD_SEC = 86400;

};

// void SmallTest(){
//     stringstream ss;
//     ss <<"13\n";
//     ss << "CLIENTS Marriott\n";
//     ss << "ROOMS Marriott\n";
//     ss << "BOOK 10 FourSeasons 1 2\n";
//     ss << "BOOK 10 Marriott 1 1\n";
//     ss << "BOOK 86409 FourSeasons 2 1\n";
//     ss << "CLIENTS FourSeasons\n";
//     ss << "ROOMS FourSeasons\n";
//     ss << "CLIENTS Marriott\n";
//     ss << "BOOK 86410 Marriott 2 10\n";
//     ss << "ROOMS FourSeasons\n";
//     ss << "ROOMS Marriott\n";
//     ss << "CLIENTS Marriott\n";
//     ss << "CLIENTS FourSeasons\n";
//     vector<int> expected = {0,0,2,3,1,1,10,1,1};
//     vector<int> res;
//     BookManager manager;
//     int query_count;
//     ss >> query_count;
//     for (int query_id = 0; query_id < query_count; ++query_id) {
//         string query_type;
//         ss >> query_type;
//         cerr << query_id << " " << query_type << endl;
//         if (query_type == "BOOK") {
//             long long time;
//             string hotel_name;
//             int client_id;
//             int room_count;
//             ss >> time >> hotel_name >> client_id >> room_count;
//             manager.Book(time, hotel_name, client_id, room_count);
//         }
//         else if (query_type == "CLIENTS") {
//             string hotel_name;
//             ss >> hotel_name;
//             res.push_back(manager.GetClients(hotel_name));
//         }
//         else if (query_type == "ROOMS") {
//             string hotel_name;
//             ss >> hotel_name;
//             res.push_back(manager.GetRooms(hotel_name));
//         }
//     }
//     ASSERT_EQUAL(res, expected);
// }


// int main(){
//     TestRunner trunner;
//     RUN_TEST(trunner, SmallTest);

// }


int main(){
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BookManager manager;
    int query_count;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            long long time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.GetClients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.GetRooms(hotel_name) << endl;
        }
  }
}