#include "Tyrannosaurus.h"

std::string Tyrannosaurus::print()
{
    return "pics\\pix_tyrannosaur.PNG";
}

std::string Tyrannosaurus::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Tyrannosaurus::getName()
{
    return this->name;
}

int Tyrannosaurus::getCost()
{
    return cost;
}

int Tyrannosaurus::getHP()
{
    return this->hp;
}

std::string Tyrannosaurus::getStrType()
{
    return terrainToString(type);
}

std::string Tyrannosaurus::getAtk()
{
    return std::to_string(str);
}

int Tyrannosaurus::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
