#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
int main()
{

    std::vector<std::string> Vec{ "rajir", "aaaaa", "baaaaac", "abc" };

    char letter;
    std::cin >> letter;

    int result = std::count_if(Vec.begin(), Vec.end(), [letter](std::string s) {return s[0] == letter; });
    std::cout << result << " Elements start with " << letter << std::endl;
}

