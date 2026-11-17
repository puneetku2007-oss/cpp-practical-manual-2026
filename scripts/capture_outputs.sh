#!/usr/bin/env bash
# Compiles every practical (C++17, warnings on) and stores the real program output in output.txt.
# Usage: ./scripts/capture_outputs.sh      (run from the repository root)
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/build"; mkdir -p "$BUILD"
FLAGS="-std=c++17 -Wall -Wextra -Wpedantic -g"
fail=0
compile() { g++ $FLAGS -o "$BUILD/$2" "$ROOT/$1" || { echo "COMPILE FAILED: $1"; fail=1; return 1; }; echo "compiled: $1"; }

run_in() { # dir exe [stdin-file]   -> runs inside the practical folder
  ( cd "$ROOT/$1" && if [ -n "${3:-}" ]; then "$BUILD/$2" < "$3"; else "$BUILD/$2"; fi ) > "$ROOT/$1/output.txt" 2>&1
}

compile Practical-01-GitHub-Fundamentals/fundamentals.cpp p01 && {
  D="$ROOT/Practical-01-GitHub-Fundamentals"
  python3 "$ROOT/scripts/run_interactive.py" "$BUILD/p01" "$D/input_valid.txt" "$D/output.txt"
  python3 "$ROOT/scripts/run_interactive.py" "$BUILD/p01" "$D/input_invalid.txt" "$D/output_invalid_input.txt"; }
compile Practical-02-Classes/bank_account.cpp p02 && run_in Practical-02-Classes p02
compile Practical-03-Constructors-Rule-of-Five/rule_of_five.cpp p03 && run_in Practical-03-Constructors-Rule-of-Five p03
compile Practical-04-RAII-Smart-Pointers/smart_pointers.cpp p04 && run_in Practical-04-RAII-Smart-Pointers p04
compile Practical-05-Inheritance/inheritance.cpp p05 && run_in Practical-05-Inheritance p05
compile Practical-06-Runtime-Polymorphism/shapes_polymorphism.cpp p06 && run_in Practical-06-Runtime-Polymorphism p06
compile Practical-07-Compile-Time-Polymorphism/overloading.cpp p07 && run_in Practical-07-Compile-Time-Polymorphism p07
compile Practical-08-Design-Patterns/singleton_pattern.cpp p08 && run_in Practical-08-Design-Patterns p08
compile Practical-09-Templates/template_stack.cpp p09 && run_in Practical-09-Templates p09
compile Practical-10-Custom-Exceptions/bank_exceptions.cpp p10 && run_in Practical-10-Custom-Exceptions p10
compile Practical-11-File-Handling/csv_file_io.cpp p11 && run_in Practical-11-File-Handling p11

# Memory checks (Valgrind) for the resource-owning practicals
if command -v valgrind >/dev/null; then
  valgrind --leak-check=full --error-exitcode=1 "$BUILD/p03" >/dev/null 2> "$ROOT/Practical-03-Constructors-Rule-of-Five/memcheck.txt"; echo "valgrind P03 exit=$?"
  valgrind --leak-check=full --error-exitcode=1 "$BUILD/p04" >/dev/null 2> "$ROOT/Practical-04-RAII-Smart-Pointers/memcheck.txt"; echo "valgrind P04 exit=$?"
  g++ -std=c++17 -g -fsanitize=address,undefined -o "$BUILD/p04_asan" "$ROOT/Practical-04-RAII-Smart-Pointers/smart_pointers.cpp" \
    && "$BUILD/p04_asan" >/dev/null 2> "$ROOT/Practical-04-RAII-Smart-Pointers/asan.txt"; echo "ASan P04 exit=$?"
fi
exit $fail
