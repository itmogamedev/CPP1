#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Dino {
public:
	int STR; // сила 10 - 30
	int DEX; // ловкость 10 - 30
	int INT; // интеллект 10 - 30
	int HP = 100;
	std::string name; // имя
	int cost; // цена
	sf::Sprite spriteDino;
	sf::Texture textureDino;

	int getSTR() {
		return STR;
	}
	int getINT() {
		return INT;
	}
	int getDEX() {
		return DEX;
	}
	int getHP() {
		return HP;
	}
	int getCost() {
		return cost;
	}
	std::string getName() {
		return name;
	}
	sf::Sprite getSprite() {
		return spriteDino;
	}

	void setHP(int i) {
		HP = HP - i;
	}

	virtual int getDamage(int i) {
		return 100;
	}



};


class Rex : public Dino {
public:
	
	Rex() {
		sf::Image i;
		i.loadFromFile("image/rex.png");
		textureDino.loadFromImage(i);
		spriteDino.setTexture(textureDino);
		STR = 10; // сила 10 - 30
		DEX = 10; // ловкость 10 - 30
		INT = 10;
		
	}

	int getDamage(int i) {
		if (i == 0) {
			return STR * 2;
		}
		if (i == 1) {
			return DEX;
		}
		if (i == 2) {
			return INT;
		}
	}
};

class Raptor : public Dino {
public:
	Raptor() {
		sf::Image i;
		i.loadFromFile("image/raptor.png");
		textureDino.loadFromImage(i);
		spriteDino.setTexture(textureDino);
		STR = 10; // сила 10 - 30
		DEX = 10; // ловкость 10 - 30
		INT = 10;
		
	}
	int getDamage(int i) {
		if (i == 0) {
			return STR;
		}
		if (i == 1) {
			return DEX * 2;
		}
		if (i == 2) {
			return INT;
		}
	}
};

class Tricer : public Dino {
public:
	Tricer() {
		sf::Image i;
		i.loadFromFile("image/tricer.png");
		textureDino.loadFromImage(i);
		spriteDino.setTexture(textureDino);
		STR = 10; // сила 10 - 30
		DEX = 10; // ловкость 10 - 30
		INT = 10;
		
	}

	int getDamage(int i) {
		if (i == 0) {
			return STR;
		}
		if (i == 1) {
			return DEX;
		}
		if (i == 2) {
			return INT * 2;
		}
	}
};

