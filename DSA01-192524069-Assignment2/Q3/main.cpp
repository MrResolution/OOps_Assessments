#include <iostream>
#include <iomanip>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

long long charge(int weightGrams, bool express = false, bool insured = false) {
    long long cost = (weightGrams * 50) / 100;
    if (express) cost += 1500;
    if (insured) cost += 2500;
    std::cout << "[Overload 1: int weightGrams (" << weightGrams << "g)] -> ";
    return cost;
}

long long charge(double weightKg, bool express = false, bool insured = false) {
    long long cost = static_cast<long long>(weightKg * 50000) / 100;
    if (express) cost += 1500;
    if (insured) cost += 2500;
    std::cout << "[Overload 2: double weightKg (" << weightKg << "kg)] -> ";
    return cost;
}

long long charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    std::cout << "Testing Unambiguous Function Overload Resolution:\n\n";

    long long r1 = charge(2);
    std::cout << "Charge: Rs " << r1 / 100 << "\n";

    long long r2 = charge(2.0f);
    std::cout << "Charge: Rs " << r2 / 100 << "\n";

    long long r3 = charge(3.5);
    std::cout << "Charge: Rs " << r3 / 100 << "\n";

    long long r4 = charge(3.5, true);
    std::cout << "Charge: Rs " << r4 / 100 << "\n";

    long long r5 = charge(3.5, true, true);
    std::cout << "Charge: Rs " << r5 / 100 << "\n";

    Parcel p1{4.2, false, true};
    std::cout << "[Overload 3: Parcel struct] -> ";
    long long r6 = charge(p1);
    std::cout << "Charge: Rs " << r6 / 100 << "\n";

    return 0;
}
