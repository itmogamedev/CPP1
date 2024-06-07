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

    // ����� ��� ������ �������� balance � ����
    void saveDataToFile(const std::string&);

    // ����� ��� ������ �������� balance �� �����
    void loadDataFromFile(const std::string&);

    int getBalance();
    void setBalance(int);
    std::vector <bool> getStatus();
    void setStatus(std::vector <bool>);
};

#endif