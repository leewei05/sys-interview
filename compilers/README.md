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