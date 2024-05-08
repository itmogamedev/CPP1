#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::vector;
using std::string;

int main()
{
    vector<string> vc = { "ni", "ko", "nn" };

    auto f = [&vc](char x)
    {
        int c = 0;
        for (std::string word : vc) {
            if (word[0] == x) { c++; }
        }
        return c;
    };
    cout << f('n');

}