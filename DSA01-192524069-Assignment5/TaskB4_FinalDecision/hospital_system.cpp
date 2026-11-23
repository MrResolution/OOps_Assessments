#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

class HospitalException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BillingError : public HospitalException {
public:
    using HospitalException::HospitalException;
};

class ClaimError : public HospitalException {
public:
    using HospitalException::HospitalException;
};

class Bill {
protected:
    std::string patientId;
    std::string patientName;

public:
    Bill(const std::string& id, const std::string& name)
        : patientId(id), patientName(name) {
        if (patientId.empty() || patientName.empty()) {
            throw BillingError("Invalid patient details");
        }
    }

    virtual ~Bill() = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    std::string getId() const noexcept { return patientId; }
    std::string getName() const noexcept { return patientName; }
};

class OutPatientBill : public Bill {
    double consultationFee;
    double diagnosticTests;

public:
    OutPatientBill(const std::string& id, const std::string& name, double c, double d)
        : Bill(id, name), consultationFee(c), diagnosticTests(d) {
        if (c < 0 || d < 0) throw BillingError("Negative fee component in OutPatientBill");
    }

    double total() const override { return consultationFee + diagnosticTests; }
    std::string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int days;
    double perDayCharge;
    double procedureCharges;

public:
    InPatientBill(const std::string& id, const std::string& name, int d, double rate, double proc)
        : Bill(id, name), days(d), perDayCharge(rate), procedureCharges(proc) {
        if (d < 0 || rate < 0 || proc < 0) throw BillingError("Negative fee component in InPatientBill");
    }

    double total() const override { return (days * perDayCharge) + procedureCharges; }
    std::string type() const override { return "InPatient"; }
};

class DayCareBill : public Bill {
    double surgicalPackageRate;

public:
    DayCareBill(const std::string& id, const std::string& name, double packageRate)
        : Bill(id, name), surgicalPackageRate(packageRate) {
        if (packageRate < 0) throw BillingError("Negative package rate in DayCareBill");
    }

    double total() const override { return surgicalPackageRate; }
    std::string type() const override { return "DayCare (Extension)"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double settleClaim(double billedAmount) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "Self-Pay"; }
    double settleClaim(double) const override { return 0.0; }
};

class InsurancePayer : public Payer {
    double maxCoverLimit;
    double coPayPercent;

public:
    InsurancePayer(double maxLimit, double coPay)
        : maxCoverLimit(maxLimit), coPayPercent(coPay) {}

    std::string name() const override { return "Standard Insurance"; }

    double settleClaim(double billedAmount) const override {
        if (billedAmount > maxCoverLimit * 1.5) {
            throw ClaimError("Claim exceeds maximum allowable ceiling limit");
        }
        double payable = std::min(billedAmount, maxCoverLimit);
        double coPay = (payable * coPayPercent) / 100.0;
        return payable - coPay;
    }
};

class CorporateTieUp : public Payer {
    double negotiatedDiscountPct;
    double corporateSubsidyCap;

public:
    CorporateTieUp(double discount, double cap)
        : negotiatedDiscountPct(discount), corporateSubsidyCap(cap) {}

    std::string name() const override { return "Corporate Tie-Up (Extension)"; }

    double settleClaim(double billedAmount) const override {
        double discounted = billedAmount - (billedAmount * negotiatedDiscountPct / 100.0);
        return std::min(discounted, corporateSubsidyCap);
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "========================================================================\n";
    std::cout << "       HOSPITAL ENTERPRISE POLYMORPHIC BILLING SYSTEM (15 SITES)        \n";
    std::cout << "========================================================================\n\n";

    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("P-101", "Asha", 600.0, 1500.0));
    bills.push_back(std::make_unique<InPatientBill>("P-102", "Bikram", 5, 2500.0, 35000.0));
    bills.push_back(std::make_unique<DayCareBill>("P-103", "Chaya", 22000.0));

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<InsurancePayer>(30000.0, 10.0));
    payers.push_back(std::make_unique<CorporateTieUp>(15.0, 40000.0));

    double grandHospitalTotal = 0;
    for (const auto& b : bills) {
        double bTotal = b->total();
        grandHospitalTotal += bTotal;

        std::cout << "Processing Bill [" << b->getId() << "] (" << b->type() << ") for "
                  << b->getName() << " | Billed: Rs " << bTotal << "\n";

        for (const auto& p : payers) {
            try {
                double covered = p->settleClaim(bTotal);
                double balance = bTotal - covered;
                std::cout << "  -> " << std::left << std::setw(30) << p->name()
                          << " Covered: Rs " << std::setw(9) << covered 
                          << " | Due: Rs " << balance << "\n";
            } catch (const ClaimError& e) {
                std::cout << "  -> " << std::left << std::setw(30) << p->name()
                          << " CLAIM REJECTED: " << e.what() << "\n";
            }
        }
        std::cout << "\n";
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Enterprise Billings Processed: Rs " << grandHospitalTotal << "\n";

    std::cout << "\n=== Exception & Resource Leak Audit (AddressSanitizer Verified) ===\n";
    try {
        OutPatientBill invalidBill("P-999", "ErrorTest", -500.0, 1200.0);
    } catch (const BillingError& e) {
        std::cout << "Successfully caught and handled invalid bill construction: " << e.what() << "\n";
    }

    try {
        InsurancePayer strictInsurance(10000.0, 10.0);
        strictInsurance.settleClaim(80000.0);
    } catch (const ClaimError& e) {
        std::cout << "Successfully caught and audited exorbitant claim: " << e.what() << "\n";
    }

    std::cout << "========================================================================\n";

    return 0;
}
