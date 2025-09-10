## Core Concepts

### RAII

Resource Acquisition is Initialization (RAII) is a C++ idiom where acquisition of a resource is tied to the initialization of an object.
**The lifetime of a resource is managed by the object's lifetime.**

### Access Specifiers

In C++, access specifiers are keywords that define the accessibility of class members (both attributes and methods). They are fundamental to the concept of **encapsulation**. Encapsulation is the bundling of data with the methods that operate on that data, which is used to restrict direct access to some of an object's components.

- `public`: Members are accessible from any part of the program. This is the least restrictive access level.
- `private`: Members are only accessible from within the class itself. This is the most restrictive access level. By default, members of a class are private.
- `protected`: Members are accessible from within the class and by derived (child) classes. They are not accessible by unrelated code.

### Virtual Function and Vtable

A **virtual function** is a member function that you expect to be redefined in derived classes. When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for that object and execute the derived class's version of the function. This is the essence of **polymorphism**.

There are two types of virtual functions:

- **Normal Virtual Function**: A virtual function that has an implementation in the base class.
- **Pure Virtual Function**: A virtual function that has no implementation in the base class and must be overridden in the derived class. A class with one or more pure virtual functions is called an **abstract class**.

#### Vtable

A **vtable** (virtual table) is a lookup table of function pointers used to resolve virtual function calls at runtime. Each class that has virtual functions has its own vtable. When an object of such a class is created, a hidden pointer to the vtable (often called a **vptr**) is added to the object. When a virtual function is called through a base class pointer, the vptr is used to find the correct function in the vtable of the derived class. This process is called **dynamic dispatch**.

### volatile

The `volatile` keyword tells the compiler that a variable's value may change at any time without any action being taken by the code the compiler finds nearby. It is a directive to the compiler to suppress optimization on that variable.

**Use Cases:**

- **Memory-mapped I/O**: When a memory address is mapped to a device register, the value can be changed by the hardware.
- **Variables modified by an interrupt service routine**: If a global variable is modified by an ISR, it should be declared `volatile`.

### Iterators

An **iterator** is an object that acts like a generic pointer, providing a way to access elements in a container (like a `std::vector` or `std::list`) sequentially without exposing the container's underlying representation. Iterators are a key component of the C++ Standard Library, enabling generic algorithms to work with any container that provides an iterator interface.

