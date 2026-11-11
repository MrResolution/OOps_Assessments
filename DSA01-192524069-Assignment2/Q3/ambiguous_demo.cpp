#include <iostream>

void charge(double weight) {
    std::cout << "charge(double): " << weight << "\n";
}

void charge(double weight, bool express) {
    std::cout << "charge(double, bool): " << weight << ", " << express << "\n";
}

void charge(double weight, bool express = false, bool insured = false) {
    std::cout << "charge(double, bool, bool): " << weight << ", " << express << ", " << insured << "\n";
}

int main() {
    charge(5.0);
    return 0;
}
