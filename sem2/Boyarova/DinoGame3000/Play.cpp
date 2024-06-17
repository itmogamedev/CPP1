#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <random>
#include "Player.h"
#include "Play.h"
#include "Help.h"
#include "Fun.h"


Terrain TPlay;

using namespace sf;

void Play(sf::RenderWindow& window) {

	sf::Font MC;
	MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
	bool ran = true;
	sf::Text Ter;
	int random,random2;
	if (ran == true) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 2);
		random = dis(gen);
		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dis2(0, 3);
		random2 = dis2(gen);
		ran = false;
		Ter.setFont(MC);
		if (random == 0) {
			Ter.setString("Plain");
			Terrain TPlay = Terrain::Plain;
		}
		if (random == 1) {
			Ter.setString("River");
			Terrain TPlay = Terrain::River;
		}
		if (random == 2) {
			Ter.setString("Mountain");
			Terrain TPlay = Terrain::Mountain;
		}
	}
	sf::Color color1 = sf::Color(4, 255, 67);
	sf::Color color2 = sf::Color(0, 202, 51);
	sf::Text Ch(L"Выбери бойца", MC, 70);
	Ch.setFillColor(color1);
	Ch.setOutlineThickness(5);
	Ch.setOutlineColor(color2);
	Ch.setPosition(230, 200);

	sf::Text Exit(L"Выход", MC, 40);
	Exit.setFillColor(color1);
	Exit.setOutlineThickness(5);
	Exit.setOutlineColor(color2);
	Exit.setPosition(1000, 70);
	sf::RectangleShape exitButton(sf::Vector2f(240, 55));
	exitButton.setFillColor(sf::Color(0, 0, 0, 0));
	exitButton.setPosition(990, 60);

	Ter.setCharacterSize(30);
	float textWidth = Ter.getLocalBounds().width;
	Ter.setPosition((window.getSize().x - textWidth) / 2, 30);
	Ter.setOutlineThickness(4);
	Ter.setOutlineColor(sf::Color(163, 73, 164));
	Ter.setFillColor(sf::Color(188, 177, 226));

	Player player1;
	player1.LoadGame("data.txt");
	std::vector <bool> Info = player1.getInfo();

	Texture Dino1, Dino2, Dino3, Dino4, Dino12, Dino22, Dino32, Dino42;
	Dino1.loadFromFile("images/DCyno.jpg");
	Dino2.loadFromFile("images/DNari.jpg");
	Dino3.loadFromFile("images/DKaveh.jpg");
	Dino4.loadFromFile("images/DHaitam.jpg");
	Dino12.loadFromFile("images/CCyno.jpg");
	Dino22.loadFromFile("images/CNari.jpg");
	Dino32.loadFromFile("images/CKaveh.jpg");
	Dino42.loadFromFile("images/CHaitam.jpg");
	Sprite Sprite1, Sprite2, Sprite3, Sprite4;

	if (Info[0] == true)
		Sprite1.setTexture(Dino1);
	if (Info[1] == true)
		Sprite2.setTexture(Dino2);
	if (Info[2] == true)
		Sprite3.setTexture(Dino3);
	if (Info[3] == true)
		Sprite4.setTexture(Dino4);

	Sprite1.setPosition(100, 400);
	Sprite2.setPosition(385, 400);
	Sprite3.setPosition(670, 400);
	Sprite4.setPosition(955, 400);
	std::vector <bool> Balte = { false, false, false, false };
	bool isMouseOver = false;
	while (window.isOpen() && isMenuActive != 1)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					Sprite1.setTexture(Dino12);
					isMouseOver = true;
				}
				else if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					Sprite1.setTexture(Dino1);
					isMouseOver = false;
				}
				else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					Sprite2.setTexture(Dino22);
					isMouseOver = true;
				}
				else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					Sprite2.setTexture(Dino2);
					isMouseOver = false;
				}

				else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					Sprite3.setTexture(Dino32);
					isMouseOver = true;
				}
				else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					Sprite3.setTexture(Dino3);
					isMouseOver = false;
				}

				else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					Sprite4.setTexture(Dino42);
					isMouseOver = true;
				}
				else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					Sprite4.setTexture(Dino4);
					isMouseOver = false;
				}
				else if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					exitButton.setFillColor(sf::Color(0, 0, 0, 150));
					isMouseOver = true;
				}
				else if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					exitButton.setFillColor(sf::Color(0, 0, 0, 0));
					isMouseOver = false;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{

				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
				{
					isMenuActive = 1;
				}
				else if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos)) && Info[0] == true)
				{
					Fun(1, random2, random, window);
				}
				else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && Info[1] == true)
				{
					Fun(2, random2, random, window);
				}
				else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && Info[2] == true)
				{
					Fun(3, random2, random, window);
				}
				else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && Info[3] == true)
				{
					Fun(4, random2, random, window);
				}
			}
			if (isMenuActive == 4) {
				window.clear(Color::Black);
				window.draw(Ter);
				window.draw(Sprite1);
				window.draw(Sprite2);
				window.draw(Sprite3);
				window.draw(Sprite4);
				window.draw(Ch);
				window.draw(Exit);
				window.draw(exitButton);
				window.display();
			}

			if (event.type == sf::Event::Closed)
				window.close();

		}
	}
}

    