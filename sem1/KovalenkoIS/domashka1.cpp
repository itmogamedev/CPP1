#include <iostream>
int main() {
    char symbol = 'A'; //65 элемент в таблице ASCII (всего 255)
    std::cout << symbol << " " << int(symbol) << std::endl;
    symbol = symbol + 192; //выводит ☺ (или пустоту) тк он первый в таблице (вышли за пределы)
    std::cout << symbol << " " << int(symbol);
    return 0;
}