#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"

// TODO add health bars
class FightMenu {
private:
	GameState* state_;
	sf::RenderWindow* window_;
	sf::Font* font_;
	sf::Text title_, welcome_, allyName_, allyDesc_, oppName_, oppDesc_;
	sf::Event* event_;
	sf::Texture bgPic_, allyPic_, oppPic_;
	sf::Sprite bg_, ally_, opp_;
	Button back_;
	int choice_ = 0;
	void draw();

public:
	FightMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font, GameState* state);
	~FightMenu() = default;
	int render();
};
