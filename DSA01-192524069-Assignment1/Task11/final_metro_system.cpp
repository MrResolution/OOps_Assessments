#include <iostream>
#include <iomanip>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };

namespace MetroRules {
    constexpr long long FARES_PAISE[] = {1000, 2000, 3000};
    constexpr int PEAK_SURCHARGE_PCT = 20;
    constexpr long long MIN_BALANCE_PAISE = 5000;
}

class SmartCard {
    long long cardNumber;
    long long balancePaise;

public:
    SmartCard(long long num, long long initialBalance)
        : cardNumber(num), balancePaise(initialBalance) {}

    bool canTravel(long long fare) const {
        return (balancePaise - fare) >= MetroRules::MIN_BALANCE_PAISE;
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

    long long getId() const {
        return cardNumber;
    }
};

class FareEngine {
public:
    static bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long computeFare(Zone z, int hour) {
        int idx = static_cast<int>(z) - 1;
        long long base = MetroRules::FARES_PAISE[idx];
        if (isPeak(hour)) {
            base += (base * MetroRules::PEAK_SURCHARGE_PCT) / 100;
        }
        return base;
    }
};

int main() {
    SmartCard card(882031, 10000);
    int hour = 8;
    Zone zone = Zone::Outer;

    long long fare = FareEngine::computeFare(zone, hour);
    std::cout << "Metro Smart-Card Gate System (Production Design)\n";
    std::cout << "Card ID: " << card.getId() << "\n";
    std::cout << "Current Balance: Rs " << card.getBalance() / 100 << "." 
              << std::setfill('0') << std::setw(2) << (card.getBalance() % 100) << "\n";
    std::cout << "Trip Fare: Rs " << fare / 100 << "." 
              << std::setfill('0') << std::setw(2) << (fare % 100) << "\n";

    if (card.deduct(fare)) {
        std::cout << "Transaction Approved. New Balance: Rs " << card.getBalance() / 100 << "."
                  << std::setfill('0') << std::setw(2) << (card.getBalance() % 100) << "\n";
    } else {
        std::cout << "Transaction Rejected: Insufficient balance to maintain Rs 50.00 minimum.\n";
    }

    return 0;
}
