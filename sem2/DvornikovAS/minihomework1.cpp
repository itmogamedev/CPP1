#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>

enum Colors {
    Black = 0,
    Blue = 9,
    Green = 10,
    LBlue = 11,
    White = 15
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    std::vector <std::string> my_vector;

    char symbol;

    SetConsoleTextAttribute(hConsole, Blue);
    std::cout << "Enter a vector data (if you want to stop, enter 'stop' or 's'): " << std::endl;

    SetConsoleTextAttribute(hConsole, White);
    std::string input;

    std::getline(std::cin, input);
    while (input != "stop" and input != "s") {
        my_vector.push_back(input);
        SetConsoleCursorPosition(hConsole, { 0, 1 });
        printf("\33[2K\r");
        SetConsoleCursorPosition(hConsole, { 0, 1 });
        std::getline(std::cin, input);
    }

    SetConsoleCursorPosition(hConsole, { 0, 0 });
    printf("\33[2K\r");
    SetConsoleCursorPosition(hConsole, { 0, 0 });
    SetConsoleTextAttribute(hConsole, LBlue);
    std::cout << "Your vector: {";
    for (int i = 0; i < my_vector.size(); i++) {
        if (i == my_vector.size() - 1)
            std::cout << "'" << my_vector.at(i) << "'}" << std::endl;
        else
            std::cout << "'" << my_vector.at(i) << "', ";
    }

    SetConsoleTextAttribute(hConsole, Blue);
    std::cout << "Enter a symbol you wanna item start with: " << std::endl;

    SetConsoleTextAttribute(hConsole, White);
    std::cin >> symbol;

    SetConsoleCursorPosition(hConsole, { 0, 1 });
    printf("\33[2K\r");
    SetConsoleCursorPosition(hConsole, { 0, 1 });
    SetConsoleTextAttribute(hConsole, LBlue);
    std::cout << "Your symbol: " << symbol << std::endl;
    
    int result = count_if(my_vector.begin(), my_vector.end(), [&symbol](const std::string& _s)
        {
            return _s.at(0) == symbol;
        });

    SetConsoleTextAttribute(hConsole, Green);
    std::cout << "result = " << result;

    SetConsoleTextAttribute(hConsole, White);

    return 0;
}