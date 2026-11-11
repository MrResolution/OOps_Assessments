# Q3: Dynamic Constructors and Destructors

## 1. Output Prediction and Actual Output

### Predicted Output:
```text
+A +B -B copyAc use -Ac +P -P end -A 
```

### Actual Output:
```text
+A +B -B copyAc use -Ac +P -P end -A 
```

## 2. Object Lifecycle Tracing
1. `Logger a("A")`: Constructs `a` on the stack (`+A`).
2. Local Block `{ Logger b("B"); }`: Enters block, constructs `b` (`+B`), exits block, destroys `b` (`-B`).
3. `use(a)`: Takes parameter by value. Calls copy constructor (`copyAc`). Function runs (`use`). Parameter temporary goes out of scope and is destroyed (`-Ac`).
4. `Logger* p = new Logger("P")`: Allocates on heap (`+P`).
5. `delete p`: Explicitly frees heap object and triggers destructor (`-P`).
6. `std::cout << "end "`: Prints `end`.
7. `main` returns: Destroys stack object `a` (`-A`).

## 3. Dynamic 2D Matrix Allocation & RAII
- **Two-Tiered Allocation**:
  1. Primary row pointer array: `seats = new char*[rows];`
  2. Nested row buffers: `for (int i = 0; i < rows; ++i) seats[i] = new char[cols];`
- **Strict Destruction Order**:
  - Destructor must free each row array (`delete[] seats[i]`) before releasing the top-level pointer array (`delete[] seats`). Reversing this order or omitting inner deletions causes memory leaks caught by AddressSanitizer.
- **Complexity**: Allocation and deallocation require $O(rows)$ operations; accessing any seat `seats[r][c]` is $O(1)$.
