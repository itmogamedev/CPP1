#include "Parasaurolophus.h"

std::string Parasaurolophus::print()
{
	return "pics\\pix_parasaur.PNG";
}

std::string Parasaurolophus::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Parasaurolophus::getName()
{
    return this->name;
}

int Parasaurolophus::getCost()
{
    return cost;
}

int Parasaurolophus::getHP()
{
    return this->hp;
}

std::string Parasaurolophus::getStrType()
{
    return terrainToString(type);
}

std::string Parasaurolophus::getAtk()
{
    return std::to_string(str);
}

int Parasaurolophus::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
