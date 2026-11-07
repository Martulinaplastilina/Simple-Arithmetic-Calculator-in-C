# Simple Arithmetic Calculator in C (v2.0 — Shunting-Yard)

A command-line arithmetic expression evaluator written in C, now powered by a stack-based implementation of Edsger Dijkstra's **Shunting-Yard algorithm**.

This project started as a personal learning exercise while studying the C programming language. 
- **v1.0** was written completely from scratch without consulting external parsing algorithms, using a multi-pass array-compression approach to understand the fundamentals of expression evaluation.
- **v2.0** represents a complete architectural redesign, moving to a single-pass, character-by-character stream evaluator using operator and operand stacks to support nested parentheses and formal operator precedence.

## Features

The calculator currently supports:

- **Basic arithmetic operations:** Addition (`+`), Subtraction (`-`), Multiplication (`*`), and Division (`/`)
- **Nested parentheses:** Full support for grouped sub-expressions `(...)`
- **Operator precedence & associativity:** Proper handling of precedence levels and left/right associativity rules
- **Floating-point numbers:** Double-precision (`double`) support, including leading-dot decimals (e.g., `.5 + .25`)

### Examples of Valid Expressions

**Input:**

((1.5+2.5)*(3.2-1.2))/(0.5*4)

**Output:**

4.000000


**Input:**

100-20*3+40/2-5

**Output:**

55.000000

## How It Works

Unlike v1.0—which read the entire string into memory and performed multiple passes to simplify signs, strip whitespace, and compress arrays—v2.0 evaluates expressions on the fly in a single pass:

- **Character Stream Reading:** Reads characters directly from standard input (getchar()) until a newline (\n) or EOF is reached.
- **Dynamic Number Construction:** Accumulates digits and tracks decimal point positions to build double operands on the fly (createNumber, createInteger, createFloat).
- **Two-Stack Evaluation (Shunting-Yard):**
  - **Operands Stack (operands[]):** Stores numerical values ready to be operated on.
  - **Operators Stack (operators[]):** Holds pending operators and open parentheses (.
- **Precedence & Associativity Resolution:** Before pushing a new operator, the program checks the top of the operator stack. If the existing operator has higher precedence (or equal precedence with left-associativity), it pops the operator and the top two operands, computes the intermediate result via operate(), and pushes the result back onto the operand stack.
- **Parentheses Handling:** Open parentheses ( are pushed as markers; closing parentheses ) trigger stack evaluation until the matching ( is popped.

## Compilation

Compile the program using gcc:

gcc v2_shunting_yard.c -o calculator

## Execution

Run the program from the terminal:

./calculator

## Current Limitations

- **Unary operators / negative numbers:** Expressions starting with a negative sign (e.g., -5+8) or negative numbers inside parentheses (e.g., 4*(-2)) are not supported yet in v2.0.
- **Exponentiation (^):** Precedence and right-associativity rules for ^ are defined in the parser, but the mathematical operation itself is still pending implementation.
- **Fixed buffer sizes:** Stack sizes and maximum digit lengths are currently statically allocated.

## Future Improvements

Planned improvements for upcoming iterations include:
- Implementing unary + and - support within the Shunting-Yard flow
- Completing the exponentiation (^) operation
- Adding robust syntax and input validation (mismatched parentheses, invalid characters)

## Project Status

This project is an active work in progress (v2.0) and will continue evolving as I refine the parser, handle edge cases, and deepen my understanding.
