#ifndef DatabaseFunc_hpp
#define DatabaseFunc_hpp

#include "includes.h"

void insertUser(Textbox textbox);
void selectInventory (std::string &outInventory);
void selectBalance(sf::Font font, std::string &outStr);
void selectNamespace(std::string &outStrNamespace);
void updateBalance(std::string outStr, std::string name);
void updateBalanceAfterWin();
#endif /* DatabaseFunc_hpp */
