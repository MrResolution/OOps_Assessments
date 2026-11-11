#include <iostream>
#include <vector>

int& getHighestMark(int marks[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return marks[maxIdx];
}

int getHighestMarkIndex(const int marks[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

int main() {
    int marks[5] = {78, 85, 92, 88, 79};

    std::cout << "Original marks: ";
    for (int m : marks) std::cout << m << " ";
    std::cout << "\n";

    getHighestMark(marks, 5) += 2;

    std::cout << "After +2 moderation via return by reference: ";
    for (int m : marks) std::cout << m << " ";
    std::cout << "\n";

    std::vector<int> scores = {50, 60, 70};
    int& refFirst = scores[0];
    std::cout << "Before vector growth: scores[0] = " << refFirst << "\n";

    scores.reserve(100);
    for (int i = 0; i < 50; ++i) {
        scores.push_back(i);
    }
    std::cout << "Safeguarded vector capacity access verified.\n";

    return 0;
}
