#include "pch.h"
#include <vector>
#include <algorithm>
#include "framework.h"
#include <iostream>
#include <cmath>

float average;

float Average(std::vector <int> mass)
{
	float answer = 0.0;
	for (int i = 0; i < mass.size(); i++)
	{
		answer += mass.at(i);
	}
	average = answer / mass.size();
	return average;
}

void Mediana(std::vector <int> mass)
{
	std::sort(mass.begin(), mass.end());
	if (mass.size() % 2 == 0)
	{
		int middle;
		middle = mass.size() / 2;
		std::cout << mass.at(middle) << ", " << mass.at(middle + 1) << std::endl;
	}
	else
	{
		int middle;
		middle = mass.size() / 2;
		std::cout << mass.at(middle) << std::endl;
	}
}

float Mean_square1(std::vector <int> mass)
{
	float answer = 0.0;
	for (int i = 0; i < mass.size(); i++)
	{
		answer += pow(mass.at(i), 2);
	}
	answer = sqrt(answer / mass.size());
	return answer;
}

float Mean_square2(std::vector <int> mass)
{
	float answer = 0.0;
	for (int i = 0; i < mass.size(); i++)
	{
		answer += pow((mass.at(i) - average), 2);
	}
	answer /= (mass.size() - 1);
	answer = sqrt(answer);
	return answer;
}

float Dispersion(std::vector <int> mass)
{
	float answer = 0.0;
	for (int i = 0; i < mass.size(); i++)
	{
		answer += pow((mass.at(i) - average), 2);
	}
	answer /= (mass.size() - 1);
	return answer;
}