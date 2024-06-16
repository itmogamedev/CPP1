#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"

struct CollectDino {
	CollectDino(sf::RenderWindow* window, sf::Font* font);
	sf::RenderWindow* window_;
	sf::Texture tex;
	sf::Sprite sprite;
	sf::Text name, type, params;
	Button isFighter;
	void setPosition(int x, int y);
	void draw();
};

class CollectMenu {
private:
	GameState* state_;
	sf::RenderWindow* window_;
	sf::Font* font_; sf::Text title_;
	sf::Event* event_;
	sf::Texture bgPic_, leftDino_, rightDino_;
	sf::Sprite bg_;
	Button back_, leftArrow_, rightArrow_;
	std::vector<CollectDino> list;
	int choice_ = 0, maxListSize = 0;
	void draw();
	void updateList(int i);

public:
	CollectMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font, GameState* state);
	~CollectMenu() = default;
	int render();
};

