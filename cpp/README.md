### RAII

Resource Acquisition is Initialization (RAII) is a C++ idiom where acquisition of a resource is tied to the initialization of an object.
**The lifetime of a resource is managed by the object's lifetime.**

### Smart Pointers

Smart Pointers are a direct application of RAII. They are used for managing dynamically allocated memory. Smart Pointers wrap raw pointers and ensure the memory is automatically deallocated when the smart pointer object is destroyed.

- `std::unique_ptr` has exclusive ownership. It cannot be copied, only moved. Only one `std::unique_ptr` can own a raw pointer at a time.
- `std::shared_ptr` has a shared ownership. Multiple `std::shared_ptr` can own the same raw pointer. The resource is deallocated when the last reference is destroyed.
- `std::weak_ptr` is a **non-owning** smart pointer that works with `std::shared_ptr`. There can be a memory leak if there's a circular references with `std::shared_ptr`. [Example](https://godbolt.org/z/q1TfdzxP7).

### Move Semantics

The purpose of Move Semantics is to **avoid expensive, unnecessary data copies**.

- Copy vs. Move
- Copy Constructor/Assignment Operator: these operations performs **deep copy**, which creates a completely new, independent object and copies the data from the object.
- Move Constructor/Assignment Operator: these operations takes an rvalue as a source and hand over the resources from the source object. The source object is left in a valid but unspecified state, often empty or NULL.

`std::move` does not change ownership or move anything, instead, it is a **static cast**. It coverts an lvalue into an rvalue reference. `std::move` is a zero-cost abstraction.

### Const and Constexpr

- `const` guarantees a variable is read-only after initialization, either at compile-time or run-time. Compiler might not know the value of a constant until the program is running.
- `constexpr` guarantees a variable's value must be computable at compile-time. Compiler knows the exact value of constexpr.

In the [Example](https://godbolt.org/z/6jM1q68Tv), the value of `result` is hard-coded in the instruction.

### Atomic

`std::atomic` provides a type-safe way to use these operations. Atomic operations or variables are guaranteed to be completed without being interrupted by another thread.
