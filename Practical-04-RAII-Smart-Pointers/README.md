# Practical 04 | RAII and Smart Pointers

## Question
Replace suitable raw new/delete usage with std::unique_ptr and std::shared_ptr. Compare behaviour and check for memory leaks.

## Aim
To learn how RAII ties resource lifetime to object lifetime and reduces manual memory-management errors.

## What to do in this practical
- Create a small demo that allocates an object or array using std::unique_ptr.
- Create a second example where two parts of a program genuinely need shared ownership and use std::shared_ptr.
- Display or explain the ownership difference: unique_ptr has one owner; shared_ptr allows shared ownership.
- Avoid using shared_ptr when unique_ptr is sufficient. Do not manually delete smart-pointer-managed objects.
- Run the program through many iterations and compare its behaviour with a raw-pointer version if your instructor asks for a comparison.
- Use Valgrind or AddressSanitizer to check memory handling. Optionally record runtime or peak-memory observations using a system tool.

## Submission / evidence
- Source code and output.
- A short comparison of raw pointers, unique_ptr and shared_ptr, plus memory-check results.

> **Note:** Benchmark results depend on the system and workload. Record the tool and test conditions instead of claiming that one measurement applies everywhere.

## Files

- `smart_pointers.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)
- `memcheck.txt` - Valgrind report
- `asan.txt` - AddressSanitizer/UBSan stderr (empty = no errors)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical04 smart_pointers.cpp
./practical04
```

## Review and verification

- Compiles with no warnings.
- Reviewed: `unique_ptr` is used where one owner is enough; `shared_ptr` only for the genuinely shared case; no manual `delete`.
- Valgrind: 100,004 allocations / 100,004 frees, 0 errors (`memcheck.txt`). AddressSanitizer + UBSan run: no errors (`asan.txt` is empty because nothing was reported).

## Output

```text
Name: Puneet Kumar

1) unique_ptr (single owner)
  [acquired] File-A
  using File-A
  u1 empty after move? yes
  using File-A
  [released] File-A

2) shared_ptr (shared ownership)
  [acquired] Shared-DB
  use_count = 1
  use_count = 2 (second owner added)
  using Shared-DB
  use_count = 1 (second owner gone)
  [released] Shared-DB

3) 100000 iterations with unique_ptr (no leak)
  loop finished, sum = 4999950000
```
