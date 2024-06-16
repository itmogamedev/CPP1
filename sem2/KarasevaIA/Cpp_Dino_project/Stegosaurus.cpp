#include "Stegosaurus.h"

std::string Stegosaurus::print()
{
    return "pics\\pix_stegosaur.PNG";
}

std::string Stegosaurus::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Stegosaurus::getName()
{
    return this->name;
}

int Stegosaurus::getCost()
{
    return cost;
}

int Stegosaurus::getHP()
{
    return this->hp;
}

std::string Stegosaurus::getStrType()
{
    return terrainToString(type);
}

std::string Stegosaurus::getAtk()
{
    return std::to_string(str);
}

int Stegosaurus::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
