# E++ Expression Evaluator Project

This assignment involves creating an expression evaluator for E++ programs. Key components include the implementation of `UnlimitedInt` and `UnlimitedRational` classes, a parser for E++ statements, and an expression evaluator. Additionally, a Symbol Table using an unbalanced Binary Search Tree (BST) is implemented for efficient variable resolution.

## UnlimitedInt Class (Part 1)

Handles integers of arbitrary size with functions for size, sign, and basic arithmetic operations.

## UnlimitedRational Class (Part 2)

Manages rational numbers using the `UnlimitedInt` class for numerator and denominator with arithmetic operations.

## Parser for E++ (Part 3)

Converts each statement into a parse tree structure following specific conditions.

## Expression Evaluator (Part 4)

Evaluates well-formed expressions in the parse tree using explicit value association and recursive subtree evaluation.

## Symbol Table (Part 5)

Implements a Symbol Table using a BST for efficient variable resolution during parsing and expression evaluation.

## Compiler for E++ (Part 6)

A compiler is a program that translates an input program in a source language S to an equivalent program in a target language Targ. I have created a compiler for the language of expressions E++. The compiler will generate code for the expressions, which can run on a stack machine.

### Parser Modifications (Part 6.1)

1. **Delete Statement**
   - Syntax: `del := variable name`
   - Tokenized Form: `["del", ":=", "variable name"]`
   - Expression tree modification: A simple tree with three nodes, where the root is `:=`, left node is of type `DEL`, and the right node is of type `VAR`.

2. **Return Statement**
   - Syntax: `ret := E++ expression`
   - Tokenized Form: `["ret", ":=", "(", "a", "x", "(", "b", "+", "c", ")", ")"]`
   - Expression tree modification: The `ret` node in the expression tree will have the type `RET`.

### Parser Class (parser.h) Modifications (Part 6.2)

1. **Parameters**
   - `vector<ExprTreeNode*> expr_trees`: Stores roots of parsed expressions.
   - `SymbolTable* symtable`: Modified symbol table.

2. **Functions to Implement (parser.cpp)**
   - `parse(vector<string> expression)`: Reads a tokenized expression, parses it, converts it to a parse tree, and pushes the root into `expr_trees`. Modifies the symbol table based on the expression (inserts for variable assignment, deletes for delete statement, and does nothing for return statement).

### Improving the Expression Evaluator (Part 7)

In this part, I have converted the BSTs from Assignment 4 into AVL Trees, enhancing efficiency for code compilation. The AVL Tree Node class is introduced with parameters such as key, height, address, parent, left, and right. Optional functions for AVL rotations are provided.

### Code Generator (Part 8)

1. **Stack Machine**
   - The code generated in Targ language assumes a stack machine architecture with operations on a stack and memory.

2. **Targ Syntax**
   - A set of Targ commands includes PUSH, POP, DEL, ADD, SUB, MUL, DIV, and RET.

3. **Generating Code**
   - Recursively iterate over the parse tree to generate Targ code. Each command is associated with specific operations.

4. **Handling Memory Allocation**
   - Variables are assigned memory indexes during compilation, managed using a vector for available memory locations.

### EPPCompiler Class (eppcompiler.h) (Part 9)

1. **Parameters**
   - `Parser targ`: Stores the symbol table and parsed expression tree nodes.
   - `int memory_size`: Size of the indexable memory.
   - `string output_file`: Output file for generated Targ code.
   - `vector<int> mem_loc`: Vector to maintain available memory locations.
   - `MinHeap least_mem_loc`: Min-heap to maintain least available memory indexes (optional).

2. **Functions to Implement (eppcompiler.cpp)**
   - `compile(vector<vector<string>> code)`: Parses tokenized expressions, assigns memory mappings for variable assignments or frees up memory addresses for delete statements, and compiles the code by generating Targ commands.
   - `generate_targ_commands()`: Compiles the last tree node in the Parser, generates Targ commands, and returns them.
   - `write_to_file(vector<string> commands)`: Helper function to write a set of commands to the output file.

