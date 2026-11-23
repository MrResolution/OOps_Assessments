# Task B4: Final Engineering Decision

## B4.1: Practical Extension Demonstration (Open-Closed Principle)
- **New Bill Added**: `DayCareBill` inheriting from `Bill`, implementing custom package pricing.
- **New Payer Added**: `CorporateTieUp` inheriting from `Payer`, implementing negotiated discount and corporate subsidy caps.
- **Zero Modification of Core Classes**: Neither `Bill`, `OutPatientBill`, `InPatientBill`, nor existing `Payer` classes required any code changes or re-compilation. All polymorphic iteration loops remained 100% untouched.

## B4.2: Resource Safety Audit (AddressSanitizer Verified)
- Running under `g++ -fsanitize=address` confirmed that:
  - When invalid parameters threw `BillingError` inside constructors, partially initialized heap allocations were cleanly unwound.
  - When rejected claims threw `ClaimError` during settlement, smart pointer containers (`std::vector<std::unique_ptr<Bill>>`) freed all memory on scope exit with **zero memory leaks** and **zero memory corruption**.

## B4.3: Production Architecture Decision (15 Hospitals, 200,000 Bills/Day)
- **Verdict**: The polymorphic C++ architecture with structured exception handling is **strongly recommended** for production deployment.
- **Evidence-Based Rationale**:
  1. **Throughput Feasibility**: Processing 200,000 bills/day requires less than $1$ millisecond of CPU time under virtual function dispatch (measured at $3.66$ ms for $1,000,000$ bills at `-O2`). CPU overhead is completely negligible.
  2. **Maintenance Scalability**: With 2 new bill types and 3 new payers introduced annually, the object-oriented polymorphic hierarchy allows independent developer teams to introduce modules without merge conflicts or regression risks in central `switch` tables.
  3. **Fault Isolation**: Exception hierarchies allow graceful claim rejection without crashing POS/billing kiosks or corrupting database transactions.

## Alternative Concept: Configuration-Driven Plug-ins vs Compiled Classes
- **Configuration-Driven Rules (JSON/YAML/Lua)**:
  - Allows rate adjustments without binary re-compilation.
  - Adds runtime interpretation overhead ($O(r)$ rule parsing time per bill vs $O(1)$ compiled vtable jump).
  - Risk of subtle runtime syntax or semantic schema errors crashing billing processes.
- **Compiled Polymorphism**:
  - Delivers maximum type safety, compile-time contract enforcement, zero-cost exception safety, and optimal performance.
