# Practical 03 | Constructors and Rule of Five

## Question
Implement a class that demonstrates default, parameterized, copy and move constructors, and the Rule of Five.

## Aim
To understand object creation, copying, moving and safe management of an owned resource.

## What to do in this practical
- Create a small resource-owning class, for example a class that manages a dynamically allocated integer array.
- Implement a default constructor and a parameterized constructor.
- Implement a copy constructor and copy assignment operator that perform a deep copy.
- Implement a move constructor and move assignment operator that transfer ownership safely.
- Implement a destructor to release the owned resource. Add comments explaining all five Rule of Five members.
- Create objects that exercise each constructor/assignment path. Compile and run the program.
- Where available, run Valgrind with --leak-check=full and correct any reported leaks or invalid memory operations.

## Submission / evidence
- Source code demonstrating each operation and the output.
- Valgrind output or a note stating which alternative checking tool was used.

> **Note:** The Rule of Five refers to destructor, copy constructor, copy assignment, move constructor and move assignment. The default and parameterized constructors are additional constructor forms.

## Files

- `rule_of_five.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)
- `memcheck.txt` - Valgrind report

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical03 rule_of_five.cpp
./practical03
```

## Review and verification

- Compiles with no warnings.
- Reviewed: deep copy (changing the copy does not change the original), move operations are `noexcept` and leave the source empty, self-assignment is guarded.
- Valgrind `--leak-check=full`: no leaks, 0 errors (`memcheck.txt`).

## Output

```text
Name: Puneet Kumar
Default constructor
Parameterized constructor (size 3)
Copy constructor
b [size=3]: 7 7 7 
c [size=3]: 99 7 7 
Copy assignment
a [size=3]: 7 7 7 
Move constructor
d [size=3]: 7 7 7 
b (moved-from) [size=0]: 
Default constructor
Move assignment
e [size=3]: 99 7 7 
c (moved-from) [size=0]: 
```
