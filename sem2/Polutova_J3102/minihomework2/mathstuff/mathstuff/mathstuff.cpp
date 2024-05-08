// arrmath.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "mathstuff.h"
#include <algorithm>
#include <cmath>
#include <vector>

long double arith_mean(const std::vector<long long int> arr) {
	long double sum = 0;
	std::for_each(arr.begin(), arr.end(), [&sum](long long int n) {
		sum += (long double)n;
		});

	return sum / arr.size();
}

long double median(std::vector<long long int> arr) {
	sort(arr.begin(), arr.end());
	if (arr.size() % 2 == 1) {
		return arr[(int)(arr.size() / 2)];
	}
	else {
		int middle = arr.size() / 2;
		long double left = arr[middle - 1];
		long double right = arr[middle];
		return (left + right) / 2;
	}

}

long double square_mean(const std::vector<long long int> arr) {
	return std::sqrt(arith_mean(arr));
}

long double dispersion(const std::vector<long long int> arr) {
	long double mean = arith_mean(arr);
	long double sum = 0;

	std::for_each(arr.begin(), arr.end(), [mean, &sum](long long int n) {
		sum += pow((long double)n - mean, 2);
		});

	return sum / arr.size();
}