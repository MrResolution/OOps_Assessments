# Q4: Specifying a Class with an Array Inside It

## 1. Class Structure and Scope Resolution
- Member data (`accountNumber`, `balancePaise`, `transactions[10]`, `count`) are strictly `private`.
- Public interface methods (`deposit()`, `withdraw()`, `miniStatement()`) are declared inside the class.
- Member functions defined outside the class use the scope resolution operator (`SavingsAccount::withdraw`).

## 2. Encapsulation Rationale
- The transactions array must be `private` to prevent external code from tampering with historical records, fabricating deposits, or corrupting transaction counts without balance adjustments.

## 3. Shifting Array vs. Circular Buffer ($O(k)$ vs $O(1)$)
- **Shifting Array**:
  - When the 11th transaction arrives, every element from index 1 to $k-1$ must be shifted left by one position.
  - Takes $O(k)$ time per insertion (where $k=10$ or $k=50$).
- **Circular Buffer**:
  - Tracks a `head` index where each new transaction overwrites `transactions[head]` and advances `head = (head + 1) % MAX_TX`.
  - Takes $O(1)$ constant time per insertion.
- **Scaling to 50 Transactions**:
  - A circular buffer scales effortlessly with zero shifting overhead, whereas an array shift requires 49 element copies per transaction.
