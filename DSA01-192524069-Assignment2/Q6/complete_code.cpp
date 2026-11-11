#include <iostream>
#include <cmath>

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
}

bool earlier(const Time& a, const Time& b)
{
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    Time noonBefore(11, 55), noonAfter(12, 5);
    std::cout << "Noon crossing: " << minutesBetween(noonBefore, noonAfter) << " mins | Earlier: "
              << earlier(noonBefore, noonAfter) << '\n';

    Time identical1(10, 30), identical2(10, 30);
    std::cout << "Identical times: " << minutesBetween(identical1, identical2) << " mins | Earlier: "
              << earlier(identical1, identical2) << '\n';

    return 0;
}
