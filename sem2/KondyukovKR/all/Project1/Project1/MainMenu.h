#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
	sf::RenderWindow* window_;
	sf::Texture optionPlay, optionQuit, background;
	sf::Texture optionCat, optionDog, optionChin;
	sf::Sprite play, quit, bg;
	sf::Sprite cat, dog, chin;
	bool isOn = true;
	int choice = 0;

public:
	MainMenu(sf::RenderWindow* window);
	bool render();
	int choosePet();
};