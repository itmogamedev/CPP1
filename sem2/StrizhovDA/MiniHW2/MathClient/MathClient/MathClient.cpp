// MathClient.cpp : Client app for MathLibrary DLL.

#include <iostream>
#include <vector>
#include "MathLibrary.h"

int main()
{
    setlocale(LC_ALL, "ru");
    int amount_of_elem;
    std::vector <long long> vec;
    std::cout << "Введите количество элементов ряда: ";
    std::cin >> amount_of_elem;
    std::cout << "Далее вводите элементы: \n";
    for (int i = 0; i < amount_of_elem; i++)
    {
        long long input;
        std::cin >> input;
        vec.push_back(input);
    }
    int funcVar=-1;
    std::cout << "Введите что вы хотитет сделать с вашим рядом чисел:\n"<<
        "1. Вычислить среднее арифметическое ряда\n"<<
        "2. Вычислить медианное значение ряда\n"<<
        "3. Вычислить среднее квадратическое ряда\n"<<
        "4. Вычислить дисперсию числового ряда\n"<<
        "0. Выйти из программы\n";
    while (funcVar!=0) {
        std::cin >> funcVar;
        switch (funcVar)
        {
        case 1:
            std::cout << "Средним арифметическим ряда является: " << average(vec) << std::endl;
            break;
        case 2:
            std::cout << "Медианное значение ряда является: " << medain(vec) << std::endl;
            break;
        case 3:
            std::cout << "Средним квадратическое ряда является: " << average_qadr(vec) << std::endl;
            break;
        case 4:
            std::cout << "Дисперсией ряда является: " << dispersion(vec) << std::endl;
            break;
        case 0:
            break;
        default:
            std::cout << "Ошибка. Такой функции нет";
            break;
        }
    }
}