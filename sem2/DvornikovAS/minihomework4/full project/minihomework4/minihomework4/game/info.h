#pragma once

#ifndef INFO_H__
#define INFO_H__

#include <iostream>
#include <string>
#include <vector>

#include "../cat/cat.h"
#include "window.h"

#include <SFML/Graphics.hpp>

class Info : Cat {
private:
	sf::Font font;
	sf::Text tSatiety;
	sf::Text tSatisfaction;
	sf::Text tPurity;
	sf::Text tSize;

public:
	void load(sf::Font);
	void update(double, double, double, double);
	sf::Text getSatiety() { return tSatiety; }
	sf::Text getSatisfaction() { return tSatisfaction; }
	sf::Text getPurity() { return tPurity; }
	sf::Text getSize() { return tSize; }

};

#endif INFO_H__