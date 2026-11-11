# Q6: Friend Functions and Inline Functions

## 1. Friend Function Design Rationale
- **Symmetric Invocation**: Functions like `minutesBetween(a, b)` and `earlier(a, b)` treat both operand arguments with identical priority. Making one a member (`a.earlier(b)`) introduces artificial asymmetry where `a` is privileged as `*this`.
- **Encapsulation Preservation**: Friend functions can access `private` data (`h`, `m`) without making those members public to the entire codebase.

## 2. Inlining and Compiler Optimization (`-O0` vs `-O2`)
| Configuration | Compiler Level | Measured Runtime (10M calls) |
| :--- | :--- | :--- |
| **Non-Inline** | `-O0` (No optimization) | ~31.02 ms |
| **Inline** | `-O0` (No optimization) | ~31.13 ms |
| **Non-Inline** | `-O2` (Optimized) | < 0.001 ms |
| **Inline** | `-O2` (Optimized) | < 0.001 ms |

- At `-O0`, the compiler strictly obeys the disablement of optimizations, generating standard stack frame calls.
- At `-O2`, modern compilers perform inter-procedural optimization (IPO) and aggressive inlining automatically, whether the `inline` keyword is present or not.
- Marking small getters/comparators `inline` serves as a hint to avoid call overhead across separate compilation units.

## 3. Complexity Analysis
- **Time Complexity**: $O(1)$ per comparison in all versions.
- **Space Complexity**: $O(1)$ stack space.
