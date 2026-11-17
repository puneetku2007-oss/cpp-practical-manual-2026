#include <iostream>
#include <exception>
#include <string>
using namespace std;

class InvalidAmount : public exception {
public:
    const char* what() const noexcept override {
        return "InvalidAmount: amount must be greater than zero";
    }
};
class InsufficientFunds : public exception {
public:
    const char* what() const noexcept override {
        return "InsufficientFunds: withdrawal exceeds available balance";
    }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b) : balance(b) {}
    void withdraw(double amt) {
        if (amt <= 0) throw InvalidAmount();
        if (amt > balance) throw InsufficientFunds();
        balance -= amt;              // changed only after all checks pass
    }
    double getBalance() const { return balance; }
};

void attempt(BankAccount& acc, double amt) {
    cout << "Withdraw " << amt << ": ";
    try {
        acc.withdraw(amt);
        cout << "SUCCESS. Balance = " << acc.getBalance() << endl;
    } catch (const InvalidAmount& e) {
        cout << e.what() << " | Balance unchanged = " << acc.getBalance() << endl;
    } catch (const InsufficientFunds& e) {
        cout << e.what() << " | Balance unchanged = " << acc.getBalance() << endl;
    }
}

int main() {
    cout << "Name: Puneet Kumar" << endl;
    BankAccount acc(5000);
    cout << "Opening balance = " << acc.getBalance() << endl;
    attempt(acc, 1200);
    attempt(acc, -100);
    attempt(acc, 9000);
    attempt(acc, 3800);
    return 0;
}
