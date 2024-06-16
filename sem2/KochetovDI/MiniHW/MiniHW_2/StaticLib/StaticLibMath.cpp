#include <vector>
#include <algorithm>
#include <cmath>

double Average(std::vector<int>& numbers) {
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
    }

    return static_cast<double>(sum) / numbers.size();
}

double Median(std::vector<int>& numbers) {
    std::sort(numbers.begin(), numbers.end());
    int n = numbers.size();
    if (n % 2 == 0) {
        return (numbers[n / 2 - 1] + numbers[n / 2]) / 2.0;
    }
    else {
        return numbers[n / 2];
    }
}

double QuadraticMean(std::vector<int>& numbers) {
    double sumOfSquares = 0;

    for (int num : numbers) {
        sumOfSquares += num * num;
    }

    return std::sqrt(sumOfSquares / numbers.size());
}

double Variance(const std::vector<int>& numbers) {
    double mean = 0;
    double variance = 0;

    // Calculate the mean
    for (int num : numbers) {
        mean += num;
    }
    mean /= numbers.size();

    // Calculate the variance
    for (int num : numbers) {
        variance += (num - mean) * (num - mean);
    }
    variance /= numbers.size();

    return variance;
}