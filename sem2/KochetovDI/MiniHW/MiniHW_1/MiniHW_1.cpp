#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> strings = { "Dog", "Mountain", "Sunshine", "Butterfly", "Chocolate", "Egg" };

    char startingStringChar;

    auto countStringsStartingWith = [&](char ch) {
        int count = 0;
        for (const std::string& str : strings) {
            if (!str.empty() && str[0] == ch) {
                count++;
            }
        }
        return count;
        };

    std::cout << "Enter the letter you want to search for:" << std::endl;
    std::cin >> startingStringChar;
    std::cout << "Number of strings starting with '" << startingStringChar << "': " << countStringsStartingWith(startingStringChar) << std::endl;

    return 0;
}