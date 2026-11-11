# Task 12: Day-4 Design Challenge – Re-evaluate and Adapt the Design

## Part A: Impact Analysis (2 Marks)
The introduction of the fourth zone (Airport at Rs 60), the 10% non-combining weekend discount, and monthly pass cards directly affects:
1. **Enumerations**: `enum class Zone` expands to include `Zone::Airport`.
2. **Constants**: `FARES_PAISE[]` array expands to 4 elements (`{1000, 2000, 3000, 6000}`); `WEEKEND_DISCOUNT_PCT` (10%) introduced.
3. **Temporal Rules**: `isPeak()` must now incorporate `DayType` because peak surcharges do not apply on weekends.
4. **Card Abstractions**: The rigid concrete `SmartCard` is refactored into an abstract base class `Card` with specialized implementations: `StoredValueCard` and `MonthlyPassCard`.

## Part B: Evaluation of Original Design (2 Marks)
- The original design assumed a single stored-value card mechanism and simple zone switches without calendar awareness.
- Attempting to shoehorn monthly pass logic and weekend checks into a monolithic free function would violate the Single Responsibility Principle and Open-Closed Principle.
- A polymorphic redesign allows adding future pass types without altering core gate deduction mechanics.

## Part C: Adaptation & Implementation (2 Marks)
- **`Card` Interface**: Provides virtual methods `canTravel()`, `processJourney()`, and `getBalance()`.
- **`MonthlyPassCard`**: Holds two covered zones. If a journey falls within these zones, it is zero-rated; otherwise, it delegates deduction to an integrated backup wallet.
- **`FareEngineV2`**: Pure logic class enforcing mutual exclusivity between peak surcharge and weekend discount.

## Part D: Evidence-Based Defense (2 Marks)
- **Zero-Fare Assurance**: Passholder journeys within covered zones deduct exactly Rs 0.00.
- **Fail-Safe Degradation**: Journeys outside pass zones safely fall back to the backup wallet, retaining the Rs 50 minimum balance invariant.
- **Complexity**: Lookup and validation remain $O(1)$ time and $O(1)$ memory.
