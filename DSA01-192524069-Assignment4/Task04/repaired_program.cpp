#include <iostream>
#include <vector>
#include <memory>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { std::cout << "~Account (Virtual Base Destructor)\n"; }
};

class SeniorAccount : public Account {
    double* history;

public:
    SeniorAccount() : history(new double[100]{}) {}

    double rate() const override { return 4.0; }

    ~SeniorAccount() override {
        std::cout << "~SeniorAccount (Virtual Derived Destructor: Releasing history)\n";
        delete[] history;
    }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    std::cout << "Polymorphic Account Processing:\n";
    for (const auto& a : accounts) {
        std::cout << "Interest Rate: " << a->rate() << "%\n";
    }

    std::cout << "\nReleasing Accounts Safely via Virtual Destructors:\n";
    accounts.clear();

    return 0;
}
