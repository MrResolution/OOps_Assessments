#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class StudentReorder {
    long long regNo;
    Address home;

public:
    StudentReorder(long long r, const std::string& c, int p)
        : home(c, p), regNo(r) {}

    void print() const {
        std::cout << regNo << " " << home.str() << "\n";
    }
};

int main() {
    StudentReorder s(192311001, "Salem", 636001);
    s.print();
    return 0;
}
