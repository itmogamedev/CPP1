#include <iostream>
#include "C:\Study\C++\2_semestr\MiniHW\MiniHW_2\StaticLib\framework.h"
#include <vector>

int main() {
	std::vector<int> numbers = { 1, 2, 3, 4, 5 };
	std::cout << "Average: " << Average(numbers) << std::endl;
	std::cout << "Median: " << Median(numbers) << std::endl;
	std::cout << "Average Root Mean Square: " << QuadraticMean(numbers) << std::endl;
	std::cout << "Variance of the series: " << Variance(numbers) << std::endl;
}