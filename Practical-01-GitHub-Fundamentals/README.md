# Practical 01 | GitHub Setup and C++ Fundamentals

## Question
Create a GitHub repository and write a C++ program that demonstrates data types, constants, variables, operators and input/output.

## Aim
To practise basic C++ syntax and learn how to track code changes using Git and GitHub.

## What to do in this practical
- Create a GitHub repository named cpp-practicals (or another clear name) and clone it to your computer.
- Write a program that declares variables of suitable types, uses at least one const value, and accepts input from the user.
- Demonstrate arithmetic, relational and logical operators in a small calculation or decision.
- Display the input and calculated result clearly using cin and cout.
- Compile and run the program. Add a short README with the purpose and compile/run instructions.
- Commit and push the files with a meaningful message, such as “Add C++ fundamentals demo”.

## Submission / evidence
- C++ source file, README and visible commit in the GitHub repository.
- Record one sample input and output.

## Files

- `fundamentals.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)
- `input_valid.txt` - scripted input used for the run
- `output_invalid_input.txt` - run with invalid marks (`input_invalid.txt`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical01 fundamentals.cpp
./practical01 < input_valid.txt
```

## Review and verification

- Compiles with no warnings (`-Wall -Wextra -Wpedantic`).
- Changed: marks are now validated (whole number, 0-100) and re-requested on bad input; magic numbers replaced by named constants (`MAX_MARKS`, `PASS_MARK`).
- Tested a valid run (`input_valid.txt`) and an invalid-input run (`input_invalid.txt`: letters, 150, -5 before a valid mark).

## Output

```text
Name: Puneet Kumar
Enter student name: Puneet
Marks in subject 1 (0-100): 85
Marks in subject 2 (0-100): 72
Marks in subject 3 (0-100): 90

--- Result ---
Student : Puneet
Total   : 247 / 300
Percent : 82.3333%
Total % 7 (modulus demo) : 2
Status  : PASS
```
