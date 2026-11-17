# Practical 06 | Runtime Polymorphism and Abstract Classes

## Question
Create an abstract Shape class and implement Circle, Rectangle and Triangle with an area() function.

## Aim
To demonstrate how a base-class interface can be used to call the correct derived-class function at runtime.

## What to do in this practical
- Declare a Shape base class with a pure virtual area() function and a virtual destructor.
- Derive Circle, Rectangle and Triangle from Shape. Implement area() for each shape.
- Store or refer to the derived objects through Shape pointers or references.
- Call area() through the base-class interface and display each calculated area.
- Use valid dimensions and explain why Shape itself cannot be instantiated when it is abstract.

## Submission / evidence
- Source code and sample output for all three shapes.
- A short explanation of virtual functions and runtime polymorphism.

## Files

- `shapes_polymorphism.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical06 shapes_polymorphism.cpp
./practical06
```

## Review and verification

- Compiles with no warnings.
- Reviewed: `Shape` has a pure virtual `area()` and a virtual destructor; shapes are stored as `unique_ptr<Shape>`; `Shape s;` is shown in a comment as the compile error it would cause.

## Output

```text
Name: Puneet Kumar
Circle area = 78.5398
Rectangle area = 24
Triangle area = 12
```
