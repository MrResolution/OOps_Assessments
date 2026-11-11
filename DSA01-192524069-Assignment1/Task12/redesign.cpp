#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3, Airport = 4 };

enum class DayType { Weekday, Weekend };

namespace MetroConfigV2 {
    constexpr long long FARES_PAISE[] = {1000, 2000, 3000, 6000};
    constexpr int PEAK_SURCHARGE_PCT = 20;
    constexpr int WEEKEND_DISCOUNT_PCT = 10;
    constexpr long long MIN_BALANCE_PAISE = 5000;
}

class FareEngineV2 {
public:
    static bool isPeak(int hour, DayType day) {
        if (day == DayType::Weekend) return false;
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long computeFare(Zone z, int hour, DayType day) {
        int idx = static_cast<int>(z) - 1;
        long long base = MetroConfigV2::FARES_PAISE[idx];

        if (isPeak(hour, day)) {
            base += (base * MetroConfigV2::PEAK_SURCHARGE_PCT) / 100;
        } else if (day == DayType::Weekend) {
            base -= (base * MetroConfigV2::WEEKEND_DISCOUNT_PCT) / 100;
        }
        return base;
    }
};

class Card {
public:
    virtual ~Card() = default;
    virtual bool canTravel(Zone z, int hour, DayType day) const = 0;
    virtual bool processJourney(Zone z, int hour, DayType day, long long& charged) = 0;
    virtual long long getBalance() const = 0;
};

class StoredValueCard : public Card {
    long long balancePaise;

public:
    explicit StoredValueCard(long long bal) : balancePaise(bal) {}

    bool canTravel(Zone z, int hour, DayType day) const override {
        long long fare = FareEngineV2::computeFare(z, hour, day);
        return (balancePaise - fare) >= MetroConfigV2::MIN_BALANCE_PAISE;
    }

    bool processJourney(Zone z, int hour, DayType day, long long& charged) override {
        long long fare = FareEngineV2::computeFare(z, hour, day);
        if (!canTravel(z, hour, day)) {
            charged = 0;
            return false;
        }
        balancePaise -= fare;
        charged = fare;
        return true;
    }

    long long getBalance() const override {
        return balancePaise;
    }
};

class MonthlyPassCard : public Card {
    Zone primaryZone;
    Zone secondaryZone;
    StoredValueCard wallet;

public:
    MonthlyPassCard(Zone z1, Zone z2, long long backupBalance)
        : primaryZone(z1), secondaryZone(z2), wallet(backupBalance) {}

    bool covers(Zone z) const {
        return (z == primaryZone || z == secondaryZone);
    }

    bool canTravel(Zone z, int hour, DayType day) const override {
        if (covers(z)) return true;
        return wallet.canTravel(z, hour, day);
    }

    bool processJourney(Zone z, int hour, DayType day, long long& charged) override {
        if (covers(z)) {
            charged = 0;
            return true;
        }
        return wallet.processJourney(z, hour, day, charged);
    }

    long long getBalance() const override {
        return wallet.getBalance();
    }
};

int main() {
    std::cout << "====================================================================\n";
    std::cout << "     NAMMA METRO DAY-4 DESIGN CHALLENGE: ADAPTED FARE SYSTEM        \n";
    std::cout << "====================================================================\n";

    StoredValueCard standardCard(15000);
    MonthlyPassCard passCard(Zone::Inner, Zone::Middle, 15000);

    struct Scenario {
        std::string desc;
        Zone zone;
        int hour;
        DayType day;
    };

    std::vector<Scenario> scenarios = {
        {"Airport Trip (Weekday Peak 9am): Base Rs 60 + 20% Peak = Rs 72", Zone::Airport, 9, DayType::Weekday},
        {"Airport Trip (Weekend 2pm): Base Rs 60 - 10% Discount = Rs 54", Zone::Airport, 14, DayType::Weekend},
        {"Pass Trip in Inner Zone (Covered by Pass): Unlimited free", Zone::Inner, 9, DayType::Weekday},
        {"Pass Trip to Airport (Not Covered by Pass, deducted from backup wallet)", Zone::Airport, 9, DayType::Weekday}
    };

    for (const auto& s : scenarios) {
        long long charged = 0;
        bool ok = false;
        long long bal = 0;

        if (s.desc.find("Pass Trip") != std::string::npos) {
            ok = passCard.processJourney(s.zone, s.hour, s.day, charged);
            bal = passCard.getBalance();
        } else {
            ok = standardCard.processJourney(s.zone, s.hour, s.day, charged);
            bal = standardCard.getBalance();
        }

        std::cout << "\nScenario: " << s.desc << "\n";
        std::cout << "Status: " << (ok ? "APPROVED" : "DENIED") << "\n";
        std::cout << "Fare Deducted: Rs " << charged / 100 << "." 
                  << std::setfill('0') << std::setw(2) << (charged % 100) << "\n";
        std::cout << "Remaining Wallet Balance: Rs " << bal / 100 << "."
                  << std::setfill('0') << std::setw(2) << (bal % 100) << "\n";
    }

    return 0;
}
