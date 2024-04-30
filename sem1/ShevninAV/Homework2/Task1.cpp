#include <iostream>
#include <vector>

void FibonacciRow(int length)
{
    if (length < 0)
        throw std::range_error("Fibonacci row length cannot be less than 0");

    if (length == 0) return;

    std::cout << 0 << " ";

    if (length == 1) return;

    std::cout << 1 << " ";

    if (length == 2) return;
    
    std::vector<int> fibonacciRow = {0, 1};

    for (int i = 2; i < length; i++)
    {
        fibonacciRow.push_back(fibonacciRow[i - 1] + fibonacciRow[i - 2]);

        std::cout << fibonacciRow[i] << " ";
    }
}

int main()
{
    int fibonacciRowLength;
    std::cin >> fibonacciRowLength;

    FibonacciRow(fibonacciRowLength);
}
