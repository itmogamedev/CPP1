#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu
{
private:
	sf::RenderWindow* window_;
	sf::Texture bgPic_, menuPic_, contPic_, exitPic_;
	sf::Sprite bg_, menu_, cont_, exit_;
	int choice_ = 0;
	bool isOn_ = false;
	void renderExit();

public:
	PauseMenu(sf::RenderWindow* window);
	~PauseMenu() = default;
	void draw();
	int render();
	void win();
	void lose();
};
