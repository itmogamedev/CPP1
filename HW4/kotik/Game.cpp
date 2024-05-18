#include "Game.h"
#include "Windows.h"
#include <iostream>

// Privates
void Game::initVars()
{
	this->window = nullptr;
	start = true;
	playing = false;
	won = false;
	lost = false;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "My tamagochi", sf::Style::Titlebar | sf::Style::Close);
}

Game::Game()
{
	this->initVars();
	this->initWindow();
	font.loadFromFile("tuffy.ttf");

	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text4.setFont(font);
	text1.setFillColor(sf::Color::Black);
	text1.setCharacterSize(24);
	text1.setPosition(600, 100);
	text2.setFillColor(sf::Color::Black);
	text2.setCharacterSize(24);
	text2.setPosition(600, 200);
	text3.setFillColor(sf::Color::Black);
	text3.setCharacterSize(24);
	text3.setPosition(600, 300);
	text4.setFillColor(sf::Color::Black);
	text4.setCharacterSize(24);
	text4.setPosition(600, 400);
	buttonText.setFont(font);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setCharacterSize(24);

	sizeTexture.loadFromFile("resources/size.png");
	dirtTexture.loadFromFile("resources/soap.png");
	thirstTexture.loadFromFile("resources/water.png");
	hungerTexture.loadFromFile("resources/food.png");

	sizeSprite.setTexture(sizeTexture);
	dirtSprite.setTexture(dirtTexture);
	thirstSprite.setTexture(thirstTexture);
	hungerSprite.setTexture(hungerTexture);

	sizeSprite.setPosition(500, 100);
	dirtSprite.setPosition(500, 400);
	thirstSprite.setPosition(500, 300);
	hungerSprite.setPosition(500, 200);

	button.setPosition(1000, 100);
	button.setSize(sf::Vector2f(200.f, 50.f));
	button.setFillColor(sf::Color::Black);
}

Game::~Game()
{
	delete this->window; 
}

const bool Game::running() const
{
	return this->window->isOpen();

}

// Publics
void Game::updateEvs()
{
	
	while (this->window->pollEvent(this->event))
	{

		this->window->display();
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (start) {
				if (event.key.code == sf::Keyboard::Num1) {
					myCat.textureName = "cat.png";
					playing = true;
					start = false;
				}
				if (event.key.code == sf::Keyboard::Num2) {
					myCat.textureName = "dog.png";
					playing = true;
					start = false;
				}
				if (event.key.code == sf::Keyboard::Num3) {
					myCat.textureName = "bobr.png";
					playing = true;
					start = false;
				}
				if (!start) {
					myCat.herotexture.loadFromFile("resources/" + myCat.textureName);
					myCat.herosprite.setTexture(myCat.herotexture);
				}
			}
			if (playing){
				if (event.key.code == sf::Keyboard::P) {
					paused = true;
					playing = false;
				}
			}
			else if (paused) {
				if (event.key.code == sf::Keyboard::P) {
					paused = false;
					playing = true;
				}
			}
		case sf::Event::MouseButtonReleased:
			if (playing and event.mouseButton.button == 0) {
				int x = event.mouseButton.x;
				int y = event.mouseButton.y;
				
				if (1000 <= x and x <= 1200) {
					if (200 <= y and y <= 250) {
						myCat.Feed();
					}
					if (300 <= y and y <= 350) {
						myCat.Drink();
					}
					if (400 <= y and y <= 450) {
						myCat.Wash();
					}
				}
			}
		default:
			break;
		}
	}
}

void Game::update()
{
	this->updateEvs();
}

void Game::render()
{
	this->window->clear(sf::Color(i%256, i % 256 + 100, i % 256 + 50, 100));
	this->i++;
	//draw here

	if (start) {
		text1.setString("1 - cat");
		text2.setString("2 - dog");
		text3.setString("3 - beaver :3");
		window->draw(text1);
		window->draw(text2);
		window->draw(text3);
	}
	if (playing){
		int out = myCat.update();
		if (out == 1) {
			won = true;
			playing = false;
		}
		else if (out == -1) {
			lost = true;
			playing = false;
		}
		text1.setString("Size: " + std::to_string(myCat.size));
		text2.setString("Hunger: " + std::to_string(myCat.hunger));
		text3.setString("Thirst: " + std::to_string(myCat.thirst));
		text4.setString("Dirt: " + std::to_string(myCat.dirt));
		window->draw(this->myCat.herosprite);
		window->draw(text1);
		window->draw(text2);
		window->draw(text3);
		window->draw(text4);
		window->draw(sizeSprite);
		window->draw(hungerSprite);
		window->draw(thirstSprite);
		window->draw(dirtSprite);

		button.setPosition(1000, 200);
		window->draw(button);
		button.setPosition(1000, 300);
		window->draw(button);
		button.setPosition(1000, 400);
		window->draw(button);

		buttonText.setString("Feed");
		buttonText.setPosition(1050, 210);
		window->draw(buttonText);
		buttonText.setString("Give water");
		buttonText.setPosition(1050, 310);
		window->draw(buttonText);
		buttonText.setString("Wash");
		buttonText.setPosition(1050, 410);
		window->draw(buttonText);
	}
	if (won) {
		text1.setString("You won");
		window->draw(text1);
	}
	if (lost) {
		text1.setString("You lost");
		window->draw(text1);
	}
	if (paused) {
		text1.setString("Pause. Push P to resume");
		window->draw(text1);
	}

	

	this->window->display();
	Sleep(100);
}


