#include <vector>
#pragma once

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

extern "C" DLL1_API long double srArifmet(std::vector<double>);


extern "C" DLL1_API long double Mediana(std::vector<double>);


extern "C" DLL1_API long double srKvadr(std::vector<double>);


extern "C" DLL1_API long double Disp(std::vector<double>);
