#include <iostream>


int main()
{
    double d;
    d = 18446744073709551616; // это превращается в 0
    std::cout << d << std::endl;
    std::cout << d+10 << std::endl;
    
    d = 18446744073709551615; // это ещё влезает в тип double, из-за представления экспонентой
    //                           не увеличивется при +10
    std::cout << d << std::endl;
    std::cout << d+10 << std::endl;
    std::cout << d*10000000000000000000000000000000000000000000000000000000000 << std::endl;
    // даже так не переполняется

    d = 1; // и это не переполняется
    std::cout << d << std::endl;
    std::cout << d+18446744073709551615 << std::endl;
    
    d = 6.18446744073709551616; // это обрезается
    std::cout << d << std::endl;
    // double почти не переполняется
    
    return 0;
}
