#include <iostream>
#include <vector>

int ReverseNum(int num)
{
    int ten = 1;

    std::vector<int> decomposeNum;
    
    while (num != 0)
    {
        decomposeNum.push_back(num % 10);

        num /= 10;
    }
    
    for (int i = decomposeNum.size() - 1; i >= 0; i--)
    {
        num += decomposeNum[i] * ten;
        ten *= 10;
    }
    
    return num;
}

int main()
{
    int num;
    std::cin >> num;

    std::cout << ReverseNum(num);
}