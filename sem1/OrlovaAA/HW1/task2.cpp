
#include <iostream>

int main() {

    const int n0 = 0;
    const int n1 = 1;
    const int n2 = 2;
    const int n3 = 3;
    const int n4 = 4;
    const int n5 = 5;
    const int n6 = 6;
    const int n7 = 7;
    const int n8 = 8;
    const int n9 = 9;

    int input = 0;
    std::cout << "select a number from 0 to 9: ";
    std::cin >> input;

    switch (input) {
    case n0:
        std::cout << "z";
        break;
    case n1:
        std::cout << "o";
        break;
    case n2:
        std::cout << "t";
        break;
    case n3:
        std::cout << "t";
        break;
    case n4:
        std::cout << "f";
        break;
    case n5:
        std::cout << "f";
        break;
    case n6:
        std::cout << "s";
        break;
    case n7:
        std::cout << "s";
        break;
    case n8:
        std::cout << "e";
        break;
    case n9:
        std::cout << "n";
        break;
    }
 
    return 0;
}