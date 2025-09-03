### Implment a compiler with four arithmetic operations

1. Set up a shell script to compile and test.
2. Create a hello world file.
3. Read argument from `argv`.
4. Parse argument into multiple tokens.

### SSA

Static Single Assignment (SSA) is a form of an IR where each variable is assigned a value only once.

- Each variable has only one definition.
- Use-Definition chains are good for analysis.
- Phi Functions merge multiple control flow paths and choose the correct source path.

### Polyhedral Compilation

Polyhedral compilation is a mathematical framework for optimizing programs with **nested loops and array access**.

The core idea is to represent nested loop as a geometric shape called a **polyhedron**. Instead of analyzing dependencies between individual statements, polyhedral compilation analyzes depedencies between these iteration points (polyhedrons).