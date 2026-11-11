#include <iostream>
#include <string>

enum class Zone {
    Inner,
    Middle,
    Outer
};

class SmartCard {
    long long balancePaise;
    long long cardNumber;

public:
    SmartCard(long long num, long long initialBalancePaise)
        : balancePaise(initialBalancePaise), cardNumber(num) {}

    bool canTravel(long long farePaise) const {
        return (balancePaise - farePaise) >= 5000;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) {
            return false;
        }
        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const {
        return balancePaise;
    }

    long long getCardNumber() const {
        return cardNumber;
    }
};

class FareTable {
public:
    static constexpr long long getBaseFare(Zone z) {
        switch (z) {
            case Zone::Inner:  return 1000;
            case Zone::Middle: return 2000;
            case Zone::Outer:  return 3000;
        }
        return 0;
    }

    static long long calculateFare(Zone z, bool isPeak) {
        long long base = getBaseFare(z);
        if (isPeak) {
            base += (base * 20) / 100;
        }
        return base;
    }
};

class Journey {
    Zone zone;
    int hour;
    bool peak;

public:
    Journey(Zone z, int h) : zone(z), hour(h) {
        peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    bool isPeak() const {
        return peak;
    }

    Zone getZone() const {
        return zone;
    }

    int getHour() const {
        return hour;
    }
};

int main() {
    SmartCard card(1001, 10000);
    Journey j1(Zone::Outer, 9);

    long long fare = FareTable::calculateFare(j1.getZone(), j1.isPeak());
    std::cout << "Card: " << card.getCardNumber() << "\n";
    std::cout << "Initial Balance: Rs " << card.getBalance() / 100 << "\n";
    std::cout << "Journey Zone: Outer, Hour: " << j1.getHour() << " (Peak: " << (j1.isPeak() ? "Yes" : "No") << ")\n";
    std::cout << "Calculated Fare: Rs " << fare / 100 << "." << (fare % 100) << "\n";

    if (card.deduct(fare)) {
        std::cout << "Status: Success | Remaining Balance: Rs " << card.getBalance() / 100 << "\n";
    } else {
        std::cout << "Status: Denied (Low Balance)\n";
    }

    return 0;
}
