#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
    stack<T> items;                      // STL container used internally
public:
    void push(const T& v) { items.push(v); }
    void pop() {
        if (items.empty()) throw runtime_error("Stack underflow: cannot pop from empty stack");
        items.pop();
    }
    const T& top() const {
        if (items.empty()) throw runtime_error("Stack is empty: no top element");
        return items.top();
    }
    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

template <typename T>
void test(const char* label, T a, T b, T c) {
    cout << "\n--- Stack<" << label << "> ---" << endl;
    Stack<T> s;
    s.push(a); s.push(b); s.push(c);
    cout << "Size after 3 pushes: " << s.size() << endl;
    while (!s.empty()) { cout << "Top = " << s.top() << " -> pop" << endl; s.pop(); }
    try { s.pop(); }
    catch (const exception& e) { cout << "Error caught: " << e.what() << endl; }
}

int main() {
    cout << "Name: Puneet Kumar" << endl;
    test<int>("int", 10, 20, 30);
    test<float>("float", 1.5f, 2.5f, 3.5f);
    test<string>("string", "C++", "is", "fun");
    return 0;
}
