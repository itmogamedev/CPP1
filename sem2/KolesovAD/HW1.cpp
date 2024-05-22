#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>


int main() {
	std::vector<std::string> strings;
	std::cout << "Hello! This is a program that takes a vector of strings from user and returns number of those of them which starts from a certain symbol (also takes it from user)." << std::endl;
	std::cout << "Enter vector of strings (one string per line, enter \"end\" to finish input):" << std::endl;
	std::string line;
	std::cin >> line;
	while (line != "end") {
		strings.push_back(line);
		std::cin >> line;
	}
	std::cout << "Enter the symbol to see the number of strings which starts from it: ";
	char symbol;
	std::cin >> symbol;
	int count = count_if(strings.begin(), strings.end(), [symbol] (std::string line) {
		return line[0] == symbol;
		});
	std::cout << "The number of strings which starts from \"" << symbol << "\" is " << count << ".";
}
