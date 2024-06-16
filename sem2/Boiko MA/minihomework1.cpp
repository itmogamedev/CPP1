#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
	std::vector<std::string> vecForCheck;

	for (int a = 0; a <= 200; a++)
	{
	    vecForCheck.push_back(std::to_string(rand()%1000 + 50 - 20));
	}

	char lookFor; 
	std::cout << "What are you looking for today?" << std::endl << "Type in a digit, as we are looking through a vector of numbers" << std::endl << "(if you don't want to get a zero :3)" << std::endl;
	std::cin >> lookFor;

	int howMany = count_if(vecForCheck.begin(), vecForCheck.end(), [lookFor] (std::string _n) {
			return _n[0] == lookFor;
	});

	std::cout << howMany << " strings in our vector start with " << lookFor << std::endl;
}
