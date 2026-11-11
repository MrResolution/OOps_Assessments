# Task 7: From Procedural to Object-Oriented

## 1. Procedural vs. Object-Oriented Paradigm
- **Procedural Implementation**:
  - State (`balancePaise`) is decoupled from logic.
  - Any external function or routine can directly mutate the balance variable, leading to critical security and operational failures (such as setting negative balances).
- **Object-Oriented Implementation**:
  - `SmartCard` encapsulates `balancePaise` as a `private` member variable.
  - Access is restricted strictly through vetted member functions: `deduct()` and `canTravel()`.
  - Negative balance is mathematically impossible because `deduct()` enforces `(balance - fare) >= MIN_BALANCE_PAISE`.

## 2. Invariant Protection & Maintenance
- If `MIN_BALANCE_PAISE` changes, in the OOP version it is updated in exactly one place inside the `SmartCard` class.
- In procedural code, every caller interacting with free functions across multiple modules must be manually refactored.

## 3. Complexity Analysis
- **Time Complexity**: $O(1)$ per operation in both versions.
- **Space Complexity**: $O(1)$ (8 bytes per balance in both versions).
