# DSA01-192524069-Assignment4: Designing Reusable Class Hierarchies

**Course Outcome**: CO4 – Inheritance, Polymorphism, Virtual Bases, and Object Lifecycle  
**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler & Version**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**Compilation Command**: `g++ -std=c++17 -Wall -Wextra <filename>.cpp -o <binary>`

---

## Task Summary and Execution Results

| Task | Topic | Execution Command | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Task 01** | Class Design Review | `cd Task01 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Diagnosed 6 flaws in college payroll; refactored into `Staff` hierarchy with overridden `pay()`. |
| **Task 02** | Requirement to Hierarchy | `cd Task02 && g++ -std=c++17 -Wall -Wextra university_system.cpp -o main && ./main` | Resolved diamond inheritance with `virtual public Person`; prepared member access tables under inheritance. |
| **Task 03** | Derived & Member Constructors | `cd Task03 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Traced Base $\rightarrow$ Member $\rightarrow$ Derived construction order; captured `-Wreorder` on initializer list swap. |
| **Task 04** | Pointers to Derived Forensics | `cd Task04 && g++ -std=c++17 -Wall -Wextra -fsanitize=address repaired_program.cpp -o repaired_program && ./repaired_program` | Diagnosed static binding and leaking non-virtual destructor under ASan; repaired using virtual destructors. |
| **Task 05** | Pointers to Objects & `this` | `cd Task05 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Implemented method chaining returning `*this` (`Cart&`); searched array of pointers to locate highest cart total. |
| **Task 06** | Day-4 Design Challenge | `cd Task06 && g++ -std=c++17 -Wall -Wextra fleet_system.cpp -o fleet_system && ./fleet_system` | Built extensible `Vehicle` rental fleet; demonstrated rental billing, late charges, and adding `ElectricBus` via OCP. |

---

## Instructions to Run All Programs
To compile and execute any task:
```bash
g++ -std=c++17 -Wall -Wextra <filename>.cpp -o main
./main
```
