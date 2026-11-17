#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;     // pure virtual -> Shape is abstract
    virtual const char* name() const = 0;
    virtual ~Shape() {}                  // virtual destructor
};
class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return M_PI * r * r; }
    const char* name() const override { return "Circle"; }
};
class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double l, double w) : l(l), w(w) {}
    double area() const override { return l * w; }
    const char* name() const override { return "Rectangle"; }
};
class Triangle : public Shape {
    double b, h;
public:
    Triangle(double b, double h) : b(b), h(h) {}
    double area() const override { return 0.5 * b * h; }
    const char* name() const override { return "Triangle"; }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    // Shape s;  // ERROR: cannot instantiate abstract class
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5));
    shapes.push_back(make_unique<Rectangle>(4, 6));
    shapes.push_back(make_unique<Triangle>(3, 8));
    for (const auto& s : shapes)          // base-class interface, derived behaviour
        cout << s->name() << " area = " << s->area() << endl;
    return 0;
}
