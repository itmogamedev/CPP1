#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<std::string> v;
	int n, result;
	std::string line;
	char symbol;
	std::cout << "How much lines? ";
	std::cin >> n;

	std::cout << "Enter lines: ";
	std::getline(std::cin, line);
	for (int i = 0; i < n; i++) {
		std::getline(std::cin, line);
		v.push_back(line);
	}

	std::cout << "Enter symbol: ";
	std::cin >> symbol;

	result = std::count_if(v.begin(), v.end(), [symbol](std::string s) {
		return s.at(0) == symbol;
		});

	std::cout << "Lines starting with '" << symbol << "' symbol - " << result << std::endl;
	return 0;
}