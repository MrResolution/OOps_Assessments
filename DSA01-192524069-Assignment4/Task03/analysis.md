# Task 3: Constructors in Derived Classes and Member Classes

## Task 3.1 & 3.2: Constructor Delegation and Member Objects
- Derived classes initialize base classes by specifying base constructor calls in the member initializer list (`Person(n, a)`).
- **Virtual Base Rule**: When virtual inheritance is involved, the most-derived class is directly responsible for initializing the virtual base. Intermediate classes do not pass parameters to the virtual base.
- **Member Classes (Composition)**: Embedded objects like `Address home` are constructed before the derived class constructor body executes.

## Task 3.3: Lifecycle Order Rule
1. **Construction Order**:
   - Virtual base classes in order of appearance.
   - Non-virtual direct base classes in declaration order (`Vehicle`).
   - Member objects in declaration order (`Engine`).
   - Derived class constructor body (`Car`).
2. **Destruction Order**:
   - Destructors execute in the **exact reverse order of construction**: `~Car` $\rightarrow$ `~Engine` $\rightarrow$ `~Vehicle`.

## Prediction Verification
- **Predicted**: `Vehicle Engine Car | ~Car ~Engine ~Vehicle `
- **Observed**: `Vehicle Engine Car | ~Car ~Engine ~Vehicle `

## Task 3.4: Initializer List Declaration Order (`-Wreorder`)
- Class members are initialized strictly in the order they are declared in the class definition, not the order listed in the constructor initializer list.
- Swapping the initializer list order produces:
  ```text
  warning: ‘StudentReorder::home’ will be initialized after ‘long long int StudentReorder::regNo’ [-Wreorder]
  ```

## Alternative Concept & Complexity Analysis
- **Dynamic Pointer (`Address* home = new Address(...)`)**:
  - Adds heap allocation overhead ($O(1)$ amortized allocation time).
  - Requires extra pointer storage (8 bytes).
  - Forces manual lifecycle management: custom copy constructor, assignment operator, and destructor (Rule of Three) to prevent memory leaks and dangling pointers.
- Direct member containment (`Address home`) guarantees automatic RAII allocation and deallocation with zero heap fragmentation.
