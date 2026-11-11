#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };

long long getFare(Zone z, bool peak) {
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = 1000; break;
        case Zone::Middle: base = 2000; break;
        case Zone::Outer:  base = 3000; break;
    }
    return peak ? (base + (base * 20) / 100) : base;
}

int readSafeInt(const std::string& prompt, int minVal, int maxVal) {
    int val = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            if (val >= minVal && val <= maxVal) {
                return val;
            }
            std::cout << "Error: Value must be between " << minVal << " and " << maxVal << ".\n";
        } else {
            std::cout << "Error: Invalid input. Numerical entry required.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    std::cout << "========================================\n";
    std::cout << "      NAMMA METRO GATE CONTROLLER       \n";
    std::cout << "========================================\n";

    int zoneNum = readSafeInt("Enter Destination Zone (1=Inner, 2=Middle, 3=Outer): ", 1, 3);
    int hour = readSafeInt("Enter Journey Hour (0 to 23): ", 0, 23);

    Zone zone = static_cast<Zone>(zoneNum);
    bool isPeak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long farePaise = getFare(zone, isPeak);

    std::cout << "\n----------------------------------------\n";
    std::cout << "             JOURNEY TICKET             \n";
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(20) << "Zone Category:" 
              << (zoneNum == 1 ? "Inner" : (zoneNum == 2 ? "Middle" : "Outer")) << "\n";
    std::cout << std::left << std::setw(20) << "Departure Time:" 
              << std::setfill('0') << std::setw(2) << hour << ":00" << std::setfill(' ') << "\n";
    std::cout << std::left << std::setw(20) << "Surcharge Rate:" 
              << (isPeak ? "20% (Peak Surcharge)" : "0% (Regular)") << "\n";
    std::cout << std::left << std::setw(20) << "Calculated Fare:" 
              << "Rs " << farePaise / 100 << "." 
              << std::setfill('0') << std::setw(2) << (farePaise % 100) << std::setfill(' ') << "\n";
    std::cout << "----------------------------------------\n";

    return 0;
}
