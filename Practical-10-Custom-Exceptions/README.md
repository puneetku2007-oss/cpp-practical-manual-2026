# Practical 10 | Custom Exceptions: Banking Transaction

## Question
Create a custom exception hierarchy and throw/catch specific exceptions in a banking transaction program.

## Aim
To practise reporting application-specific failures and handling different errors in a controlled way.

## What to do in this practical
- Create a BankAccount class with a balance and a withdraw or transfer operation.
- Define custom exceptions such as InsufficientFunds and InvalidAmount, derived from std::exception or a suitable standard exception class.
- Throw InvalidAmount for a non-positive amount and InsufficientFunds when the requested withdrawal exceeds the balance.
- Catch each exception type separately and display a helpful message.
- Test successful and unsuccessful transactions, and make sure a failed transaction does not change the balance incorrectly.

## Submission / evidence
- Source code and output for successful and failed transactions.
- A short note describing what each custom exception represents.

## Files

- `bank_exceptions.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical10 bank_exceptions.cpp
./practical10
```

## Review and verification

- Compiles with no warnings.
- Reviewed: `InvalidAmount` and `InsufficientFunds` derive from `std::exception`; the balance changes only after every check passes; tested a successful withdrawal, a negative amount, an excessive amount and a final successful withdrawal.

## Output

```text
Name: Puneet Kumar
Opening balance = 5000
Withdraw 1200: SUCCESS. Balance = 3800
Withdraw -100: InvalidAmount: amount must be greater than zero | Balance unchanged = 3800
Withdraw 9000: InsufficientFunds: withdrawal exceeds available balance | Balance unchanged = 3800
Withdraw 3800: SUCCESS. Balance = 0
```
