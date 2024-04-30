#include <iostream>
#include "..\HWlib\Header.h"

int main(){
    float arr[5] = { 1, 4, 2, 3, 5 };
    std::cout << srarf(5, arr) << std::endl;
    std::cout << median(5, arr) << std::endl;
    std::cout << srkvadr(5, arr) << std::endl;
    std::cout << dispers(5, arr) << std::endl;
}