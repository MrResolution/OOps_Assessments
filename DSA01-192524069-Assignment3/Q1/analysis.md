# Q1: Constructors and Constructor Overloading

## 1. Member Initializer Lists vs Body Assignment
- Member initializer lists construct data members in-place directly as memory is allocated for the instance.
- Assignment inside the constructor body forces default construction first, followed immediately by copy-assignment, introducing redundant operations for non-primitive types (`std::string`).

## 2. Declaration Order vs Initializer List Order (`-Wreorder`)
- In C++, class members are initialized strictly in the order they are **declared in the class definition**, completely ignoring the order written in the constructor initializer list.
- If member `b` is initialized before member `a` in the list, but declared after `a`, `a` will attempt to read uninitialized memory from `b`, triggering `-Wreorder` and `-Wuninitialized`.

## 3. Constructor Delegation & `explicit` Keyword
- **Delegation**: `Book()` and `Book(const std::string&)` delegate to the master 3-argument constructor, ensuring validation (`copies < 0 ? 0 : copies`) is enforced in exactly one centralized location.
- **`explicit`**: Prevents single-argument constructors from participating in implicit user-defined conversions (e.g., passing a raw string literal to a function expecting a `Book` object).

## 4. Alternative Concept & Complexity
- Default arguments in a single constructor (`Book(string="", string="", int=0)`) reduce constructor count, but can create ambiguity in overload resolution and permit partial invalid configurations.
- Object creation time and memory footprint are both $O(1)$.
