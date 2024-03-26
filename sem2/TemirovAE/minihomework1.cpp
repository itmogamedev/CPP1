#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


int main()
{
	int k;
	std::cout << "Amount of vector elements: ";
	std::cin >> k;

	char a;
	std::cout << "Which symbol are you searching for?: ";
	std::cin >> a;

	std::vector<std::string> vec;
	std::cout << "Enter the vector( 1 element per line )" << std::endl;

	std::string line;
	std::getline(std::cin, line);
	for (size_t i = 0; i < k; i++)
	{
		std::getline(std::cin, line);
		vec.push_back(line);
	}


	int count = count_if(vec.begin(), vec.end(), [a](const std::string str) {return str[0] == a; });
	std::cout << count;
}