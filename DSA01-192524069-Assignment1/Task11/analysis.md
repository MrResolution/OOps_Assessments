# Task 11: Final Design Recommendation and Defense

## 1. Architectural Recommendations
- **Types**: `long long` for all monetary storage in integer paise; `enum class Zone` for strong type-safe zoning; `bool` for peak flags.
- **Constants**: `constexpr` inside dedicated namespace `MetroRules`.
- **Classes**: Encapsulated `SmartCard` with private state; static stateless `FareEngine` for pure functional fare evaluation.

## 2. Fare Revision Management
- Future fare revisions (e.g., changing zone base prices or minimum balance thresholds) require updating values in exactly one translation unit (`MetroRules` constants) without altering transaction logic.

## 3. Configuration File vs. Compile-Time Constants
- **Compiled `constexpr`**: Zero startup latency, compile-time optimization, zero allocation failure risk.
- **Runtime Configuration File**: Allows dynamic fare adjustments without re-compilation, but introduces $O(z)$ startup disk I/O, string parsing overhead, and runtime configuration failure modes.
