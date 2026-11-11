# Task 4: Control Implicit Conversions

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
3 3.5
C 68
1 true
s >= u
```

### Actual Output:
```text
3 3.5
C 68
1 true
s >= u
```

## 2. Line-by-Line Conversion Analysis
1. **`a / b` vs `static_cast<double>(a) / b`**:
   - `a / b` performs integer division (`7 / 2 = 3`), discarding the remainder before assigning to `double c`.
   - `static_cast<double>(a)` converts `a` to `7.0`, causing `b` to be promoted to `double`, yielding `3.5`.
2. **`'A' + 2` and `ch + 1`**:
   - `'A' + 2` evaluates to integer `67`, implicitly converted to `char` `'C'`.
   - In `ch + 1`, character `ch` undergoes integral promotion to `int` before addition, printing `68`.
3. **`bool flag = 5;`**:
   - Any non-zero integral value implicitly converts to `true` (`1`). `std::boolalpha` prints the literal `"true"`.
4. **`s < u` (Signed vs Unsigned)**:
   - When comparing signed `int` (`-1`) with `unsigned int` (`1`), C++ promotes the signed integer to `unsigned int`.
   - Under two's complement, `-1` becomes `4,294,967,295`. Because `4294967295 < 1` is false, it prints `"s >= u"`.
   - The compiler emits `-Wsign-compare`.

## 3. Safe Alternative & Complexity
- Replacing implicit conversions with `static_cast` and uniform brace initialization (`{}`) detects narrowing at compile time.
- Compile-time checking incurs zero runtime overhead ($O(1)$ time, $O(1)$ space).
