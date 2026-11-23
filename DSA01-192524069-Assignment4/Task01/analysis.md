# Task 1: Class Design Review – College Payroll

## Task 1.1: Diagnosis of Design Deficiencies
1. **Public Data Exposure**: `name`, `id`, `basic`, etc., were declared `public`, violating encapsulation and allowing unvetted external modifications.
2. **Duplicated Pay Calculation**: The dearness allowance formula (`basic + basic * 0.42`) was copy-pasted across `Professor` and `LabAssistant`.
3. **Magic Number**: The multiplier `0.42` was hardcoded directly in member functions rather than encapsulated as a named `constexpr` constant.
4. **Dead / Unused Data Member**: Variable `da` was declared in both classes but never used in `pay()`.
5. **Inconsistent Naming**: Identical domain attributes were inconsistently named (`nm` vs `name`, `code` vs `id`) across classes.
6. **Inability to Process Staff Uniformly**: Lack of a common polymorphic base type prevented storing staff in a single collection or iterating with a single payroll loop.

## Task 1.2: Repaired Class Hierarchy & UML Diagram
```
              +--------------------------+
              |      <<abstract>>        |
              |          Staff           |
              +--------------------------+
              | # name: string           |
              | # id: int                |
              +--------------------------+
              | + pay(): double = 0      |
              | + ~Staff() = default     |
              +--------------------------+
                           ^
             +-------------+-------------+
             |                           |
  +----------------------+    +----------------------+
  |    SalariedStaff     |    |     GuestFaculty     |
  +----------------------+    +----------------------+
  | # basic: double      |    | - hours: double      |
  | # DA_RATE = 0.42     |    | - hourlyRate: double |
  +----------------------+    +----------------------+
  | + getBaseSalary()    |    | + pay(): double      |
  +----------------------+    +----------------------+
             ^
      +------+------+
      |             |
+-------------+ +---------------+
|  Professor  | | LabAssistant  |
+-------------+ +---------------+
| - research  | | + pay()       |
+-------------+ +---------------+
| + pay()     |
+-------------+
```

## Task 1.3: Design Defence
The refactored inheritance hierarchy localizes common attributes and DA computation within `SalariedStaff`. Adding a new staff category (e.g., `AdministrativeOfficer`) requires only subclassing `SalariedStaff` or `Staff` and implementing its unique pay formula, without touching or risking regressions in existing classes (Open-Closed Principle).

## Alternative Concept & Complexity Analysis
- **Monolithic Class with `switch`**:
  - Requires union/superset of all fields (`hours`, `rate`, `research`, `basic`), wasting memory for unused attributes.
  - Adding a staff category requires modifying the central `switch` statement in `pay()`, violating OCP.
- **Complexity**: Both virtual dispatch and switch-based lookup take $O(1)$ time per invocation. Space per object in the hierarchy is minimal and tailored to the subclass.
