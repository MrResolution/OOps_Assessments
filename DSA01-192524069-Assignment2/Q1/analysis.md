# Q1: Parameter Passing Mechanisms

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
1 12 13
1 100
16 13 6 
```

### Actual Output:
```text
1 12 13
1 100
16 13 6 
```

## 2. Parameter Passing Analysis
- **Call by Value (`int a`)**: Creates a separate copy on the function activation record. Changes modify only the local copy and do not affect caller variable `a`.
- **Call by Reference (`int& b`)**: Binds an lvalue alias to caller variable `b`. Mutations directly alter caller memory.
- **Call by Pointer (`int* c`)**: Passes the memory address of `c`. Dereferencing `*c` mutates the memory location of caller variable `c`.
- **Return by Reference (`bigger(a, c) = 100`)**: Since `c (13) > a (1)`, `bigger` returns an lvalue reference to `c`, allowing assignment directly to `c`.
- **Default Arguments**: `show(1)` uses defaults for `y` (5) and `z` (10); `show(1, 2)` uses default for `z` (10); `show(1, 2, 3)` overrides all defaults.

## 3. Alternative Architecture & Complexity Analysis
- Modifying fee in place via `long long&` vs returning a new fee `long long apply(long long)`:
  - Both take $O(1)$ time and $O(1)$ stack space for primitive types.
  - For large objects (e.g. `Student`), call by value copies the entire object ($O(M)$ space and time), whereas passing by `const Student&` copies only an 8-byte reference address ($O(1)$ space and time).
