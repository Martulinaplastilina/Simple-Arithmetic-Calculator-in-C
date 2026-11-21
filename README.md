# Arithmetic Expression Evaluator in C

A personal project exploring expression parsing and evaluation from scratch in C, without external parsing libraries.

This repository documents the architectural evolution of the project—from an initial ad-hoc implementation to a formal algorithm-based evaluator—with the long-term goal of evolving into a tree-based symbolic calculator.

## Repository Structure

| Version | Directory | Parsing Strategy | Memory Model | Key Capabilities |
| :--- | :--- | :--- | :--- | :--- |
| **v1.0** | [`v1/`](./v1/) | Multi-pass array compression ($\mathcal{O}(n^2)$) | Static arrays | Basic arithmetic (`+`, `-`, `*`, `/`), floats, consecutive sign reduction |
| **v2.2** | [`v2/`](./v2/) | Single-pass **Shunting-Yard** with two stacks ($\mathcal{O}(n)$) | Dynamic allocation (`malloc`/`realloc`/`free`) | Precedence & associativity, parentheses, unary `+`/`-`, modular architecture |

## Roadmap

- [x] **v1.0:** From-scratch multi-pass evaluator using flat parallel arrays
- [x] **v2.x:** Single-pass Shunting-Yard evaluator with dynamic memory and unary operators *(active development)*
- [ ] **v3.0 (Planned):** Abstract Syntax Tree (AST) representation and symbolic manipulation

## Quick Start

Each version is self-contained and includes its own source code and documentation. See [`v1/README.md`](./v1/README.md) or [`v2/README.md`](./v2/README.md) for compilation and usage instructions.
