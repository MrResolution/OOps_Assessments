#include <iostream>
#include <iomanip>

class Auditorium {
    int rows;
    int cols;
    char** seats;

public:
    Auditorium(int r, int c) : rows(r), cols(c), seats(nullptr) {
        if (rows > 0 && cols > 0) {
            seats = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                seats[i] = new char[cols];
                for (int j = 0; j < cols; ++j) {
                    seats[i][j] = 'O';
                }
            }
        }
        std::cout << "[Constructor] Allocated 2D Seat Map: " << rows << " x " << cols << "\n";
    }

    ~Auditorium() {
        if (seats) {
            for (int i = 0; i < rows; ++i) {
                delete[] seats[i];
            }
            delete[] seats;
            seats = nullptr;
        }
        std::cout << "[Destructor] Deallocated 2D Seat Map (" << rows << " rows released)\n";
    }

    bool bookSeat(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] == 'X') {
            return false;
        }
        seats[r][c] = 'X';
        return true;
    }

    bool cancelSeat(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] == 'O') {
            return false;
        }
        seats[r][c] = 'O';
        return true;
    }

    void display() const {
        std::cout << "Auditorium Layout (O=Available, X=Booked):\n";
        for (int i = 0; i < rows; ++i) {
            std::cout << "Row " << std::setw(2) << i + 1 << ": ";
            for (int j = 0; j < cols; ++j) {
                std::cout << seats[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "=== Scope 1: Stack Allocation ===\n";
    {
        Auditorium hall1(3, 5);
        hall1.bookSeat(0, 0);
        hall1.bookSeat(1, 2);
        hall1.display();
    }

    std::cout << "\n=== Scope 2: Heap Allocation ===\n";
    Auditorium* hall2 = new Auditorium(2, 4);
    hall2->bookSeat(0, 1);
    hall2->display();
    delete hall2;

    return 0;
}
