#include <iostream>
#include "dllmath.h"

int main()
{
    const int size = 7;
    int arr[size] = { 23, 45, 62, 7, 89, 11, 4};

    std::cout << arithmetic_mean(arr, size) << std::endl;
    std::cout << median(arr, size) << std::endl;
    std::cout << quadratic_mean(arr, size) << std::endl;
    std::cout << dispersion(arr, size) << std::endl;

}