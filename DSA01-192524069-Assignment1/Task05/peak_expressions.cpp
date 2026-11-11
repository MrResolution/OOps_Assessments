#include <iostream>

bool isPeakExpression(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

constexpr bool PEAK_TABLE[24] = {
    false, false, false, false, false, false, false, false,
    true,  true,  false, false, false, false, false, false,
    false, true,  true,  true,  false, false, false, false
};

bool isPeakLookup(int hour) {
    if (hour < 0 || hour >= 24) return false;
    return PEAK_TABLE[hour];
}

int main() {
    int testHours[] = {7, 8, 9, 10, 16, 17, 19, 20};
    for (int h : testHours) {
        std::cout << "Hour " << h << " -> Expression: " << (isPeakExpression(h) ? "Peak" : "Off-Peak")
                  << " | Lookup: " << (isPeakLookup(h) ? "Peak" : "Off-Peak") << "\n";
    }
    return 0;
}
