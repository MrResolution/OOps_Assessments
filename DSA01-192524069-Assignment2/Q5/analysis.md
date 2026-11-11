# Q5: Static Members and Arrays of Objects

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
101 103 104 4
```

### Actual Output:
```text
101 103 104 4
```

## 2. Static Members Mechanics
- **Single Memory Instance**: A `static` data member (`int BusTicket::issued`) belongs to the class scope rather than any individual object instance. It must be defined outside the class definition in global/namespace scope.
- **`this` Pointer Absence**: A `static` member function lacks a `this` pointer because it is invoked without a class instance (`BusTicket::count()`). Consequently, it cannot access non-static instance members (`seat`, `name`).
- **Array of Objects**: Instantiating an array of objects `BusTicket trip[4]` triggers the constructor 4 consecutive times, progressively incrementing the shared static counter up to capacity.

## 3. Alternative Architecture & Complexity Analysis
- **Static Member vs. Global Counter vs. `TicketOffice` Class**:
  - Global variable destroys encapsulation and invites naming collisions.
  - A `static` member keeps data encapsulated within the class scope, but restricts the application to a single bus route.
  - A separate `TicketOffice` instance allows managing multiple distinct buses concurrently.
- **Complexity**: In all designs, ticket generation and counting operate in $O(1)$ time and $O(1)$ space.
