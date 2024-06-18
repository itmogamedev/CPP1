#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::string> strings = {"Hello", "World", "Baby", "GameDev", "Is", "Cool", "Hashbrown"};
    char symbol;
    std::cout << "Enter symbol: ", std::cin >> symbol;
    
    int result = std::count_if(strings.begin(), strings.end(), [symbol](const std::string& str) {
        return str[0] == symbol;
    });

    std::cout << result << std::endl;
    return 0;
}
