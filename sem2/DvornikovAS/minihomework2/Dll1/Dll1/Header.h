#pragma once
#include <vector>

extern "C" __declspec(dllexport) double average_of(std::vector <double>);

extern "C" __declspec(dllexport) double median(std::vector <double>);

extern "C" __declspec(dllexport) double average_kvadr_of(std::vector <double>);

extern "C" __declspec(dllexport) double dispers(std::vector <double>);