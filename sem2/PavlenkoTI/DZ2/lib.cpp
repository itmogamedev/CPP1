// Timofey Pavlenko 409294

#include <vector>
#include <algorithm>
#include <cmath>

namespace MyLib {

    double calculateMean(const std::vector<double>& data) { // ср.арифметическое
        double sum = 0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    double calculateMedian(const std::vector<double>& data) { // медиана
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        size_t size = sortedData.size();
        if (size % 2 == 0) {
            return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2.0;
        } else {
            return sortedData[size / 2];
        }
    }

    double calculateMeanSquare(const std::vector<double>& data) { // среднее квадратичное
        double sum = 0;
        for (double value : data) {
            sum += value * value;
        }
        return std::sqrt(sum / data.size());
    }

    double calculateVariance(const std::vector<double>& data) { // дисперсия числового ряда
        double mean = calculateMean(data);
        double sumSquareDiff = 0;
        for (double value : data) {
            sumSquareDiff += (value - mean) * (value - mean);
        }
        return sumSquareDiff / data.size();
    }

}
