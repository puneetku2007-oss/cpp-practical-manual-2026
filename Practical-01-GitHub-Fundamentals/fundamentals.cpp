// Practical 01: C++ fundamentals - data types, constants, variables, operators, input/output.
#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int MAX_MARKS = 100;    // constant: maximum marks per subject
const int PASS_MARK = 40;     // constant: minimum marks to pass one subject
const int SUBJECTS = 3;

// Keeps asking until the user enters a whole number between 0 and MAX_MARKS.
// Returns false if input ends (EOF) before a valid number is entered.
bool readMarks(int subjectNo, int& marks) {
    while (true) {
        cout << "Marks in subject " << subjectNo << " (0-" << MAX_MARKS << "): ";
        if (cin >> marks && marks >= 0 && marks <= MAX_MARKS) return true;
        if (cin.eof()) return false;
        cout << "Invalid marks. Please enter a number between 0 and " << MAX_MARKS << "." << endl;
        cin.clear();                                              // reset the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');      // discard the bad input
    }
}

int main() {
    cout << "Name: Puneet Kumar" << endl;

    string studentName;
    cout << "Enter student name: ";
    cin >> studentName;

    int marks[SUBJECTS];
    for (int i = 0; i < SUBJECTS; ++i) {
        if (!readMarks(i + 1, marks[i])) {
            cout << "Input ended unexpectedly." << endl;
            return 1;
        }
    }

    int total = 0;                                               // arithmetic operators
    for (int m : marks) total += m;
    double percent = (total * 100.0) / (SUBJECTS * MAX_MARKS);

    // relational (>=) and logical (&&, ||) operators
    bool passedAll = true;
    for (int m : marks) passedAll = passedAll && (m >= PASS_MARK);
    bool distinction = (percent >= 75.0);

    cout << "\n--- Result ---" << endl;
    cout << "Student : " << studentName << endl;
    cout << "Total   : " << total << " / " << SUBJECTS * MAX_MARKS << endl;
    cout << "Percent : " << percent << "%" << endl;
    cout << "Total % 7 (modulus demo) : " << total % 7 << endl;
    cout << "Status  : " << ((passedAll || distinction) ? "PASS" : "FAIL") << endl;
    return 0;
}
