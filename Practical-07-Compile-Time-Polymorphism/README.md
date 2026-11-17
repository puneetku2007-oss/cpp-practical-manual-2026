# Practical 07 | Compile-Time Polymorphism: Overloading

## Question
Demonstrate function overloading and operator overloading using a Complex Number or Matrix class.

## Aim
To understand how C++ selects functions at compile time based on parameters and operator definitions.

## What to do in this practical
- Write two or more functions with the same name but different parameter lists, such as add(int, int) and add(double, double).
- Create a ComplexNumber class with real and imaginary parts, or a Matrix class with a small fixed number of values.
- Overload a suitable operator, such as +, to combine two objects.
- Display the operands and result clearly. Include a case that tests the overloaded operator.
- Explain the difference between function overloading, operator overloading and runtime polymorphism.

## Submission / evidence
- Source code and output.
- One or two sentences describing why the chosen operator overload is useful.

## Files

- `overloading.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical07 overloading.cpp
./practical07
```

## Review and verification

- Compiles with no warnings.
- Reviewed: three `add` overloads (int/int, double/double, int/int/int) and `ComplexNumber::operator+`; a negative imaginary part is printed correctly.

## Output

```text
Name: Puneet Kumar
add(int,int)       : 12
add(double,double) : 6.25
add(int,int,int)   : 6
c1 = 3 + 4i
c2 = 1.5 - 2i
c1 + c2 = 4.5 + 2i
```
