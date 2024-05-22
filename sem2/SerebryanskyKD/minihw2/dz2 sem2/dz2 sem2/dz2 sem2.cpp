#include <iostream>
#include <vector>
#include "..\..\StaticLib1\StaticLib1\Header.h"

int main()

{
    setlocale(LC_ALL, "ru");

    std::vector <int> v = { 3, 2, 4, 1, 6, 5 };

    float average;
    average = Average(v);
    std::cout << average << std::endl;

    Mediana(v);

    float mean_square1;
    mean_square1 = Mean_square1(v);
    std::cout << mean_square1 << std::endl;

    float mean_square2;
    mean_square2 = Mean_square2(v);
    std::cout << mean_square2 << std::endl;

    float dispersion;
    dispersion = Dispersion(v);
    std::cout << dispersion << std::endl;

    /*Два средних квадратических, потому что я не понял, какую формулу использовать*/

    return 0;
}