#include <iostream>

class SmartCard {
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    explicit SmartCard(long long initialBalance) : balancePaise(initialBalance) {}

    bool canTravel(long long fare) const {
        return (balancePaise - fare) >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long fare) {
        if (!canTravel(fare)) {
            return false;
        }
        balancePaise -= fare;
        return true;
    }

    long long getBalance() const {
        return balancePaise;
    }
};

int main() {
    SmartCard card(10000);
    long long fare1 = 3600;
    long long fare2 = 2000;

    std::cout << "Object-Oriented Encapsulated Metro System:\n";
    std::cout << "Initial Balance: Rs " << card.getBalance() / 100 << "\n";

    if (card.deduct(fare1)) {
        std::cout << "Trip 1 Allowed. Balance: Rs " << card.getBalance() / 100 << "\n";
    }

    if (card.deduct(fare2)) {
        std::cout << "Trip 2 Allowed. Balance: Rs " << card.getBalance() / 100 << "\n";
    } else {
        std::cout << "Trip 2 Denied. Insufficient Balance. Current: Rs " << card.getBalance() / 100 << "\n";
    }

    return 0;
}
