#include <vector>
#include <numeric>
#include <iostream>
#include "MathLibrary.h"
#include <cmath>

int main() {
	setlocale(LC_ALL, "ru");

	std::cout << "Доброе пожаловать, вот список команд, благодаря которым вы можете провернуть определенные операции:" << std::endl;
	std::cout << "1. Подсчет среднего арифметического числа" << std::endl;
	std::cout << "2. Подсчет медианы" << std::endl;
	std::cout << "3. Подсчет среднего квадратического числа" << std::endl;
	std::cout << "4. Подсчет дисперсии числового ряда" << std::endl;
	std::cout << "0. Завершить программу" << std::endl;
	std::cout << "Введите нужную операцию: ";

	std::vector<long long> myVector;

	int command;
	std::cin >> command;

	if (command == 1) {
		double average = calculateAverage();
		std::cout << "Среднее арифметическое: " << average << std::endl;
	}

	if (command == 2) {
		double myMedian = median();
		std::cout << "Медиана числового ряда: " << myMedian << std::endl;
	}

	if (command == 3) {
		double funcSquare = square();
		std::cout << "Медиана числового ряда: " << funcSquare << std::endl;
	}

	if (command == 4) {
		double funcDispersion = dispersion();
		std::cout << "Дисперсия чисел: " << funcDispersion << std::endl;
	}

}
