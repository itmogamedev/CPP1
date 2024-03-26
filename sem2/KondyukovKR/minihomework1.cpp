#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int main() {

    std::vector<std::string> vec_for_strings;
    int count_strings;
    std::cout << "How many strings will your vector have: ";
    std::cin >> count_strings;

    std::cout << "Input strings please:" << count_strings << "\n";
    std::string strings_input;

    for (int i = 0; i < count_strings + 1; ++i) {
        std::getline(std::cin, strings_input);
        vec_for_strings.push_back(strings_input);
    }

    char char_for_strings;
    std::cout << "Enter the character to check the strings against: ";
    std::cin >> char_for_strings;

    auto countStringsStartingWith = [&char_for_strings](const std::vector<std::string>& strings) {
        return std::count_if(strings.begin(), strings.end(), [&char_for_strings](const std::string strings_input) {
            return strings_input[0] == char_for_strings and !strings_input.empty(); });
        };

    int count = countStringsStartingWith(vec_for_strings);
    std::cout << "The following number of rows has been detected: " << count << "\n";
    std::cout << "The first character: " << char_for_strings << "\n";
}
