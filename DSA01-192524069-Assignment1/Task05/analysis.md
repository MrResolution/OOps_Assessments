# Task 5: Operator Precedence and Expressions

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```

### Actual Output:
```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```

## 2. Operator Precedence and Associativity Analysis
1. **`x + y * 2`**: Multiplication (`*`) has higher precedence than addition (`+`), evaluating as `5 + (3 * 2) = 11`. `(x + y) * 2` forces addition first, producing `16`.
2. **`x++ + ++y`**: Postfix `x++` evaluates to `5` before incrementing `x` to `6`. Prefix `++y` increments `y` to `4` before evaluation. Their sum `5 + 4 = 9`.
3. **`x > y ? x : y` and `x % 4 * 2`**: Relational `>` precedes conditional `?:`. Modulus `%` and multiplication `*` share left-to-right associativity: `(6 % 4) * 2 = 4`.
4. **Division and Remainder with Negatives**: Integer division truncates towards zero (C++11). `-10 / 3 = -3`, and `-10 % 3 = -1` satisfying $(a / b) \times b + (a \% b) = a$.
5. **Loop Summation**: Increments in steps of 3 (`i = 0, 3, 6, 9`), summing to `18`.

## 3. Alternative Peak Logic & Complexity
- **Boolean Expression**: Evaluates short-circuit logical operators ($O(1)$ time, $0$ bytes static memory).
- **Lookup Table (`bool PEAK_TABLE[24]`)**: Array indexing requires single memory lookup ($O(1)$ time, 24 bytes memory).
