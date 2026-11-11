# Task 10: Compare Expectations with Execution

## 1. Measured Results Across Scale
| Journey Scale | 32-bit `int` (Paise) | 64-bit `long long` (Paise) | `double` (Rupees) | `int` Overflow? |
| :--- | :--- | :--- | :--- | :--- |
| **20,000 (1 Station)** | $46,665,400$ | $46,665,400$ | Rs $466,654.00$ | No |
| **500,000 (1 Line)** | $1,166,665,400$ | $1,166,665,400$ | Rs $11,666,654.00$ | No |
| **3,000,000 (Network)** | **$-1,589,934,592$** | **$7,000,000,000$** | Rs $70,000,000.00$ | **YES (Arithmetic Wrap)** |

## 2. Integer Overflow Analysis
- Standard signed 32-bit `int` spans $[-2,147,483,648, 2,147,483,647]$.
- Daily revenue of $7.0 \times 10^9$ paise exceeds `INT_MAX` by more than a factor of three.
- The signed overflow results in undefined behavior and wraps to a negative value ($-1,589,934,592$), which in a financial accounting system would cause massive balance corruption.
- `long long` (64-bit) supports up to $9.22 \times 10^{18}$ paise, remaining sound for centuries of network traffic.

## 3. Compiler Warning Audit (`-Wall -Wextra`)
- `-Wsign-compare`: Emitted in Task 4 when comparing signed and unsigned integers without explicit casting.
- `-Wunused-variable`: Emitted if trip variables are initialized without downstream reads.
- Both warnings enforce strict type hygiene and avoid implicit promotion hazards.
