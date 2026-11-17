# Practical 02 | Classes, Access Specifiers and Member Functions

## Question
Design and implement a class hierarchy or class model for a real-world entity, such as BankAccount or Vehicle.

## Aim
To understand how classes combine data and behaviour, and how access specifiers protect data.

## What to do in this practical
- Create a class such as BankAccount with suitable private data members, for example account number and balance.
- Add public member functions to set or display details and perform a meaningful operation such as deposit or withdraw.
- Use a constructor to initialise the object. Validate values where needed.
- Explain in comments which members are private and which are public, and why.
- Create at least two objects and demonstrate their member functions from main().

## Submission / evidence
- Source code and sample output for at least two objects.
- A short note explaining the purpose of private and public members.

## Files

- `bank_account.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical02 bank_account.cpp
./practical02
```

## Review and verification

- Compiles with no warnings.
- Reviewed: balance is private; constructor rejects negative opening balance; deposit/withdraw reject invalid and excessive amounts.
- Tested two objects including a failed withdrawal and an invalid deposit.

## Output

```text
Name: Puneet Kumar

--- Object 1 ---
A/C No: 1001 | Holder: Puneet | Balance: 5000
Deposited 1500
Withdrew 800
A/C No: 1001 | Holder: Puneet | Balance: 5700

--- Object 2 ---
A/C No: 1002 | Holder: Jehal | Balance: 2000
Insufficient balance.
Invalid deposit amount.
Deposited 500
A/C No: 1002 | Holder: Jehal | Balance: 2500
```
