
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

using namespace std;

const float PI = 3.14;

class Figure {
public:
    Figure(){}
    virtual std::string Name() = 0;
    virtual float Perimeter() = 0;
    virtual float Area() = 0;
};

class Triangle : public Figure{
    int w, h, c;
    std::string name = "TRIANGLE";
    float area;
    float perimeter;

public:
    Triangle(int _w, int _h, int _c): w(_w), h(_h), c(_c) 
    {
        perimeter = static_cast<float> (w + h + c);
        auto p = perimeter / 2.0;
        area = sqrt(p * (p - w) * (p - h) * (p - c));
    }
    std::string Name() {return name;}
    float Perimeter() {return perimeter;}
    float Area() { return area; }
};

class Rect : public Figure{
    int w, h;
    std::string name = "RECT";
    float area;
    float perimeter;

public:
    Rect(int _w, int _h): w(_w), h(_h) 
    {
        perimeter = static_cast<float> (2*(w + h));
        area = static_cast<float>(w*h);
    }
    std::string Name() {return name;}
    float Perimeter() {return perimeter;}
    float Area() { return area; }
};


class Circle : public Figure{
    int r;
    std::string name = "CIRCLE";
    float area;
    float perimeter;

public:
    Circle(int _r): r(_r)
    {
        perimeter = static_cast<float> (2*PI*r);
        area = static_cast<float>(PI*r*r);
    }
    std::string Name() {return name;}
    float Perimeter() {return perimeter;}
    float Area() { return area; }
};

shared_ptr<Figure> CreateFigure(std::istringstream &is){
    std::string command;
    is >> command;
    if(command == "TRIANGLE"){
        int x, y, z;
        is >> x >> y >> z;
        return make_shared<Triangle>(x, y, z);
    }
    if(command == "RECT"){
        int x, y;
        is >> x >> y ;
        return make_shared<Rect>(x, y);
    }
    if(command == "CIRCLE"){
        int x;
        is >> x;
        return make_shared<Circle>(x);
    }
    return nullptr;
}
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    std::string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } 
    else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}