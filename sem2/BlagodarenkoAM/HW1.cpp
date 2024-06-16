#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> strings = {};
    char targetChar;
    std::string b, a = "";
    std::cout << "text\n";
    std::getline(std::cin,b,'\n');
    std::cout << "char\n";
    std::cin >> targetChar;
    for (int i = 0; i <= b.length(); i++) {
        if (b[i] == ' ') {
            strings.push_back(a);
            a = "";
        }
        else {
            a += b[i];
        }
    }
    strings.push_back(a);

    int count = std::count_if(strings.begin(), strings.end(), [targetChar](const std::string& str) {
        return !str.empty() && str.front() == targetChar;
        });

    std::cout << "Number of strings starting with '" << targetChar << "': " << count << std::endl;

    return 0;
}