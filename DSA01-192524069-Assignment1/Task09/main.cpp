#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3, Invalid = 99 };

constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long computeFare(Zone z, int hour) {
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = 1000; break;
        case Zone::Middle: base = 2000; break;
        case Zone::Outer:  base = 3000; break;
        default:           return -1;
    }
    if (isPeakHour(hour)) {
        base += (base * 20) / 100;
    }
    return base;
}

struct TestCase {
    std::string description;
    Zone zone;
    int hour;
    long long initialBalance;
    long long expectedFare;
    bool expectedAllowed;
    long long expectedFinalBalance;
};

int main() {
    std::vector<TestCase> testCases = {
        {"Zone 1 Off-Peak", Zone::Inner, 12, 10000, 1000, true, 9000},
        {"Zone 2 Off-Peak", Zone::Middle, 14, 10000, 2000, true, 8000},
        {"Zone 3 Off-Peak", Zone::Outer, 15, 10000, 3000, true, 7000},
        {"Zone 1 Peak", Zone::Inner, 9, 10000, 1200, true, 8800},
        {"Zone 2 Peak", Zone::Middle, 18, 10000, 2400, true, 7600},
        {"Zone 3 Peak", Zone::Outer, 8, 10000, 3600, true, 6400},
        {"Boundary 8:00 AM (Peak)", Zone::Inner, 8, 10000, 1200, true, 8800},
        {"Boundary 10:00 AM (Off-Peak)", Zone::Inner, 10, 10000, 1000, true, 9000},
        {"Boundary 17:00 (Peak)", Zone::Inner, 17, 10000, 1200, true, 8800},
        {"Boundary 20:00 (Off-Peak)", Zone::Inner, 20, 10000, 1000, true, 9000},
        {"Exact Rs 50 Remaining", Zone::Inner, 12, 6000, 1000, true, 5000},
        {"Low Balance (1 Paisa Short)", Zone::Inner, 12, 5999, 1000, false, 5999},
        {"Invalid Zone Check", Zone::Invalid, 12, 10000, -1, false, 10000}
    };

    std::cout << std::left << std::setw(30) << "Test Case"
              << std::setw(15) << "Exp Fare"
              << std::setw(15) << "Act Fare"
              << std::setw(15) << "Exp Allowed"
              << std::setw(15) << "Act Allowed"
              << std::setw(10) << "Result" << "\n";
    std::cout << std::string(100, '-') << "\n";

    int passed = 0;
    for (const auto& tc : testCases) {
        long long fare = computeFare(tc.zone, tc.hour);
        bool allowed = false;
        long long finalBal = tc.initialBalance;

        if (fare > 0 && (tc.initialBalance - fare) >= MIN_BALANCE_PAISE) {
            allowed = true;
            finalBal -= fare;
        }

        bool fareMatch = (fare == tc.expectedFare);
        bool allowedMatch = (allowed == tc.expectedAllowed);
        bool balanceMatch = (finalBal == tc.expectedFinalBalance);
        bool testPass = fareMatch && allowedMatch && balanceMatch;

        if (testPass) ++passed;

        std::cout << std::left << std::setw(30) << tc.description
                  << std::setw(15) << tc.expectedFare
                  << std::setw(15) << fare
                  << std::setw(15) << (tc.expectedAllowed ? "true" : "false")
                  << std::setw(15) << (allowed ? "true" : "false")
                  << std::setw(10) << (testPass ? "PASS" : "FAIL") << "\n";
    }

    std::cout << std::string(100, '-') << "\n";
    std::cout << "Summary: " << passed << " / " << testCases.size() << " Tests Passed.\n";

    return 0;
}
