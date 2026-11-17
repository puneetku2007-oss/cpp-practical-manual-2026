# cpp-practical-manual-2026

C++ Programming Practical Manual - all 12 practicals, verified and organised for submission.

**Student:** Puneet Kumar | **Roll No:** E25B000036 | **Division:** D | **Academic year:** 2026 | **University:** Ajeenkya D Y Patil University

Every practical folder contains the verified source code, its real program output (the first line is
always `Name: Puneet Kumar`), and a README with the original college question and aim.

## Practicals

| # | Folder | Topic |
|---|--------|-------|
| 01 | [Practical-01-GitHub-Fundamentals](Practical-01-GitHub-Fundamentals) | Data types, constants, operators, input/output, Git |
| 02 | [Practical-02-Classes](Practical-02-Classes) | Classes, access specifiers, member functions |
| 03 | [Practical-03-Constructors-Rule-of-Five](Practical-03-Constructors-Rule-of-Five) | Constructors and the Rule of Five |
| 04 | [Practical-04-RAII-Smart-Pointers](Practical-04-RAII-Smart-Pointers) | RAII, `unique_ptr`, `shared_ptr` |
| 05 | [Practical-05-Inheritance](Practical-05-Inheritance) | Single and multilevel inheritance |
| 06 | [Practical-06-Runtime-Polymorphism](Practical-06-Runtime-Polymorphism) | Virtual functions, abstract classes |
| 07 | [Practical-07-Compile-Time-Polymorphism](Practical-07-Compile-Time-Polymorphism) | Function and operator overloading |
| 08 | [Practical-08-Design-Patterns](Practical-08-Design-Patterns) | Singleton pattern |
| 09 | [Practical-09-Templates](Practical-09-Templates) | Generic `Stack<T>` |
| 10 | [Practical-10-Custom-Exceptions](Practical-10-Custom-Exceptions) | Custom exception hierarchy (banking) |
| 11 | [Practical-11-File-Handling](Practical-11-File-Handling) | CSV file I/O, `tellg`/`seekg`/`tellp`/`seekp` |
| 12 | [Practical-12-Library-Management-System](Practical-12-Library-Management-System) | **Mini project:** Library Management System |

## Build and run everything

Requirements: `g++` with C++17 support (and optionally `valgrind`, `python3`).

```bash
./scripts/capture_outputs.sh                                  # compiles practicals 01-11 and re-creates their output.txt files
./Practical-12-Library-Management-System/run_tests.sh         # compiles and tests the Library Management System
```

Compile a single practical, for example:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical05 Practical-05-Inheritance/inheritance.cpp
./practical05
```

## Verification status

- All 12 programs compile with `g++ -std=c++17 -Wall -Wextra -Wpedantic` without warnings.
- Practicals 03 and 04 pass Valgrind (`--leak-check=full`); Practical 04 is also clean under AddressSanitizer and UBSan.
- Practical 12: 15 test scenarios (37 checks) pass; see its README.
- All output files were produced by actually running the programs (see `scripts/`).

## Repository layout

```text
cpp-practical-manual-2026/
├── Practical-01-... to Practical-11-.../   source, output.txt, README.md
├── Practical-12-Library-Management-System/ src/, data/, docs/, screenshots/, README.md
├── scripts/                                capture_outputs.sh, run_interactive.py
├── .gitignore
├── LICENSE
└── README.md
```
