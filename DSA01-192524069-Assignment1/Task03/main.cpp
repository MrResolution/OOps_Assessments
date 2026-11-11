#include <iostream>
#include <climits>
#include <iomanip>

int main() {
    std::cout << "Data Type Sizes and Ranges:\n";
    std::cout << "sizeof(bool):        " << sizeof(bool) << " byte\n";
    std::cout << "sizeof(char):        " << sizeof(char) << " byte\n";
    std::cout << "sizeof(int):         " << sizeof(int) << " bytes [Min: " << INT_MIN << ", Max: " << INT_MAX << "]\n";
    std::cout << "sizeof(unsigned int):" << sizeof(unsigned int) << " bytes [Max: " << UINT_MAX << "]\n";
    std::cout << "sizeof(long long):   " << sizeof(long long) << " bytes [Min: " << LLONG_MIN << ", Max: " << LLONG_MAX << "]\n";
    std::cout << "sizeof(float):       " << sizeof(float) << " bytes\n";
    std::cout << "sizeof(double):      " << sizeof(double) << " bytes\n";

    long long networkJourneys = 3000000LL;
    long long avgFarePaise = 2500LL;
    long long totalRevenuePaise = networkJourneys * avgFarePaise;
    long long totalRevenueRupees = totalRevenuePaise / 100;

    std::cout << "\nDaily Network Revenue Analysis (3,000,000 journeys):\n";
    std::cout << "Total Revenue in Paise:  " << totalRevenuePaise << " paise\n";
    std::cout << "Total Revenue in Rupees: Rs " << totalRevenueRupees << "\n";
    std::cout << "INT_MAX:                 " << INT_MAX << "\n";
    std::cout << "Int Overflow in Paise?   " << (totalRevenuePaise > INT_MAX ? "YES (Overflows standard 32-bit int)" : "NO") << "\n";

    double fareDouble = 10.30;
    double sumDouble = 0.0;
    long long farePaise = 1030;
    long long sumPaise = 0;

    for (int i = 0; i < 1000000; ++i) {
        sumDouble += fareDouble;
        sumPaise += farePaise;
    }

    std::cout << "\nPrecision Drift Demonstration (1,000,000 additions of Rs 10.30):\n";
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Double Sum:           " << sumDouble << " rupees\n";
    std::cout << "Exact Integer Paise:  " << sumPaise / 100.0 << " rupees (" << sumPaise << " paise)\n";
    std::cout << "Absolute Discrepancy: " << std::abs(sumDouble - (sumPaise / 100.0)) << " rupees\n";

    return 0;
}
