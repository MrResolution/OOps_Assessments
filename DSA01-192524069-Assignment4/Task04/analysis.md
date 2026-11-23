# Task 4: Pointers to Derived Classes – Forensics

## Task 4.1: Diagnosis of Defects
1. **Static Binding of Non-Virtual Method**:
   - `rate()` was non-virtual in `Account`. Invoking `a->rate()` through an `Account*` statically binds at compile-time to `Account::rate()`, ignoring `SeniorAccount::rate()` and returning 3.5% instead of 4.0%.
2. **Missing Virtual Destructor (Memory Leak & Undefined Behavior)**:
   - `~Account()` was non-virtual. Deleting a `SeniorAccount` through a base pointer `Account*` executes only the base destructor. The derived destructor `~SeniorAccount()` is skipped, completely leaking the dynamic `history` array. AddressSanitizer terminates the process with `new-delete-type-mismatch`.
3. **Object Slicing**:
   - `Account copy = SeniorAccount();` performs pass/assign-by-value, copying only the `Account` base sub-object and slicing off `SeniorAccount` state and dynamic vtable identity.

## Task 4.2: Sanitizer Evidence
AddressSanitizer output:
```text
==ERROR: AddressSanitizer: new-delete-type-mismatch on 0x502000000030 in thread T0:
  object passed to delete has wrong type:
  size of the allocated type:   8 bytes;
  size of the deallocated type: 1 bytes.
```

## Task 4.3 & 4.4: Prevention Rules & Repaired Code
- **Rule 1**: Any class intended to serve as a polymorphic base class (containing at least one virtual function) **must declare a virtual destructor** (`virtual ~Base() = default;`).
- **Rule 2**: Always mark overridden virtual functions with the `override` specifier to catch signature mismatches at compile time.
- **Rule 3**: Store polymorphic objects by pointer/reference (preferably `std::unique_ptr<Base>`) rather than by value to prevent object slicing.

## Output Prediction Analysis
```text
3.5 4 3.5
```
- `p->rate()`: Non-virtual call resolved statically by pointer type (`Account*`) $\rightarrow$ `3.5`.
- `p->vrate()`: Virtual call dispatched dynamically via vtable to `SeniorAccount::vrate()` $\rightarrow$ `4.0`.
- `copy.vrate()`: Object sliced into an `Account` instance $\rightarrow$ `3.5`.

## Alternative Concept & Complexity Analysis
- Managing polymorphic entities using `std::vector<std::unique_ptr<Account>>` provides automatic RAII deallocation, zero leak risk, and identical $O(n)$ processing time with $O(1)$ overhead per pointer.
