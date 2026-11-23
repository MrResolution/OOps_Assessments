#include <iostream>
#include <string>
#include <stdexcept>
#include <new>

struct CleanResource {
    std::string name;
    CleanResource(const std::string& n) : name(n) { std::cout << "  [Allocated " << name << "]\n"; }
    ~CleanResource() { std::cout << "  [Cleaned " << name << "]\n"; }
};

void parseAmount(const std::string& str) {
    CleanResource res("ParserBuffer");
    double val = std::stod(str);
    if (val < 0) throw std::invalid_argument("Negative fee rejected");
    std::cout << "Parsed successfully: Rs " << val << "\n";
}

void triggerBadAlloc() {
    CleanResource res("BigAllocTracker");
    std::cout << "Attempting to allocate 10 Terabytes...\n";
    size_t hugeSize = 10000000000000ULL;
    char* hugeArray = new char[hugeSize];
    delete[] hugeArray;
}

int main() {
    std::cout << "=== Test 1: Invalid Text Parsing ===\n";
    try {
        parseAmount("invalid_number_twenty");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    std::cout << "\n=== Test 2: Negative Number Parsing ===\n";
    try {
        parseAmount("-450.00");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    std::cout << "\n=== Test 3: Forcing std::bad_alloc ===\n";
    try {
        triggerBadAlloc();
    } catch (const std::bad_alloc& e) {
        std::cout << "Caught Memory Exhaustion: " << e.what() << "\n";
    }

    std::cout << "\n=== Test 4: Top-Level catch(...) Shielding Crash ===\n";
    try {
        CleanResource topRes("TopLevelGuard");
        throw 999;
    } catch (...) {
        std::cout << "Caught unknown arbitrary exception cleanly. Application intact.\n";
    }

    return 0;
}
