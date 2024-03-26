#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    int k;
    std::cout << "Введите число элементов в векторе: ";
    std::cin >> k;
    std::vector<std::string> vec;
    std::cout << "Введите слова по 1 в строчке: " << std::endl;
    for (int i = 0; i<k; i++){
        std::string ss;
        std::cin >> ss;
        vec.push_back(ss);
    }
    char x;
    std::cout << "Введите проверочный символ: ";
    std::cin >> x;
    int count = count_if(vec.begin(), vec.end(), [x](std::string ss) {return ss[0]==x;});
    std::cout <<"У вас " << count << " слов(а) начинаются с символа '" << x << "', поздравляю!" <<std::endl;
}