#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    setlocale(LC_ALL, "RUS");
    std::vector<std::string> lines;

    int stringAmount;
    std::cout << "Введите кол-во строк: ";
    std::cin >> stringAmount;
    std::cout << "Далее вводите ваши строки: \n";
    std::string nowLine;
    for (int i =0; i<=stringAmount; i++)
    {
        getline(std::cin, nowLine);
        std::transform(nowLine.begin(), nowLine.end(), nowLine.begin(), [](char c) {return std::tolower(c); });
        if (nowLine != "") {
            lines.push_back(nowLine);
         nowLine = "";
        }
    }

    char symbol;
    std::cout << "Введите ваш символ для проверки: " << std::endl;
    std::cin >> symbol;
    symbol = std::tolower(symbol);
    int amount;
    amount = std::count_if(lines.begin(), lines.end(), [symbol](std::string line) {return line[0] == symbol; });

    std::cout << "Количество строк, начинающихся с символа \"" << symbol << "\": " << amount << std::endl;
}
