#pragma once
#include <iostream>
#include <string>

enum Terrain { Plain, River, Mountain };

class Dino {
protected:
	int str; // сила 10 - 30
	int hp = 100;
	enum Terrain type = Plain;
	std::string name;
	int cost;

public:
	Dino(std::string name);
	Dino();
	~Dino();

	bool operator== (const Dino& d);

	virtual std::string getName();
	virtual int getCost();
	virtual int getHP();
	virtual std::string getStrType();
	virtual std::string getAtk() = 0;

	virtual int damage(Terrain terrain);

	virtual std::string print();
	virtual std::string toString();
};

std::string terrainToString(Terrain terrain);