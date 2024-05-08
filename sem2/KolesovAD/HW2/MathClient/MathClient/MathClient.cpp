#include <iostream>
#include "MathLibrary.h"
#include <vector>
#include <string>

int main()
{
    std::cout << "This is a program, which gives you arithmetic average, median, square average or dispersion of list of numbers." << std::endl;
    std::cout << "Enter the numbers of the list (one number per line) and after this enter \"end\": ";
    std::vector<long double> numbersRow;
    std::string number;
    std::cin >> number;
    while (number != "end") {
        numbersRow.push_back(stold(number));
        std::cin >> number;
    }
    std::cout << "The arithmetic average is " << arithmeticAverage(numbersRow) << std::endl;
    std::cout << "The median is " << median(numbersRow) << std::endl;
    std::cout << "The square average is " << squareAverage(numbersRow) << std::endl;
    std::cout << "The dispersion is " << dispersion(numbersRow) << std::endl;
}