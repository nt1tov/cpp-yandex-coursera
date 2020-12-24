#include <iostream>

using namespace std;

class Animal {
public:
    Animal(const std::string &_Name): Name(_Name) {}
    // ваш код

    const string Name;
};


class Dog : public Animal {
public:
    Dog(const std::string &_Name): Animal(_Name) {}
    // ваш код

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

// int main(){
//     auto d = Dog("cat");
//     d.Bark();
// }