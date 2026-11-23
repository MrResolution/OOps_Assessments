# Object-Oriented Programming (OOP) in C++: Laboratory Assessments

**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**C++ Standard**: C++17 (`-std=c++17 -Wall -Wextra`)

---

## Directory Index

### 1. [Assignment 1 (CO1): Namma Metro Smart-Card Fare System](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment1/README.md)
* **Directory**: [`DSA01-192524069-Assignment1`](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment1)
* **Scope**: Tasks 01 through 12
* **Key Topics**: C++ fundamentals, compile-time `constexpr`, 64-bit integer money vs floating-point drift, implicit conversion hazards, operator precedence, control flow, procedural to OOP refactoring, stream safety, 3M-scale transaction simulation, and the Day-4 Design Challenge (Airport Zone, Weekend Discount, and Monthly Passes).

### 2. [Assignment 2 (CO2): Functions, Classes & OOP Mechanics](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment2/README.md)
* **Directory**: [`DSA01-192524069-Assignment2`](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment2)
* **Scope**: Questions Q1 through Q7
* **Key Topics**: Parameter passing (value, reference, pointer), return by reference & dangling local hazards, overload ambiguity resolution, class specification with internal arrays, static members & arrays of objects, friend functions & 10M-call inlining benchmark (`-O0` vs `-O2`), and the Day-4 Design Challenge ($O(k)$ shifting to $O(1)$ circular ring buffer).

### 3. [Assignment 3 (CO3): Lifecycle Management & Operator Overloading](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment3/README.md)
* **Directory**: [`DSA01-192524069-Assignment3`](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment3)
* **Scope**: Questions Q1 through Q7
* **Key Topics**: Constructors (default, parameterized, delegation), initializer list declaration order (`-Wreorder`), deep copy constructor vs shallow double-free (AddressSanitizer audit), dynamic 2D array allocation and RAII, operator overloading (`+`, `-`, `+=`, `*`, `==`, `<`, `<<`, `++`, `[]`), and Capstone Complex-number class for AC circuit impedance.

### 4. [Assignment 4 (CO4): Designing Reusable Class Hierarchies](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment4/README.md)
* **Directory**: [`DSA01-192524069-Assignment4`](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment4)
* **Scope**: Tasks 01 through 06
* **Key Topics**: Inheritance hierarchies, access control specifications (public, protected, private), constructor and member initialization sequencing (`-Wreorder`), diamond inheritance resolution via virtual base classes, polymorphic destructors, object slicing prevention, AddressSanitizer forensics on non-virtual destruction (`new-delete-type-mismatch`), method chaining using the `this` pointer, and the Day-4 Design Challenge (Extensible Vehicle Rental Fleet with Open-Closed Principle compliance).

### 5. [Assignment 5 (CO5): Reliable Software with Polymorphism & Exception Handling](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment5/README.md)
* **Directory**: [`DSA01-192524069-Assignment5`](file:///home/sabo/Documents/OOps_Assessments/DSA01-192524069-Assignment5)
* **Scope**: Part A (Design A1–A5) and Part B (Tasks B1–B4)
* **Key Topics**: Dynamic polymorphism and late binding via pure virtual interfaces (`VTable`/`VPtr` architectural analysis), hand-calculated bill-payer matrix tests, exception engineering (`throw;` vs `throw e;`, RAII stack unwinding with AddressSanitizer verification), 10,000,000 record benchmark comparing virtual dispatch vs switch (23.35 ms vs 5.66 ms), exception overhead quantification across error rates (350× slowdown at 50% errors), and Day-4 Capstone Hospital Billing Production Deployment Defense.

---

## Quick Build & Run Script
Each subfolder contains its own standalone `main.cpp` or `complete_code.cpp` and pre-captured execution output.
To compile and execute any program:
```bash
cd DSA01-192524069-Assignment<N>/<Task_or_Q>
g++ -std=c++17 -Wall -Wextra <filename>.cpp -o main
./main
```

To run with AddressSanitizer:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address <filename>.cpp -o main
./main
```
