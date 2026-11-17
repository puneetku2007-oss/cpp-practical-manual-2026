#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:   // hidden from outside, so balance cannot be changed directly
    int accountNumber;
    string holderName;
    double balance;
public:                        // public: safe interface used by main()
    BankAccount(int no, string name, double initial) : accountNumber(no), holderName(name) {
        balance = (initial >= 0) ? initial : 0;   // validation
    }
    void deposit(double amt) {
        if (amt <= 0) { cout << "Invalid deposit amount." << endl; return; }
        balance += amt;
        cout << "Deposited " << amt << endl;
    }
    void withdraw(double amt) {
        if (amt <= 0) { cout << "Invalid withdrawal amount." << endl; return; }
        if (amt > balance) { cout << "Insufficient balance." << endl; return; }
        balance -= amt;
        cout << "Withdrew " << amt << endl;
    }
    void display() const {
        cout << "A/C No: " << accountNumber << " | Holder: " << holderName
             << " | Balance: " << balance << endl;
    }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    BankAccount a1(1001, "Puneet", 5000);
    BankAccount a2(1002, "Jehal", 2000);
    cout << "\n--- Object 1 ---" << endl;
    a1.display();
    a1.deposit(1500);
    a1.withdraw(800);
    a1.display();
    cout << "\n--- Object 2 ---" << endl;
    a2.display();
    a2.withdraw(3000);      // fails: insufficient
    a2.deposit(-50);        // fails: invalid
    a2.deposit(500);
    a2.display();
    return 0;
}
