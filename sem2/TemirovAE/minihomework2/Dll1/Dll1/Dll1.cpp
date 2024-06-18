#include "pch.h"
#include "HeaderDll1.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


long double srArifmet(std::vector<double> vec)
{
    double Sum = 0;
    for (double i : vec)
        Sum += i;

    return Sum / vec.size();
}

long double Mediana(std::vector<double> vec)
{
    std::sort(vec.begin(), vec.end());
    if (vec.size() % 2 == 0)
        return (vec[vec.size() / 2-1] + vec[vec.size() / 2]) / 2;

    return vec[vec.size() / 2];
}

long double srKvadr(std::vector<double> vec)
{
    double Sum = 0;
    for (double i : vec)
        Sum += pow(i, 2);

    return pow(Sum, 0.5);
}

long double Disp(std::vector<double> vec)
{
    double Sum = 0;
    for (double i : vec)
        Sum += pow(i - srArifmet(vec), 2);
    return Sum / vec.size();
}