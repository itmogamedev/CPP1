#include <iostream>
#include "MathLibrary.h"
#include <vector>

int main()
{
    setlocale(LC_ALL, "RUS");
    std::vector <double> vec;
    std::cout << "Из скольки чисел будет состоять ваш числовой ряд?" << std::endl;
    int n;
    double temp;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        vec.push_back(temp);
    }
    std::cout << std::endl << "Среднее арифметическое: " << average(vec);
    std::cout << std::endl << "Медиана: " << median(vec);
    std::cout << std::endl << "Среднее квардатичное: " << square(vec);
    std::cout << std::endl << "Дисперсия: " << dispersion(vec);
}