#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

class Bill {
protected:
    std::string patient;

public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    std::string getPatient() const { return patient; }
};

class OutPatient : public Bill {
    double consultation, tests;

public:
    OutPatient(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}

    double total() const override { return consultation + tests; }
    std::string type() const override { return "OutPatient"; }
};

class InPatient : public Bill {
    int days;
    double perDay, surgery;

public:
    InPatient(const std::string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {}

    double total() const override { return (days * perDay) + surgery; }
    std::string type() const override { return "InPatient"; }
};

class DayCareSurgery : public Bill {
    double packageRate;

public:
    DayCareSurgery(const std::string& p, double rate)
        : Bill(p), packageRate(rate) {}

    double total() const override { return packageRate; }
    std::string type() const override { return "DayCareSurgery"; }
};

class EmergencyBill : public Bill {
    double baseFee;
    double hours;
    double hourlyRate;

public:
    EmergencyBill(const std::string& p, double base, double h, double rate)
        : Bill(p), baseFee(base), hours(h), hourlyRate(rate) {}

    double total() const override { return baseFee + (hours * hourlyRate); }
    std::string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double calculateCoverage(double billTotal) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "Self-Pay"; }
    double calculateCoverage(double) const override { return 0.0; }
};

class Insurance : public Payer {
    double maxCover;
    double coPayPct;

public:
    Insurance(double cover, double copay) : maxCover(cover), coPayPct(copay) {}

    std::string name() const override { return "Private Insurance"; }

    double calculateCoverage(double billTotal) const override {
        double eligible = std::min(billTotal, maxCover);
        double patientCoPay = (eligible * coPayPct) / 100.0;
        return eligible - patientCoPay;
    }
};

class GovernmentScheme : public Payer {
    double packageCap;

public:
    explicit GovernmentScheme(double cap) : packageCap(cap) {}

    std::string name() const override { return "Government Scheme"; }

    double calculateCoverage(double billTotal) const override {
        return std::min(billTotal, packageCap);
    }
};

int main() {
    std::vector<Bill*> bills = {
        new OutPatient("Arjun", 600, 1400),
        new InPatient("Bhavna", 4, 3000, 25000),
        new DayCareSurgery("Chetan", 18000),
        new EmergencyBill("Deepa", 2000, 5, 800)
    };

    std::vector<Payer*> payers = {
        new SelfPay(),
        new Insurance(30000, 10),
        new GovernmentScheme(20000)
    };

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "========================================================================================\n";
    std::cout << "                   HOSPITAL BILLING & CLAIMS SETTLEMENT MATRIX                          \n";
    std::cout << "========================================================================================\n";

    for (const auto* b : bills) {
        double t = b->total();
        std::cout << "\nBill: [" << b->type() << "] Patient: " << b->getPatient() 
                  << " | Total Billed: Rs " << t << "\n";
        std::cout << std::string(88, '-') << "\n";

        for (const auto* p : payers) {
            double covered = p->calculateCoverage(t);
            double patientLiability = t - covered;
            std::cout << "  Payer: " << std::left << std::setw(22) << p->name()
                      << " | Covered: Rs " << std::setw(10) << covered
                      << " | Patient Due: Rs " << patientLiability << "\n";
        }
    }

    std::cout << "========================================================================================\n";

    for (auto* b : bills) delete b;
    for (auto* p : payers) delete p;

    return 0;
}
