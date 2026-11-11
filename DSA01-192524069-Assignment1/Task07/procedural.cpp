#include <iostream>

const long long MIN_BALANCE_PAISE = 5000;

bool canTravelProcedural(long long balance, long long fare) {
    return (balance - fare) >= MIN_BALANCE_PAISE;
}

bool deductProcedural(long long& balance, long long fare) {
    if (!canTravelProcedural(balance, fare)) {
        return false;
    }
    balance -= fare;
    return true;
}

int main() {
    long long balancePaise = 10000;
    long long fare1 = 3600;
    long long fare2 = 2000;

    std::cout << "Procedural Metro System:\n";
    std::cout << "Initial Balance: Rs " << balancePaise / 100 << "\n";

    if (deductProcedural(balancePaise, fare1)) {
        std::cout << "Trip 1 Allowed. Balance: Rs " << balancePaise / 100 << "\n";
    }

    if (deductProcedural(balancePaise, fare2)) {
        std::cout << "Trip 2 Allowed. Balance: Rs " << balancePaise / 100 << "\n";
    } else {
        std::cout << "Trip 2 Denied. Insufficient Balance. Current: Rs " << balancePaise / 100 << "\n";
    }

    balancePaise = -1500;
    std::cout << "Vulnerability Demonstration: Unprotected balance modified directly to Rs " << balancePaise / 100 << "\n";

    return 0;
}
