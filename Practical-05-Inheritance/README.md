# Practical 05 | Single and Multilevel Inheritance

## Question
Implement a university-management example using inheritance: Person → Student → GraduateStudent.

## Aim
To understand base and derived classes and how data and behaviour can be reused.

## What to do in this practical
- Create a Person base class with common information such as name and age.
- Create a Student class derived from Person with student ID and course details.
- Create a GraduateStudent class derived from Student with a research topic or supervisor name.
- Add constructors and display functions in the relevant classes.
- Demonstrate single inheritance using Person → Student, and multilevel inheritance using all three classes.
- Create objects and explain which inherited members are available to each derived class.

## Submission / evidence
- Source code and output for Student and GraduateStudent objects.
- A simple inheritance diagram showing the class relationships.

## Files

- `inheritance.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical05 inheritance.cpp
./practical05
```

## Review and verification

- Compiles with no warnings.
- Reviewed: Person -> Student -> GraduateStudent; derived constructors call the base constructor; protected members are reachable from derived classes.

## Output

```text
Name: Puneet Kumar

--- Student (single inheritance: Person -> Student) ---
Name: Puneet Kumar, Age: 19
Student ID: 36, Course: B.Tech AI & DS

--- GraduateStudent (multilevel: Person -> Student -> GraduateStudent) ---
Name: Jehal Shah, Age: 23
Student ID: 101, Course: M.Tech AI
Research: Emergency Response Systems, Supervisor: Dr. Mehta
```
