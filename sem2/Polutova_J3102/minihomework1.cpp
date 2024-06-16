#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::size_t beginsWith(std::vector<std::string> vec, char start) {
    return std::count_if(vec.begin(), vec.end(), [start](std::string str) {
        return str.length() != 0 && str[0] == start; //required lambda function
        });
}

int main()
{
    std::vector<std::string> yourVec;
    int n;
    std::cout << "How many strings will your vector have: "; //a little bit of interactivity
    std::cin >> n;
    std::cout << "Input " << n << " strings please.\n";
    std::string str;
    std::getline(std::cin, str); //just a dummy for getline to work properly
    for (int i = 0; i < n; i++) {
        std::getline(std::cin, str);
        yourVec.push_back(str);
    }

    std::cout << "Input a char you want to check your strings to begin with: ";
    char begin;
    std::cin >> begin;

    std::cout << "There are " << static_cast<int>(beginsWith(yourVec, begin)) << " strings in your vector that begins with '" << begin << "'.\n";
}
