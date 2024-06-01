// Timofey Pavlenko 409294

#include "myLib.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7};

    std::cout << "number series:" << std::endl;
    for(auto s : vec){ std::cout << s << " "; }
    std::cout << "\n\n";

    std::cout << "mean: " << MyLib::calculateMean(vec) << std::endl;
    std::cout << "median: " << MyLib::calculateMedian(vec) << std::endl;
    std::cout << "mean square: " << MyLib::calculateMeanSquare(vec) << std::endl;
    std::cout << "variance: " << MyLib::calculateVariance(vec) << std::endl;
}
