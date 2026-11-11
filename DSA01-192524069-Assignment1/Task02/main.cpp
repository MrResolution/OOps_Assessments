#include <iostream>

enum class Zone {
    Inner,
    Middle,
    Outer
};

namespace MetroConfig {
    constexpr long long FARE_INNER_PAISE = 1000;
    constexpr long long FARE_MIDDLE_PAISE = 2000;
    constexpr long long FARE_OUTER_PAISE = 3000;
    constexpr int PEAK_SURCHARGE_PERCENT = 20;
    constexpr long long MIN_REQUIRED_BALANCE_PAISE = 5000;
}

constexpr long long getZoneBaseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return MetroConfig::FARE_INNER_PAISE;
        case Zone::Middle: return MetroConfig::FARE_MIDDLE_PAISE;
        case Zone::Outer:  return MetroConfig::FARE_OUTER_PAISE;
    }
    return 0;
}

int main() {
    constexpr Zone selectedZone = Zone::Outer;
    constexpr long long baseFare = getZoneBaseFare(selectedZone);
    constexpr long long peakFare = baseFare + (baseFare * MetroConfig::PEAK_SURCHARGE_PERCENT) / 100;

    std::cout << "Base Fare (Outer): Rs " << baseFare / 100 << "\n";
    std::cout << "Peak Surcharge: " << MetroConfig::PEAK_SURCHARGE_PERCENT << "%\n";
    std::cout << "Peak Fare: Rs " << peakFare / 100 << "." << (peakFare % 100) << "\n";
    std::cout << "Minimum Required Balance: Rs " << MetroConfig::MIN_REQUIRED_BALANCE_PAISE / 100 << "\n";

    return 0;
}
