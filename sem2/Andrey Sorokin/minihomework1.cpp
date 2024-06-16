#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    vector<string> vect;

    string str = "";
    cout << "Вводите строки через Enter. Чтобы закончить напишите stop" << endl;
    while (str != "stop") {
        cin >> str;
        vect.push_back(str);
    }

    char g;
    cout << "Введите символ с которого должна начинаться строка: ";
    cin >> g;

    int result = count_if(vect.begin(), vect.end(), [g](string n) {return n[0] == g; });

    cout << "\n\t\t\t\t\tРезультат: " << result << endl;
}