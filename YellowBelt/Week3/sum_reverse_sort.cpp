#include "sum_reverse_sort.h"
#include <algorithm>
int Sum(int x, int y) {
    return x + y;
}
string Reverse(string s) {

    string reversed = s;
    for(auto i = 0; i < static_cast<int>(s.size()); ++i)
        reversed[i] = s[s.size() - 1 - i];
    return reversed;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}
