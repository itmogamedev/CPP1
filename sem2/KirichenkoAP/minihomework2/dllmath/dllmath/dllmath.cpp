#include "pch.h"
#include <utility>
#include <limits.h>
#include "dllmath.h"
#include <cmath>
#include <algorithm>

float arithmetic_mean(int arr[], const int size)
{
    float sum = 0;
    float am = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    am = sum / size;

    return am;
}

float median(int arr[], const int size)
{
    std::sort(arr, arr + size);
    if (size % 2 != 0) {
        return arr[size / 2];
    }
    else {
        return (arr[(size / 2) - 1] + arr[size / 2]) / 2;
    }
}

float quadratic_mean(int arr[], const int size)
{
    float sumq = 0;
    float qm = 0;

    for (int i = 0; i < size; i++) {
        sumq += pow(arr[i], 2);
    }
    qm = sqrt(sumq / size);

    return qm;
}

float dispersion(int arr[], const int size)
{
    float sum = 0;
    float sum2 = 0;
    float mathexp = 0;
    float disp = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    mathexp = sum / size;

    for (int j = 0; j < size; j++) {
        sum2 += pow((arr[j] - mathexp), 2);
    }
    disp = sum2 / size;

    return disp;
}