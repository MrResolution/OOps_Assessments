#include <iomanip>
#include <iostream>
#include <cmath>

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = this->paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = this->paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        this->paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return this->paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return this->paise < other.paise;
    }

    Money operator*(double scalar) const {
        Money result;
        result.paise = static_cast<long long>(std::round(this->paise * scalar));
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long absPaise = std::abs(m.paise);
        if (m.paise < 0) os << "-";
        os << "Rs " << absPaise / 100 << "." 
           << std::setfill('0') << std::setw(2) << (absPaise % 100) << std::setfill(' ');
        return os;
    }
};

int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money p1(0, 75);
    Money p2(0, 50);
    Money carrySum = p1 + p2;
    std::cout << "Carry test (Rs 0.75 + Rs 0.50): " << carrySum << "\n";

    Money sub = a - b;
    std::cout << "Subtraction test (" << a << " - " << b << "): " << sub << "\n";

    Money bill(50, 0);
    bill += Money(25, 50);
    std::cout << "Compound assignment test (bill += Rs 25.50): " << bill << "\n";

    return 0;
}
