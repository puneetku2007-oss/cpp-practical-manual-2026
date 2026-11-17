# Practical 08 | Singleton or Factory Design Pattern

## Question
Implement either the Singleton or Factory design pattern in C++ and discuss its use case and trade-offs.

## Aim
To practise applying a common object-creation design pattern instead of creating objects without a clear structure.

## What to do in this practical
- Choose one pattern: Singleton or Factory. State why it fits your example.
- For Singleton, create a class that controls access to a single instance. For Factory, create a function or factory class that returns objects based on a requested type.
- Demonstrate the pattern in a small program, such as application settings (Singleton) or shape/vehicle creation (Factory).
- Show the pattern working with at least two calls or requested object types.
- Write a short note covering one benefit and one trade-off, such as global access and testing difficulty for Singleton, or extra structure for Factory.

## Submission / evidence
- Source code and sample output.
- A small class/object diagram or flow diagram, plus the use case and trade-off.

> **Note:** Choose only one pattern for implementation. Do not implement both unless your instructor asks for an extension.

## Files

- `singleton_pattern.cpp` - verified source code
- `output.txt` - actual program output (first line is `Name: Puneet Kumar`)

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o practical08 singleton_pattern.cpp
./practical08
```

## Review and verification

- Compiles with no warnings.
- Reviewed: Singleton with private constructor, deleted copy operations and a function-local static instance; two `getInstance()` calls are shown to return the same object. Only one pattern is implemented, as the manual requires.

## Output

```text
Name: Puneet Kumar
AppSettings instance created
Theme: Light, Font size: 12
Theme: Dark, Font size: 16
Same instance? Yes
```
