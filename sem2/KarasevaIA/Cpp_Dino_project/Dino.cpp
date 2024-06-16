#include "Dino.h"

Dino::Dino(std::string name) {
	this->name = name;
}

Dino::Dino() {
}

Dino::~Dino() {
}

bool Dino::operator==(const Dino& d)
{
	if (getName() == d.name)
	{
		return true;
	}
	return false;
}

std::string Dino::getName()
{
	return std::string();
}

int Dino::damage(Terrain terrain) {
	if (terrain == this->type) {
		return this->str * 2;
	} else {
		return this->str;
	}
}

int Dino::getHP()
{
	return 100;
}

int Dino::getCost()
{
	return 0;
}

std::string Dino::getStrType()
{
	return std::string();
}

std::string Dino::print() {
	return std::string();
}

std::string Dino::toString()
{
	return std::string();
}

std::string terrainToString(Terrain terrain)
{
	if (terrain == Plain)
	{
		return "Plain";
	}
	else if (terrain == Mountain)
	{
		return "Mountain";
	}
	else if (terrain == River)
	{
		return "River";
	}

	return "Plain";
}
