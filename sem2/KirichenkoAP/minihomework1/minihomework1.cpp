#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
	std::vector<std::string> myVec;
	myVec.push_back("garden");
	myVec.push_back("fashion");
	myVec.push_back("university");
	myVec.push_back("animal");
	myVec.push_back("feeling");
	myVec.push_back("ultraviolence");
	myVec.push_back("figure");
	myVec.push_back("energy");

	std::cout << "Strings of vector:" << "\n";

	std::for_each(myVec.begin(), myVec.end(), [](std::string n) {
		std::cout << n << "\n";
	});

	std::cout << "\n";

	char letter = 'f';

	std::cout << "Press a letter: ";
	std::cin >> letter;
	std::cout << "\n";

	int result = count_if(myVec.begin(), myVec.end(), [&letter](std::string n) {
			return (n[0] == letter) == true;
		});

	std::cout << "The count of strings starting with '" << letter << "': " << result << "\n";
}