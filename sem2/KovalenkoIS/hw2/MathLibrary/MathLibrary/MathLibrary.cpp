#include "pch.h"
#include <utility>
#include <limits.h>
#include "MathLibrary.h"
#include <vector>
#include <numeric>
#include <iostream>
#include <cmath>

double calculateAverage() {
    int count;
    double total = 0.0;

    std::cout << "Введите количество чисел: ";
    std::cin >> count;

    if (count <= 0) {
        std::cout << "Некорректное количество чисел." << std::endl;
        return 0.0;
    }

    std::cout << "Введите числа через пробел: ";
    for (int i = 0; i < count; ++i) {
        double num;
        std::cin >> num;
        total += num;
    }

    return total / count;
}

double median() {
    std::vector<long long> myVector;
    int count;

    std::cout << "Введите количество чисел: ";
    std::cin >> count;

    std::cout << "Введите числа через пробел: ";

    for (int i = 0; i < count; ++i) {
        int num;
        std::cin >> num;
        myVector.push_back(num);
    }

    if (myVector.size() % 2 == 1)
        return myVector[myVector.size() / 2];
    else
    {
        return (myVector[myVector.size() / 2] + myVector[(myVector.size() / 2) - 1]) / 2.0;
    }
}

double square() {
    int count;
    double total = 0.0;

    std::cout << "Введите количество чисел: ";
    std::cin >> count;

    std::cout << "Введите числа через пробел: ";
    for (int i = 0; i < count; ++i) {
        double num;
        std::cin >> num;
        total += num * num;
    }

    return std::sqrt(total) / count;
}

double dispersion() {
    int count;
    double total = 0.0;
    std::vector<long long> myVector;
    std::vector<long long> Vector_for_otkl;

    std::cout << "Введите количество чисел: ";
    std::cin >> count;

    std::cout << "Введите числа через пробел: ";
    for (int i = 0; i < count; ++i) {
        double num;
        std::cin >> num;
        myVector.push_back(num);
        total += num;

    }

    long long arithmeticMean = total / count;

    for (int i = 0; i < count; ++i) {
        long long Otkl = (myVector[i] - arithmeticMean);
        long long sqOtkl = pow(Otkl, 2);
        Vector_for_otkl.push_back(sqOtkl);
    }

    double doubleValue = static_cast<double>(count);

    long long sum_of_elems = std::accumulate(Vector_for_otkl.begin(), Vector_for_otkl.end(), 0);

    return sum_of_elems / doubleValue;
}

