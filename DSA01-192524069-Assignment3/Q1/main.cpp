#include <iostream>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;

public:
    Book() : Book("Untitled", "Unknown", 0) {}

    explicit Book(const std::string& t) : Book(t, "Unknown", 1) {}

    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c < 0 ? 0 : c) {}

    void print() const {
        std::cout << "Title: " << title << " | Author: " << author 
                  << " | Copies: " << copies << "\n";
    }

    int getCopies() const {
        return copies;
    }
};

int main() {
    Book b1;
    Book b2("Clean Code");
    Book b3("The C++ Programming Language", "Bjarne Stroustrup", 5);
    Book b4("Invalid Book", "Test Author", -10);

    std::cout << "Library Records:\n";
    b1.print();
    b2.print();
    b3.print();
    b4.print();

    Book catalog[3] = {Book(), Book("Design Patterns"), Book("Refactoring", "Martin Fowler", 2)};
    std::cout << "\nCatalog Array Initialized:\n";
    for (const auto& b : catalog) {
        b.print();
    }

    return 0;
}