[Simple iterator example](https://godbolt.org/z/cnKKThx4b)

#### Iterator Categories

C++ iterators are categorized based on their functionality. Each category builds upon the previous one, adding more capabilities.

- **Input Iterator**: The simplest category. Can be used to read elements from a container in a single pass. It can be incremented, but not decremented.
- **Output Iterator**: Can be used to write elements to a container in a single pass. It can be incremented, but not decremented.
- **Forward Iterator**: Combines the functionality of input and output iterators for single-pass algorithms. It can be incremented, but not decremented. It can be used to read from and write to the same element multiple times.
- **Bidirectional Iterator**: Like a forward iterator, but can also be decremented. This allows for traversing the container in both directions. `std::list`, `std::set`, and `std::map` provide bidirectional iterators.
- **Random Access Iterator**: The most powerful category. Provides all the features of a bidirectional iterator, plus the ability to access elements by an index in constant time (like a pointer). `std::vector` and `std::deque` provide random access iterators.

[Iterator Categories Example](https://godbolt.org/z/9bKMKMPrM)

### Templates

Templates are a fundamental feature of C++ that allow you to write generic programs. They are blueprints that the compiler uses to generate code for different types at compile time.

#### Function Templates

A function template is a blueprint for creating a family of functions. For example, you can write a single `max` function that works with any type that supports the `>` operator.

#### Class Templates

A class template is a blueprint for creating a family of classes. For example, you can create a generic `Stack` class that can hold elements of any type.

[Template Example](https://godbolt.org/z/5x33M6z8n)

### The Rule of Three/Five/Zero

These are rules of thumb in C++ for managing resources.

- **The Rule of Three**: If a class defines any of the following, it should probably explicitly define all three:
    1.  Destructor
    2.  Copy constructor
    3.  Copy assignment operator

- **The Rule of Five**: With the introduction of move semantics in C++11, the Rule of Three is extended to the Rule of Five. If a class defines any of the five special member functions, it should probably define all of them:
    1.  Destructor
    2.  Copy constructor
    3.  Copy assignment operator
    4.  Move constructor
    5.  Move assignment operator

- **The Rule of Zero**: The best practice is to not define any of the special member functions. Instead, use smart pointers and other RAII objects to manage resources, and let the compiler generate the special member functions. This leads to cleaner and safer code.

## C++11

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

> A **const member function** is a member function that promises not to modify the object's member data. It is declared by placing the `const` keyword after the function's parameter list. A key rule is that you can only call const member functions on a const object.

### Atomic

`std::atomic` provides a type-safe way to use these operations. Atomic operations or variables are guaranteed to be completed without being interrupted by another thread.

### Lambda Expressions

A lambda expression is an unnamed function object capable of capturing variables in scope. It's a concise way to create simple function objects that can be passed as arguments to algorithms or other functions.

**When to use Lambda Expressions:**

Lambdas are particularly useful when you need a short, simple function for a limited scope, and you don't want to define a full, named function elsewhere. They are commonly used with Standard Library algorithms like `std::sort`, `std::for_each`, and `std::find_if`.

**Anatomy of a Lambda Expression:**

```cpp
[capture_clause](parameters) -> return_type {
    // function body
};
```

- **`capture_clause`**: Specifies which variables from the surrounding scope are available inside the lambda, and how they are captured (by value or by reference).
- **`parameters`**: The parameter list for the lambda function.
- **`return_type`**: The return type of the lambda. This is optional; the compiler can often deduce it.
- **`function body`**: The code to be executed.

**Capture Clause in Detail:**

The capture clause is what makes lambdas powerful, allowing them to "remember" information from their enclosing scope.

- **`[]`**: No variables are captured from the surrounding scope.
- **`[=]`**: Capture all variables from the surrounding scope by **value**. The captured variables are read-only inside the lambda unless the lambda is declared `mutable`.
- **`[&]`**: Capture all variables from the surrounding scope by **reference**.
- **`[this]`**: Capture the `this` pointer by value, allowing access to member variables of the enclosing class.
- **`[a, &b]`**: Capture `a` by value and `b` by reference.
- **`[&, a]`**: Capture `a` by value and all other variables by reference.
- **`[=, &a]`**: Capture `a` by reference and all other variables by value.

**Lambdas vs. Functions:**

| Feature | Lambda | Function |
| :--- | :--- | :--- |
| **Definition** | Can be defined inline, right where it's needed. | Must be defined in a specific scope (e.g., global, namespace, or class). |
| **State** | Can capture and store state from the surrounding scope (closure). | Cannot capture local state from the calling scope. |
| **Verbosity**| Less verbose, more concise for simple operations. | More verbose, requires a full function definition. |

Lambdas can be more easily inlined by the compilers.

### Concurrency

C++11 introduced standard library support for concurrency.

- **`std::thread`**: A class to create and manage threads.
- **`std::mutex`**: A mutual exclusion primitive to protect shared data from being simultaneously accessed by multiple threads.
- **`std::lock_guard`**: A simple RAII-style wrapper for `std::mutex`. It locks the mutex in its constructor and unlocks it in its destructor.

[Mutex Example](https://godbolt.org/z/eWo6n6zPW)

### Range-based for loops

C++11 introduced a new syntax for iterating over a range of elements, making the code more readable and less error-prone.

[Compiler Explorer Link](https://godbolt.org/z/8G7ooGTxo)

### `auto` keyword

C++11 introduced the `auto` keyword to allow the compiler to automatically deduce the type of a variable from its initializer. This can make the code more readable and less verbose, especially when dealing with complex types like iterators or template-heavy code.

[Compiler Explorer Link](https://godbolt.org/z/P8fzeqTen)

### `nullptr`

C++11 introduced `nullptr` as a type-safe null pointer constant. It is of type `std::nullptr_t` and can be implicitly converted to any pointer type, but not to an integer type. This avoids the ambiguity of `NULL`, which is often just a macro for `0`.

[Compiler Explorer Link](https://godbolt.org/z/4e6xcq54G)

### Enum classes

C++11 introduced "enum classes" (also known as "scoped enumerations") to address some of the shortcomings of traditional C-style enums.

**Key advantages:**
- **Strongly typed**: Enum classes are not implicitly convertible to integers. This prevents accidental comparisons and assignments between different enum types.
- **Scoped**: The enumerators are scoped within the enum class, so you don't have to worry about name clashes.

[Compiler Explorer Link](https://godbolt.org/z/csaEaW334)

### Initializer lists

C++11 introduced `std::initializer_list` to provide a uniform syntax for initialization. It allows you to initialize objects with a list of values enclosed in curly braces `{}`.

[Compiler Explorer Link](https://godbolt.org/z/YYoGvjfPb)

### `std::function`

`std::function` is a general-purpose polymorphic function wrapper. It can store, copy, and invoke any callable target—functions, lambda expressions, bind expressions, or other function objects.

**When to use `std::function`:**
- **Callbacks**: When you want to allow users to provide their own functions to be called when a certain event happens.
- **Storing callables in a container**: For example, you can have a `std::vector<std::function<void()>>` that stores various functions to be executed later.
- **Decoupling code**: It helps in writing code that doesn't need to know the exact type of the callable it's using, making your code more flexible.

[Compiler Explorer Link](https://godbolt.org/z/619fzs61c)

#### `std::function` vs. Function Pointers

While both `std::function` and C-style function pointers can store and invoke callable entities, `std::function` offers significant advantages:

-   **Type Safety**: `std::function` is type-safe, enforcing signature matching at compile time. C-style function pointers can be implicitly converted, leading to potential runtime errors.
-   **Flexibility**: `std::function` can wrap any callable type (free functions, lambdas, function objects, member functions), whereas C-style function pointers are limited to free functions (or static member functions).
-   **Statefulness**: `std::function` can store stateful callables (e.g., lambdas with captures), which C-style function pointers cannot.
-   **Overhead**: `std::function` introduces some overhead due to type erasure and potential dynamic allocation, while function pointers are raw pointers with minimal overhead.


## C++14

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

In C++14, Generic Lambdas allow developers to use `auto` in the parameter lists.

### Binary Literals and Digit Separators

C++14 introduced binary literals and digit separators to make numeric literals more readable.

- **Binary Literals**: You can now specify integer literals in binary format using the `0b` or `0B` prefix.
- **Digit Separators**: You can use a single quote (`'`) as a digit separator to make long numbers more readable. The separator is ignored by the compiler.

## C++17

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

### std::variant

Introduced in C++17, `std::variant` is a type-safe union. It is a template class that can hold a value of any of the types specified in the template parameter list. At any given time, a `std::variant` holds a value of one of its alternative types (or no value if it is in a valueless state, which can happen in exceptional circumstances).

`std::variant` is a powerful tool for representing a value that can be one of a fixed set of types. It is a sum type, as opposed to a product type like a struct or a tuple.

Here's an [example](https://godbolt.org/z/eqrPnf9dj).