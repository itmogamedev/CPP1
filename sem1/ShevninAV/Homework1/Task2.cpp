#include <format>
#include <iostream>

char DigitInFirstChar(int num)
{
    if (num < 0 || num > 9)
        throw std::range_error(std::format("{} is not digit", num));

    switch (num)
    {
        case 0:
            return 'z';
        case 1:
            return 'o';
        case 2:
        case 3:
            return 't';
        case 4:
        case 5:
            return 'f';
        case 6:
        case 7:
            return 's';
        case 8:
            return 'e';
        case 9:
            return 'n';
    }
}

int main()
{
    int num;
    std::cin >> num;

    std::cout << DigitInFirstChar(num);
}
