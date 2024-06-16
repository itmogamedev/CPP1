
#include <iostream>

int main() {

    char a = 256; //происходит переполнение, тк значение a превышает существующий лимит
    std::cout << a << std::endl;
 
    return 0;
}