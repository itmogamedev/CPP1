#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdlib>  

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;
using std::ifstream;
std::vector<std::string> getdinos() {
    std::vector<std::string> Dinomass;
    std::ifstream Dinostream("./Dinodata.data");
    std::string dino1;

    if (Dinostream.is_open()) {
        while (std::getline(Dinostream, dino1)) {
            Dinomass.push_back(dino1);
        }
        Dinostream.close();
    }

    return Dinomass;
}

std::vector<std::string> NmDinos = getdinos();

int getmoney() {
    int Moneyint;
    std::vector<std::string> inf;
    std::ifstream money;
    money.open("./moneydata.data");
    std::string balance;

    if (money.is_open()) {
        while (std::getline(money, balance)) {
            Moneyint = stoi(balance);
        }
    }

    return Moneyint;
}

int Mnny = getmoney();