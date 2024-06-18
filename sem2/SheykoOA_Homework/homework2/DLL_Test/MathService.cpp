#include "MathService.h"
#include <math.h>
#include <algorithm>

double mean(const std::vector<double>& numbers) {
    int sum = 0;
    for (double n : numbers)
        sum += n;
    return sum / numbers.size();
}

double median(const std::vector<double>& numbers) {
    std::vector<double> sortednums = numbers;
    std::sort(sortednums.begin(), sortednums.end());
    if (sortednums.size() % 2 == 0)
        return (sortednums[sortednums.size() / 2 - 1] + sortednums[sortednums.size() / 2]) / 2;
    return sortednums[sortednums.size() / 2];
}

double medianSquared(const std::vector<double>& numbers) {
    std::vector <double> squarednums = numbers;
    for (double& n : squarednums)
        n *= n;
    double averaged = mean(squarednums);
    return sqrt(averaged);
}

double variance(const std::vector<double>& numbers) {
    double averaged = mean(numbers);
    int diff = 0;
    for (double n : numbers)
        diff += pow(n - averaged, 2);
    return diff / numbers.size();
}
