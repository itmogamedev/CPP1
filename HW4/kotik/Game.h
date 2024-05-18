#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Cat.h"
// Kinda Engine class
class Game
{
private:

	void initVars();
	void initWindow();
	int i = 0;

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Font font;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	sf::Text text4;

	sf::Sprite sizeSprite;
	sf::Sprite dirtSprite;
	sf::Sprite thirstSprite;
	sf::Sprite hungerSprite;

	sf::Texture sizeTexture;
	sf::Texture dirtTexture;
	sf::Texture thirstTexture;
	sf::Texture hungerTexture;

	sf::RectangleShape button;
	sf::Text buttonText;
	Cat myCat;
	bool start;
	bool playing;
	bool won;
	bool lost;
	bool paused;

public:
	Game();
	virtual ~Game();

	const bool running() const;


	void update();
	void render();
	void updateEvs();
};

