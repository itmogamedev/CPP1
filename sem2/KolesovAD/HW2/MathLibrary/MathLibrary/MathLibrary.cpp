#include "pch.h"
#include <utility>
#include <limits.h>
#include "MathLibrary.h"
#include "math.h"
#include <vector>


long double arithmeticAverage(const std::vector<long double> numbers) {
    long double summa = 0;
    for (long double number : numbers) {
        summa += number;
    }
    return summa / numbers.size();
}


long double median(const std::vector<long double> numbers)
{
    std::vector<long double> sortedNumbers = numbers;
    int size = numbers.size();
    for (int i = 1; i < size; i++) {
        if (sortedNumbers[i] < sortedNumbers[i - 1]) {
            int j = i;
            while (j > 0 && sortedNumbers[j] < sortedNumbers[j - 1]) {
                std::swap(sortedNumbers[j], sortedNumbers[j - 1]);
            }
        }
    }
    if (size % 2 == 1) {
        return sortedNumbers[size / 2];
    }
    std::vector<long double> medianNumbers = { sortedNumbers[size / 2 - 1], sortedNumbers[size / 2] };
    return arithmeticAverage(medianNumbers);
}


long double squareAverage(const std::vector<long double> numbers)
{
    long double squareSum = 0;
    for (long double number : numbers) {
        squareSum += number * number;
    }
    return sqrt(squareSum / numbers.size());
}


long double dispersion(const std::vector<long double> numbers)
{
    long double average = arithmeticAverage(numbers);
    std::vector<long double> newNumbers;
    for (int i = 0; i < numbers.size(); i++) {
        newNumbers.push_back((numbers[i] - average) * (numbers[i] - average));
    }
    return arithmeticAverage(newNumbers);
}