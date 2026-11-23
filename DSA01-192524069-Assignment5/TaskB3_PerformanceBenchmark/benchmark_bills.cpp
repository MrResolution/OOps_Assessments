#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

class VBill {
public:
    virtual ~VBill() = default;
    virtual double total() const = 0;
};

class VOutPatient : public VBill {
    double fee;
public:
    explicit VOutPatient(double f) : fee(f) {}
    double total() const override { return fee; }
};

class VInPatient : public VBill {
    double fee;
public:
    explicit VInPatient(double f) : fee(f) {}
    double total() const override { return fee; }
};

enum class BillType { OP, IP };

struct SBill {
    BillType type;
    double fee;

    double total() const {
        switch (type) {
            case BillType::OP: return fee;
            case BillType::IP: return fee;
        }
        return 0;
    }
};

void runBenchmark(long long count) {
    std::cout << "\n--- Scale: " << count << " Bills ---\n";

    VOutPatient op(1500.0);
    VInPatient ip(45000.0);
    VBill* vlist[2] = { &op, &ip };

    auto s1 = std::chrono::high_resolution_clock::now();
    double vSum = 0;
    for (long long i = 0; i < count; ++i) {
        vSum += vlist[i % 2]->total();
    }
    auto e1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vTime = e1 - s1;

    SBill s1_bill{BillType::OP, 1500.0};
    SBill s2_bill{BillType::IP, 45000.0};
    SBill slist[2] = { s1_bill, s2_bill };

    auto s2_time = std::chrono::high_resolution_clock::now();
    double sSum = 0;
    for (long long i = 0; i < count; ++i) {
        sSum += slist[i % 2].total();
    }
    auto e2_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> sTime = e2_time - s2_time;

    std::cout << "Virtual Dispatch: " << vTime.count() << " ms | Sum = Rs " << vSum << "\n";
    std::cout << "Switch Dispatch:  " << sTime.count() << " ms | Sum = Rs " << sSum << "\n";
    std::cout << "Totals Equal?     " << (vSum == sSum ? "YES (VERIFIED)" : "NO") << "\n";
}

int main() {
    std::cout << "=================================================================\n";
    std::cout << "     BENCHMARK: VIRTUAL DISPATCH VS SWITCH (COMPILED -O2)        \n";
    std::cout << "=================================================================\n";

    long long scales[] = {1000, 1000000, 10000000};
    for (long long n : scales) {
        runBenchmark(n);
    }

    return 0;
}
