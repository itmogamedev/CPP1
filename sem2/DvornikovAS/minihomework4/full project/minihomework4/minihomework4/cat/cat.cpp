#include <iostream>

#include "cat.h"

void Cat::setType(Animal newType) { type = newType; }

void Cat::setAlive() { _isAlive = true; }
void Cat::setWon() { _isWon = false; }

double Cat::getSize() const { return size; }
void Cat::setSize(const double newSize) { size = newSize; }

double Cat::getSatiety() const { return satiety; }
void Cat::setSatiety(const double newSatiety) { satiety = newSatiety; }
void Cat::increaseSatiety() {
	satiety += 10;
	if (satiety > maxSatiety)
		satiety = maxSatiety;
}

double Cat::getSatisfaction() const { return satisfaction; }
void Cat::setSatisfaction(const double newSatisfaction) { satisfaction = newSatisfaction; }
void Cat::increaseSatisfaction() {
	satisfaction += 10;
	if (satisfaction > maxSatisfaction)
		satisfaction = maxSatisfaction;
}

double Cat::getPurity() const { return purity; }
void Cat::setPurity(const double newPurity) { purity = newPurity; }
void Cat::increasePurity() {
	purity += 10;
	if (purity > maxPurity)
		purity = maxPurity;
}

sf::Sprite Cat::getSprite() const { return catSprite; }

void Cat::setTexture(std::string newPath) {
	sf::Texture newTexture;
	newTexture.loadFromFile(newPath);
	catTexture = newTexture;
}

void Cat::born() {
	if (type == Animal::CAT)
		catTexture.loadFromFile("src/img/ordinaryCat.png");
	else if (type == Animal::DOG)
		catTexture.loadFromFile("src/img/ordinaryDog.png");
	else if (type == Animal::BEAVER)
		catTexture.loadFromFile("src/img/ordinaryBeaver.png");
	catSprite.setTexture(catTexture);
	catSprite.setOrigin(catSprite.getLocalBounds().width / 2, catSprite.getLocalBounds().height / 2);
	catSprite.setPosition(600, 300);
}

void Cat::live() {
	if (satiety > 0)
		satiety -= lifeRate;
	if (satisfaction > 0)
		satisfaction -= lifeRate;
	if (purity > 0)
		purity -= lifeRate;
	if (satiety <= 0 and satisfaction <= 0 and purity <= 0) {
		dead();
		satiety = satisfaction = purity = 0;
	}
	
	size = (satiety + satisfaction + purity) / 3 / 100;
	if (size > 0.8 and satiety > 80 and satisfaction > 80 and purity > 80)
		won();
	catSprite.setScale(size, size);
}

void Cat::dead() { _isAlive = false; }

void Cat::won() { _isWon = true; }