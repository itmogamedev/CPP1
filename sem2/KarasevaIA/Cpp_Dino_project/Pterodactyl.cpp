#include "Pterodactyl.h"

std::string Pterodactyl::print()
{
    return "pics\\pix_pterodactyl.PNG";
}

std::string Pterodactyl::toString()
{
    return std::to_string(str) + " strength, " + std::to_string(hp) + " hp, type - " + terrainToString(type);
}

std::string Pterodactyl::getName()
{
    return this->name;
}

int Pterodactyl::getCost()
{
    return cost;
}

int Pterodactyl::getHP()
{
    return this->hp;
}

std::string Pterodactyl::getStrType()
{
    return terrainToString(type);
}

std::string Pterodactyl::getAtk()
{
    return std::to_string(str);
}

int Pterodactyl::damage(Terrain terrain)
{
    if (terrain == this->type) {
        return this->str * 2;
    }
    else {
        return this->str;
    }
}
