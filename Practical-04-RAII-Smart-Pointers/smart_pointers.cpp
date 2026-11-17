#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Resource {
    string name;
public:
    Resource(string n) : name(n) { cout << "  [acquired] " << name << endl; }
    ~Resource() { cout << "  [released] " << name << endl; }
    void use() const { cout << "  using " << name << endl; }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;

    cout << "\n1) unique_ptr (single owner)" << endl;
    {
        unique_ptr<Resource> u1 = make_unique<Resource>("File-A");
        u1->use();
        unique_ptr<Resource> u2 = move(u1);   // ownership transferred
        cout << "  u1 empty after move? " << (u1 == nullptr ? "yes" : "no") << endl;
        u2->use();
    }   // released automatically

    cout << "\n2) shared_ptr (shared ownership)" << endl;
    {
        shared_ptr<Resource> s1 = make_shared<Resource>("Shared-DB");
        cout << "  use_count = " << s1.use_count() << endl;
        {
            shared_ptr<Resource> s2 = s1;
            cout << "  use_count = " << s1.use_count() << " (second owner added)" << endl;
            s2->use();
        }
        cout << "  use_count = " << s1.use_count() << " (second owner gone)" << endl;
    }   // released when last owner dies

    cout << "\n3) 100000 iterations with unique_ptr (no leak)" << endl;
    long sum = 0;
    for (int i = 0; i < 100000; ++i) {
        unique_ptr<int[]> arr(new int[10]);
        arr[0] = i;
        sum += arr[0];
    }
    cout << "  loop finished, sum = " << sum << endl;
    return 0;
}
