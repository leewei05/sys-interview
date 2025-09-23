### What is MLIR?

It is a framework for building compilers. More specifically, MLIR is an infrastructure that that bridges high-level languages(domain specific IR) to low-lever languages (LLVM). MLIR uses the word "dialect" to represent its domain specific IRs.

- **Multi-level**: allow compilers to have multiple IRs at a different level of abstraction. A high-level dialect might represent an entire neural network, while a lower-level one might represent GPU kernels or SIMD instructions.
- **Dialect**:  A dialect is a collection of operations and types that represent a domain-specific abstraction. For example, the `mhlo` dialect represents machine learning operations, the `gpu` dialect represents GPU code, and the `vector` dialect represents SIMD operations.
- **Progressive Lowering**: This is the process of translating a high-level program to a lower-level one by transforming operations from one dialect to another.
- **High-level Analysis and Transformation**: MLIR allows users to implement pattern-matching transformations. These transformations can be implemented with C++ patter-match and rewrite (Imperative) or Table-driven Declarative Rewrite Rules (DRR), which requires operations be defined using ODS.

### What problem does MLIR solve?

The key problem MLIR solves is the limitations of a single-level IR like LLVM IR for complex domains like machine learning and hardware accelerators. While LLVM IR is great for low-level, CPU-centric optimizations, it's a poor fit for representing high-level concepts like tensors, matrix multiplications, and hardware-specific memory layouts. **MLIR was designed to handle these domain-specific abstractions.**

### Operation Definition Specification

Operation Definition Specification (ODS) is a framework for defining `ops` in a table-driven way, which offers several advantages:

- **Simplified Op Definition**: Instead of manually defining operations using the `mlir::Op` C++ template, ODS allows for a more concise, table-driven approach.
- **Automatic Verification**: The ODS framework automatically generates verification logic based on the constraints provided, ensuring that operations are well-formed.
- **Builder Generation**: ODS can generate simple build methods for operations, and also allows for the definition of custom builders to suit specific needs.

### Dialect Conversions

MLIR's Dialect Conversion framework is used to transform operations from one dialect to another. To perform a conversion, you need to define a `ConversionTarget` which specifies which operations are considered legal. Then, you provide a set of `RewritePattern`s to convert any illegal operations into legal ones.

A common use case is **partial lowering**, where only a subset of operations are lowered to a different dialect. For example, you might lower compute-intensive operations to the Affine and Arith dialects for optimization, while keeping other operations like a print function in the original dialect.

Note that lowering from a value-type to a buffer-type representation is a common pattern in MLIR.

### Commonly Used Dialects

- linalg
- tensor
- memref
- arith
- math
- vector
- scf
- cf
- llvm
- spv