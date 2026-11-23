# Task 2: From Requirement to Hierarchy – University People Management

## Task 2.1: Relationship & Inheritance Classification
- **`Student` is-a `Person`**: Hierarchical / Single inheritance.
- **`Staff` is-a `Person`**: Hierarchical / Single inheritance.
- **`TeachingAssistant` is-a `Student` AND is-a `Staff`**: Multiple inheritance (forming Diamond / Hybrid inheritance).
- **`ResearchScholar` is-a `Student`**: Multilevel inheritance (`Person` $\rightarrow$ `Student` $\rightarrow$ `ResearchScholar`).

## Task 2.2: Resolving the Diamond Problem with Virtual Base Classes
- **The Diamond Problem**: When `TeachingAssistant` derives from both `Student` and `Staff`, two distinct copies of `Person` are inherited. This creates ambiguity when accessing members like `name` or `id` (`ta.name` is ambiguous: `Student::Person::name` vs `Staff::Person::name`).
- **Resolution**: Marking `Person` as a `virtual` base class (`class Student : virtual public Person` and `class Staff : virtual public Person`) ensures that only **one shared instance** of `Person` is embedded in `TeachingAssistant`.
- In virtual inheritance, the most-derived class constructor (`TeachingAssistant`) is directly responsible for constructing the virtual base (`Person`).

## Task 2.3 & 2.4: Inheritance Access Table
How members of base class `Person` are visible in derived class `Student`:

| Member in Base (`Person`) | `public` Inheritance | `protected` Inheritance | `private` Inheritance |
| :--- | :--- | :--- | :--- |
| **`public` member** | `public` in derived | `protected` in derived | `private` in derived |
| **`protected` member** | `protected` in derived | `protected` in derived | `private` in derived |
| **`private` member** | Hidden / Inaccessible | Hidden / Inaccessible | Hidden / Inaccessible |

## Prediction and Observed Output
- **With `virtual`**:
  ```text
  Person Student Staff TA
  ```
  `Person` is constructed once by `TeachingAssistant`.
- **Without `virtual`**:
  ```text
  Person Student Person Staff TA
  ```
  `Student` constructs its own `Person`, and `Staff` constructs another separate `Person`.

## Alternative Concept & Complexity
- **Composition (Has-a)**: `TeachingAssistant` holds `Student` and `Staff` member instances. Eliminates diamond virtual pointer overhead, but breaks substitutability (`TeachingAssistant` is no longer a `Person` pointer).
- Reaching `name` in virtual inheritance requires offset resolution through the vtable ($O(1)$ time).
