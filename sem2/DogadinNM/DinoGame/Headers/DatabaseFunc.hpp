//
//  DatabaseFunc.hpp
//  DinoGame
//
//  Created by Nikitoooooozy) on 16.05.2024.
//  Copyright © 2024 Nikitoooooozy). All rights reserved.
//

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
