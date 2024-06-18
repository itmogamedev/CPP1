#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> lines;

    std::cout << "Write lines\n\nTo end line-writing: write with a new line \"STOP\" and press Enter\n";

    std::string nowLine;
    while (true)
    {
        getline(std::cin, nowLine);

        if (nowLine != "STOP")
        {
            std::transform(nowLine.begin(), nowLine.end(), nowLine.begin(), [](char c) {return std::tolower(c); });

            if(nowLine != "")
                lines.push_back(nowLine);

            nowLine = "";
        }
        else break;
    }

    char symbol;
    std::cout << "\nWrite your symbol" << std::endl;
    std::cin >> symbol;
    symbol = std::tolower(symbol);

    int c;
    c = std::count_if(lines.begin(), lines.end(), [symbol](std::string line) {return line[0] == symbol; });

    std::cout << "And number of lines starts with a symbol" << " \"" << symbol << "\" " << "is " << c << std::endl;
}
