# Task 8: Read and Print Data Safely

## 1. Stream Recovery Mechanism
- When non-numeric characters are entered into an integer stream extraction (`std::cin >> val`), the stream sets `std::ios_base::failbit`.
- If unhandled, future read attempts immediately fail without waiting for user input, causing infinite loops.
- **Recovery Pattern**:
  1. Detect failure via `if (std::cin.fail())` or `if (!(std::cin >> val))`.
  2. Reset stream error state using `std::cin.clear()`.
  3. Flush remaining invalid characters from the buffer up to newline using `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')`.

## 2. Formatting Currency and Reports
- Formatted alignment and monetary decimal precision using `<iomanip>`:
  - `std::setw(20)`: Column width spacing.
  - `std::left`: Left-justification of labels.
  - `std::setfill('0')` and `std::setw(2)`: Zero-padded minutes and paise.

## 3. Alternative Input Processing & Complexity
- **`std::cin >>`**: In-place extraction directly parses stream buffer ($O(L)$ time for line length $L$, $O(1)$ memory).
- **`std::getline()` with `std::stoi()`**: Reads entire line into `std::string` buffer ($O(L)$ space), parsing within `try-catch` blocks.
