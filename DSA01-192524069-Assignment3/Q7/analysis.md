# Q7: Capstone Engineering Design – Complex-Number Class (AC Circuit Impedance)

## Stage 1: Interpret the Problem (2 Marks)
- **Data Model**: A complex number $Z = R + jX$, where $R$ represents resistance and $X$ represents reactance.
- **Circuit Requirements**:
  - Resistors: $Z_R = R + 0j$
  - Inductors: $Z_L = 0 + j\omega L$
  - Capacitors: $Z_C = 0 - j\frac{1}{\omega C}$
  - Series combination: $Z_{series} = Z_1 + Z_2$
  - Parallel combination: $Z_{parallel} = \frac{Z_1 \cdot Z_2}{Z_1 + Z_2}$
- **Constructors Required**: Default (`0 + 0j`), single-argument from real (`r + 0j`), and full Cartesian (`r + ij`).

## Stage 2: Class Design & Mathematical Operators (3 Marks)
- **Member vs Friend Decisions**:
  - `+`, `-`, `*`, `/`, `==`: Overloaded as member functions taking `const Complex&`.
  - `<<`: Overloaded as a non-member friend function taking `std::ostream&`.
- **Formulas Implemented**:
  - Addition: $(a+bi) + (c+di) = (a+c) + (b+d)i$
  - Subtraction: $(a+bi) - (c+di) = (a-c) + (b-d)i$
  - Multiplication: $(a+bi)(c+di) = (ac - bd) + (ad + bc)i$
  - Division: $\frac{a+bi}{c+di} = \frac{(ac + bd) + (bc - ad)i}{c^2 + d^2}$
  - Magnitude: $|Z| = \sqrt{a^2 + b^2}$

## Stage 3: Implementation, Hand Verification, and Safety (3 Marks)
- **Parameters**: $R = 100\ \Omega, \omega = 1000\text{ rad/s}, L = 0.05\text{ H}, C = 10\ \mu\text{F}$.
- **Hand Calculation vs Program Output**:
  - $Z_L = 50j, Z_C = -100j$
  - $Z_{series} = 100 - 50j \implies |Z_{series}| = \sqrt{100^2 + 50^2} = 111.80\ \Omega$ (Matches Program).
  - $Z_{parallel(LC)} = \frac{(50j)(-100j)}{-50j} = 100j \implies Z_{total} = 100 + 100j \implies |Z| = 141.42\ \Omega$ (Matches Program).
- **Zero Division Safety**: When denominator $c^2 + d^2 == 0.0$, the class throws `std::runtime_error`, avoiding hardware floating-point trap crashes.

## Stage 4: Defend the Design & Comparison with `std::complex<double>` (2 Marks)
- **Comparison**: `std::complex<double>` provides polar conversions and complex transcendental functions, but defaults to returning IEEE `inf`/`nan` on division by zero without raising exceptions.
- **Limitation**: Cartesian coordinates require conversion when dealing with polar phase angles ($\theta = \text{atan2}(b, a)$).
- **Complexity**: All arithmetic operations execute in $O(1)$ time and occupy exactly 16 bytes (two 8-byte `double` values).
