#pragma once

#ifndef CAT_H__
#define CAT_H__

#include <SFML/Graphics.hpp>

enum Animal {
	DOG,
	CAT,
	BEAVER
};

class Cat {
protected:
	Animal type = Animal::CAT;
	bool _isAlive = true;
	bool _isWon = false;
	double size = 0.5;
	const double lifeRate = 0.03; //difficulty of the game: the higher the number, the more difficult it is to play. It must be within 0 < lifeRate < 1, otherwise it is impossible to win. The optimal number is 0.03
	double satiety = 50; //food
	double satisfaction = 50; //thirsty
	double purity = 50; //clean
	const double maxSatiety = 100;
	const double maxSatisfaction = 100;
	const double maxPurity = 100;
	sf::Texture catTexture;
	sf::Sprite catSprite;

public:

	void setType(Animal);
	Animal getType() { return type; }

	bool isAlive() const { return _isAlive; }
	void setAlive();

	bool isWon() const { return _isWon; }
	void setWon();

	double getSize() const;
	void setSize(double);

	double getSatiety() const;
	void setSatiety(double);
	void increaseSatiety();

	double getSatisfaction() const;
	void setSatisfaction(double);
	void increaseSatisfaction();

	double getPurity() const;
	void setPurity(double);
	void increasePurity();

	sf::Sprite getSprite() const;

	void setTexture(std::string);

	void born();
	void live();
	void dead();
	void won();
};

#endif