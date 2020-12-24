#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
using namespace std;

int main(){
    std::string start_expr;
    int x;
    std::cin>>x;
    start_expr = std::to_string(x);
    int op_count;
    std::cin>>op_count;
    //start_expr = "(" + start_expr + ")";

    deque<std::string> strQueue;
    strQueue.push_back(start_expr);
    std::string op;
    string operand;
    for(auto i = 0; i < op_count; ++i){
        strQueue.push_front("(");
        strQueue.push_back(")");
        std::cin>>op>>x;
        strQueue.push_back(" ");
        strQueue.push_back(op);
        strQueue.push_back(" ");
        strQueue.push_back(std::to_string(x));
    }
    for(auto it = strQueue.begin(); it != strQueue.end(); ++it){
        std::cout<<(*it);
    };
}

/*
in:
8
3
* 3
- 6
/ 1

out:
(((8) * 3) - 6) / 1
*/
