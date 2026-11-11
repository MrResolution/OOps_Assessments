# Q5: Overloading Increment, Comparison, and Subscript Operators

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
5 7 7
```

### Actual Output:
```text
5 7 7
```

## 2. Prefix vs Postfix Increment Mechanics
- **Prefix (`operator++()`)**: Directly mutates instance members and returns an lvalue reference to `*this` (`TrackTimer&`).
- **Postfix (`operator++(int)`)**: Takes an unused dummy `int` parameter to distinguish its signature for the compiler. It must copy the pre-increment state to a local temporary (`TrackTimer old = *this`), increment the current object, and return `old` by value.

## 3. Measured Benchmark Comparison (10,000,000 Iterations)
| Optimization Level | Prefix (`++c`) | Postfix (`c++`) | Observation |
| :--- | :--- | :--- | :--- |
| **`-O0`** | **$9.19$ ms** | **$20.91$ ms** | **Postfix is $> 2.2\times$ slower** due to temporary copy creation. |
| **`-O2`** | $< 0.001$ ms | $< 0.001$ ms | Compiler optimizes away dead copies. |

- This empirical evidence justifies why idiomatic C++ favors `++i` over `i++` for class types.

## 4. Subscript Operator (`operator[]`) Dual Overloading
- **Non-const `std::string& operator[](int)`**: Enables mutating the element (`pl[0] = "New Title"`).
- **Const `const std::string& operator[](int) const`**: Guarantees read-only access for `const Playlist` references without mutating state.
- **Range Safety**: Out-of-bounds indices throw `std::out_of_range`, preventing segmentation faults and buffer overruns.
