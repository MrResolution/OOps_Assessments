#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

template <size_t CAPACITY>
class ShiftingAccount {
    long long balancePaise;
    long long history[CAPACITY];
    size_t count;

public:
    explicit ShiftingAccount(long long bal) : balancePaise(bal), count(0) {}

    void record(long long tx) {
        if (count < CAPACITY) {
            history[count++] = tx;
        } else {
            for (size_t i = 0; i < CAPACITY - 1; ++i) {
                history[i] = history[i + 1];
            }
            history[CAPACITY - 1] = tx;
        }
    }

    long long getLatest() const {
        return count > 0 ? history[count - 1] : 0;
    }
};

template <size_t CAPACITY>
class CircularAccount {
    long long balancePaise;
    long long history[CAPACITY];
    size_t head;
    size_t count;

public:
    explicit CircularAccount(long long bal) : balancePaise(bal), head(0), count(0) {}

    void record(long long tx) {
        history[head] = tx;
        head = (head + 1) % CAPACITY;
        if (count < CAPACITY) {
            count++;
        }
    }

    long long getLatest() const {
        if (count == 0) return 0;
        size_t lastIdx = (head == 0) ? (CAPACITY - 1) : (head - 1);
        return history[lastIdx];
    }
};

int main() {
    const size_t BUFFER_SIZE = 50;
    const long long TX_COUNT = 1000000LL;

    std::cout << "====================================================================\n";
    std::cout << "       DAY-4 DESIGN CHALLENGE: SHIFTING VS. CIRCULAR BUFFER         \n";
    std::cout << "       Buffer Capacity: " << BUFFER_SIZE << " | Transactions: " << TX_COUNT << "\n";
    std::cout << "====================================================================\n";

    ShiftingAccount<BUFFER_SIZE> shiftingAcc(1000000);
    auto startShift = std::chrono::high_resolution_clock::now();
    for (long long i = 1; i <= TX_COUNT; ++i) {
        shiftingAcc.record(i);
    }
    auto endShift = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> shiftTime = endShift - startShift;

    CircularAccount<BUFFER_SIZE> circularAcc(1000000);
    auto startCirc = std::chrono::high_resolution_clock::now();
    for (long long i = 1; i <= TX_COUNT; ++i) {
        circularAcc.record(i);
    }
    auto endCirc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> circTime = endCirc - startCirc;

    std::cout << "Shifting Buffer Time (O(k)):   " << shiftTime.count() << " ms\n";
    std::cout << "Circular Buffer Time (O(1)):   " << circTime.count() << " ms\n";
    double speedup = shiftTime.count() / circTime.count();
    std::cout << "Speedup Factor:                " << std::fixed << std::setprecision(2) << speedup << "x\n";
    std::cout << "Validation (Latest Tx Match):  " 
              << (shiftingAcc.getLatest() == circularAcc.getLatest() ? "VALIDATED (EQUAL)" : "ERROR") << "\n";
    std::cout << "====================================================================\n";

    return 0;
}
