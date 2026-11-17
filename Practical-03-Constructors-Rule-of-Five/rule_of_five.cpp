#include <iostream>
#include <utility>
using namespace std;

class IntArray {
    int* data;
    size_t size;
public:
    IntArray() : data(nullptr), size(0) { cout << "Default constructor" << endl; }
    IntArray(size_t n, int value) : data(new int[n]), size(n) {
        for (size_t i = 0; i < n; ++i) data[i] = value;
        cout << "Parameterized constructor (size " << n << ")" << endl;
    }
    // 1. Destructor: releases the owned array
    ~IntArray() { delete[] data; }
    // 2. Copy constructor: deep copy
    IntArray(const IntArray& o) : data(new int[o.size]), size(o.size) {
        for (size_t i = 0; i < size; ++i) data[i] = o.data[i];
        cout << "Copy constructor" << endl;
    }
    // 3. Copy assignment: deep copy, safe against self-assignment
    IntArray& operator=(const IntArray& o) {
        cout << "Copy assignment" << endl;
        if (this != &o) {
            delete[] data;
            size = o.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) data[i] = o.data[i];
        }
        return *this;
    }
    // 4. Move constructor: steals the pointer
    IntArray(IntArray&& o) noexcept : data(o.data), size(o.size) {
        o.data = nullptr; o.size = 0;
        cout << "Move constructor" << endl;
    }
    // 5. Move assignment: releases own resource, steals the other's
    IntArray& operator=(IntArray&& o) noexcept {
        cout << "Move assignment" << endl;
        if (this != &o) {
            delete[] data;
            data = o.data; size = o.size;
            o.data = nullptr; o.size = 0;
        }
        return *this;
    }
    void set(size_t i, int v) { if (i < size) data[i] = v; }
    void show(const char* label) const {
        cout << label << " [size=" << size << "]: ";
        for (size_t i = 0; i < size; ++i) cout << data[i] << " ";
        cout << endl;
    }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    IntArray a;                     // default
    IntArray b(3, 7);               // parameterized
    IntArray c = b;                 // copy constructor
    c.set(0, 99);                   // proves deep copy
    b.show("b"); c.show("c");
    a = b;                          // copy assignment
    a.show("a");
    IntArray d = move(b);           // move constructor
    d.show("d"); b.show("b (moved-from)");
    IntArray e;
    e = move(c);                    // move assignment
    e.show("e"); c.show("c (moved-from)");
    return 0;
}
