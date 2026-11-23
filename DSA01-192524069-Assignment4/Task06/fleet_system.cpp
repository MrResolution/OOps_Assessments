#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Date {
    int day, month, year;

public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
    std::string str() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }
};

class Vehicle {
protected:
    std::string regNumber;
    double dailyRate;
    bool isRented;

public:
    Vehicle(const std::string& reg, double rate)
        : regNumber(reg), dailyRate(rate), isRented(false) {}

    virtual ~Vehicle() = default;

    virtual std::string getType() const = 0;
    virtual double calculateCharge(int daysRented, int lateDays) const = 0;

    bool rentVehicle() {
        if (isRented) return false;
        isRented = true;
        return true;
    }

    bool returnVehicle() {
        if (!isRented) return false;
        isRented = false;
        return true;
    }

    bool getStatus() const { return isRented; }
    std::string getReg() const { return regNumber; }
    double getRate() const { return dailyRate; }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}

    std::string getType() const override { return "Bicycle"; }

    double calculateCharge(int daysRented, int lateDays) const override {
        double base = daysRented * dailyRate;
        double lateFee = lateDays * (dailyRate * 1.5);
        return base + lateFee;
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    Date serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double energyLevel, const Date& serviceDate)
        : Vehicle(reg, rate), fuelOrChargeLevel(energyLevel), serviceDueDate(serviceDate) {}

    Date getServiceDate() const { return serviceDueDate; }
    double getEnergy() const { return fuelOrChargeLevel; }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel, const Date& serviceDate)
        : MotorVehicle(reg, rate, fuel, serviceDate) {}

    std::string getType() const override { return "Two-Wheeler (Motorcycle)"; }

    double calculateCharge(int daysRented, int lateDays) const override {
        double base = daysRented * dailyRate;
        double lateFee = lateDays * (dailyRate * 1.75);
        return base + lateFee;
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double fuel, const Date& serviceDate, int seats)
        : MotorVehicle(reg, rate, fuel, serviceDate), seatingCapacity(seats) {}

    std::string getType() const override { return "Petrol/Diesel Car"; }

    double calculateCharge(int daysRented, int lateDays) const override {
        double base = daysRented * dailyRate;
        double lateFee = lateDays * (dailyRate * 2.0);
        double insuranceSurcharge = daysRented * 200.0;
        return base + lateFee + insuranceSurcharge;
    }
};

class ElectricCar : public Car {
    double batteryCapacityKWh;
    double kwhRate;

public:
    ElectricCar(const std::string& reg, double rate, double chargeLevel,
                const Date& serviceDate, int seats, double batteryKWh, double ratePerKWh)
        : Car(reg, rate, chargeLevel, serviceDate, seats),
          batteryCapacityKWh(batteryKWh), kwhRate(ratePerKWh) {}

    std::string getType() const override { return "Electric Car (EV)"; }

    double calculateCharge(int daysRented, int lateDays) const override {
        double base = daysRented * dailyRate;
        double lateFee = lateDays * (dailyRate * 2.2);
        double energyCharge = batteryCapacityKWh * kwhRate;
        return base + lateFee + energyCharge;
    }
};

class ElectricBus : public MotorVehicle {
    int passengerCapacity;
    double batteryKWh;

public:
    ElectricBus(const std::string& reg, double rate, double chargeLevel,
                const Date& serviceDate, int capacity, double battery)
        : MotorVehicle(reg, rate, chargeLevel, serviceDate),
          passengerCapacity(capacity), batteryKWh(battery) {}

    std::string getType() const override { return "Electric Transit Bus (Extension)"; }

    double calculateCharge(int daysRented, int lateDays) const override {
        double base = daysRented * dailyRate;
        double lateFee = lateDays * (dailyRate * 2.5);
        double commercialPermit = 1500.0;
        return base + lateFee + commercialPermit;
    }
};

int main() {
    std::vector<Vehicle*> fleet;
    fleet.push_back(new Bicycle("BIKE-01", 150.0));
    fleet.push_back(new TwoWheeler("TN-02-AB-1234", 600.0, 5.5, Date(15, 12, 2026)));
    fleet.push_back(new Car("KA-01-CD-5678", 2500.0, 30.0, Date(20, 1, 2027), 5));
    fleet.push_back(new ElectricCar("DL-03-EV-9999", 3200.0, 95.0, Date(10, 3, 2027), 5, 60.0, 8.5));
    fleet.push_back(new ElectricBus("TN-BUS-001", 8000.0, 100.0, Date(1, 6, 2027), 40, 250.0));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "========================================================================\n";
    std::cout << "               AUTONOMOUS FLEET MANAGEMENT SYSTEM                       \n";
    std::cout << "========================================================================\n\n";

    std::cout << "--- 1. Initial Fleet Listing ---\n";
    for (const auto* v : fleet) {
        std::cout << "[" << std::left << std::setw(32) << v->getType() << "] "
                  << "Reg: " << std::setw(15) << v->getReg() 
                  << " | Rate: Rs " << std::setw(8) << v->getRate()
                  << " | Status: " << (v->getStatus() ? "RENTED" : "AVAILABLE") << "\n";
    }

    std::cout << "\n--- 2. Renting Vehicles ---\n";
    fleet[0]->rentVehicle();
    fleet[2]->rentVehicle();
    fleet[4]->rentVehicle();
    std::cout << "Rented: " << fleet[0]->getReg() << ", " << fleet[2]->getReg() 
              << ", and " << fleet[4]->getReg() << "\n";

    std::cout << "\n--- 3. Returns and Billing Calculations ---\n";
    struct RentalReturn {
        int index;
        int days;
        int late;
    };

    RentalReturn returns[] = {
        {0, 3, 1},
        {2, 5, 2},
        {4, 4, 0}
    };

    for (const auto& r : returns) {
        Vehicle* v = fleet[r.index];
        double bill = v->calculateCharge(r.days, r.late);
        v->returnVehicle();
        std::cout << "Returned " << v->getReg() << " (" << v->getType() << ")\n"
                  << "  Rental Period: " << r.days << " days | Late: " << r.late << " days\n"
                  << "  Final Settlement Bill: Rs " << bill << "\n";
    }

    for (auto* v : fleet) delete v;

    return 0;
}
