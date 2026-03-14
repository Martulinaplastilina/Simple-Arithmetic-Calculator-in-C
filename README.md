# Simple Arithmetic Calculator in C

A small command-line calculator written in C capable of evaluating basic arithmetic expressions.

This project started as a personal learning exercise while studying the C programming language.
The implementation was written from scratch, without following external calculator implementations, in order to better understand how arithmetic expressions can be parsed and evaluated internally.

The long-term goal is to continue improving and expanding the project, gradually turning it into a more complete and robust calculator.

## Features

The calculator currently supports:

* Addition (+)
* Subtraction (-)
* Multiplication (*)
* Division (/)
* Floating point numbers
* Handling of multiple consecutive signs (for example +-+-+-)

Example of a valid expression:

5*-2+3*4+--+++1*-+-+-985385394/-----++++89+-+-+-+---10

Output:

11071758

## How it Works

The program processes the input expression in several stages:

1. Reading and storing the input expression
2. Simplifying consecutive signs
3. Removing unnecessary spaces
4. Extracting operands and operators
5. Resolving operator precedence (* and / before + and -)
6. Evaluating the expression step by step

The goal of this approach was to manually explore how a simple expression evaluator can be implemented using arrays and basic parsing techniques.

## Compilation

Compile the program using gcc:

gcc calculator1.c -o calculator

## Execution

Run the program from the terminal:

./calculator

Then enter the arithmetic expression you want to evaluate.

## Current Limitations

* Parentheses are not supported yet
* Only the four basic arithmetic operators are implemented
* Expressions must be entered on a single line

## Future Improvements

Planned improvements include:

* Support for parentheses
* More robust input validation
* Better expression parsing
* Additional mathematical operations

## Project Status

This project is a work in progress and will continue evolving as I keep learning more about C, parsing techniques, and program design.
