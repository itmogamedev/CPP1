#include "Brachiosaurus.h"


std::string Brachiosaurus::print()
{
    return "pics\\pix_brachiosaur.PNG";
}

std::string Brachiosaurus::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Brachiosaurus::getName()
{
    return this->name;
}

int Brachiosaurus::getCost()
{
    return cost;
}

int Brachiosaurus::getHP()
{
    return this->hp;
}

std::string Brachiosaurus::getStrType()
{
    return terrainToString(type);
}

std::string Brachiosaurus::getAtk()
{
    return std::to_string(str);
}

int Brachiosaurus::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
