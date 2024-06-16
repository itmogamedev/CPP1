#pragma once
#include "Dino.h"
class Triceratops :
    public Dino
{
private:
	int str = 25;
	int hp = 110;
	enum Terrain type = Mountain;
	std::string name = "Triceratops";
	int cost = 25;

public:
	std::string getName();
	int getCost();
	int getHP();
	std::string getStrType();
	std::string getAtk();

	int damage(Terrain terrain);

	std::string print();
	std::string toString();
};
