#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {

}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4}); //8 1 6
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4}); //4 5 8 1 6
  cout << endl;
  return 0;
}