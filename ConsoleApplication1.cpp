#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec;
    std::string input;
    char startChar;

    std::cout << "Enter strings for the vector, end with 'done':\n";
    while (std::cin >> input && input != "done") {
        vec.push_back(input);
    }

    std::cout << "Enter the character to count strings that start with it: ";
    std::cin >> startChar;

    auto count_start_char = [](const std::vector<std::string>& v, char c) -> int {
        int count = 0;
        for (const auto& s : v) {
            if (!s.empty() && s[0] == c) {
                ++count;
            }
        }
        return count;
    };

    int count = count_start_char(vec, startChar);
    std::cout << "Number of strings starting with '" << startChar << "': " << count << std::endl;

    return 0;
}
