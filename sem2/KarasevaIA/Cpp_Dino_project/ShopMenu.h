#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"

struct ShopDino {
	ShopDino(sf::RenderWindow* window, sf::Font* font);
	sf::RenderWindow* window_;
	Button buy;
	sf::Texture tex;
	sf::Sprite sprite;
	sf::Text name, terrain, cost;
	void setPosition(int x, int y);
	void draw();
};

class ShopMenu {
private:
	GameState* state_;
	sf::RenderWindow* window_;
	sf::Font* font_;
	sf::Text title_, dialog_, budget_;
	sf::Event* event_;
	sf::Texture bgPic_;
	sf::Sprite bg_;
	Button back_;
	std::vector<ShopDino> list;
	int choice_ = 0;
	void draw();
	void updateList();

public:
	ShopMenu(sf::RenderWindow* window, sf::Event* event, sf::Font*, GameState* state);
	~ShopMenu() = default;
	int render();
};