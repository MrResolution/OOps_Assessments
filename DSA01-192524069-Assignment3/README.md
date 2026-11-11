# DSA01-192524069-Assignment3: Lifecycle Management & Operator Overloading

**Course Outcome**: CO3 - Constructors, Destructors, and Operator Overloading  
**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler & Version**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**Compilation Command**: `g++ -std=c++17 -Wall -Wextra -fsanitize=address <filename>.cpp -o <binary>`

---

## Question Summary and Execution Results

| Question | Topic | Execution Command | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Q1** | Constructors & Member Initialization | `cd Q1 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Implemented constructor delegation and initializer lists. Documented `-Wreorder` and `explicit` conversion safety. |
| **Q2** | Deep Copying & Rule of Three | `cd Q2 && g++ -std=c++17 -Wall -Wextra -fsanitize=address complete_code.cpp -o complete_code && ./complete_code` | Implemented deep copy constructor, copy assignment with self-assignment guard, and destructor. Documented double-free under ASan. |
| **Q3** | Dynamic Constructors & RAII | `cd Q3 && g++ -std=c++17 -Wall -Wextra -fsanitize=address auditorium.cpp -o auditorium && ./auditorium` | Built 2D dynamic auditorium seat matrix with verified cleanup. Traced object lifecycle with Logger across stack, heap, and block scope. |
| **Q4** | Arithmetic & Stream Operators | `cd Q4 && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Overloaded `+`, `-`, `+=`, `==`, `<`, `*`, and stream `<<` for Money domain in integer paise. Enforced scalar multiplication. |
| **Q5** | Increment, Subscript & Timers | `cd Q5 && g++ -std=c++17 -Wall -Wextra playlist_timer.cpp -o playlist_timer && ./playlist_timer` | Implemented prefix/postfix `++` with rollover and `Playlist` `operator[]` bounds checking. Benchmarked 10M increments showing prefix is $>2.2\times$ faster. |
| **Q6** | Operator Overloading Rules | `cd Q6 && g++ -std=c++17 -Wall -Wextra -fsanitize=address main.cpp -o main && ./main` | Built custom `Text` string class with concatenation `+`, `==`, `!=`, and `<<`. Documented non-overloadable operators (`::`, `.`, `.*`, `?:`, `sizeof`). |
| **Q7** | Capstone: Complex Class Design | `cd Q7 && g++ -std=c++17 -Wall -Wextra main.cpp -o main && ./main` | Engineered full `Complex` class from first principles. Calculated series ($111.80\ \Omega$) and parallel ($141.42\ \Omega$) AC circuit impedances with zero-division safety. |

---

## Instructions to Run All Programs
To compile and execute any task, navigate to its directory and run:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address <filename>.cpp -o main
./main
```
