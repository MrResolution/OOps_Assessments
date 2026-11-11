# DSA01-192524069-Assignment1: Namma Metro Smart-Card Fare System

**Course Outcome**: CO1 - C++ Fundamentals & Procedural to Object-Oriented Paradigm  
**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler & Version**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**Compilation Command**: `g++ -std=c++17 -Wall -Wextra <filename>.cpp -o <binary>`

---

## Task Summary and Execution Results

| Task | Topic | Execution Command | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Task 01** | OOP Analysis & Entities | `cd Task01 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Defined `SmartCard`, `Zone`, `FareTable`, `Journey`. Verified Rs 50 minimum balance invariant. |
| **Task 02** | Tokens & Compile-time Constants | `cd Task02 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Implemented `constexpr` and `enum class Zone`. Proved $O(1)$ memory folding. |
| **Task 03** | Data Types & Precision Analysis | `cd Task03 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Demonstrated floating-point double drift vs exact `long long` paise across 1,000,000 transactions. Showed `int` overflow. |
| **Task 04** | Control Implicit Conversions | `cd Task04 && g++ -std=c++17 -Wall -Wextra predict_output.cpp -o predict_output && ./predict_output` | Predicted exact output. Analyzed integer division, char promotion, and `-Wsign-compare` on unsigned comparison. |
| **Task 05** | Expressions & Operator Precedence | `cd Task05 && g++ -std=c++17 -Wall -Wextra predict_output.cpp -o predict_output && ./predict_output` | Verified arithmetic precedence, postfix vs prefix side-effects, and negative division/modulus. |
| **Task 06** | Control Structures | `cd Task06 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Completed `TODO 1` (`switch`) and `TODO 2` (`canTravel`). Verified 10 AM and 8 PM off-peak boundaries. |
| **Task 07** | Procedural vs. Object-Oriented | `cd Task07 && g++ -std=c++17 -Wall -Wextra object_oriented.cpp -o object_oriented && ./object_oriented` | Encapsulated balance in private member to prevent external negative balance corruption. |
| **Task 08** | Safe Stream Input & iomanip | `cd Task08 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main < input.txt` | Handled stream `failbit`, `cin.clear()`, buffer discard, and tabular currency formatting with `<iomanip>`. |
| **Task 09** | Fare Logic Test Matrix | `cd Task09 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | 13/13 automated test cases passed across zones, boundaries, threshold limits, and error handling. |
| **Task 10** | Expectation vs. Execution | `cd Task10 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Simulated 20k, 500k, and 3M journeys. Proved 32-bit `int` wraps negatively at 3M journeys whereas `long long` succeeds. |
| **Task 11** | Final Architecture Defense | `cd Task11 && g++ -std=c++17 -Wall -Wextra final_metro_system.cpp -o main && ./main` | Delivered modular production architecture using `MetroRules` namespace and pure functional engine. |
| **Task 12** | Day-4 Design Challenge | `cd Task12 && g++ -std=c++17 -Wall -Wextra redesign.cpp -o redesign && ./redesign` | Implemented 4th Airport zone (Rs 60), 10% non-stacking weekend discount, and polymorphic `MonthlyPassCard`. |

---

## Instructions to Run All Programs
To compile and execute any task, navigate to its directory and run:
```bash
g++ -std=c++17 -Wall -Wextra <filename>.cpp -o main
./main
```
