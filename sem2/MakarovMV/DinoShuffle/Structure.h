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

enum Terrain { Plain, River, Mountain };

class Dino {
protected:
    int STR;
    int DEX;
    int INT;
    int HP = 100;
    std::string name;
    int cost;
    int num;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Dino(const std::string& imagePath) {
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << "Error loading image\n";
        }
        sprite.setTexture(texture);
    }

    virtual std::vector<std::string> getinfo() const {
        std::vector<std::string> vec{ name, std::to_string(cost), std::to_string(num), std::to_string(HP), std::to_string(INT), std::to_string(STR), std::to_string(DEX) };
        return vec;
    }

    sf::Sprite getSprite() const {
        return sprite;
    }

    int getCost() const {
        return cost;
    }

    int getNum() const {
        return num;
    }

    std::string getName() const {
        return name;
    }

    virtual int damage(Terrain terrain) = 0;

    int getHP() const {
        return HP;
    }

    void setHP(int hp) {
        HP = hp;
    }

    void reduceHP(int amount) {
        HP -= amount;
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void resetHP() {
        HP = 100;
    }
};

class Tyranosaurus : public Dino {
public:
    Tyranosaurus() : Dino("tyranosaurus.png") {
        STR = 20;
        DEX = 10;
        INT = 15;
        num = 0;
        cost = 500;
        name = "Tyranosaurus";
    }

    int damage(Terrain terrain) override {
        if (terrain == Plain) {
            return 2 * STR;
        }
        else if (terrain == River) {
            return DEX;
        }
        else if (terrain == Mountain) {
            return INT;
        }
        return 0;
    }
};

class Brahiosaurus : public Dino {
public:
    Brahiosaurus() : Dino("brahiosaurus.png") {
        STR = 15;
        DEX = 20;
        INT = 10;
        num = 1;
        cost = 500;
        name = "Brahiosaurus";
    }

    int damage(Terrain terrain) override {
        if (terrain == River) {
            return 2 * DEX;
        }
        else if (terrain == Plain) {
            return STR;
        }
        else if (terrain == Mountain) {
            return INT;
        }
        return 0;
    }
};

class Diplodoc : public Dino {
public:
    Diplodoc() : Dino("diplodoc.png") {
        STR = 10;
        DEX = 15;
        INT = 20;
        num = 2;
        cost = 500;
        name = "Diplodoc";
    }

    int damage(Terrain terrain) override {
        if (terrain == River) {
            return 2 * DEX;
        }
        else if (terrain == Plain) {
            return STR;
        }
        else if (terrain == Mountain) {
            return INT;
        }
        return 0;
    }
};

class Tryceraptops : public Dino {
public:
    Tryceraptops() : Dino("tryceraptops.png") {
        STR = 20;
        DEX = 10;
        INT = 15;
        num = 3;
        cost = 500;
        name = "Tryceraptops";
    }

    int damage(Terrain terrain) override {
        if (terrain == Mountain) {
            return 2 * INT;
        }
        else if (terrain == River) {
            return DEX;
        }
        else if (terrain == Plain) {
            return STR;
        }
        return 0;
    }
};

class Stegosaurus : public Dino {
public:
    Stegosaurus() : Dino("stegosaurus.png") {
        STR = 20;
        DEX = 15;
        INT = 10;
        num = 4;
        cost = 500;
        name = "Stegosaurus";
    }

    int damage(Terrain terrain) override {
        if (terrain == Plain) {
            return 2 * STR;
        }
        else if (terrain == River) {
            return DEX;
        }
        else if (terrain == Mountain) {
            return INT;
        }
        return 0;
    }
};

class Pterodactyl : public Dino {
public:
    Pterodactyl() : Dino("pterodactyl.png") {
        STR = 10;
        DEX = 15;
        INT = 20;
        num = 5;
        cost = 500;
        name = "Pterodactyl";
    }

    int damage(Terrain terrain) override {
        if (terrain == Mountain) {
            return 2 * INT;
        }
        else if (terrain == River) {
            return DEX;
        }
        else if (terrain == Plain) {
            return STR;
        }
        return 0;
    }
};