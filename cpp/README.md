### RAII

Resource Acquisition is Initialization (RAII) is a C++ idiom where acquisition of a resource is tied to the initialization of an object.
**The lifetime of a resource is managed by the object's lifetime.**

### Smart Pointers

Smart Pointers are a direct application of RAII. They are used for managing dynamically allocated memory. Smart Pointers wrap raw pointers and ensure the memory is automatically deallocated when the smart pointer object is destroyed.

- `std::unique_ptr` has exclusive ownership. It cannot be copied, only moved. Only one `std::unique_ptr` can own a raw pointer at a time.
- `std::shared_ptr` has a shared ownership. Multiple `std::shared_ptr` can own the same raw pointer. The resource is deallocated when the last reference is destroyed.
- `std::weak_ptr` is a **non-owning** smart pointer that works with `std::shared_ptr`. There can be a memory leak if there's a circular references with `std::shared_ptr`. [Example](https://godbolt.org/z/q1TfdzxP7).

#### `std::make_unique`

Introduced in C++14, `std::make_unique` is the recommended way to create instances of `std::unique_ptr`.

```cpp
// Instead of this:
std::unique_ptr<MyClass> ptr(new MyClass(arg1, arg2));

// Prefer this:
auto ptr = std::make_unique<MyClass>(arg1, arg2);
```

`std::make_unique` solves a subtle exception-safety problem. Consider a function call like this:

```cpp
foo(std::unique_ptr<T>(new T), function_that_might_throw());
```

The compiler is allowed to evaluate arguments in any order. It might first evaluate `new T`, then `function_that_might_throw()`, and only then call the `std::unique_ptr` constructor. If `function_that_might_throw()` throws an exception, the memory allocated for `T` is leaked because no smart pointer has taken ownership of it yet.

`std::make_unique` prevents this by ensuring that memory allocation and `std::unique_ptr` construction happen together in a single function call, which cannot be interleaved with other argument evaluations. This guarantees that the resource is properly managed even in the presence of exceptions.

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

### Lambda Expressions

A lambda expression is an unnamed function object capable of capturing variables in scope. It's a concise way to create simple function objects that can be passed as arguments to algorithms or other functions.

**When to use Lambda Expressions:**

Lambdas are particularly useful when you need a short, simple function for a limited scope, and you don't want to define a full, named function elsewhere. They are commonly used with Standard Library algorithms like `std::sort`, `std::for_each`, and `std::find_if`.

**Lambdas vs. Functions:**

| Feature | Lambda | Function |
| :--- | :--- | :--- |
| **Definition** | Can be defined inline, right where it's needed. | Must be defined in a specific scope (e.g., global, namespace, or class). |
| **State** | Can capture and store state from the surrounding scope (closure). | Cannot capture local state from the calling scope. |
| **Verbosity**| Less verbose, more concise for simple operations. | More verbose, requires a full function definition. |

Lambdas can be more easily inlined by the compilers.

In C++14, Generic Lambdas allow developers to use `auto` in the parameter lists.

### Structured Bindings

Introduced in C++17, structured bindings allow for a more convenient and readable way to unpack and assign values from tuples, pairs, or structs. It simplifies the process of creating multiple variables from a single compound object.

Here's an [example](https://godbolt.org/z/xsvfjcz8E) using a `std::tuple`.

This feature makes the code cleaner and less error-prone, as you don't need to use `std::get` with indices, which can be a source of bugs.

### if constexpr

Introduced in C++17, `if constexpr` allows for compile-time conditional branching based on constant expressions. This is particularly useful in template metaprogramming.

#### `if constexpr` vs. `if`

The key difference is when the condition is evaluated:

- **`if`**: The condition is evaluated at **run-time**. Both branches of the `if-else` statement must be valid and compilable, even if one branch is never executed.
- **`if constexpr`**: The condition is evaluated at **compile-time**. The compiler will discard the branch that is not taken. This means the code in the discarded branch doesn't need to be valid for the given template parameters.

#### `if constexpr` in a Template Function

Here is an [example](https://godbolt.org/z/b67zPsKqv) of using `if constexpr` inside a template function.

Without `if constexpr`, a similar template function would fail to compile because, for example, you can't stream a `std::vector` to `std::cout` with `<<` by default, and all branches of a regular `if` must be valid. `if constexpr` avoids this by discarding the invalid branches at compile-time.

### std::optional

Introduced in C++17, `std::optional` is a wrapper that may or may not contain a value. It is a vocabulary type for representing an optional value, which is useful for functions that might fail to return a value.

Before `std::optional`, developers often used special values (like `nullptr` or `-1`) or a pair of a boolean and a value to indicate the absence of a value. `std::optional` provides a cleaner, more expressive, and safer way to handle such cases.

Here's an [example](https://godbolt.org/z/PYrhTdc6o).

Using `std::optional` helps to avoid ambiguity and makes the code's intent clearer.

### Access Specifiers

In C++, access specifiers are keywords that define the accessibility of class members (both attributes and methods). They are fundamental to the concept of **encapsulation**. Encapsulation is the bundling of data with the methods that operate on that data, which is used to restrict direct access to some of an object's components.

- `public`: Members are accessible from any part of the program. This is the least restrictive access level.
- `private`: Members are only accessible from within the class itself. This is the most restrictive access level. By default, members of a class are private.
- `protected`: Members are accessible from within the class and by derived (child) classes. They are not accessible by unrelated code.