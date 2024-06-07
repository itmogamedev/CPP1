#pragma once

#ifndef GAMEDATA_H__
#define GAMEDATA_H__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class GameData {
    int bal = 300;
    std::vector <bool> status = {false, false, false, false};
public:

    // Метод для записи значения balance в файл
    void saveDataToFile(const std::string&);

    // Метод для чтения значения balance из файла
    void loadDataFromFile(const std::string&);

    int getBalance();
    void setBalance(int);
    std::vector <bool> getStatus();
    void setStatus(std::vector <bool>);
};

#endif