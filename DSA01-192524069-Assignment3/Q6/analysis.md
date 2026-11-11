# Q6: Rules of Operator Overloading

## 1. Fundamental Rules of Operator Overloading
1. **Precedence and Arity are Fixed**: Overloading cannot change operator precedence, associativity, or operand arity (e.g., binary `+` cannot become ternary).
2. **User-Defined Type Requirement**: At least one operand must be a user-defined class, struct, or enumeration type. Overloading operators exclusively for primitive types (e.g., `int + int`) is forbidden.
3. **No New Operators**: Programmers cannot invent syntax (e.g., `**` or `<?>`).
4. **Member-Only Operators**: `operator=`, `operator[]`, `operator()`, and `operator->` must strictly be non-static member functions.

## 2. Operators That Cannot Be Overloaded
- **Scope Resolution (`::`)**: Resolves names at compile time; runtime evaluation would break the type system.
- **Member Access (`.`)**: Member selection via direct reference is fundamental to language dispatch.
- **Pointer-to-Member (`.*`)**: Mirrors `.` semantics.
- **Conditional Ternary (`?:`)**: Relies on short-circuit evaluation of operands. Overloading would require evaluating all arguments prior to call dispatch.
- **`sizeof`**: Compile-time constant operator querying object storage requirements.

## 3. Concatenation Complexity ($a + b + c$)
- In evaluating `a + b + c`:
  - `(a + b)` allocates a buffer of size $n_1 + n_2 + 1$ and copies $n_1 + n_2$ characters.
  - Adding `+ c` allocates a new buffer of size $n_1 + n_2 + n_3 + 1$ and copies all characters again.
  - Total characters copied: $2(n_1 + n_2) + n_3$.
  - Using compound concatenation `+=` reduces temporary allocations and avoids duplicate copying.
