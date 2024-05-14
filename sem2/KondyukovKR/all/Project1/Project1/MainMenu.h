#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
	sf::RenderWindow* window_;
	sf::Texture optionPlay, optionQuit, background;
	sf::Sprite play, quit, bg;
	bool isOn = true;
	int choice = 0;

public:
	MainMenu(sf::RenderWindow* window);
	bool render();
};