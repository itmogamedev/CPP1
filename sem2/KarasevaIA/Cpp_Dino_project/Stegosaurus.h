#pragma once
#include "Dino.h"
class Stegosaurus : public Dino {
private:
	int str = 15;
	int hp = 100;
	enum Terrain type = River;
	std::string name = "Stegosaurus";
	int cost = 10;

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
