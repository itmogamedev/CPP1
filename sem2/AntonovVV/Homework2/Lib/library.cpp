#include "library.h"
#include <iostream>
#include <cmath>
float Average(int n, int arr[])
{
    float sum = 0;
    for (int i = 0; i < n; i ++)
    {
        sum+= float(arr[i]);
    }
    return sum/float(n);
}

float Median(int n, int arr[])
{
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    if (n % 2 != 0) return arr[n/2];
    else return (arr[n/2] + arr[(n-1)/2])/2;
}

float Mean_square(int n, int arr[])
{
    float sum = 0;
    for (int i = 0; i < n; i ++)
    {
        sum += float(arr[i] * arr[i]);
    }
    return sqrt(sum/n);
}

float Dispersion(int n, int arr[])
{
    float sum = 0;
    for (int i = 0; i < n; i ++)
    {
        sum += float(arr[i]);
    }
    float avg = sum/float(n);
    float Sum = 0;
    for (int i = 0; i < n; i++)
    {
        Sum += float (pow( float (arr[i]) - avg, 2));
    }
    return Sum / n;
}