# Practical 09 | Generic Stack or Queue Using Templates

## Question
Write a generic Stack or Queue class using templates and test it with int, float and std::string values.

## Aim
To understand generic programming and how one class can work with multiple data types.

## What to do in this practical
- Create a class template for Stack or Queue using a suitable STL container internally, or use a simple fixed-size implementation if instructed.
- Provide basic operations such as push and pop for a stack, or enqueue and dequeue for a queue.
- Add a method to check whether the structure is empty and a safe way to access its next item.
- Create and test instances for int, float and std::string.
- Handle invalid operations, such as popping from an empty structure, in a clear way.
- Explain how a template avoids writing three separate implementations.

## Submission / evidence
- Source code and output showing all three data types.
- Brief test cases for normal use and an empty-container condition.

## Files

- `template_stack.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical09 template_stack.cpp
./practical09
```

## Review and verification

- Compiles with no warnings.
- Reviewed: `Stack<T>` wraps `std::stack`; tested with `int`, `float` and `std::string`; popping an empty stack throws `std::runtime_error`, which is caught and reported.

## Output

```text
Name: Puneet Kumar

--- Stack<int> ---
Size after 3 pushes: 3
Top = 30 -> pop
Top = 20 -> pop
Top = 10 -> pop
Error caught: Stack underflow: cannot pop from empty stack

--- Stack<float> ---
Size after 3 pushes: 3
Top = 3.5 -> pop
Top = 2.5 -> pop
Top = 1.5 -> pop
Error caught: Stack underflow: cannot pop from empty stack

--- Stack<string> ---
Size after 3 pushes: 3
Top = fun -> pop
Top = is -> pop
Top = C++ -> pop
Error caught: Stack underflow: cannot pop from empty stack
```
