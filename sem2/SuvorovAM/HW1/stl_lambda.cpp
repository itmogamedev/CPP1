#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<std::string> all_strings;
    std::cout << "Введите строки (каждая с новой строки, для завершения введите на новой строке '.'):\n";
    std::string input;
    while (true) {
        std::cin >> input;
        if (input == ".") {
            break;
        }
        all_strings.push_back(input);
    }
    char Symbol;
    std::cout << "Введите символ: ";
    std::cin >> Symbol;

    int quontity = std::count_if(all_strings.begin(), all_strings.end(), [&Symbol](const std::string & all_strings) {
        return not(all_strings.empty()) and all_strings.front() == Symbol; });
    std::cout << "Количество строк, начинающихся с символа '" << Symbol << "': " << quontity << std::endl;
    return 0;
};