#pragma once

#ifndef FONT_H__
#define FONT_H__


#include <iostream>
#include <SFML/Graphics.hpp>

sf::Font inkfree;
sf::Font muller;

void load_fonts() {
	inkfree.loadFromFile("fonts/Inkfree.ttf");
	muller.loadFromFile("fonts/ofont.ru_Muller.ttf");
}

#endif // !FONT_H__