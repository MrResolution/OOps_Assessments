#include <iostream>

int& getLocalReference() {
    int localMark = 95;
    return localMark;
}

int main() {
    int& ref = getLocalReference();
    std::cout << "Value: " << ref << "\n";
    return 0;
}
