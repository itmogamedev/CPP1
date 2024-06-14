#pragma once

#ifdef DLLKIR_EXPORTS
#define DLLKIR_API __declspec(dllexport)
#else
#define DLLKIR_API __declspec(dllimport)
#endif

extern "C" DLLKIR_API float arithmetic_mean(int arr[], const int size);

extern "C" DLLKIR_API float median(int arr[], const int size);

extern "C" DLLKIR_API float quadratic_mean(int arr[], const int size);

extern "C" DLLKIR_API float dispersion(int arr[], const int size);