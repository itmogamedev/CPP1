#include "pch.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) double average_of(std::vector <double> v)
{
	if (v.size() == 0) {
		std::cout << "N/A ";
		return 0;
	}
	double s = 0;
	for (int i = 0; i < v.size(); i++)
		s += v.at(i);
	return (double)(s / v.size());
}

extern "C" __declspec(dllexport) double median(std::vector <double> v)
{
	if (v.size() == 0) {
		std::cout << "N/A ";
		return 0;
	}
	std::sort(v.begin(), v.end());

	int s = v.size() / 2;

	if (v.size() % 2 == 0) {
		return (double)((v.at(s) + v.at(s - 1)) / 2);
	}
	else {
		return v.at(s);
	}
}

extern "C" __declspec(dllexport) double average_kvadr_of(std::vector <double> v)
{
	if (v.size() == 0) {
		std::cout << "N/A ";
		return 0;
	}
	double s = 0;
	for (int i = 0; i < v.size(); i++)
		s += pow(v.at(i), 2);

	return (double)sqrt(s / v.size());
}

extern "C" __declspec(dllexport) double dispers(std::vector <double> v)
{
	if (v.size() == 0) {
		std::cout << "N/A ";
		return 0;
	}
	double s = 0;
	double aver = average_of(v);
	for (int i = 0; i < v.size(); i++)
		s += pow(v.at(i) - aver, 2);
	return (double)(s / v.size());
}