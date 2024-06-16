// MathLibrary.h - Contains declarations of math functions
#pragma once
#include <vector>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


extern "C" MATHLIBRARY_API bool If_num_overflowing(const long long num);

extern "C" MATHLIBRARY_API double average(const std::vector<long long> vec);

extern "C" MATHLIBRARY_API double medain(const std::vector<long long> vec);

extern "C" MATHLIBRARY_API double average_qadr(const std::vector<long long> vec);

extern "C" MATHLIBRARY_API double dispersion(const std::vector<long long> vec);