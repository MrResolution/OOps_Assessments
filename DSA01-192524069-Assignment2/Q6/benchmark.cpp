#include <iostream>
#include <chrono>
#include <cmath>

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

#ifdef USE_INLINE
inline int minutesBetween(const Time& a, const Time& b)
#else
int minutesBetween(const Time& a, const Time& b)
#endif
{
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
}

#ifdef USE_INLINE
inline bool earlier(const Time& a, const Time& b)
#else
bool earlier(const Time& a, const Time& b)
#endif
{
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

int main() {
    Time t1(8, 30), t2(17, 45);
    const long long ITERATIONS = 10000000LL;

    auto start = std::chrono::high_resolution_clock::now();
    long long checksum = 0;
    for (long long i = 0; i < ITERATIONS; ++i) {
        checksum += minutesBetween(t1, t2);
        if (earlier(t1, t2)) checksum++;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "10,000,000 calls completed in: " << elapsed.count() << " ms (Checksum: " << checksum << ")\n";

    return 0;
}
