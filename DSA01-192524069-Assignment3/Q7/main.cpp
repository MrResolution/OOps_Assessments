#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

class Complex {
    double real;
    double imag;

public:
    Complex() : real(0.0), imag(0.0) {}

    Complex(double r) : real(r), imag(0.0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0.0) {
            throw std::runtime_error("Division by zero in Complex division");
        }
        return Complex((real * other.real + imag * other.imag) / denom,
                       (imag * other.real - real * other.imag) / denom);
    }

    bool operator==(const Complex& other) const {
        constexpr double EPSILON = 1e-9;
        return (std::abs(real - other.real) < EPSILON && std::abs(imag - other.imag) < EPSILON);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << std::fixed << std::setprecision(2);
        os << c.real;
        if (c.imag >= 0) {
            os << " + " << c.imag << "j";
        } else {
            os << " - " << std::abs(c.imag) << "j";
        }
        return os;
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << "          AC CIRCUIT IMPEDANCE CALCULATOR (RLC)             \n";
    std::cout << "============================================================\n";

    double R = 100.0;
    double omega = 1000.0;
    double L = 0.05;
    double C = 0.00001;

    Complex zR(R, 0.0);
    Complex zL(0.0, omega * L);
    Complex zC(0.0, -1.0 / (omega * C));

    std::cout << "Component Impedances:\n";
    std::cout << "Resistor (R):  " << zR << " | Magnitude: " << zR.magnitude() << " ohms\n";
    std::cout << "Inductor (L):  " << zL << " | Magnitude: " << zL.magnitude() << " ohms\n";
    std::cout << "Capacitor (C): " << zC << " | Magnitude: " << zC.magnitude() << " ohms\n";

    Complex zSeries = zR + zL + zC;
    std::cout << "\nSeries RLC Total Impedance (Z_series = ZR + ZL + ZC):\n";
    std::cout << "Z_series:  " << zSeries << " ohms\n";
    std::cout << "|Z_series|: " << zSeries.magnitude() << " ohms\n";

    Complex num = zL * zC;
    Complex den = zL + zC;
    Complex zParallelLC = num / den;
    Complex zTotal = zR + zParallelLC;

    std::cout << "\nParallel LC in Series with Resistor:\n";
    std::cout << "Parallel (ZL || ZC): " << zParallelLC << " ohms\n";
    std::cout << "Total Network (ZR + (ZL || ZC)): " << zTotal << " ohms\n";
    std::cout << "|Z_total|: " << zTotal.magnitude() << " ohms\n";

    std::cout << "\nTesting Division by Zero Exception Safety:\n";
    try {
        Complex zero(0.0, 0.0);
        Complex invalid = zSeries / zero;
        std::cout << "Result: " << invalid << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Caught Expected Exception: " << e.what() << "\n";
    }

    return 0;
}
