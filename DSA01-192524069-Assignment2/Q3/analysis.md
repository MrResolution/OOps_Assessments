# Q3: Default Arguments and Function Overloading

## 1. Ambiguity Diagnosis
- The compiler rejected `charge(double weight)` vs `charge(double weight, bool = false, bool = false)` because a single argument call `charge(5.0)` could match either candidate with equal viability.
- In C++, overloading functions that differ only by arguments having default values creates an ambiguous overload set whenever calls omit those default arguments.

## 2. Redesign Strategy & Overload Resolution
- Consolidated optional boolean flags into a single canonical signature with trailing default arguments:
  `long long charge(double weightKg, bool express = false, bool insured = false)`
- Overloaded strictly by distinct parameter types:
  1. `int weightGrams`: Exact match for integer literals (`charge(2)`).
  2. `double weightKg`: Exact match for `double` and promotion target for `float` (`charge(2.0f)`).
  3. `const Parcel&`: Custom entity structure.
- **Rule**: Default arguments must strictly be specified from right to left because arguments are matched positionally from left to right.

## 3. Alternative Architecture & Complexity Analysis
- Overload resolution is performed entirely at compile time via static name mangling with zero runtime performance cost ($O(1)$ time, $0$ runtime bytes).
- Passing a `Parcel` structure aggregates all options cleanly, allowing forward-compatible additions without modifying function signatures.
