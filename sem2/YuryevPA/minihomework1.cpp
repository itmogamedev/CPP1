#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

int main() {
    std::vector<std::string> vec = {
        "hello",
        "world",
        "i",
        "like",
        "programing",
        "abba",
        "bba",
        "baba",
        "is",
        "you",
        "my",
        "isu",
        "is",
        "333250",
        "kjhgfsdarf",
        "iuhsagej",
        "join",
        "to",
        "the",
        "club",
        "boddy"
    };

    char letter;
    std::cin >> letter;
    int answer = std::count_if(vec.begin(), vec.end(), [letter](std::string elem)
    {
        return elem[0] == letter ? true : false;
    });
    std::cout << answer << std::endl;
}