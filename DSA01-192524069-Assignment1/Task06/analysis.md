# Task 6: Control Structures and Decision Logic

## 1. Control Flow Structures
- **`switch(z)`**: Dispatches base fare determination cleanly based on the scoped enumeration `Zone`.
- **`if-else` & Short-Circuit `&&` / `||`**: Evaluates boundary hours and eligibility.
- **Range-based `for` loop**: Iterates over trip sequences without indexing errors or out-of-bounds risks.

## 2. Boundary Verification (10 AM and 8 PM)
- Peak hours are defined as 8:00 AM – 10:00 AM and 5:00 PM – 8:00 PM (17:00 – 20:00).
- At **10:00 AM** (`hour == 10`), `hour < 10` evaluates to `false`, correctly treating it as **Off-Peak**.
- At **8:00 PM** (`hour == 20`), `hour < 20` evaluates to `false`, correctly treating it as **Off-Peak**.

## 3. Alternative Architecture & Complexity Analysis
- **`switch` statement**: Compiles into a jump table if cases are contiguous ($O(1)$ time).
- **Array Lookup (`FARE[]`)**: Direct array indexing by enum ordinal ($O(1)$ time, $3 \times 8 = 24$ bytes storage).
- **Extensibility**: Adding a 4th zone requires adding an array element vs adding a `case` label.
