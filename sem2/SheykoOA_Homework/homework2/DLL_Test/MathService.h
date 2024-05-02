#include <vector>

#ifndef MATHSERVICE_EXPORTS
#define MATHSERVICE_API __declspec(dllexport)
#else
#define MATHSERVICE_API __declspec(dllimport)
#endif

extern "C" MATHSERVICE_API double mean(const std::vector<double>& numbers);
extern "C" MATHSERVICE_API double median(const std::vector<double>& numbers);
extern "C" MATHSERVICE_API double medianSquared(const std::vector<double>& numbers);
extern "C" MATHSERVICE_API double variance(const std::vector<double>& numbers);


