#include <iostream>

int main() {
    int a{7};
    int b{2};
    double c = static_cast<double>(a) / static_cast<double>(b);
    double d = static_cast<double>(a) / b;
    std::cout << c << ' ' << d << '\n';

    char ch{static_cast<char>('A' + 2)};
    std::cout << ch << ' ' << static_cast<int>(ch) + 1 << '\n';

    bool flag{5 != 0};
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';

    int u{1};
    int s{-1};
    std::cout << (s < u ? "s < u" : "s >= u") << '\n';

    return 0;
}
