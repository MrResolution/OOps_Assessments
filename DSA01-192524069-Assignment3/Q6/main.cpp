#include <iostream>
#include <cstring>

class Text {
    char* data;
    size_t length;

public:
    Text() : data(new char[1]{'\0'}), length(0) {}

    Text(const char* str) : data(nullptr), length(0) {
        if (str) {
            length = std::strlen(str);
            data = new char[length + 1];
            std::strcpy(data, str);
        } else {
            data = new char[1]{'\0'};
        }
    }

    Text(const Text& other) : data(new char[other.length + 1]), length(other.length) {
        std::strcpy(data, other.data);
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            char* newData = new char[other.length + 1];
            std::strcpy(newData, other.data);
            delete[] data;
            data = newData;
            length = other.length;
        }
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text operator+(const Text& other) const {
        Text result;
        delete[] result.data;
        result.length = this->length + other.length;
        result.data = new char[result.length + 1];
        std::strcpy(result.data, this->data);
        std::strcat(result.data, other.data);
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(this->data, other.data) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    size_t size() const {
        return length;
    }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        os << t.data;
        return os;
    }
};

int main() {
    Text empty;
    Text msg1("Your OTP is 482910. ");
    Text msg2("Do not share with anyone.");

    Text fullMsg = msg1 + msg2;
    std::cout << "Concatenated Message: " << fullMsg << "\n";
    std::cout << "Message Length: " << fullMsg.size() << " chars\n";

    Text duplicate = fullMsg;
    std::cout << "Equality Check (duplicate == fullMsg): " 
              << std::boolalpha << (duplicate == fullMsg) << "\n";
    std::cout << "Inequality Check (msg1 != msg2): " 
              << (msg1 != msg2) << "\n";

    fullMsg = fullMsg;
    std::cout << "Self-assignment handled safely: " << fullMsg << "\n";

    return 0;
}
