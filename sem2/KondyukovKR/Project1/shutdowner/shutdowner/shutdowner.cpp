// shutdowner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;

    std::cout << "Do you want to shutdown your computer now (y/n)\n";
    std::cin >> ch;

    if (ch == 'y' || ch == 'Y')
        system("C:\\WINDOWS\\System32\\shutdown -s");
    return 0;
}