#include <iostream>
int main() {
    int n;
    std::cin >> n;
    if (n > 0) {
        if (n == 1) {
            std::cout << 1;
        }
        else if (n == 2) {
            std::cout << 1 << ' ' << 1 << ' ';
        }
        else {
            n = n - 2;
            int a = 1, b = 1, c;
            std::cout << 1 << ' ' << 1 << ' ';
            while (n > 0) {
                c = a + b;
                a = b;
                b = c;
                std::cout << b << ' ';
                n = n - 1;
            }
        }
        return 0;
    }
    else {
        std::cout << "error, there is no such element number in the fibonacci sequence";
    }
}