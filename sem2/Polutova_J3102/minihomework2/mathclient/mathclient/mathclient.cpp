
#include <iostream>
#include "../../mathstuff/mathstuff/mathstuff.h"
#include <string>
#include <sstream>

int main() {
    std::cout << "Input an array of numbers separated by space:\n";
    std::string arrayStr;
    while (!arrayStr.length()) {
        std::getline(std::cin, arrayStr); //для удобства, чтобы получить все аргументы в одной строке
    }
    std::vector<long long int> numbers;
    std::istringstream ss(arrayStr);
    std::string token;

    try {
        while (std::getline(ss, token, ' ')) {
            numbers.push_back(stoll(token));
        }
    }
    catch (const std::invalid_argument e) { //обработка возможных ошибок, если будут переданы не только числа
        std::cout << "ERROR: " << e.what() << std::endl;
        std::cout << "You can put only numbers.";
        return 1;
    }

    std::cout << "Arithmetical mean is: " << arith_mean(numbers) << '\n';
    std::cout << "Median is: " << median(numbers) << '\n';
    std::cout << "Square mean is: " << square_mean(numbers) << '\n';
    std::cout << "Dispersion is: " << dispersion(numbers) << '\n';
}
