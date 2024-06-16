#pragma once
#include "Dino.h"
class Brachiosaurus :
    public Dino
{
private:
	int str = 25;
	int hp = 130;
	enum Terrain type = Plain;
	std::string name = "Brachiosaurus";
	int cost = 30;

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
