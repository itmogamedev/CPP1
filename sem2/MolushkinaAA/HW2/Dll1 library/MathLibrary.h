#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API float average(int A[], const int size);
extern "C" MATHLIBRARY_API float median(int A[], const int size);
extern "C" MATHLIBRARY_API float dispersion(int A[], const int size);
extern "C" MATHLIBRARY_API float mean_square(int A[], const int size);
