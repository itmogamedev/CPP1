#include "pch.h"
#include <utility>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <cmath>

#include "MathLibrary.h"

double* values;
int size;

double calc_arifmetic_avg(double* values, int size) {
    if (size <= 0) {
        return 0;
    }

    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += values[i];
    }

    return sum / size;
}

double calc_median(double* values, int size) {
    std::vector<double> vec(values, values + size);
    std::sort(vec.begin(), vec.end());

    if (size % 2 == 1) {
        return vec[size / 2];
    }
    else {return ((vec[size / 2 - 1] + vec[size / 2]) / 2.0);}
}

double calñ_deviation(double* values, int size) {
    std::vector<double> vec(values, values + size);

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += vec[i];
    }

    double mean = sum / size;
    double sq_diff_sum = 0.0;

    for (int i = 0; i < size; ++i) {
        sq_diff_sum += (vec[i] - mean) * (vec[i] - mean);
    }

    return sqrt(sq_diff_sum / size);
}

double calc_variance_num_series(double* values, int size) {
    std::vector<double> vec(values, values + size);

    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += vec[i];
    }

    double mean = sum / size;

    double variance = 0.0;
    for (int i = 0; i < size; ++i)
    {
        variance += (vec[i] - mean) * (vec[i] - mean);
    }

    return variance / size;
}