#include <iostream>

void applyByValue(long long fee, int percent)
{
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent)
{
    fee -= (fee * percent) / 100;
}

void applyByPointer(long long* fee, int percent)
{
    if (fee) {
        *fee -= (*fee * percent) / 100;
    }
}

int main()
{
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value    : " << hostelFee << '\n';

    applyConcession(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << '\n';

    applyByPointer(&hostelFee, 10);
    std::cout << "after call by pointer  : " << hostelFee << '\n';

    return 0;
}
