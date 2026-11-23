# Task B2: Engineer Error Conditions

## Prediction and Output Verification
- **Predicted**: `ok done caught negative [log too large] caught too large `
- **Observed**: `ok done caught negative [log too large] caught too large `
- **Explanation**:
  - `process(100.0)`: Passes validation normally $\rightarrow$ prints `ok done `.
  - `process(-5.0)`: Throws `std::invalid_argument`. The inner catch in `process()` catches only `std::out_of_range`. The exception bypasses `process()`, unwinds to `main()`, and is caught by `const std::exception& e` $\rightarrow$ `caught negative `.
  - `process(2e6)`: Throws `std::out_of_range`. Caught by inner catch $\rightarrow$ prints `[log too large] `, re-throws with `throw;`, and caught in `main()` $\rightarrow$ `caught too large `.

## `throw;` vs `throw e;` (Exception Slicing)
- **`throw;` (Empty Rethrow)**: Re-propagates the active exception object without copying, preserving its derived dynamic type (`ClaimError`).
- **`throw e;`**: Creates a copy of `e`. If `e` is caught by reference to a base class (`const std::runtime_error& e`), copying slices off the derived `ClaimError` type, transforming it permanently into a base `std::runtime_error`.

## Deliberately Engineered Error Conditions
1. **Invalid Numeric Parsing**: `std::stod("invalid_number_twenty")` threw `std::invalid_argument`. Automatic stack resource `ParserBuffer` was cleanly destroyed before catch handled the error.
2. **Negative Currency Rejection**: Guard checks intercepted `-450.00` and threw custom domain errors.
3. **Memory Exhaustion**: Allocating $10\text{ TB}$ triggered `std::bad_alloc`. Stack unwinding verified zero resource leakage.
4. **Catch-All Shielding**: A top-level `catch (...)` prevents abnormal program termination (`std::terminate()`) on unexpected exceptions.

## Alternative Concept & Complexity Analysis
- **`std::optional<double>` vs Exceptions**:
  - `std::optional` is $O(1)$ fast on both success and failure, making it ideal when invalid inputs are frequent ($> 10\%$).
  - Exceptions have zero runtime cost on the happy path (table-based zero-cost exceptions), but incur expensive stack-unwinding overhead on the failure path. Exceptions should be reserved for truly exceptional conditions.
