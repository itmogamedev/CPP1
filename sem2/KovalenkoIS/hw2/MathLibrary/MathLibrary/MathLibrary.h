// MathLibrary.h - Contains declarations of math functions
#pragma once
#include <vector>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API double calculateAverage();

extern "C" MATHLIBRARY_API double median();

extern "C" MATHLIBRARY_API double square();

extern "C" MATHLIBRARY_API double dispersion();