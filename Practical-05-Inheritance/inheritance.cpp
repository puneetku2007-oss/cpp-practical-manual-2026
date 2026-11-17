#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name; int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    void displayPerson() const { cout << "Name: " << name << ", Age: " << age << endl; }
};
class Student : public Person {          // single inheritance
protected:
    int studentId; string course;
public:
    Student(string n, int a, int id, string c) : Person(n, a), studentId(id), course(c) {}
    void displayStudent() const {
        displayPerson();
        cout << "Student ID: " << studentId << ", Course: " << course << endl;
    }
};
class GraduateStudent : public Student { // multilevel inheritance
    string researchTopic, supervisor;
public:
    GraduateStudent(string n, int a, int id, string c, string topic, string sup)
        : Student(n, a, id, c), researchTopic(topic), supervisor(sup) {}
    void displayGraduate() const {
        displayStudent();
        cout << "Research: " << researchTopic << ", Supervisor: " << supervisor << endl;
    }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    cout << "\n--- Student (single inheritance: Person -> Student) ---" << endl;
    Student s("Puneet Kumar", 19, 36, "B.Tech AI & DS");
    s.displayStudent();
    cout << "\n--- GraduateStudent (multilevel: Person -> Student -> GraduateStudent) ---"
         << endl;
    GraduateStudent g("Jehal Shah", 23, 101, "M.Tech AI",
                      "Emergency Response Systems", "Dr. Mehta");
    g.displayGraduate();
    return 0;
}
