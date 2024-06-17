#include "pch.h"
#include "MathLibrary.h"
#include <iostream>
#include <algorithm>
#include <cmath>
float average(int A[], const int size) {
    int ssum = 0;
    for (int i = 0; i < size; i++) {
        ssum += A[i];
    }
    float aver = float(ssum) / float(size);
    return aver;
}
float median(int A[], const int size) {
    float ans;
    std::sort(A, A + size);
    if (size % 2 != 0) {
        ans = A[(size / 2)];
    }
    else {
        ans = (float(A[(size / 2) - 1]) + float(A[(size / 2)])) / 2;
    }
    return ans;
}
float dispersion(int A[], const int size){
    float aver = average(A, size);
    float disp = 0;
    for (int j = 0; j < size; j++) {
        disp += (float(A[j] - aver) * float(A[j] - aver)) / float(size);
    }
    return disp;
}
float mean_square(int A[], const int size) {
    float ans = float(sqrt(dispersion(A, size)));
    return ans;
}
