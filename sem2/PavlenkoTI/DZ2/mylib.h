// Timofey Pavlenko 409294

#include <vector>

namespace MyLib {
    // ср.арифметическое
    double calculateMean(const std::vector<double>& data);
    // медиана
    double calculateMedian(const std::vector<double>& data);
    // среднее квадратичное
    double calculateMeanSquare(const std::vector<double>& data);
    // дисперсия числового ряда
    double calculateVariance(const std::vector<double>& data);
}
