#include <iostream>
#include "..\Domashka2\Header.h"
using namespace std;

int main()
{
    int n = 15;
    int ryad[15]{ 2, 5, 7 ,16, 22, 9, 17, 23, 11, 12, 5, 9, 11, 15, 20 };

    setlocale(LC_ALL, "RU");

    cout << "\tСреднее арифметическое: " << mid(ryad, n) << endl;
    cout << "\tМедиана: " << med(ryad, n) << endl;
    cout << "\tСреднее квадратическое: " << midkv(ryad, n) << endl;
    cout << "\tДисперсия: " << disp(ryad, n) << endl;
}
