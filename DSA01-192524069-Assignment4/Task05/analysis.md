# Task 5: Pointers to Objects and the `this` Pointer

## Task 5.1 & 5.3: Four Ways to Access an Object
1. **Direct by Name (`Cart c`)**: Automatic storage on the stack. Safe, clean syntax, destroyed when leaving enclosing scope.
2. **Through Pointer (`Cart* p = &c`)**: Stores memory address. Requires explicit dereference or arrow syntax (`p->`). Allows nullability and reseating.
3. **Through Reference (`Cart& ref = c`)**: Non-null alias to existing object. Syntactically identical to direct access (`ref.add()`). Cannot be reseated or null.
4. **Dynamic Heap Pointer (`Cart* h = new Cart`)**: Explicit dynamic lifetime. Must be released with `delete` to prevent memory leaks.

## Method Chaining and `this` Pointer Mechanics
- **`this` Pointer**: In non-static member functions, `this` is an implicit prvalue pointer of type `Cart* const` pointing directly to the object on which the method is called.
- **Disambiguation**: Distinguishes member variables from shadowing parameters:
  `this->discount = discount;`
- **Method Chaining**: Returning `*this` with an lvalue reference return type (`Cart&`) enables cascading invocations:
  `c.add("Rice", 60).add("Dal", 120).setDiscount(10);`
- **Return by Value Hazard**: If `add()` returned `Cart` by value, each chained call would create an independent temporary copy. Subsequent calls would modify the discardable temporary, leaving the original `Cart` unmodified.

## Task 5.2: Array of Pointers Search
- Managing customer carts through `Cart* activeCarts[]` enables linear search ($O(n)$ time) without copying cart structures or internal item arrays.
- Memory overhead is restricted strictly to one 8-byte pointer per cart.

## Alternative Concept & Complexity Analysis
- **`std::vector<Cart>` (Value Containment)**:
  - Copying large cart objects on vector reallocation incurs memory copying overhead ($O(n)$).
  - Pointers/references into the vector risk becoming dangling when `push_back()` triggers buffer reallocation.
- Storing stable pointers (or `std::vector<std::unique_ptr<Cart>>`) provides lifetime safety and constant-time element moves.
