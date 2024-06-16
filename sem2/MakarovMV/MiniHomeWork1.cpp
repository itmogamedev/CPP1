
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> words = { "apple", "banana", "orange", "afghanistan" };
    std::string a;
    std::cout << "Enter a character: ";
    std::cin >> a;
    int c = std::count_if(words.begin(), words.end(), [&](std::string x) {return  x[0] == a[0];});
    std::cout << c << std::endl;

    return 0;
}

