#pragma once
#include "Dino.h"
class Plesiosaurus :
    public Dino
{
private:
	int str = 20;
	int hp = 110;
	enum Terrain type = River;
	std::string name = "Plesiosaurus";
	int cost = 20;

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
