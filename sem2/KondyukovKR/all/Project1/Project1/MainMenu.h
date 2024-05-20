#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
	sf::RenderWindow* window_;
	sf::Event* event_;
	unsigned int winX, winY;
	sf::Texture optionPlay, optionQuit, background;
	sf::Texture optionCat, optionDog, optionChin, optionText;
	sf::Sprite play, quit, bg;
	sf::Sprite cat, dog, chin, text;
	bool isOn = true;
	int choice = 0;

public:
	MainMenu(sf::RenderWindow* window, sf::Event* event);
	bool render();
	int choosePet();
};