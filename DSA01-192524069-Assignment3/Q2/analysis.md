# Q2: Copy Constructors: Shallow and Deep Copies

## 1. The Shallow Copy Dilemma & AddressSanitizer Crash Report
- **Default Compiler Copy**: Copies pointer addresses directly (`medicines = other.medicines`). Both objects end up pointing to the exact same heap memory block.
- **Double-Free Crash**: When the first object goes out of scope, its destructor invokes `delete[] medicines`. When the second object goes out of scope, its destructor attempts to invoke `delete[]` on the already deallocated heap address.
- **AddressSanitizer Output**:
  ```text
  ERROR: AddressSanitizer: heap-use-after-free
  freed by thread T0 here: operator delete[]
  SUMMARY: AddressSanitizer: heap-use-after-free in ShallowPrescription::~ShallowPrescription()
  ```

## 2. The Rule of Three
- If a class requires a user-defined **destructor** to release raw dynamic resources, it almost certainly requires an explicit **copy constructor** and **copy assignment operator**.
- **Deep Copy Implementation**:
  - Allocates an independent heap array (`new std::string[n]`).
  - Performs element-wise copy.
  - Guards against self-assignment (`if (this != &other)`).

## 3. Alternative Architecture & Rule of Zero
- Storing items in `std::vector<std::string>` delegates lifecycle management to standard RAII containers. The compiler-synthesized copy constructor, assignment operator, and destructor automatically achieve deep copying without manual memory management (**The Rule of Zero**).
- **Complexity**:
  - Deep copy: $O(n)$ time and $O(n)$ space for $n$ elements.
  - Shallow copy: $O(1)$ time and $O(1)$ space, but causes fatal memory corruption.
