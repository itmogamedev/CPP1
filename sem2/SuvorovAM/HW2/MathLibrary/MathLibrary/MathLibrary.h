#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

extern "C" DLL_API double calc_arifmetic_avg(double* values, int size);

extern "C" DLL_API double calc_median(double* values, int size);

extern "C" DLL_API double calñ_deviation(double* values, int size);

extern "C" DLL_API double calc_variance_num_series(double* values, int size);