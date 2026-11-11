#include <iostream>
#include <chrono>

struct HeavyCounter {
    long long value;
    int payload[8];

    HeavyCounter() : value(0) {
        for (int i = 0; i < 8; ++i) payload[i] = i;
    }

    HeavyCounter& operator++() {
        ++value;
        return *this;
    }

    HeavyCounter operator++(int) {
        HeavyCounter old = *this;
        ++value;
        return old;
    }
};

int main() {
    const long long N = 10000000LL;

    HeavyCounter c1;
    auto s1 = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; ++i) {
        ++c1;
    }
    auto e1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dPrefix = e1 - s1;

    HeavyCounter c2;
    auto s2 = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; ++i) {
        c2++;
    }
    auto e2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dPostfix = e2 - s2;

    std::cout << "10,000,000 Increments Benchmark:\n";
    std::cout << "Prefix  (++c): " << dPrefix.count() << " ms\n";
    std::cout << "Postfix (c++): " << dPostfix.count() << " ms\n";

    return 0;
}
