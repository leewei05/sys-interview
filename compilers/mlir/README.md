### What is MLIR?

It is a framework for building compilers. More specifically, MLIR is an infrastructure that that bridges high-level languages(domain specific IR) to low-lever languages (LLVM). MLIR uses the word "dialect" to represent its domain specific IRs.

- Multi-level: allow compilers to have multiple IRs at a different level of abstraction. A high-level dialect might represent an entire neural network, while a lower-level one might represent GPU kernels or SIMD instructions.
- Dialect:  A dialect is a collection of operations and types that represent a domain-specific abstraction. For example, the `mhlo` dialect represents machine learning operations, the `gpu` dialect represents GPU code, and the `vector` dialect represents SIMD operations.
- Progressive Lowering: This is the process of translating a high-level program to a lower-level one by transforming operations from one dialect to another.
