#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

auto program = [](const std::vector<std::string>& v, char symb) {
    return count_if(v.begin(), v.end(), [symb](std::string line) {return line[0] == symb; });
};


int main() {
    std::vector<std::string> list = {"pen", "rubber", "pencil", "ruler", "case", "backpack", "notebook"};
    
    while (true){
        std::cout << "Введите символ " << std::endl;
        char x;
        std::cin >> x;
        int character = program(list, x);
        if (character == 1){
            std::cout << "По символу "  << x << " найдено " << character <<  " строка" << std::endl << std::endl;
        }
        else if(character > 1 and character < 5){
            std::cout << "По символу "  << x << " найдено " << character <<  " строки" << std::endl << std::endl;
            
        }
        else{
            std::cout << "По символу "  << x << " найдено " << character <<  " строк" << std::endl << std::endl;
        }
    }
}
