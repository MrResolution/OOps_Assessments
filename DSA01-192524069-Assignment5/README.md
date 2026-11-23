# DSA01-192524069-Assignment5: Reliable Software with Runtime Polymorphism & Exceptions

**Course Outcome**: CO5 – Virtual Functions, Runtime Polymorphism, and Exception Resilience  
**Student Name**: Sandip Singh Bohara  
**Register Number**: 192524069  
**Compiler & Version**: `g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`  
**Compilation Command**: `g++ -std=c++17 -Wall -Wextra -fsanitize=address <filename>.cpp -o <binary>`

---

## Part A: Design Summary (25 Marks)

| Task | Topic | Deliverables | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Task A1** | Polymorphic Bill Hierarchy | [`PartA_Design/design_report.md`](PartA_Design/design_report.md#task-a1-polymorphic-bill-hierarchy-7-marks) | Specified abstract `Bill` class with pure virtual `total()`, `type()`, UML hierarchy, and SIMATS algorithmic pseudocode. |
| **Task A2** | Runtime Binding & VTables | [`PartA_Design/predict_A2.cpp`](PartA_Design/predict_A2.cpp) | Mapped VTable/VPtr pointer layouts; predicted and verified output for virtual destructor order and late dispatch via `show()`. |
| **Task A3** | Abstract Payer Interfaces | [`PartA_Design/design_report.md`](PartA_Design/design_report.md#task-a3-abstract-payer-interfaces-5-marks) | Designed `Payer` interface with derived `SelfPay`, `Insurance`, `GovernmentScheme`, and open-closed extension path. |
| **Task A4** | Exception Hierarchy Strategy | [`PartA_Design/design_report.md`](PartA_Design/design_report.md#task-a4-exception-strategy-4-marks) | Classified system errors; architected `BillingError` and `ClaimError` derived from `std::runtime_error`; specified `noexcept` rules. |
| **Task A5** | Stack Unwinding & Rethrowing | [`PartA_Design/predict_A5.cpp`](PartA_Design/predict_A5.cpp) | Traced RAII destructor cleanup during stack unwinding; analyzed semantic differences between `throw;` and `throw e;`. |

---

## Part B: Implementation & Benchmarks Summary (25 Marks)

| Task | Topic | Execution Command | Result / Outcome |
| :--- | :--- | :--- | :--- |
| **Task B1** | Implement Polymorphic Billing | `cd TaskB1_PolymorphicBilling && g++ -std=c++17 -Wall -Wextra -fsanitize=address billing_payer_matrix.cpp -o main && ./main` | Completed `TODO 1-3`; tested and verified hand calculation matrix across all bill and payer combinations under ASan. |
| **Task B2** | Engineer Error Conditions | `cd TaskB2_ErrorEngineering && g++ -std=c++17 -Wall -Wextra complete_code.cpp -o complete_code && ./complete_code` | Completed `TODO 1-2`; tested invalid text (`stod`), negative fees, memory exhaustion (`bad_alloc`), and rethrow audits. |
| **Task B3** | Scale & Exception Benchmark | `cd TaskB3_PerformanceBenchmark && g++ -std=c++17 -Wall -Wextra -O2 benchmark_bills.cpp -o bench_bills && ./bench_bills` | Benchmarked 10,000,000 bills (virtual dispatch 23.3ms vs switch 5.6ms); measured exception cost across 1M records at 0%, 1%, 50% errors. |
| **Task B4** | Production Decision & Extension | `cd TaskB4_FinalDecision && g++ -std=c++17 -Wall -Wextra -fsanitize=address hospital_system.cpp -o hospital_system && ./hospital_system` | Implemented `DayCareBill` and `CorporateTieUp` via OCP; proved 0 memory leaks under ASan; delivered production architecture defense. |

---

## Instructions to Run All Programs
To compile and execute any task:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address <filename>.cpp -o main
./main
```
