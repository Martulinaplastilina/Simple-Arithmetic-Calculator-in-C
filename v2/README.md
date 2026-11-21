# Arithmetic Expression Evaluator in C (v2.2 — Shunting-Yard)

A command-line arithmetic expression evaluator written in C, powered by a two-stack implementation of Edsger Dijkstra's **Shunting-Yard algorithm**.

- **v1.0** was written from scratch using a multi-pass array-compression approach over static arrays.
- **v2.x** is an architectural redesign into a single-pass, character-by-character stream evaluator using dynamically allocated stacks, modular operator dispatch, and formal precedence/associativity rules.

## Features

- **Basic binary operations:** Addition (`+`), Subtraction (`-`), Multiplication (`*`), and Division (`/`)
- **Unary operators:** Support for unary `+` and `-` via internal token disambiguation (`~` and `` ` ``) with right-associativity
- **Parentheses:** Support for grouped sub-expressions `(...)`
- **Operator precedence & associativity:** Formal precedence levels and left/right associativity handling
- **Floating-point numbers:** Double-precision (`double`) support, including leading-dot decimals (e.g., `.5 + .25`)
- **Dynamic memory allocation:** Heap-allocated buffers (`malloc`, `realloc`, `free`) for digits, operands, and operators
- **Unix-style I/O:** Outputs the raw numeric result to `stdout` (pipe-friendly) and routes warnings/errors to `stderr`

### Examples

**Input:**

100-20*3+40/2-5

**Output:**

55.000000

---

**Input:**

((4+1)*2)-5

**Output:**

5.000000

---

**Input:**

5+-2*3

**Output:**

-1.000000

---

**Input:**

-.5*-.5

**Output:**

0.250000

## How It Works

Unlike v1.0—which stored the full expression and ran multiple passes—v2.2 processes input on the fly in a single pass:
- **Character Stream Reading:** Reads input directly from stdin via getchar() until \n or EOF.
- **On-the-Fly Number Construction:** Collects digits and decimal point positions to build double values (createInteger, createFloat, createNumber).
- **Two-Stack Evaluation (Shunting-Yard):**
 - **Operands Stack (operands):** Dynamically allocated double buffer storing numeric values.
 - **Operators Stack (operators):** Dynamically allocated char buffer storing pending operators and parentheses.
- **Modular Operator Dispatch:** operate() checks operator arity via isBinary() and delegates execution to BinaryOperation() or UnaryOperation(), while isOperator() assists in distinguishing unary signs from binary operators.
- **Precedence & Associativity Resolution:** Before pushing a new operator, higher-precedence operators (or equal-precedence left-associative operators) are popped and evaluated immediately.

## Compilation

Compile using gcc (replace shunting.c with your actual filename if different):

gcc -Wall -Wextra shunting.c -o calculator

## Execution

Run interactively from the terminal or pipe an expression directly:

./calculator


echo "100-20*3+40/2-5" | ./calculator

## Current Limitations
- **Exponentiation (^):** Precedence and right-associativity rules are defined, but the mathematical operation is not yet implemented.
- **Input & syntax validation:** Comprehensive error handling for malformed expressions, invalid characters, and full edge-case coverage is still in progress.
- **Performance benchmarking:** <time.h> is included for upcoming performance comparisons against v1.0.

## Future Improvements
- Implementing exponentiation (^)
- Adding comprehensive syntax validation and clean error exit codes
- Benchmarking execution time against v1.0
- Expanding edge-case coverage across complex nested expressions

## Project Status

Active work in progress (**v2.2**). This implementation is part of an ongoing learning project in C and parsing algorithms.
