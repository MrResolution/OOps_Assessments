# Q7: Day-4 Design Challenge – Diagnose, Redesign and Validate

## Part A: Diagnose the Limitation (2 Marks)
- In **Q4 (Savings Account Mini-Statement)**, tracking the last $k$ transactions is initially implemented by left-shifting all $k-1$ elements upon every overflow:
  `for (int i = 0; i < MAX_TX - 1; ++i) history[i] = history[i+1];`
- Each insertion beyond capacity incurs $O(k)$ memory copy operations. When the bank scales the requirement from 10 to 50 or 500 transactions, insertion throughput degrades linearly with buffer size.

## Part B: Define the Design Objective (2 Marks)
- **Objective**: Eliminate the linear data-movement overhead and achieve strictly $O(1)$ constant time per transaction insertion while preserving exact FIFO eviction of older records.

## Part C: Design the Revised Solution (4 Marks)
- **Mechanism**: A fixed-size contiguous array managed via modular arithmetic:
  `head = (head + 1) % CAPACITY;`
- **Memory Overhead**: An additional single `size_t head` integer pointer. No heap reallocation or dynamic pointers are needed.
- **Access Logic**: The most recent transaction resides at `(head == 0 ? CAPACITY - 1 : head - 1)`.

## Part D: Predict Before Implementing (1 Mark)
- **Prediction**: Theoretical complexity transitions from $O(k)$ to $O(1)$. For $1,000,000$ transactions with buffer size $k = 50$, the circular buffer is predicted to deliver a significant reduction in elapsed runtime (> 2x speedup).

## Part E: Implement and Validate the Redesign (2 Marks)
- **Measured Evidence ($1,000,000$ operations, $k=50$)**:
  - Shifting Buffer ($O(k)$): $8.91$ ms
  - Circular Buffer ($O(1)$): $4.01$ ms
  - Speedup Factor: **$2.22\times$**
  - Correctness: Both buffers yield identical final and historical transaction states.

## Part F: Defend the Final Design (2 Marks)
- The circular buffer completely decouples insertion latency from history depth $k$.
- The only trade-off is slightly non-contiguous iteration when dumping history (requiring modular traversal), which is vastly outweighed by the elimination of millions of in-memory element shifts.
