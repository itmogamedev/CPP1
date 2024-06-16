#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu {
private:
	sf::RenderWindow* window_;
	sf::Font* font_;
	sf::Event* event_;
	sf::Texture bgPic_;
	sf::Sprite bg_;
	sf::Text mainText_;
	Button fight_, collect_, shop_, exit_;
	int choice_ = 0;
	void draw();

public:
	MainMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font);
	~MainMenu() = default;
	int render();
};

