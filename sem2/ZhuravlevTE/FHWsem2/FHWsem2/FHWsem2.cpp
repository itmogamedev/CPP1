#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<string> words;
	int number;
	cin >> number;

	// задаём слова в вектор
	for (int i = 0; i < number; i++) {
		string word;
		cin >> word;

		words.push_back(word);
	}

	cout << endl;

	auto countletters = [&words](char letter)
	{
		int i = 0;

		for (string word : words) {
			if (word[0] == letter) {
				i++;
			}
		}

		return i;
	};


	char bukva;
	cin >> bukva;

	cout << endl;
	cout << countletters(bukva);
}