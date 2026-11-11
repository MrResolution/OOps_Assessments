#include <iostream>
#include <string>

class ShallowPrescription {
    int n;
    std::string* medicines;

public:
    explicit ShallowPrescription(int count) : n(count), medicines(new std::string[count]) {}
    ~ShallowPrescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
};

int main() {
    ShallowPrescription p(2);
    p.set(0, "Aspirin");
    ShallowPrescription q = p;
    return 0;
}
