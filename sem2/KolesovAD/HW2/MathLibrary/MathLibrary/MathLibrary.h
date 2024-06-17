
#pragma once

#include <vector>
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


extern "C" MATHLIBRARY_API long double arithmeticAverage(const std::vector<long double> numbers);


extern "C" MATHLIBRARY_API long double median(const std::vector<long double> numbers);


extern "C" MATHLIBRARY_API long double squareAverage(const std::vector<long double> numbers);


extern "C" MATHLIBRARY_API long double dispersion(const std::vector<long double> numbers);