#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;

    virtual double pay() const = 0;

    std::string getName() const { return name; }
    int getId() const { return id; }
};

class SalariedStaff : public Staff {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    SalariedStaff(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double getBaseSalary() const {
        return basic + (basic * DA_RATE);
    }
};

class Professor : public SalariedStaff {
    double researchAllowance;

public:
    Professor(const std::string& n, int i, double b, double r)
        : SalariedStaff(n, i, b), researchAllowance(r) {}

    double pay() const override {
        return getBaseSalary() + researchAllowance;
    }
};

class LabAssistant : public SalariedStaff {
public:
    LabAssistant(const std::string& n, int i, double b)
        : SalariedStaff(n, i, b) {}

    double pay() const override {
        return getBaseSalary();
    }
};

class GuestFaculty : public Staff {
    double hours;
    double hourlyRate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i), hours(h), hourlyRate(r) {}

    double pay() const override {
        return hours * hourlyRate;
    }
};

int main() {
    std::vector<Staff*> collegeStaff = {
        new Professor("Dr. Aris", 101, 80000, 15000),
        new LabAssistant("Bala", 102, 35000),
        new GuestFaculty("Chitra", 103, 40, 1200)
    };

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "====================================================\n";
    std::cout << "           COLLEGE PAYROLL REFACTORED               \n";
    std::cout << "====================================================\n";

    double totalPayroll = 0;
    for (const Staff* s : collegeStaff) {
        double p = s->pay();
        totalPayroll += p;
        std::cout << "ID: " << s->getId() << " | Name: " << std::left << std::setw(12) 
                  << s->getName() << " | Monthly Pay: Rs " << p << "\n";
    }

    std::cout << "----------------------------------------------------\n";
    std::cout << "Total Monthly Payroll Expenditure: Rs " << totalPayroll << "\n";
    std::cout << "====================================================\n";

    for (Staff* s : collegeStaff) {
        delete s;
    }

    return 0;
}
