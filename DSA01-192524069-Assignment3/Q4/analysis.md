# Q4: Overloading Arithmetic and Stream Operators

## 1. Return by Value (`+`) vs. Return by Reference (`+=`)
- Binary addition `a + b` generates a **new result object** without mutating either operand `a` or `b`. Therefore, `operator+` must return by value (`Money`).
- Compound assignment `a += b` mutates the left operand in place and allows chaining (`(a += b) += c`). Therefore, `operator+=` returns an lvalue reference to `*this` (`Money&`).

## 2. Why `operator<<` Must Be a Non-Member Friend Function
- In C++, a binary member operator treats the invoking instance as its left-hand operand (`this->operator+(rhs)`).
- For stream insertion `std::cout << m`, the left operand is of type `std::ostream&`, not `Money`.
- Since we cannot modify the standard library `std::ostream` class to add a member function, `operator<<` must be declared as a free non-member function (and granted `friend` status to access private `paise`).

## 3. Engineering Decision: Multiplication Restrictions
- Multiplying `Money * Money` produces "square rupees" ($\text{Rs}^2$), which is physically and semantically meaningless in financial accounting.
- Only scalar multiplication `Money * double` (e.g., calculating tax percentages or quantity pricing) is dimensionally valid and implemented.

## 4. Complexity Analysis
- All arithmetic operations (`+`, `-`, `+=`, `*`) and comparisons (`==`, `<`) run in $O(1)$ constant time and $O(1)$ memory.
