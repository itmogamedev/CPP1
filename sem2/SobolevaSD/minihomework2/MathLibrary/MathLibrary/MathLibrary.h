#pragma once

#include <vector>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API double average(std::vector <double> vec);

extern "C" MATHLIBRARY_API double median(std::vector <double> vec);

extern "C" MATHLIBRARY_API double square(std::vector <double> vec);

extern "C" MATHLIBRARY_API double dispersion(std::vector <double> vec);

