#include <iostream>
#include <string>

class ExplicitBook {
    std::string title;
public:
    explicit ExplicitBook(const std::string& t) : title(t) {}
    void show() const { std::cout << "Book: " << title << "\n"; }
};

void displayBook(const ExplicitBook& b) {
    b.show();
}

int main() {
    ExplicitBook b1("Algorithms");
    displayBook(b1);

    return 0;
}
