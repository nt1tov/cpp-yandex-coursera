#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
using namespace std;

int main(){
    std::string start_expr;
    std::map<std::string, int> op_priority = { {"+", 1},
                                                {"-", 1},
                                                {"*", 2},
                                                {"/", 2}
                                            };
    int x;
    std::cin>>x;
    start_expr = std::to_string(x);
    int op_count;
    std::cin>>op_count;
    //start_expr = "(" + start_expr + ")";

    std::string prev_op = "*";
    std::string op;
    string operand;
    deque<std::string> strQueue;
    strQueue.push_back(start_expr);
    for(auto i = 0; i < op_count; ++i){

        std::cin>>op>>x;
        if(i != 0 && (op_priority[op] > op_priority[prev_op]) ){
            strQueue.push_front("(");

            strQueue.push_back(")");

            //start_expr = "(" + start_expr + ")";
        }
        prev_op = op;
        strQueue.push_back(" ");
        strQueue.push_back(op);
        strQueue.push_back(" ");
        strQueue.push_back(std::to_string(x));

    }

    for(auto it = strQueue.begin(); it != strQueue.end(); ++it){
        std::cout<<(*it);
    }
}


/*
in:
8
3
* 3
- 6
/ 1

out:
(8 * 3 - 6) / 1
*/
