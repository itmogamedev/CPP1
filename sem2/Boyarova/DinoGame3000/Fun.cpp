#include "Help.h"
#include "Player.h"
#include "Fun.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "windows.h"

using namespace sf;

class Dino
{
protected:
	int STR;
	int DEX;
	int INT;
	int hp = 100;
	Terrain Ter;
	std::string Name;

public:
	virtual int damage(Terrain terrain) = 0;
	void set_strength(int st) { STR = st; }
	void set_agility(int de) { DEX = de; }
	void set_brain(int in) { INT = in; }
	void setHealth(int);
	void setHealth2(int);
	int getHealth() { return hp; }
};

class PlainDino : protected Dino {
public:
	PlainDino();
	PlainDino(int str, int dex, int intel, Terrain terrain, std::string N) {
		STR = str;
		DEX = dex;
		INT = intel;
		hp = 100;
		Ter = terrain;
		Name = N;
	};
	PlainDino(const PlainDino& other) = default;
	PlainDino& operator=(const PlainDino& other) = default;
	int damage(Terrain terrain) {
		if (terrain == Terrain::Plain)
			return (2 * STR);
		else if (terrain == Terrain::River)
			return DEX;
		return INT;
	};
	int getHealth() { return hp; }
};

class RiverDino : protected Dino {
public:
	RiverDino();
	RiverDino(int str, int dex, int intel, Terrain terrain, std::string N) {
		STR = str;
		DEX = dex;
		INT = intel;
		hp = 100;
		Ter = terrain;
		Name = N;
	};
	RiverDino(const RiverDino& other) = default;
	RiverDino& operator=(const RiverDino& other) = default;
	int damage(Terrain terrain) {
		if (terrain == Terrain::Plain)
			return STR;
		else if (terrain == Terrain::River)
			return (2 * DEX);
		return INT;
	}
	int getHealth() { return hp; }
};

class MountainDino : protected Dino {
public:
	MountainDino();
	MountainDino(int str, int dex, int intel, Terrain terrain, std::string N) {
		STR = str;
		DEX = dex;
		INT = intel;
		hp = 100;
		Ter = terrain;
		Name = N;
	};
	MountainDino(const MountainDino& other) = default;
	MountainDino& operator=(const MountainDino& other) = default;
	int damage(Terrain terrain) {

		if (terrain == Terrain::Plain)
			return STR;
		else if (terrain == Terrain::River)
			return DEX;
		else if (terrain == Terrain::Mountain)
		    return (2 * INT);
	}
	int getHealth() { return hp; }
};

#include <sstream>

