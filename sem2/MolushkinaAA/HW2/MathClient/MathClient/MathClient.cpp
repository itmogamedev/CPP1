#include <iostream>
#include "MathLibrary.h"

int main() {
    const int size = 8;
    int A[size] = { 11, 10, 5, 4, 15, 6, 1, 13};
    std::cout << average(A, size) << std::endl;
    std::cout << median(A, size) << std::endl;
    std::cout << dispersion(A, size) << std::endl;
    std::cout << mean_square(A, size) << std::endl;
}