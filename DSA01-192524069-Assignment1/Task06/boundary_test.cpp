#include <iostream>

bool isPeak(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

int main() {
    int testCases[] = {8, 9, 10, 17, 19, 20};
    for (int h : testCases) {
        std::cout << "Time " << h << ":00 -> " << (isPeak(h) ? "PEAK SURCHARGE (20%)" : "OFF-PEAK (REGULAR)") << "\n";
    }
    return 0;
}
