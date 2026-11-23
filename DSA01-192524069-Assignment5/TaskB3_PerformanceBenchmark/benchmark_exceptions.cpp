#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdexcept>

bool validateReturnCode(double val, double& outVal) {
    if (val < 0.0) {
        return false;
    }
    outVal = val;
    return true;
}

double validateException(double val) {
    if (val < 0.0) {
        throw std::invalid_argument("Negative");
    }
    return val;
}

void testErrorRate(const std::string& label, int errorRatePercent) {
    const long long N = 1000000LL;

    std::cout << "\n--- Scenario: " << label << " (" << errorRatePercent << "% Error Rate) ---\n";

    auto s1 = std::chrono::high_resolution_clock::now();
    long long returnErrors = 0;
    double dummySum1 = 0;
    for (long long i = 0; i < N; ++i) {
        double val = (i % 100 < errorRatePercent) ? -100.0 : 100.0;
        double out = 0;
        if (!validateReturnCode(val, out)) {
            returnErrors++;
        } else {
            dummySum1 += out;
        }
    }
    auto e1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tReturn = e1 - s1;

    auto s2 = std::chrono::high_resolution_clock::now();
    long long exceptionErrors = 0;
    double dummySum2 = 0;
    for (long long i = 0; i < N; ++i) {
        double val = (i % 100 < errorRatePercent) ? -100.0 : 100.0;
        try {
            dummySum2 += validateException(val);
        } catch (const std::invalid_argument&) {
            exceptionErrors++;
        }
    }
    auto e2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tException = e2 - s2;

    std::cout << "Return Codes Time: " << tReturn.count() << " ms (Errors: " << returnErrors << ")\n";
    std::cout << "Exceptions Time:   " << tException.count() << " ms (Errors: " << exceptionErrors << ")\n";
    if (tReturn.count() > 0) {
        double ratio = tException.count() / tReturn.count();
        std::cout << "Relative Cost:     Exceptions are " << std::fixed << std::setprecision(1) 
                  << ratio << "x " << (ratio >= 1.0 ? "slower" : "faster") << "\n";
    }
}

int main() {
    std::cout << "=================================================================\n";
    std::cout << "   BENCHMARK: RETURN CODES VS. EXCEPTIONS (1,000,000 RECORDS)    \n";
    std::cout << "=================================================================\n";

    testErrorRate("No Errors (0%)", 0);
    testErrorRate("Low Errors (1%)", 1);
    testErrorRate("High Errors (50%)", 50);

    return 0;
}
