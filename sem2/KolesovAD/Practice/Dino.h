#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>


enum Terrain { PLAIN, RIVER, MOUNTAIN };

class Dino {
protected:
	int STR;
	int DEX;
	int INT;
	int HP;
	std::string NAME;
	int COST;
	sf::Sprite* dinoSprite;
public:
	virtual double damage(Terrain terr) = 0;

	virtual ~Dino() = default;

	std::string dinoInfo() {
		return NAME + "\t" + "STR: " + std::to_string(STR) + "\t" + "DEX: " + std::to_string(DEX) + "\t" + "INT: " + std::to_string(INT) + "\t" + "HP: " + std::to_string(HP);
	}

	sf::Sprite& sprite() {
		return *dinoSprite;
	}

	std::string buyInfo() {
		return NAME + "\t" + "cost: " + std::to_string(COST);
	}

	std::string info() {
		return NAME + " " + std::to_string(STR) + " " + std::to_string(DEX) + " " + std::to_string(INT) + " " + std::to_string(HP);
	}

	void takeDamage(int damage) {
		HP = std::max(HP - damage, 0);
	}

	int getHP() {
		return HP;
	}

	std::string getName() {
		return NAME;
	}

	int getCost() {
		return COST;
	}

	void changeTexture(sf::Texture& texture, int x, int y) {
		dinoSprite->setTexture(texture);
		dinoSprite->setPosition(x, y);
	}
};


class DinoStr : public Dino {
public:
	double damage(Terrain terr) override {
		if (terr == PLAIN) {
			return STR * 2;
		}
		else if (terr == RIVER) {
			return DEX;
		}
		else {
			return INT;
		}
	}
	DinoStr(std::string name, sf::Texture &texture, int x, int y, int cost = 100, int strength = rand() % 21 + 10, int dexterity = rand() % 21 + 10, int intelligence = rand() % 21 + 10, int hp = 100) {
		STR = strength;
		DEX = dexterity;
		INT = intelligence;
		HP = hp;
		NAME = name;
		COST = cost;
		dinoSprite = new sf::Sprite;
		dinoSprite->setTexture(texture);
		dinoSprite->setPosition(x, y);
	}
	~DinoStr() {}
};


class DinoDex : public Dino {
public:
	double damage(Terrain terr) override {
		if (terr == PLAIN) {
			return STR;
		}
		else if (terr == RIVER) {
			return DEX * 2;
		}
		else {
			return INT;
		}
	}
	DinoDex(std::string name, sf::Texture &texture, int x, int y, int cost = 100, int strength = rand() % 21 + 10, int dexterity = rand() % 21 + 10, int intelligence = rand() % 21 + 10, int hp = 100) {
		STR = strength;
		DEX = dexterity;
		INT = intelligence;
		HP = hp;
		NAME = name;
		COST = cost;
		dinoSprite = new sf::Sprite;
		dinoSprite->setTexture(texture);
		dinoSprite->setPosition(x, y);
	}
	~DinoDex() {}
};


class DinoInt : public Dino {
public:
	double damage(Terrain terr) override {
		if (terr == PLAIN) {
			return STR;
		}
		else if (terr == RIVER) {
			return DEX;
		}
		else {
			return INT * 2;
		}
	}
	DinoInt(std::string name, sf::Texture &texture, int x, int y, int cost = 100, int strength = rand() % 21 + 10, int dexterity = rand() % 21 + 10, int intelligence = rand() % 21 + 10, int hp = 100) {
		STR = strength;
		DEX = dexterity;
		INT = intelligence;
		HP = hp;
		NAME = name;
		COST = cost;
		dinoSprite = new sf::Sprite;
		dinoSprite->setTexture(texture);
		dinoSprite->setPosition(x, y);
	}
	~DinoInt() {}
};