#include <iostream>
int main() {
    int n, a;
    std::cin >> n;
    if (n < 0) {
        n = -n;
        while (n > 0) {
            a = n % 10;
            std::cout << a;
            n = n / 10;
        }
        std::cout << '-'; //перевернула число и добавила минус, тк отрицательное
    }
    else if (n >= 0 and n < 10) {
        std::cout << n;
    }
    else {
        while (n > 0) {
            a = n % 10;
            std::cout << a;
            n = n / 10;
        }
    }

    return 0;
}