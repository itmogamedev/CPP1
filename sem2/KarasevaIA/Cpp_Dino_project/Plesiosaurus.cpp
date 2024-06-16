#include "Plesiosaurus.h"

std::string Plesiosaurus::print()
{
    return "pics\\pix_plesiosaur.PNG";
}

std::string Plesiosaurus::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Plesiosaurus::getName()
{
    return this->name;
}

int Plesiosaurus::getCost()
{
    return cost;
}

int Plesiosaurus::getHP()
{
    return this->hp;
}

std::string Plesiosaurus::getStrType()
{
    return terrainToString(type);
}

std::string Plesiosaurus::getAtk()
{
    return std::to_string(str);
}

int Plesiosaurus::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
