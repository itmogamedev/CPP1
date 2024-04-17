#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    std::cout << "Сколько строк вы хотите ввести?" << std::endl;
    std::cin >> n;
    std::string temp;
    std::vector <std::string> str;
    std::cout << "Введите строки" << std::endl;
    //str = { "Aaaaaa", "Bbbbbb", "Gouegfow", "Obhoefi", "qegwweg", "qegw", "Ahoe" };
    for (int i = 0; i <= n; i++) {
        std::getline(std::cin, temp);
        str.push_back(temp);
    }
    char simb;
    std::cout << "Введите символ для поиска:" << std::endl;
    std::cin >> simb;
    int answer;
    answer = count_if(str.begin(), str.end(), [simb](std::string _str) {
        return (_str[0] == simb);
        });
    std::cout << answer;
}