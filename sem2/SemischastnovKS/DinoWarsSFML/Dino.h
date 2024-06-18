#pragma once

#include <iostream>


class Dino {
protected:
    int STR;
    int DEX;
    int INT;
    std::string name;
public:
    virtual int damage(std::string terrain) = 0;
    virtual void setSTR(int num){
        STR = num;
    }
    virtual void setDEX(int num){
        DEX = num;
    }
    virtual void setINT(int num){
        INT = num;
    }
    virtual void setName(const std::string &dinoName) {
        name = dinoName;
    }
};

class DinoStr: public Dino {
public:
    int damage(std::string terrain) override {
        if (terrain == "plain") {
            return 2 * STR;
        }
        else if (terrain == "river") {
            return DEX;
        }
        else {
            return INT;
        }
    }
};

class DinoDex: public Dino {
public:
    int damage(std::string terrain) override {
        if (terrain == "plain") {
            return STR;
        }
        else if (terrain == "river") {
            return 2 * DEX;
        }
        else {
            return INT;
        }
    }
};

class DinoInt: public Dino {
public:
    int damage(std::string terrain) override {
        if (terrain == "plain") {
            return STR;
        }
        else if (terrain == "river") {
            return DEX;
        }
        else {
            return 2 * INT;
        }
    }
};
