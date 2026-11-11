# DSA01-192524069-Assignment2: Functions, Classes & OOP Mechanics

**Course Outcome**: CO2 - C++ Functions and Object-Oriented Principles  
**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler & Version**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**Compilation Command**: `g++ -std=c++17 -Wall -Wextra <filename>.cpp -o <binary>`

---

## Question Summary and Execution Results

| Question | Topic | Execution Command | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Q1** | Parameter Passing & Default Arguments | `cd Q1 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Verified caller state retention in call-by-value vs in-place mutation in reference and pointer passing. |
| **Q2** | Return by Reference & Dangling Hazards | `cd Q2 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Implemented lvalue return for exam mark moderation. Documented `-Wreturn-local-addr` and vector reallocation invalidation. |
| **Q3** | Function Overloading & Ambiguity | `cd Q3 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Diagnosed ambiguous overload error. Designed unambiguous overload set for grams, kg, and Parcel struct with trailing defaults. |
| **Q4** | Class Specification & Arrays Inside | `cd Q4 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Built `SavingsAccount` with private 10-tx array, scope resolution methods, and mini-statement FIFO evictions. |
| **Q5** | Static Members & Arrays of Objects | `cd Q5 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Implemented class-level static counters, static methods without `this`, and ticket array overflow to waiting list. |
| **Q6** | Friend Functions & Inline Optimization | `cd Q6 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Built symmetric friend time functions. Benchmarked 10,000,000 calls under `-O0` and `-O2` to evaluate inlining speedup. |
| **Q7** | Day-4 Design Challenge | `cd Q7 && g++ -std=c++17 -Wall -Wextra -O2 redesign.cpp -o redesign && ./redesign` | Diagnosed $O(k)$ shifting array bottleneck in Q4; redesigned into an $O(1)$ circular ring buffer delivering $2.22\times$ measured speedup. |

---

## Instructions to Run All Programs
To compile and execute any task, navigate to its directory and run:
```bash
g++ -std=c++17 -Wall -Wextra <filename>.cpp -o main
./main
```
