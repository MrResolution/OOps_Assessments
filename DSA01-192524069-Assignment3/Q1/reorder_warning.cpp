#include <iostream>

class ReorderDemo {
    int a;
    int b;
public:
    ReorderDemo(int val) : b(val), a(b + 5) {}
    void print() const { std::cout << "a: " << a << ", b: " << b << "\n"; }
};

int main() {
    ReorderDemo obj(10);
    obj.print();
    return 0;
}
