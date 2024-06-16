#include <bits/stdc++.h>

int main()
{
    auto Lambda = [](std :: vector <std :: string> vec, char ch) {
        int count = 0;
        for (auto value : vec)
        {
            if (value[0] == ch) count++;
        }
        return count;
    };

    std :: vector <std :: string> vec;
    char ch;
    std :: cout << "Enter char.\n";
    std :: cin >> ch;
    std :: cout << "Enter lines.\nTo stop enter !\n";
    while (std :: cin)
    {
        std :: string st;
        std :: getline(std :: cin, st);
        vec.push_back(st);
        if (st == "!") break;
    }

    std :: cout << Lambda(vec, ch);

    return 0;
}
