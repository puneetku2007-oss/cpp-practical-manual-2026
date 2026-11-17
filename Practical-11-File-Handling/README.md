# Practical 11 | CSV Student Records Using File I/O

## Question
Implement a CSV reader/writer using fstream to store and retrieve student records. Demonstrate seekg(), seekp(), tellg() and tellp().

## Aim
To practise persistent storage, structured records, file modes and file-position operations.

## What to do in this practical
- Define a Student record with fields such as ID, name and marks. Decide and document a simple CSV format.
- Write at least three records to students.csv. Check whether the file opened and whether writing succeeded.
- Read the records back and display them in a readable format. Handle missing or malformed input where practical.
- Use tellg() and seekg() to inspect and change the read position in a simple demonstration.
- Use tellp() and seekp() to inspect and change the write position in a simple demonstration.
- Explain the difference between input (get) and output (put) positions. Avoid assuming raw struct bytes are a portable CSV format.

## Submission / evidence
- Source code and the generated CSV file.
- Sample output and evidence of all four position functions.

> **Note:** For this practical, demonstrate the file-position functions on a simple file separately from the CSV append/read workflow if that makes the program easier to understand.

## Files

- `csv_file_io.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)
- `students.csv` - CSV file produced by the program

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical11 csv_file_io.cpp
./practical11
```

## Review and verification

- Compiles with no warnings.
- Changed: CSV reading/writing moved into `readCsv` / `writeCsv` functions; added safe handling of a missing file and of malformed lines (skipped and reported); numbers are parsed with `stoi`/`stod` inside try/catch.
- `tellg`, `seekg`, `tellp` and `seekp` are demonstrated on a separate text file (`pos.txt`), as the manual suggests.

## Output

```text
Name: Puneet Kumar
Wrote 3 records to students.csv

--- Reading students.csv ---
ID  Name     Marks
1   Puneet   88.5
2   Jehal   91
3   Aarav   76.25

--- Error handling: missing file ---
  Could not open does_not_exist.csv (handled safely)

--- Error handling: malformed lines ---
  Skipping malformed line 3: this line is wrong
  Skipping line 4 (invalid number): 5,Karan,abc
  Valid records loaded: 2

--- File position functions ---
Initial tellg() = 0, tellp() = 0
seekg(4) then get() -> 'E', tellg() = 5
seekp(2) then put('x'), tellp() = 3
File content now: ABxDEFGHIJ
File size via seekg(0, end)/tellg() = 10 bytes
```
