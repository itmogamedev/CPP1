#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int main()
{
    std::vector <std::string> my_vector;

    char symbol;

    std::cout << "\x1b[34mEnter a vector data (if you want to stop, enter 'stop' or 's'): \x1b[37m" << std::endl;

    std::string input;

    std::getline(std::cin, input);
    while (input != "stop" and input != "s") {
        my_vector.push_back(input);
        std::getline(std::cin, input);
    }

    std::cout << "\x1b[31mYour vector: {";
    for (int i = 0; i < my_vector.size(); i++) {
        if (i == my_vector.size() - 1)
            std::cout << "'" << my_vector.at(i) << "'";
        else
            std::cout << "'" << my_vector.at(i) << "', ";
    }
    std::cout << "}" << std::endl;

    std::cout << "\x1b[34mEnter a symbol you wanna item start with: " << std::endl;

    std::cin >> symbol;

    std::cout << "\x1b[36mYour symbol: " << symbol << std::endl;
    
    int result = count_if(my_vector.begin(), my_vector.end(), [&symbol](const std::string& _s)
        {
            return _s.at(0) == symbol;
        });

    std::cout << "\x1b[32mresult = " << result << "\x1b[37m";

    return 0;
}