#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>

struct SimulationResult {
    long long count;
    int intPaiseTotal;
    long long longPaiseTotal;
    double doubleRupeeTotal;
    double driftRupees;
    bool intOverflowed;
};

SimulationResult runSimulation(long long journeyCount) {
    long long farePaisePattern[3] = {1000, 2400, 3600};
    double fareRupeePattern[3] = {10.0, 24.0, 36.0};

    int intPaise = 0;
    long long longPaise = 0;
    double doubleRupees = 0.0;

    for (long long i = 0; i < journeyCount; ++i) {
        int idx = i % 3;
        intPaise += static_cast<int>(farePaisePattern[idx]);
        longPaise += farePaisePattern[idx];
        doubleRupees += fareRupeePattern[idx];
    }

    double exactRupees = static_cast<double>(longPaise) / 100.0;
    double drift = std::abs(doubleRupees - exactRupees);
    bool overflowed = (longPaise > 2147483647LL) && (intPaise < 0 || intPaise != longPaise);

    return {journeyCount, intPaise, longPaise, doubleRupees, drift, overflowed};
}

int main() {
    long long scales[] = {20000, 500000, 3000000};

    std::cout << "========================================================================================\n";
    std::cout << "                  NAMMA METRO SCALE ACCUMULATION BENCHMARK                              \n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(12) << "Journeys"
              << std::setw(20) << "Int Paise"
              << std::setw(20) << "Long Long Paise"
              << std::setw(20) << "Double Rupees"
              << std::setw(15) << "Int Overflow?" << "\n";
    std::cout << std::string(88, '-') << "\n";

    for (long long n : scales) {
        SimulationResult res = runSimulation(n);
        std::cout << std::left << std::setw(12) << res.count
                  << std::setw(20) << res.intPaiseTotal
                  << std::setw(20) << res.longPaiseTotal
                  << std::fixed << std::setprecision(2) << std::setw(20) << res.doubleRupeeTotal
                  << std::setw(15) << (res.intOverflowed ? "YES (FAILED)" : "No") << "\n";
    }

    std::cout << std::string(88, '-') << "\n";

    return 0;
}
