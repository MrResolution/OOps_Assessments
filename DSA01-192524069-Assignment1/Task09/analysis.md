# Task 9: Implement and Test Fare Logic

## 1. Test Matrix and Verification Results
The test suite validates:
- **Normal Journeys**: Validates base fares (Rs 10, Rs 20, Rs 30) during standard off-peak hours and surcharge fares (Rs 12, Rs 24, Rs 36) during peak hours.
- **Boundary Hours**:
  - `08:00`: Peak (20% surcharge).
  - `10:00`: Off-Peak (regular base fare).
  - `17:00`: Peak (20% surcharge).
  - `20:00`: Off-Peak (regular base fare).
- **Balance Invariants**:
  - Exact threshold: Rs 60 initial balance minus Rs 10 fare leaves exactly Rs 50 remaining ($\ge 5000$ paise) $\rightarrow$ Allowed.
  - Sub-threshold: Rs 59.99 initial balance minus Rs 10 leaves Rs 49.99 ($< 5000$ paise) $\rightarrow$ Denied.
- **Invalid Inputs**: Unknown zone safely triggers rejection.

## 2. Complexity Analysis
- **Execution Time**: Table-driven iteration evaluates $t$ tests in $O(t)$ time.
- **Memory Overhead**: Test vector stores test descriptors taking $O(t)$ space. Adding new edge cases requires adding a single row without modifying control flow code.
