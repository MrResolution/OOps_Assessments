# Task 6: Day-4 Design Challenge – Vehicle Rental Fleet

## Stage 1: Interpret the Problem (2 Marks)
- **Entities & Data**:
  - `Vehicle`: Base entity storing `regNumber`, `dailyRate`, `isRented`.
  - `MotorVehicle`: Extends `Vehicle` with energy level (`fuelOrChargeLevel`) and `Date serviceDueDate` composition.
  - `Bicycle`: Pure muscle-powered vehicle with base daily rate.
  - `TwoWheeler`: Motorized two-wheeler with fuel and custom late fee multiplier.
  - `Car`: Adds `seatingCapacity` and insurance surcharges.
  - `ElectricCar`: Specializes `Car` with `batteryCapacityKWh` and charging rate per kWh.
- **Testable Requirements**:
  1. A rented vehicle cannot be re-rented before being returned.
  2. Late returns must accurately calculate compound penalty rates.
  3. New vehicle subclasses can be registered and billed through the same fleet loop without altering existing vehicle code.

## Stage 2: Hierarchy & Class Architecture (2 Marks)
```
                   +----------------------------------+
                   |           <<abstract>>           |
                   |             Vehicle              |
                   +----------------------------------+
                   | # regNumber: string              |
                   | # dailyRate: double              |
                   | # isRented: bool                 |
                   +----------------------------------+
                   | + calculateCharge(...): double=0 |
                   | + rentVehicle(): bool            |
                   | + returnVehicle(): bool          |
                   | + virtual ~Vehicle() = default   |
                   +----------------------------------+
                                    ^
                    +---------------+---------------+
                    |                               |
          +-------------------+           +-------------------+
          |      Bicycle      |           |   MotorVehicle    |
          +-------------------+           +-------------------+
          | + calculateCharge |           | # energyLevel     |
          +-------------------+           | # serviceDate     |
                                          +-------------------+
                                                    ^
                            +-----------------------+-----------------------+
                            |                       |                       |
                  +-------------------+   +-------------------+   +-------------------+
                  |    TwoWheeler     |   |        Car        |   |    ElectricBus    |
                  +-------------------+   +-------------------+   |    (Extension)    |
                  | + calculateCharge |   | # seats: int      |   +-------------------+
                  +-------------------+   +-------------------+   | + calculateCharge |
                                                    ^             +-------------------+
                                                    |
                                          +-------------------+
                                          |    ElectricCar    |
                                          +-------------------+
                                          | - batteryKWh      |
                                          | - ratePerKWh      |
                                          +-------------------+
                                          | + calculateCharge |
                                          +-------------------+
```

## Stage 3: Critical Design Decisions (2 Marks)
1. **Pure Virtual Interface**: Declaring `calculateCharge(days, lateDays) = 0` forces each vehicle subclass to encapsulate its domain-specific pricing algorithm.
2. **Virtual Destructor**: Mandating `virtual ~Vehicle() = default;` prevents undefined behavior and memory leaks when deleting through base pointers.
3. **Polymorphic Collection**: Storing the fleet in `std::vector<Vehicle*>` allows runtime dispatch of billing and returns across heterogeneous vehicle types.

## Stage 4: Algorithmic Pseudocode (SIMATS Standard) (4 Marks)
```text
ALGORITHM ProcessVehicleReturn(vehiclePtr, daysRented, lateDays)
INPUT:
    vehiclePtr: Pointer to Vehicle object
    daysRented: Non-negative integer representing standard rental days
    lateDays: Non-negative integer representing overdue days
OUTPUT:
    totalBill: Double-precision floating point value representing final settlement amount

BEGIN
    IF vehiclePtr = NULL THEN
        RAISE ERROR "Null vehicle pointer"
    END IF

    IF NOT vehiclePtr.getStatus() THEN
        RAISE ERROR "Vehicle is not currently rented"
    END IF

    totalBill <- vehiclePtr.calculateCharge(daysRented, lateDays)
    vehiclePtr.returnVehicle()

    RETURN totalBill
END
```

## Stage 5: Implement, Extend, and Validate (3 Marks)
- **Extension Demonstration**: Subclass `ElectricBus` was implemented and incorporated into the fleet vector seamlessly without modifying `Vehicle`, `Car`, or `Bicycle`.
- **Billing Calculations**:
  - `BIKE-01` (3 days, 1 day late @ 1.5x): $3 \times 150 + 1 \times 225 = \text{Rs } 675.00$.
  - `KA-01-CD-5678` (Car: 5 days, 2 days late @ 2.0x, Rs 200/day insurance): $5 \times 2500 + 2 \times 5000 + 5 \times 200 = \text{Rs } 23,500.00$.
  - `TN-BUS-001` (Bus: 4 days, 0 late, Rs 1500 commercial permit): $4 \times 8000 + 1500 = \text{Rs } 33,500.00$.

## Alternative Concept & Complexity Analysis
- A single `Vehicle` class with a type switch requires an open-ended union of fields (`fuel`, `seats`, `batteryKWh`, `kwhRate`, `busPermit`) resulting in significant per-object memory bloat.
- Virtual dispatch executes in $O(1)$ constant time through the vtable, whereas `switch` statements require ongoing modifications with every new vehicle release.
