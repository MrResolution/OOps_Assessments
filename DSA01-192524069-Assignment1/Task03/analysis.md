# Task 3: Data Types and Compatibility

## 1. Selected Data Types
- **Money (Fares, Balances, Revenue)**: `long long` (64-bit integer, 8 bytes). Avoids floating-point drift and prevents 32-bit integer overflow.
- **Time (Hours, Minutes)**: `int` (4 bytes).
- **Zone Identifiers**: `enum class Zone` (underlying `int`).
- **Flags (Peak, Surcharge)**: `bool` (1 byte).

## 2. Integer Paise vs. Double Rupees
- Floating-point representations (IEEE 754) cannot represent exact fractional decimals like $0.10$ or $0.30$ in binary.
- As demonstrated empirically over $1,000,000$ additions, rounding errors accumulate into noticeable fractional discrepancies.
- Integer paise representation guarantees exact transactional precision.

## 3. Range & Overflow Analysis
- Network daily total at 3,000,000 journeys exceeds $7.5 \times 10^9$ paise.
- Standard 32-bit signed `int` maximum is $2,147,483,647$ ($2.14 \times 10^9$). Storing paise in `int` produces arithmetic overflow and undefined behavior.
- `long long` has a ceiling of $9.22 \times 10^{18}$, easily accommodating network transactions.

## 4. Complexity Analysis
- **Time Complexity**: $O(1)$ per addition for both `double` and `long long`.
- **Space Complexity**: 8 bytes for both `double` and `long long`.
