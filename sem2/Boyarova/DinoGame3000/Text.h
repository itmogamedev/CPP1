#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef TEXT_H
#define TEXT_H

sf::Font MC;

void load_fonts() {
	MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
}
#endif