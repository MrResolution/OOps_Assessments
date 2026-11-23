# Assignment 5: Part A – Design (25 Marks)

## Task A1: Polymorphic Bill Hierarchy (7 Marks)
### A1.1: Common Interface & Attributes
- **Common Data**: `std::string patientId`, `std::string patientName`, `double baseFee`.
- **Pure Virtual Interface**:
  - `virtual double total() const = 0`: Computes bill total according to category-specific billing rules.
  - `virtual std::string type() const = 0`: Returns discriminator string ("OP", "IP", "DayCare", "Emergency").
  - `virtual void print() const`: Outputs a formatted invoice breakdown.
  - `virtual ~Bill() = default`: Virtual destructor ensuring derived cleanup.

### A1.2: Hierarchy & UML Diagram
```
                     +----------------------------------+
                     |           <<abstract>>           |
                     |               Bill               |
                     +----------------------------------+
                     | # patientName: string            |
                     +----------------------------------+
                     | + total(): double = 0            |
                     | + type(): string = 0             |
                     | + print(): void                  |
                     | + virtual ~Bill() = default      |
                     +----------------------------------+
                                      ^
        +---------------+-------------+-------------+---------------+
        |               |                           |               |
+---------------+ +---------------+         +---------------+ +---------------+
| OutPatientBill| | InPatientBill |         |  DayCareBill  | | EmergencyBill |
+---------------+ +---------------+         +---------------+ +---------------+
| - consultation| | - days: int   |         | - packageRate | | - baseCharge  |
| - tests: double| | - perDayRate  |         +---------------+ | - hoursActive |
+---------------+ | - surgeryCost |         | + total()     | | - hourlyRate  |
| + total()     | +---------------+         +---------------+ +---------------+
| + type()      | | + total()     |                           | + total()     |
+---------------+ | + type()      |                           +---------------+
                  +---------------+
```

### A1.3: SIMATS Algorithmic Pseudocode (Aggregate Daily Revenue)
```text
ALGORITHM AggregateDailyBilling(billArray, count)
INPUT:
    billArray: Array of pointers to Bill objects
    count: Positive integer representing total bills for the day
OUTPUT:
    grandTotal: Double-precision floating point number

BEGIN
    grandTotal <- 0.0

    FOR i <- 0 TO count - 1 DO
        IF billArray[i] != NULL THEN
            currentTotal <- billArray[i].total()
            grandTotal <- grandTotal + currentTotal
        END IF
    END FOR

    RETURN grandTotal
END
```

---

## Task A2: Runtime Binding & Virtual Tables (5 Marks)
### A2.1: Early vs. Late Binding
- **Early Binding (Compile-Time)**: Function addresses are resolved statically during compilation based on pointer/reference declaration types.
- **Late Binding (Run-Time)**: Virtual function invocations (`b->total()`) are resolved dynamically at runtime by dereferencing the object's virtual table pointer (`vptr`).

### A2.2: Virtual Table (VTable) Layout
```
Object Instance (OPBill)            VTable for OPBill
+------------------------+          +-------------------------------+
| vptr                   | -------> | &OPBill::~OPBill              |
| patient: "Ravi"        |          | &OPBill::total [returns 500]  |
| consultation: 500      |          | &Bill::print                  |
| tests: 1200            |          +-------------------------------+
+------------------------+
```

### A2.3: Prediction & Virtual Destructors
- **Prediction**:
  ```text
  500 ~OPBill ~Bill
  ```
- **Observed**: `500 ~OPBill ~Bill `
- **Why `show()` reaches `OPBill::total()`**: Even though `show()` is non-virtual in `Bill`, inside `show()` the call `total()` is dispatched through `this->total()`. Since `total()` is virtual, runtime resolution queries `this->vptr`, correctly invoking `OPBill::total()`.
- **Non-Virtual Destructor Hazard**: If `virtual` is omitted from `~Bill()`, `delete b` statically invokes only `~Bill()`, skipping `~OPBill()` and leaking derived dynamic state.

---

## Task A3: Abstract Payer Interfaces (5 Marks)
```
                     +----------------------------------+
                     |           <<abstract>>           |
                     |              Payer               |
                     +----------------------------------+
                     | + amountCovered(Bill&): double=0 |
                     | + virtual ~Payer() = default     |
                     +----------------------------------+
                                      ^
        +-----------------------------+-----------------------------+
        |                             |                             |
+---------------+             +---------------+             +---------------+
|    SelfPay    |             |   Insurance   |             |GovtHealthScheme|
+---------------+             +---------------+             +---------------+
| + amountCover |             | - maxCoverage |             | - packageCap  |
| (returns 0.0) |             | - coPayPct    |             +---------------+
+---------------+             +---------------+             | + amountCover |
                              | + amountCover |             +---------------+
                              +---------------+
```
- **Open-Closed Extension**: A new payer (`CorporateTieUp`) is introduced by deriving from `Payer` and implementing `amountCovered(const Bill&)` without changing `Bill` or existing payers.

---

## Task A4: Exception Strategy (4 Marks)
### A4.1: Error Classification & Hierarchy
```
                   std::exception
                         ^
                 std::runtime_error
                         ^
                HospitalException
                         ^
        +----------------+----------------+
        |                                 |
   BillingError                       ClaimError
 (Negative charges,                 (Exceeds cover,
  invalid package)                   invalid policy)
```

### A4.2: Exception Specifications & `noexcept`
- **Destructors Must Be `noexcept`**: If a destructor throws during stack unwinding while another exception is in flight, the C++ runtime immediately invokes `std::terminate()`, causing an unrecoverable crash.
- Pure query accessors (`type() const`, `getName() const`) are marked `noexcept`.

---

## Task A5: Recovery, Stack Unwinding, and RAII (4 Marks)
- **Stack Unwinding**: When an exception is thrown, the runtime walks up the call stack, systematically destroying all automatic local objects in reverse order of construction before transferring control to the matching `catch` block.
- **`throw;` vs `throw e;`**:
  - `throw;`: Re-throws the exact original polymorphic exception object.
  - `throw e;`: Copies `e` to a new exception object sliced to the static catch type.
- **Prediction for `Guard`**:
  ```text
  ~f ~main caught 42
  ```
  `g` inside `f()` is destroyed first (`~f `), then `m` inside `main()` is destroyed (`~main `), followed by the `catch (int x)` handler (`caught 42`).
