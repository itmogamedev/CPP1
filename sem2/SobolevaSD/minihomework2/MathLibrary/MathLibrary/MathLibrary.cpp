#include "pch.h"
#include "MathLibrary.h"
#include <vector>
#include <cmath>

using std::vector;

double average(vector <double> vec) {
    double sum = 0.0;
    for (double i : vec) {
        sum += i;
    }
    return sum/(vec.size());
}

double median(vector <double> vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i; j < vec.size(); j++) {
            if (vec[i] > vec[j]) {
                double temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
    if (vec.size() % 2 == 1) {
        return vec[round((vec.size() - 1)/2)];
    }
    else {
        return (vec[round(vec.size()/2)] + vec[round((vec.size() - 2) / 2)])/2;
    }
}

double square(vector <double> vec) {
    double sum = 0.0;
    for (double i : vec) {
        sum += i * i;
    }
    return sqrt(sum)/vec.size();
}

double dispersion(vector <double> vec) {
    double ave = average(vec);
    double sum = 0.0;
    int n = 0;
    for (double i : vec) {
        sum += (i - ave) * (i - ave);
        if (i != ave) {
            n += 1;
        }
    }
    if (n > 0) {
        return (sum/n)*(sum/n);
    }
    else {
        return 0;
    }
}