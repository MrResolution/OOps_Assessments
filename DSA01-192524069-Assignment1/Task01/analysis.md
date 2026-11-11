# Task 1: Object-Oriented Analysis

## 1. Identified Entities & Responsibilities
- **SmartCard**: Encapsulates card balance and identity. Guarantees balance never drops below the Rs 50 minimum threshold.
- **FareTable**: Encapsulates zone pricing and peak surcharge computations.
- **Journey**: Represents a passenger transit event with zone and departure hour.
- **Zone**: Scoped enumeration defining valid transit boundaries.

## 2. Procedural vs. Object-Oriented Comparison
- **Procedural Approach**: Relies on global state and free functions. Any function can directly mutate balance variables, risking negative balance errors.
- **Object-Oriented Approach**: Private member variables ensure invariant enforcement (`canTravel`, `deduct`). Modification of minimum balance or fare rules is localized without ripple effects.

## 3. Complexity Analysis
- **Time Complexity**: $O(1)$ lookup and deduction per journey in both procedural and OOP implementations.
- **Space Complexity**: $O(1)$ per card instance (holding balance and ID).
