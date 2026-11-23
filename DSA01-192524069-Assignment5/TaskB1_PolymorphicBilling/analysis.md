# Task B1: Implement and Validate Polymorphic Billing

## B1.1: Hand Calculation vs Program Verification
All matrix calculations match hand derivations precisely:
- **OutPatient (Rs 2,000)**: Self-Pay covers Rs 0; Insurance (10% co-pay) covers Rs 1,800; Govt Scheme (capped at Rs 20,000) covers Rs 2,000.
- **InPatient (Rs 37,000)**: Insurance covers $(30,000 - 10\%) = \text{Rs } 27,000$, leaving Rs 10,000 patient liability; Govt Scheme covers the Rs 20,000 cap.
- **DayCare (Rs 18,000)**: Insurance covers Rs 16,200; Govt Scheme covers full package (Rs 18,000).
- **Emergency (Rs 6,000)**: Insurance covers Rs 5,400; Govt Scheme covers Rs 6,000.

## B1.3: Proving Runtime Binding
- When `virtual` is removed from `total()`:
  - `double total() const = 0;` produces a compilation error: `error: initializer specified for non-virtual method 'double Bill::total() const'`.
  - If given a non-virtual base body returning 0, `b->total()` statically binds to `Bill::total()`, outputting 0 for every bill and breaking runtime polymorphism.

## B1.4: Proving Virtual Destructor Necessity
- Omitting `virtual ~Bill()` causes deleting derived objects via `Bill*` to execute only the base destructor, leaking derived memory and triggering AddressSanitizer `new-delete-type-mismatch`.

## Alternative Concept & Complexity Analysis
- **Compile-Time Templates vs Virtual Dispatch**:
  - Templates achieve static dispatch with zero vtable pointer overhead ($0$ byte space overhead) and allow inlining.
  - However, templates require homogeneous containers (`std::vector<OutPatient>`, `std::vector<InPatient>`), making it impossible to store all hospital bills in a single unified collection without type erasure or tagged unions.
  - Virtual functions enable storing heterogeneous bills in a single `Bill*` array with constant $O(1)$ dispatch time.
