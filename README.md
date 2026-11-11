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

---

## Quick Build & Run Script
Each subfolder contains its own standalone `main.cpp` or `complete_code.cpp` and pre-captured execution output.
To compile and execute any program:
```bash
cd DSA01-192524069-Assignment<N>/<Task_or_Q>
g++ -std=c++17 -Wall -Wextra <filename>.cpp -o main
./main
```
