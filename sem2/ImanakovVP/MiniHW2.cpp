
#include <iostream>
#include "..\DynamicL\Header.h"
int main() {
    const int length = 5;
    double numbers[length] = { 1.0, 2.0, 3.0, 4.0, 5.0 };


    double arithmeticMean = arithmetic_mean(numbers, length);
    double geometricMean = geometric_mean(numbers, length);
    double quadraticMean = quadratic_mean(numbers, length);
    double dispersionValue = dispersion(numbers, length); 

    std::cout << "Arithmetic mean: " << arithmeticMean << std::endl;
    std::cout << "Geometric mean: " << geometricMean << std::endl;
    std::cout << "Quadratic mean: " << quadraticMean << std::endl;
    std::cout << "Dispersion: " << dispersionValue << std::endl;

    return 0;
}

