#pragma once

#include <iostream>
#include <vector>

class Player {
private:
    std::vector<char> dinoList{'t', 'r', 'n'};
    int money = 100;
    int hp = 0;
public:
    void setMoney(int m) {
        money = m;
    }
    void setList(int pos, char name) {
        dinoList[pos] = name;
    }
    void setHP(int n) {
        hp = n;
    }

    int getMoney() const {
        return money;
    }
    char getList(int pos) {
        return dinoList[pos];
    }
    int getHP() const {
        return hp;
    }

    void buyDino(int cost, char name, int pos) {
        if (money >= cost) {
            money -= cost;
            dinoList[pos] = name;
        }
    }
};