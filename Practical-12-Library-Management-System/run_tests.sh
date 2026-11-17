#!/usr/bin/env bash
# Automated tests for the Library Management System.
# Each test feeds scripted input to the real program, saves the real transcript in
# docs/test-transcripts/ and checks it. Run from this folder:  ./run_tests.sh
set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
BIN="$HERE/../build/library"
OUT="$HERE/docs/test-transcripts"
TMP="/tmp/lms-test"; rm -rf "$TMP"; mkdir -p "$TMP"; trap 'rm -rf "$TMP"' EXIT
mkdir -p "$HERE/../build" "$OUT"
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -o "$BIN" "$HERE/src/library.cpp" || { echo "COMPILE FAILED"; exit 1; }
pass=0; failn=0

# fresh_csv <file> : copy the sample data into a temp file
fresh_csv() { cp "$HERE/data/books.csv" "$1"; }
# session <name> <csv> <input> : run the program, save the transcript, return its path in $T
session() { T="$OUT/$1.txt"; printf "%b" "$3" | "$BIN" "$2" > "$T" 2>&1; }
# expect <test-name> <pattern> [file]
expect() { local f="${3:-$T}"
  if grep -qE -- "$2" "$f"; then pass=$((pass+1)); echo "  ok   - $1"
  else failn=$((failn+1)); echo "  FAIL - $1 (expected: $2)"; fi; }
reject() { local f="${3:-$T}"
  if grep -qE -- "$2" "$f"; then failn=$((failn+1)); echo "  FAIL - $1 (unexpected: $2)"
  else pass=$((pass+1)); echo "  ok   - $1"; fi; }

echo "== Required tests =="
C="$TMP/t1.csv"; fresh_csv "$C"
echo "T01 Add a new book"
session T01_add_book "$C" "1\n201\nClean Code\nRobert Martin\n7\n"
expect "message shown" "Book added\."
expect "saved to CSV file" "201,Clean Code,Robert Martin,1" "$C"

echo "T02 Display all books"; fresh_csv "$C"
session T02_display_all "$C" "2\n7\n"
expect "lists book 101" "\[101\] Let Us C\+\+ by Yashavant Kanetkar - Available"
expect "shows issued status" "\[103\] Effective Modern C\+\+ by Scott Meyers - Issued"
expect "shows total" "5 book\(s\) in total"

echo "T03 Search for an existing book"
session T03_search_existing "$C" "3\n104\n4\nprimer\n7\n"
expect "found by ID" "\[104\] C\+\+ Primer by Stanley Lippman - Available"
expect "found by title (case-insensitive)" "C\+\+ Primer by Stanley Lippman"

echo "T04 Search for a nonexistent book"
session T04_search_missing "$C" "3\n999\n4\nJava\n7\n"
expect "unknown ID reported" "ERROR: Book ID 999 not found"
expect "unknown title reported" "No book found with 'Java'"

echo "T05 Issue an available book"; fresh_csv "$C"
session T05_issue_available "$C" "5\n101\n2\n7\n"
expect "issue message" "Book issued\."
expect "status changed" "\[101\].*- Issued"
expect "saved as issued" "101,Let Us C\+\+,Yashavant Kanetkar,0" "$C"

echo "T06 Issue an already-issued book"; fresh_csv "$C"
session T06_issue_already_issued "$C" "5\n103\n7\n"
expect "rejected" "ERROR: 'Effective Modern C\+\+' is already issued"
reject "not reported as issued" "Book issued\."

echo "T07 Return a book"; fresh_csv "$C"
session T07_return_book "$C" "6\n103\n7\n"
expect "return message" "Book returned\."
expect "saved as available" "103,Effective Modern C\+\+,Scott Meyers,1" "$C"

echo "T08 Return a book that was never issued"; fresh_csv "$C"
session T08_return_not_issued "$C" "6\n101\n7\n"
expect "rejected" "ERROR: 'Let Us C\+\+' was not issued"
reject "not reported as returned" "Book returned\."

echo "T09 Add a duplicate book ID"; fresh_csv "$C"
session T09_duplicate_id "$C" "1\n101\nAnother Title\nSomeone\n2\n7\n"
expect "rejected" "ERROR: Book ID 101 already exists"
reject "original not replaced" "Another Title by"

echo "T10 Restart the application and reload saved records"
C2="$TMP/t10.csv"; fresh_csv "$C2"
session T10a_first_run "$C2" "1\n301\nThe Pragmatic Programmer\nAndrew Hunt\n5\n301\n7\n"
session T10b_after_restart "$C2" "2\n7\n"
expect "records loaded on start" "Loaded 6 book\(s\) from"
expect "new book persisted" "\[301\] The Pragmatic Programmer by Andrew Hunt - Issued"

echo "== Extra tests: validation and file handling =="
fresh_csv "$C"
echo "T11 Invalid input is rejected"
session T11_invalid_input "$C" "abc\n3\nxyz\n3\n-4\n3\n0\n1\n401\n\n1\n402\nBad,Title\n7\n"
expect "invalid menu choice" "Invalid menu choice"
expect "letters rejected as ID" "ERROR: Invalid number: 'xyz'"
expect "negative rejected" "ERROR: Invalid number: '-4'"
expect "zero rejected" "ERROR: ID must be greater than zero"
expect "empty title rejected" "ERROR: Title cannot be empty"
expect "comma rejected" "ERROR: Title cannot contain a comma"
reject "invalid books not added" "401|402" "$C"
echo "T12 Missing data file starts empty, then creates it"
M="$TMP/new_folder/none.csv"
session T12_missing_file "$M" "2\n1\n501\nFirst Book\nAuthor One\n7\n"
expect "missing file handled" "No data file .* found\. Starting with an empty library\."
expect "file created on first save" "501,First Book,Author One,1" "$M"
echo "T13 Malformed CSV lines are skipped safely"
printf 'id,title,author,available\n1,Good Book,Author,1\nthis is not valid\nabc,Bad ID,Author,1\n2,Bad Flag,Author,7\n1,Duplicate,Author,1\n3,Last Book,Author,0\n' > "$TMP/bad.csv"
session T13_malformed_csv "$TMP/bad.csv" "2\n7\n"
expect "malformed line skipped" "Skipping malformed line 3"
expect "invalid records skipped" "Skipping invalid record on line 4"
expect "only valid records loaded" "Loaded 2 book\(s\)"
echo "T14 Unwritable file does not crash"
mkdir -p "$TMP/dir_as_file.csv"
session T14_unwritable "$TMP/dir_as_file.csv" "1\n601\nTest\nTester\n7\n"
expect "warning shown" "WARNING: Cannot open .* for writing"
expect "program continues" "Goodbye!"
echo "T15 End of input exits cleanly"
session T15_eof "$C" ""
expect "exits without crashing" "Input ended\. Exiting\."

echo
echo "Passed: $pass   Failed: $failn"
[ "$failn" -eq 0 ]