void Fun(int A, int B, int C, sf::RenderWindow& window) {

	PlainDino DCyno(33, 22, 11, Terrain::Plain, "Syno");
	RiverDino DNari(11, 33, 22, Terrain::River, "Nari");
	RiverDino DKaveh(22, 22, 22, Terrain::River, "Kaveh");
	MountainDino DHaitam(22, 11, 33, Terrain::Mountain, "Haitam");
	extern Terrain TPlay;
	if (C == 0) {
		Terrain TPlay = Terrain::Plain;
	}
	if (C == 1) {
		Terrain TPlay = Terrain::River;
	}
	if (C == 2) {
		Terrain TPlay = Terrain::Mountain;
	}

	Player player2;
	player2.LoadGame("data.txt");
	int DMy, D2;
	int HMy, H2;
	Texture Dino1, Dino2, Dino3, Dino4;
	Dino1.loadFromFile("images/DCyno.jpg");
	Dino2.loadFromFile("images/DNari.jpg");
	Dino3.loadFromFile("images/DKaveh.jpg");
	Dino4.loadFromFile("images/DHaitam.jpg");
	Sprite Sprite1, Sprite2, Sprite3, Sprite4, Sprite12, Sprite22, Sprite32, Sprite42;
	if (A == 1) {
		Sprite1.setTexture(Dino1);
		Sprite1.setPosition(180, 200);
		DMy = DCyno.damage(TPlay);
		HMy = DCyno.getHealth();
	}
	if (A == 2) {
		Sprite2.setTexture(Dino2);
		Sprite2.setPosition(180, 200);
		DMy = DNari.damage(TPlay);
		HMy = DNari.getHealth();
	}
	if (A == 3) {
		Sprite3.setTexture(Dino3);
		Sprite3.setPosition(180, 200);
		DMy = DKaveh.damage(TPlay);
		HMy = DKaveh.getHealth();
	}
	if (A == 4) {
		Sprite4.setTexture(Dino4);
		Sprite4.setPosition(180, 200);
		DMy = DHaitam.damage(TPlay);
		HMy = DHaitam.getHealth();
	}

	if (B == 0) {
		Sprite12.setTexture(Dino1);
		Sprite12.setPosition(900, 200);
		D2 = DCyno.damage(TPlay);
		H2 = DCyno.getHealth();
	}
	if (B == 1) {
		Sprite22.setTexture(Dino2);
		Sprite22.setPosition(900, 200);
		D2 = DNari.damage(TPlay);
		H2 = DNari.getHealth();
	}
	if (B == 2) {
		Sprite32.setTexture(Dino3);
		Sprite32.setPosition(900, 200);
		D2 = DKaveh.damage(TPlay);
		H2 = DKaveh.getHealth();
	}
	if (B == 3) {
		Sprite42.setTexture(Dino4);
		Sprite42.setPosition(900, 200);
		D2 = DHaitam.damage(TPlay);
		H2 = DHaitam.getHealth();
	}

	sf::Font MC;
	MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
	sf::Text Rule(L"Нажми пробел для атаки", MC, 40);
	Rule.setFillColor(sf::Color(255,255,255));
	Rule.setPosition(220, 70);

	sf::RectangleShape HpLineMy(sf::Vector2f(210, 40));
	HpLineMy.setOutlineThickness(3);
	HpLineMy.setOutlineColor(sf::Color(150, 0, 3));
	HpLineMy.setFillColor(sf::Color(0, 0, 0, 0));
	HpLineMy.setPosition(180, 500);
	sf::RectangleShape HpLine2(sf::Vector2f(210, 40));
	HpLine2.setOutlineThickness(3);
	HpLine2.setOutlineColor(sf::Color(150, 0, 3));
	HpLine2.setFillColor(sf::Color(0, 0, 0, 0));
	HpLine2.setPosition(900, 500);
	sf::RectangleShape HpDisplayMy(sf::Vector2f(210, 40));
	HpDisplayMy.setOutlineColor(sf::Color(0, 0, 0, 0));
	HpDisplayMy.setFillColor(sf::Color::Red);
	HpDisplayMy.setPosition(180, 500);
	sf::RectangleShape HpDisplay2(sf::Vector2f(210, 40));
	HpDisplay2.setOutlineColor(sf::Color(0, 0, 0, 0));
	HpDisplay2.setFillColor(sf::Color::Red);
	HpDisplay2.setPosition(900, 500);

	bool step = true;
	sf::Event event;
	while (window.isOpen() && isMenuActive!=1)
	{
		while (window.pollEvent(event) && isMenuActive == 4 && H2 > 0 && HMy > 0)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (step == true) {
						H2 = H2 - DMy;
						if (H2 <= 0) {
							HpDisplay2.setSize(sf::Vector2f(0, 0));
							window.draw(HpDisplay2);
							window.display();
							isMenuActive = 5;

						}
						else {
							HpDisplay2.setSize(sf::Vector2f(HpDisplay2.getSize().x - (DMy * 2.1), 40));
							step = false;
						}
					}
					else if (step == false) {
						HMy = HMy - D2;
						if (HMy <= 0) {
							HpDisplayMy.setSize(sf::Vector2f(0, 0));
							window.draw(HpDisplayMy);
							window.display();
							isMenuActive = 6;
						}
						else
						{
							HpDisplayMy.setSize(sf::Vector2f(HpDisplayMy.getSize().x - (D2 * 2.1), 40));
							step = true;
						}
					}
				}
			}


		}
		if (event.type == sf::Event::Closed)
			window.close();

		if (isMenuActive == 4) {
			window.clear(Color::Black);
			window.draw(Sprite1);
			window.draw(Sprite2);
			window.draw(Sprite3);
			window.draw(Sprite4);
			window.draw(Sprite12);
			window.draw(Sprite22);
			window.draw(Sprite32);
			window.draw(Sprite42);
			window.draw(HpDisplay2);
			window.draw(HpDisplayMy);
			window.draw(HpLineMy);
			window.draw(HpLine2);
			window.draw(Rule);
			window.display();
		}

		if (isMenuActive == 5) {
			sf::Font MC;
			sf::Color color1 = sf::Color(4, 255, 67);
			sf::Color color2 = sf::Color(0, 202, 51);
			MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
			sf::Text Exit(L"Выход", MC, 40);
			Exit.setFillColor(color1);
			Exit.setOutlineThickness(5);
			Exit.setOutlineColor(color2);
			Exit.setPosition(1000, 620);
			sf::RectangleShape exitButton(sf::Vector2f(240, 55));
			exitButton.setFillColor(sf::Color(0, 0, 0, 0));
			exitButton.setPosition(990, 610);

			sf::Text Vic(L"Урыл", MC, 80);
			Vic.setFillColor(color1);
			Vic.setOutlineThickness(5);
			Vic.setOutlineColor(color2);
			Vic.setPosition(440, 200);
			sf::Text Money(L"+100 шекелей", MC, 30);
			Money.setFont(MC);
			Money.setPosition(450, 400);
			Money.setOutlineThickness(4);
			Money.setOutlineColor(sf::Color(255, 201, 14));
			Money.setFillColor(sf::Color(255, 242, 0));

			bool isMouseOver = false;
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				if (event.type == sf::Event::MouseMoved)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
					{
						exitButton.setFillColor(sf::Color(0, 0, 0, 150));
						isMouseOver = true;
					}
					else if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
					{
						exitButton.setFillColor(sf::Color(0, 0, 0, 150));
						isMouseOver = false;
					}

				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
					{
						
						player2.setCoins(100);
						player2.SaveGame("data.txt");
						isMenuActive = 1;
					}

				}
				if (event.type == sf::Event::Closed)
					window.close();
				window.display();

			window.clear(sf::Color::Black);
			window.draw(Exit);
			window.draw(Vic);
			window.draw(exitButton);
			window.draw(Money);
		}
		if (isMenuActive == 6) {
			sf::Font MC;
			sf::Color color1 = sf::Color(4, 255, 67);
			sf::Color color2 = sf::Color(0, 202, 51);
			MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
			sf::Text Exit(L"Выход", MC, 40);
			Exit.setFillColor(color1);
			Exit.setOutlineThickness(5);
			Exit.setOutlineColor(color2);
			Exit.setPosition(1000, 620);
			sf::RectangleShape exitButton(sf::Vector2f(240, 55));
			exitButton.setFillColor(sf::Color(0, 0, 0, 0));
			exitButton.setPosition(990, 610);

			sf::Text Fail(L"Потрачено", MC, 80);
			Fail.setFillColor(sf::Color::Red);
			Fail.setOutlineThickness(5);
			Fail.setOutlineColor(sf::Color(150, 0, 3));
			Fail.setPosition(280, 290);


			bool isMouseOver = false;
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
				{
					exitButton.setFillColor(sf::Color(0, 0, 0, 150));
					isMouseOver = true;
				}
				else if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
				{
					exitButton.setFillColor(sf::Color(0, 0, 0, 150));
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

			}
			if (event.type == sf::Event::Closed)
				window.close();
			window.display();


			window.clear(sf::Color::Black);
			window.draw(Exit);
			window.draw(Fail);
			window.draw(exitButton);
		}
		
	}
}
