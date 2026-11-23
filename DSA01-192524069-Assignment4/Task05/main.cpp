#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string customer;
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:
    Cart(const std::string& cust = "Guest") : customer(cust) {}

    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }

    std::string getCustomer() const { return customer; }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== Four Ways to Reach an Object ===\n\n";

    Cart c1("Customer A");
    c1.add("Milk", 40).setDiscount(5);
    std::cout << "1. Direct Name: " << c1.getCustomer() << " Total = Rs " << c1.total() << "\n";

    Cart* ptr1 = &c1;
    ptr1->add("Bread", 30);
    std::cout << "2. Pointer (->): " << ptr1->getCustomer() << " Total = Rs " << ptr1->total() << "\n";

    Cart& ref1 = c1;
    ref1.add("Butter", 50);
    std::cout << "3. Reference: " << ref1.getCustomer() << " Total = Rs " << ref1.total() << "\n";

    Cart* heapCart = new Cart("Customer B");
    heapCart->add("Coffee", 150).add("Biscuits", 60).setDiscount(10);
    std::cout << "4. Heap Dynamic (new/delete): " << heapCart->getCustomer() 
              << " Total = Rs " << heapCart->total() << "\n";

    Cart c2("Customer C");
    c2.add("Rice", 1200).add("Oil", 800).setDiscount(15);

    Cart c3("Customer D");
    c3.add("Apples", 200).add("Oranges", 180);

    const int ACTIVE_COUNT = 4;
    Cart* activeCarts[ACTIVE_COUNT] = { &c1, heapCart, &c2, &c3 };

    std::cout << "\n=== Finding Highest Value Cart via Array of Pointers ===\n";
    int highestIdx = 0;
    for (int i = 1; i < ACTIVE_COUNT; ++i) {
        if (activeCarts[i]->total() > activeCarts[highestIdx]->total()) {
            highestIdx = i;
        }
    }

    std::cout << "Highest Cart: " << activeCarts[highestIdx]->getCustomer() 
              << " with Total Rs " << activeCarts[highestIdx]->total() << "\n";

    delete heapCart;

    return 0;
}
