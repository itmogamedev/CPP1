#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

// for testing purposes only
int countTest(const std::vector<std::string>& data, const char& symbol)
{
    return count_if(data.begin(), data.end(), [&symbol](const std::string& str){ return str[0] == symbol; });
}
int tests()
{
    std::vector<std::string> data;
    char symbol;
    
    //// test 1 - empty data, empty symbol - RETURNS 0 ////
    data.clear();
    symbol = 0;
    assert(countTest(data, symbol) == 0);
    std::cout << "TEST 1 | PASSED | empty data, empty symbol" << std::endl;
    
    //// test 2 - non-empty data, empty symbol - RETURNS 0 ////
    data.clear();
    data.push_back("anytext");
    symbol = 0;
    assert(countTest(data, symbol) == 0);
    std::cout << "TEST 2 | PASSED | non-empty data, empty symbol" << std::endl;
    
    //// test 3 - one true data entry, no others - RETURNS 1 ////
    data.clear();
    data.push_back("anytext");
    symbol = 'a';
    assert(countTest(data, symbol) == 1);
    std::cout << "TEST 3 | PASSED | one true data entry, no others" << std::endl;
    
    //// test 4 - one true data entry, others false - RETURNS 1 ////
    data.clear();
    data.push_back("anytext");
    data.push_back("btext");
    data.push_back("ctext");
    symbol = 'b';
    assert(countTest(data, symbol) == 1);
    std::cout << "TEST 4 | PASSED | one true data entry, others false" << std::endl;
    
    //// test 5 - two true data entries, one false - RETURNS 2 ////
    data.clear();
    data.push_back("anytext");
    data.push_back("brownie");
    data.push_back("atrophy");
    symbol = 'a';
    assert(countTest(data, symbol) == 2);
    std::cout << "TEST 5 | PASSED | two true data entries, one false" << std::endl;
    
    //// test 6 - all 4 true data entries - RETURNS 4 ////
    data.clear();
    data.push_back("x_anytext");
    data.push_back("xenophobia");
    data.push_back("xylophone");
    data.push_back("xeroradiography");
    symbol = 'x';
    assert(countTest(data, symbol) == 4);
    std::cout << "TEST 6 | PASSED | all true data entries" << std::endl;
    
    std::cout << std::endl;
    std::cout << "all tests passed" << std::endl;
    return 0;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> data;
    char symbol;
    
    int countResult = count_if(data.begin(), data.end(), [&symbol](const std::string& str){ return str[0] == symbol; }); // искомая функция
    tests(); // тесты искомой функции
    return 0;
}