// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "MathLibrary.h"
#include <vector>
#include <numeric>
#include <iostream>


bool If_num_overflowing(long long num)
{
 if (sqrt(LLONG_MAX) < num)
 {
    return true;
 }
 return false;
}

double average(std::vector<long long> vec)
{
    return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double medain(std::vector<long long> vec)
{
    if (vec.size() % 2 == 1)
        return vec[vec.size() / 2];
    else
    {
        return (vec[vec.size() / 2] + vec[(vec.size() / 2) - 1]) / 2.0;
    }
}

double average_qadr(std::vector<long long> vec)
{
    double sum_quad=0;

    for (long long elem : vec)
    {
        if (If_num_overflowing(elem))
        {
            std::cout << "Происходит переполнение";
            exit(0);
        }
        sum_quad += pow(elem,2);
    }
    sum_quad = sqrt(sum_quad / vec.size());
    return sum_quad;
}

double dispersion(std::vector<long long> vec)
{
    long long aver = average(vec);
    double sum_quad_disp = 0;

    for (long long elem : vec)
    {
        if (If_num_overflowing(elem - aver) || (LLONG_MIN + aver > elem))
        {
            std::cout << "Происходит переполнение";
            exit(0);
        }
        sum_quad_disp += (pow((elem - aver), 2));
    }
    sum_quad_disp = sum_quad_disp / vec.size();
    return sum_quad_disp;
}
