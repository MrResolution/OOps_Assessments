# Task B3: Virtual Functions vs. Switch vs. Exceptions – Cost Analysis

## B3.1 & B3.2: Virtual Dispatch vs. Switch Statement Benchmark
Compiled under `g++ -std=c++17 -Wall -Wextra -O2`:

| Bill Count | Virtual Function Dispatch | `switch` Statement Dispatch | Total Verification |
| :--- | :--- | :--- | :--- |
| **1,000** | $0.0039$ ms | $0.0010$ ms | Identical Sums (Verified) |
| **1,000,000** | $3.66$ ms | $0.97$ ms | Identical Sums (Verified) |
| **10,000,000** | $23.35$ ms | $5.66$ ms | Identical Sums (Verified) |

- **Analysis**:
  - The `switch` statement is approximately $3-4\times$ faster because modern compilers optimize contiguous switch statements into inline jump tables or direct branches, enabling branch prediction and instruction pipelining.
  - Virtual functions require double-pointer indirection (`this` $\rightarrow$ `vptr` $\rightarrow$ `vtable[i]`) and cannot be easily inlined when called across polymorphic collections.
  - However, virtual functions provide **Open-Closed extensibility**, eliminating the need to modify central switch code when new bills are added.

## B3.3: Cost of Exceptions Benchmark (1,000,000 Operations)
| Scenario | Error Rate | Return Code Check | Exception (`try-catch`) | Relative Cost |
| :--- | :--- | :--- | :--- | :--- |
| **Happy Path** | **0%** | $1.70$ ms | $1.38$ ms | **Exceptions are faster** (Zero-cost tables) |
| **Occasional Errors** | **1%** | $1.67$ ms | $8.29$ ms | **Exceptions are $\approx 5\times$ slower** |
| **Frequent Failures**| **50%** | $0.86$ ms | $304.70$ ms | **Exceptions are $\approx 350\times$ slower** |

- **Analysis**:
  - **Zero-Cost Exception Handling**: On modern 64-bit systems, `try` blocks add zero CPU instructions on the non-throwing execution path.
  - **Unwinding Overhead**: When an exception is thrown, the runtime must parse DWARF unwind tables, allocate exception objects, invoke destructors, and adjust the instruction pointer.
  - **Engineering Guideline**: Use return codes or `std::optional` for predictable, frequent validation checks (e.g., user input). Use exceptions exclusively for exceptional, rare system failures (e.g., database network disconnect, disk failure, memory exhaustion).
