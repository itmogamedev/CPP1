#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
	std::vector<std::string> my_vec;
	my_vec.push_back("hello");
	my_vec.push_back("good");
	my_vec.push_back("huge");
	char letter;
	std::cout << "Enter any letter" << std::endl;
	std::cin >> letter;
	int result = count_if(my_vec.begin(), my_vec.end(), [letter](std::string s) {
		return s[0] == letter;
		});
	std::cout << "Count first letter" <<  " " << letter << " = " << result << std::endl;
}