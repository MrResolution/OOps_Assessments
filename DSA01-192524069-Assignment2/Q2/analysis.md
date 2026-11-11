# Q2: Return by Reference and Its Dangers

## 1. Modifying Elements via Return by Reference
- Function `int& getHighestMark(int marks[], int size)` returns an lvalue reference to the array element having the highest score.
- Because an lvalue reference is returned, the function invocation itself can appear on the left-hand side of an assignment operator (`getHighestMark(marks, 5) += 2;`), directly updating the array element in place.

## 2. Dangling Reference Hazard
- When a function returns a reference to an automatic (stack-allocated) local variable, the variable is destroyed upon function return when its stack frame is popped.
- Retaining or dereferencing this reference accesses deallocated stack memory, causing undefined behavior.
- The compiler emits `-Wreturn-local-addr: warning: reference to local variable returned`.

## 3. Vector Growth & Iterator Invalidation
- In a dynamically growing container like `std::vector`, adding elements beyond `capacity()` triggers reallocation:
  1. A new, larger contiguous heap block is allocated.
  2. Existing elements are copied/moved to the new storage.
  3. The old memory block is freed.
- Any reference or pointer bound to elements before reallocation immediately becomes dangling.

## 4. Complexity & Alternative Access
- Finding the highest mark takes $O(n)$ time and $O(1)$ memory.
- Returning an integer index (`int getHighestMarkIndex(...)`) is safer than returning a pointer/reference because an index remains valid even if dynamic array elements are moved in memory.
