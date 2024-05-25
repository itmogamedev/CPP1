#include <iostream>
#include <vector>
#include <string>
#include "..\..\Dll1\Dll1\Header.h"

std::vector <double> v = {};

bool is_Double(const std::string& s) {
    return s.find_first_not_of("0123456789. -") == std::string::npos;
}

int main()
{

    std::string input;
    std::cout << "Enter a vector data in double (if you want to stop, enter 'stop' or 's'): " << std::endl;

    do {
        std::getline(std::cin, input);
        if (is_Double(input))
            v.push_back(std::stod(input));
        else if (input != "s" and input != "stop" and input != "S" and input != "STOP")
            std::cout << "Enter a double data!" << std::endl;
    } while (input != "s" and input != "stop" and input != "S" and input != "STOP");

    std::cout << "Your vector: {";
    for (int i = 0; i < v.size(); i++) {
        if (i != v.size() - 1)
            std::cout << v.at(i) << ", ";
        else
            std::cout << v.at(i);
    }
    std::cout << "}" << std::endl << std::endl;

    std::cout << "Average of vector: ";
    std::cout << average_of(v) << std::endl;

    std::cout << "Median of vector: ";
    std::cout << median(v) << std::endl;

    std::cout << "The quadratic mean: ";
    std::cout << average_kvadr_of(v) << std::endl;

    std::cout << "Dispersion: ";
    std::cout << dispers(v) << std::endl;

    std::cout << "\nEverything works!" << std::endl;

    return 0;
}