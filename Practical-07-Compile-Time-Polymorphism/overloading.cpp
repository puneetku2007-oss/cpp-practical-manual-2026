#include <iostream>
using namespace std;

// Function overloading
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

class ComplexNumber {
    double real, imag;
public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}
    ComplexNumber operator+(const ComplexNumber& o) const {   // operator overloading
        return ComplexNumber(real + o.real, imag + o.imag);
    }
    void show() const {
        cout << real << (imag >= 0 ? " + " : " - ") << (imag >= 0 ? imag : -imag) << "i";
    }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    cout << "add(int,int)       : " << add(5, 7) << endl;
    cout << "add(double,double) : " << add(2.5, 3.75) << endl;
    cout << "add(int,int,int)   : " << add(1, 2, 3) << endl;
    ComplexNumber c1(3, 4), c2(1.5, -2), c3;
    c3 = c1 + c2;
    cout << "c1 = "; c1.show(); cout << endl;
    cout << "c2 = "; c2.show(); cout << endl;
    cout << "c1 + c2 = "; c3.show(); cout << endl;
    return 0;
}
