#include <iostream>
#include <vector>
#include <string>

int main() {
	std::vector<std::string> a;
	std::string s;
	while (true) {
		std::getline(std::cin, s);
		if (s.empty()) {
			break;
		}
		a.push_back(s);
	}
	char symb;
	std::cout << "Enter a symbol" << std::endl;
	std::cin >> symb;
	for (int i = 0; i < a.size(); i++) {
		if (a[i][0] == symb) {
			std::cout << a[i] << std::endl;
		}
	}
	return 0;
}