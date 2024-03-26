#include <iostream>
#include <algorithm>
#include <vector>
#include <string>



int main() {
    std::vector<std::string> v = {"Alice", "Ben", "Chloe", "Dan", "Debby", "Eve", "Farrel", "George", "Harry", "Harold", "Irene"};
    auto startwithCount = [v] (char _c){
        return std::count_if(v.begin(), v.end(), [_c] (std::string _s){ return _s[0] == _c; });
    }; //LAMBDA-EXPRESSION (itself) returns amount of strings so yes, lambda inside of lambda
    std::cout << startwithCount('A') << std::endl; // 1
    std::cout << startwithCount('D') << std::endl; // 2
    std::cout << startwithCount('Z') << std::endl; // 0

}
