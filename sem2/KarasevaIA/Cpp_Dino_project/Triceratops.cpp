#include "Triceratops.h"

std::string Triceratops::print()
{
    return "pics\\pix_triceraptor.PNG";
}

std::string Triceratops::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Triceratops::getName()
{
    return this->name;
}

int Triceratops::getCost()
{
    return this->cost;
}

int Triceratops::getHP()
{
    return this->hp;
}

std::string Triceratops::getStrType()
{
    return terrainToString(type);
}

std::string Triceratops::getAtk()
{
    return std::to_string(str);
}

int Triceratops::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
