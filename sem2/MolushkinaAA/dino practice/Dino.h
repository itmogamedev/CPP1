#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> 
#include "windows.h"
#include <fstream>
#include <string>
#include <cmath>

class Dinozaur {
protected:
	int hp = 100;
	int cost;
	int power;
	int dexterity;
	int intellect;
	int num;
	std::string name;
	int dino_terrain;
	std::string terrain;
public:
	Dinozaur(int initialNum, int initialCost, int initialPower, int initialDexterity, int initialIntellect, int initialDinoTerrain, 
		std::string initialTerrain, std::string initialName) : num(initialNum), cost(initialCost), power(initialPower), dexterity(initialDexterity),
		intellect(initialIntellect), dino_terrain(initialDinoTerrain), terrain(initialTerrain), name(initialName) {}

	int get_hp() const {
		return hp;
	}
	void set_hp(int value) {
		hp = value;
	}
	int get_num() const {
		return num;
	}
	int get_cost() const {
		return cost;
	}
	int get_power() const {
		return power;
	}
	int get_dexterity() const {
		return dexterity;
	}
	int get_intellect() const {
		return intellect;
	}
	int get_dino_terrain() const {
		return dino_terrain;
	}
	std::string get_name() const {
		return name;
	}
	std::string get_terrain() const {
		return terrain;
	}
};
class Tiranozavr : public Dinozaur {
public:
	Tiranozavr() : Dinozaur(0, 100, 10, 10, 10, 0, "Plain", "Tiranozavr") {}
};
class Triceratops : public Dinozaur {
public:
	Triceratops() : Dinozaur(1, 200, 10, 10, 20, 1, "Mountain", "Triceratops") {}
};
class Braxiozavr : public Dinozaur {
public:
	Braxiozavr() : Dinozaur(2, 300, 10, 20, 20, 2, "River", "Braxiozavr") {}
};
class Pterozavr : public Dinozaur {
public:
	Pterozavr() : Dinozaur(3, 500, 30, 20, 20, 1, "Mountain", "Pterozavr") {}
};