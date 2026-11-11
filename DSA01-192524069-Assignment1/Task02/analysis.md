# Task 2: Tokens, Keywords, Identifiers, and Constants

## 1. Classification of Tokens
- **Keywords**: `enum`, `class`, `namespace`, `constexpr`, `switch`, `case`, `return`, `int`.
- **Identifiers**: `Zone`, `Inner`, `MetroConfig`, `FARE_INNER_PAISE`, `getZoneBaseFare`.
- **Constants**: `1000`, `2000`, `3000`, `20`, `5000`.
- **Operators**: `::`, `=`, `+`, `*`, `/`, `%`, `<<`.
- **Punctuators**: `;`, `{`, `}`, `(`, `)`.

## 2. Constant Specifications
- **`#define` vs `const` vs `constexpr`**:
  - `#define` lacks type safety, does not respect scopes/namespaces, and causes hard-to-debug compiler errors.
  - `const` enforces read-only semantics at runtime.
  - `constexpr` enables compile-time evaluation and constant folding with guaranteed type safety.
- **`enum` vs `enum class`**:
  - Unscoped `enum` exports enumerators into enclosing scope and implicitly converts to `int`.
  - `enum class` provides strong scoping and prevents accidental arithmetic/conversions.

## 3. Complexity & Memory Comparison
- Both `constexpr` and `#define` compile to immediate literals without runtime memory storage overhead ($O(1)$ space, $O(1)$ time).
- `constexpr` provides compile-time bounds and type verification.
