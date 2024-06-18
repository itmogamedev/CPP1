#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp> 
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <ctime>
#include <windows.h>
#include <random>
#include <cstdlib> 
#include <string>

void menuScreen(sf::RenderWindow& window, sf::Font& font);
enum Terrain { Plain, River, Mountain };
enum Dinosavrus { Teranosavr = 1, Diplodog = 2, Stegosavr = 3, NewYearDino = 4 };
int cur_dam;

bool run;
int variant, variant_shop, num_choose1, num_choose2, num_choose3, num_buy1, num_buy2, num_buy3, hp, enemyhp, dino1, dino2, coin_balance, deal_damage;
std::string pull, enemy_pull, rN1, rN2, rN3, txt_dino, ad1;


class Dino {
protected:
	int st = rand() % 8 + 10;
	int ag = rand() % 10 + 10;
	int in = rand() % 20 + 5;
public:
	virtual double damage() = 0;

};

class DinoStr : public Dino {
public:
	double damage() override {
		cur_dam += st * 1.5;
		return cur_dam;
	}
};

class DinoDex : public Dino {
public:
	double damage() override {
		cur_dam += ag * 1.7;
		return cur_dam;
	}
};

class DinoInt : public Dino {
public:
	double damage() override {
		cur_dam += in * 2.1;
		return cur_dam;
	}
};

class Player {
public:
	double damage(Dino* dino) {
		return dino->damage();
	}
};

class Button {
public:

	Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& line, sf::Font& font) {
		view.setFillColor(sf::Color(255, 240, 240));
		view.setSize(size);
		view.setPosition(position);
		view.setOutlineColor(sf::Color(230, 150, 150));
		view.setOutlineThickness(1);

		text.setFont(font);
		text.setString(line);
		text.setCharacterSize(40);
		text.setPosition(
			position.x + (size.x - (text.getLocalBounds().width + 15)) / 2,
			position.y + (size.y - (text.getLocalBounds().height + 15)) / 2
		);
		text.setFillColor(sf::Color(220, 90, 100));

	}

	void draw(sf::RenderWindow& window) {
		window.draw(view);
		window.draw(text);
	}

	bool isClicked(const sf::Vector2i& mousePos) {
		return view.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
	}

private:

	sf::RectangleShape view;
	sf::Text text;
};


void screenFightFinish(sf::RenderWindow& window, sf::Font& font) {

	sf::Text finish;
	finish.setFont(font);
	finish.setString("You finish fight!!!");
	finish.setCharacterSize(100);
	finish.setPosition(window.getSize().x / 2 - finish.getLocalBounds().width / 2, window.getSize().y / 2 - (finish.getLocalBounds().height / 2 + 100));
	finish.setFillColor(sf::Color(255, 222, 222));


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			Sleep(5000);
			menuScreen(window, font);
		}

		window.clear(sf::Color::White);
		window.draw(finish);
		window.display();
	}
}


void chooseFighters(sf::RenderWindow& window, sf::Font& font) {

	sf::Text choose;
	choose.setFont(font);
	choose.setString("Choose your fighters:");
	choose.setCharacterSize(40);
	choose.setPosition(window.getSize().x / 2 - choose.getLocalBounds().width / 2, window.getSize().y / 2 - (choose.getLocalBounds().height / 2 + 100));
	choose.setFillColor(sf::Color(180, 30, 50));

	std::string line;
	std::ifstream dino_num_in("dino_numbers.txt");
	num_buy1 = num_buy2 = num_buy3 = 0;

	if (dino_num_in.is_open())
	{
		while (std::getline(dino_num_in, line)) {

			for (auto c : line) {

				if (c - 48 == 1) {
					num_buy1++;
				}

				if (c - 48 == 2) {
					num_buy2++;
				}

				if (c - 48 == 3) {
					num_buy3++;
				}

			}
		}

	}
	dino_num_in.close();

	std::string textNumberTeran = "Teranosavr x " + std::to_string(num_buy1);
	std::string textNumberDipl = "Diplodog x " + std::to_string(num_buy2);
	std::string textNumberSteg = "Stegosavr x " + std::to_string(num_buy3);


	Button TeranosavrB({ 350, 80 }, { 700, 300 }, textNumberTeran, font);
	Button DiplodogB({ 350, 80 }, { 1100, 300 }, textNumberDipl, font);
	Button StegosavrB({ 350, 80 }, { 1500, 300 }, textNumberSteg, font);

	sf::Texture textureFighters1;
	sf::Texture textureFighters2;
	sf::Texture textureFighters3;

	textureFighters1.loadFromFile("images/Image1.png");
	textureFighters2.loadFromFile("images/Image2.png");
	textureFighters3.loadFromFile("images/Image3.png");


	sf::Sprite fighter;
	fighter.setScale(5.f, 5.f);

	int countClick = 0;
	num_choose1 = num_choose2 = num_choose3 = 0;
	sf::Event event;

	while (countClick <= 2) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);

					if (TeranosavrB.isClicked(mousePos)) {
						if ((num_choose1 + 1) <= num_buy1) {
							fighter.setTexture(textureFighters1);
							fighter.setPosition(window.getSize().x / 2 - choose.getLocalBounds().width / 2 + countClick*70, window.getSize().y / 2 - (choose.getLocalBounds().height / 2 + 200));
							countClick++;
							num_choose1++;
							pull +="1";
						}
						else {
							menuScreen(window, font);
						}
					}

					if (DiplodogB.isClicked(mousePos)) {
						if ((num_choose2 + 1) <= num_buy2) {
							fighter.setTexture(textureFighters2);
							fighter.setPosition(window.getSize().x / 2 - choose.getLocalBounds().width / 2 + countClick * 70, window.getSize().y / 2 - (choose.getLocalBounds().height / 2 + 200));
							countClick++;
							num_choose2++;
							pull += "2";
						}
						else {
							menuScreen(window, font);
						}
					}

					if (StegosavrB.isClicked(mousePos)) {
						if ((num_choose3 + 1) <= num_buy3) {
							fighter.setTexture(textureFighters3);
							fighter.setPosition(window.getSize().x / 2 - choose.getLocalBounds().width / 2 + countClick * 70, window.getSize().y / 2 - (choose.getLocalBounds().height / 2 + 200));
							countClick++;
							num_choose3++;
							pull += "3";
						}
						else {
							menuScreen(window, font);
						}
					}

				}
			}
		}
		window.clear(sf::Color(255, 222, 222));
		window.draw(choose);
		window.draw(fighter);
		TeranosavrB.draw(window);
		DiplodogB.draw(window);
		StegosavrB.draw(window);
		window.display();
	};

	std::ofstream out;
	out.open("dino_numbers.txt");
	if (out.is_open())
	{
		std::string line;
		for (int i = 0; i < (num_buy1 - num_choose1); ++i) {
			line = line + "1";
		}
		for (int i = 0; i < (num_buy2 - num_choose2); ++i) {
			line = line + "2";
		}
		for (int i = 0; i < (num_buy3 - num_choose3); ++i) {
			line = line + "3";
		}
		out << line;
	}
	out.close();

	system("cls");
	srand(time(0));

	rN1 = rand() % 4 + 1;
	rN2 = rand() % 4 + 1;
	rN3 = rand() % 4 + 1;
	enemy_pull = rN1 + rN2 + rN3;
	std::cout << enemy_pull;
	hp = 100;
	enemyhp = 100;
	dino1 = pull[0] - 48;
	Player player;
	DinoStr D;
	DinoDex D1;
	DinoInt D2;

	switch (dino1) {
	case Dinosavrus::Teranosavr:
		deal_damage = player.damage(&D);
		break;
	case Dinosavrus::Diplodog:
		deal_damage = player.damage(&D1);
		break;
	case Dinosavrus::Stegosavr:
		deal_damage = player.damage(&D2);
		break;
	}


	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> distribution(0, 2);

	int randomIndex = distribution(gen);
	Terrain randomTerrain = static_cast<Terrain>(randomIndex);

	sf::Text hpText;
	sf::Text hpEnemyText;

	sf::Texture textureIdle1;
	sf::Texture textureHurt1;
	sf::Texture textureBite1;
	sf::Texture textureDead1;

	sf::Texture textureIdle2;
	sf::Texture textureHurt2;
	sf::Texture textureBite2;
	sf::Texture textureDead2;

	sf::IntRect rectSourceSprite(0, 0, 24, 72);
	sf::IntRect rectSourceSpriteLong(0, 0, 24, 96);

	sf::Texture textureGround;
	sf::Sprite ground;

	sf::Clock clock;

	window.clear();

	while  (pull.length() != 0 or enemy_pull.length() != 0 and window.isOpen())
	{
		switch (randomTerrain) {
		case Terrain::Plain:
			textureGround.loadFromFile("images/plain.png");
			break;
		case Terrain::River:
			textureGround.loadFromFile("images/river.png");
			break;
		case Terrain::Mountain:
			textureGround.loadFromFile("images/mount.jpg");
		}
		ground.setPosition(0,300);
		ground.setTexture(textureGround);
		ground.setScale(2.f,2.f);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();

			if (pull.length() == 0 or enemy_pull.length() == 0) {
				screenFightFinish(window, font);
			};
			system("cls");
			dino1 = pull[0] - 48;

			dino2 = enemy_pull[0];

			sf::Sprite sprite1(textureIdle1, rectSourceSprite);
			sf::Sprite sprite2(textureIdle2, rectSourceSprite);


			sprite1.setScale(sf::Vector2f(10.0f, 10.0f));
			sprite2.setScale(sf::Vector2f(10.0f, 10.0f));

			sprite1.setPosition(0, 0);
			sprite2.setPosition(0, 500);

			switch (dino1) {
			case Dinosavrus::Teranosavr:
				textureIdle1.loadFromFile("images/idle1.png");
				textureHurt1.loadFromFile("images/hurt1.png");
				textureBite1.loadFromFile("images/bite1.png");
				textureDead1.loadFromFile("images/dead1.png");
				break;
			case Dinosavrus::Diplodog:
				textureIdle1.loadFromFile("images/idle2.png");
				textureHurt1.loadFromFile("images/hurt2.png");
				textureBite1.loadFromFile("images/bite2.png");
				textureDead1.loadFromFile("images/dead2.png");
				break;
			case Dinosavrus::Stegosavr:
				textureIdle1.loadFromFile("images/idle3.png");
				textureHurt1.loadFromFile("images/hurt3.png");
				textureBite1.loadFromFile("images/bite3.png");
				textureDead1.loadFromFile("images/dead3.png");
				break;
			}

			std::string hpLine;
			for (int i = 0; i < hp; i = i + 1) {
				hpLine += "|";
			}

			switch (dino2) {
			case Dinosavrus::Teranosavr:
				textureIdle2.loadFromFile("images/idle1.png");
				textureHurt2.loadFromFile("images/hurt1.png");
				textureBite2.loadFromFile("images/bite1.png");
				textureDead2.loadFromFile("images/dead1.png");
				break;
			case Dinosavrus::Diplodog:
				textureIdle2.loadFromFile("images/idle2.png");
				textureHurt2.loadFromFile("images/hurt2.png");
				textureBite2.loadFromFile("images/bite2.png");
				textureDead2.loadFromFile("images/dead2.png");
				break;
			case Dinosavrus::Stegosavr:
				textureIdle2.loadFromFile("images/idle3.png");
				textureHurt2.loadFromFile("images/hurt3.png");
				textureBite2.loadFromFile("images/bite3.png");
				textureDead2.loadFromFile("images/dead3.png");
				break;

			}

			std::string enemyhpLine;
			for (int i = 0; i < enemyhp; i++) {
				enemyhpLine += "|";
			}

			sprite1.setTextureRect(rectSourceSprite);
			sprite2.setTextureRect(rectSourceSprite);

			hpText.setFont(font);
			hpText.setString(hpLine);
			hpText.setCharacterSize(40);
			hpText.setPosition(0,200);
			hpText.setFillColor(sf::Color(180, 30, 50));

			hpEnemyText.setFont(font);
			hpEnemyText.setString(enemyhpLine);
			hpEnemyText.setCharacterSize(40);
			hpEnemyText.setPosition(0,700);
			hpEnemyText.setFillColor(sf::Color(180, 30, 50));

			hp = hp - (rand() % 20 + 10);
			sprite2.setTexture(textureBite2);
			sprite1.setTexture(textureHurt1);

			while(true){
				if (rectSourceSprite.left >= 72) {
					rectSourceSprite.left = 0;
					sprite1.setTextureRect(rectSourceSprite);
					sprite2.setTextureRect(rectSourceSprite);
					break;
				}
				else {
					rectSourceSprite.left += 24;
				}
				sprite1.setTextureRect(rectSourceSprite);
				sprite2.setTextureRect(rectSourceSprite);
				Sleep(400);
				window.clear();
				window.draw(ground);
				window.draw(sprite1);
				window.draw(sprite2);
				window.draw(hpText);
				window.draw(hpEnemyText);
				window.display();
			} 


			if ((randomTerrain == 0 and dino1 == 1) or (randomTerrain == 1 and dino1 == 2) or (randomTerrain == 2 and dino1 == 3) or (randomTerrain == 2 and dino1 == 4)) {
				enemyhp = enemyhp - (deal_damage * 2);
				sprite1.setTexture(textureBite1);
				sprite2.setTexture(textureHurt2);
				while (true) {
					if (rectSourceSprite.left >= 72) {
						rectSourceSprite.left = 0;
						sprite1.setTextureRect(rectSourceSprite);
						sprite2.setTextureRect(rectSourceSprite);
						break;
					}
					else {
						rectSourceSprite.left += 24;
					}
					sprite1.setTextureRect(rectSourceSprite);
					sprite2.setTextureRect(rectSourceSprite);
					Sleep(400);
					window.clear();
					window.draw(ground);
					window.draw(sprite1);
					window.draw(sprite2);
					window.draw(hpText);
					window.draw(hpEnemyText);
					window.display();
				}

			}
			else {
				enemyhp = enemyhp - deal_damage;
				sprite1.setTexture(textureBite1);
				sprite2.setTexture(textureHurt2);
				while (true) {
					if (rectSourceSprite.left >= 72) {
						rectSourceSprite.left = 0;
						sprite1.setTextureRect(rectSourceSprite);
						sprite2.setTextureRect(rectSourceSprite);
						break;
					}
					else {
						rectSourceSprite.left += 24;
					}
					sprite1.setTextureRect(rectSourceSprite);
					sprite2.setTextureRect(rectSourceSprite);
					Sleep(400);
					window.clear();
					window.draw(ground);
					window.draw(sprite1);
					window.draw(sprite2);
					window.draw(hpText);
					window.draw(hpEnemyText);
					window.display();
				}
			};

			if (hp <= 0) {
				pull.erase(pull.begin());
				hp = 100;
				sprite1.setTexture(textureDead1);
				sprite2.setTexture(textureIdle2);
				while (true) {
					if (rectSourceSpriteLong.left >= 96) {
						rectSourceSpriteLong.left = 0;
						sprite1.setTextureRect(rectSourceSprite);
						sprite2.setTextureRect(rectSourceSprite);
						break;
					}
					else {
						rectSourceSpriteLong.left += 24;
					}
					sprite1.setTextureRect(rectSourceSprite);
					sprite2.setTextureRect(rectSourceSprite);
					Sleep(400);
					window.clear();
					window.draw(ground);
					window.draw(sprite1);
					window.draw(sprite2);
					window.draw(hpText);
					window.draw(hpEnemyText);
					window.display();
				}
			}
			if (enemyhp <= 0) {
				enemy_pull.erase(enemy_pull.begin());
				coin_balance += (rand() % 8 + 8);
				enemyhp = 100;

				sprite2.setTexture(textureDead2);
				sprite1.setTexture(textureIdle1);
				while (true) {
					if (rectSourceSpriteLong.left >= 96) {
						rectSourceSpriteLong.left = 0;
						sprite1.setTextureRect(rectSourceSprite);
						sprite2.setTextureRect(rectSourceSprite);
						break;
					}
					else {
						rectSourceSpriteLong.left += 24;
					}
					sprite1.setTextureRect(rectSourceSpriteLong);
					sprite2.setTextureRect(rectSourceSpriteLong);
					Sleep(400);
					window.clear();
					window.draw(ground);
					window.draw(sprite1);
					window.draw(sprite2);
					window.draw(hpText);
					window.draw(hpEnemyText);
					window.display();
				}
			}
		}
	}
	pull = "";
};

void shopScreen(sf::RenderWindow& window, sf::Font& font) {

	sf::Text Money;
	Money.setFont(font);
	Money.setString("MONEY MONEY MONEY\nMONEY MONEY MONEY\nMONEY MONEY MONEY");
	Money.setCharacterSize(350);
	Money.setPosition(50, 50);
	Money.setFillColor(sf::Color(255, 233, 170, 150));

	Button Teranosavr({ 320, 80 }, { 1000, 300 }, "Teranosavr x20", font);
	Button Diplodog({ 320, 80 }, { 1000, 400 }, "Diplodog x12", font);
	Button Stegosavr({ 320, 80 }, { 1000, 500 }, "Stegosavr x16", font);
	Button menu({ 250, 80 }, { 1100, 600 }, "Menu", font);

	sf::Texture textureIDLE1;
	sf::Texture textureIDLE2;
	sf::Texture textureIDLE3;
	textureIDLE1.loadFromFile("images/idle1.png");
	textureIDLE2.loadFromFile("images/idle2.png");
	textureIDLE3.loadFromFile("images/idle3.png");

	sf::IntRect rectSourceSprite1(0, 0, 24, 144);
	sf::IntRect rectSourceSprite2(0, 0, 24, 144);
	sf::IntRect rectSourceSprite3(0, 0, 24, 144);

	sf::Sprite sprite1(textureIDLE1, rectSourceSprite1);
	sf::Sprite sprite2(textureIDLE2, rectSourceSprite2);
	sf::Sprite sprite3(textureIDLE3, rectSourceSprite3);

	sprite1.setScale(sf::Vector2f(3.5f, 3.5f));
	sprite2.setScale(sf::Vector2f(3.5f, 3.5f));
	sprite3.setScale(sf::Vector2f(3.5f, 3.5f));

	sprite1.setPosition(1350, 300);
	sprite2.setPosition(1350, 400);
	sprite3.setPosition(1350, 500);

	sf::Clock clock;

	std::string textBalance = "Your balance: "+ std::to_string(coin_balance);

	sf::Text balance;
	balance.setFont(font);
	balance.setString(textBalance);
	balance.setCharacterSize(40);
	balance.setPosition(window.getSize().x / 2 - (balance.getLocalBounds().width / 2 + 50), window.getSize().y / 2 - (balance.getLocalBounds().height / 2));
	balance.setFillColor(sf::Color(180, 30, 50));

	while (true) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (clock.getElapsedTime().asSeconds() > 0.5f) {
				if (rectSourceSprite1.left == 120) {
					rectSourceSprite1.left = 0;
					rectSourceSprite2.left = 0;
					rectSourceSprite3.left = 0;
				}
				else {
					rectSourceSprite1.left += 24;
					rectSourceSprite2.left += 24;
					rectSourceSprite3.left += 24;

					sprite1.setTextureRect(rectSourceSprite1);
					sprite2.setTextureRect(rectSourceSprite2);
					sprite3.setTextureRect(rectSourceSprite3);
					clock.restart();
				}
					
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);

					if (Teranosavr.isClicked(mousePos)) {
						if (coin_balance >= 20) {
							coin_balance = coin_balance - 20;
							std::ofstream out;
							out.open("dino_numbers.txt", std::ios::app);
							out << 1;
							std::string textBalance = "Your balance: " + std::to_string(coin_balance);
							balance.setString(textBalance);
						}
						else
						{
						}
					}

					if (Diplodog.isClicked(mousePos)) {
						if (coin_balance >= 12) {
							coin_balance = coin_balance - 12;
							std::ofstream out;
							out.open("dino_numbers.txt",std::ios::app);
							out << 2;
							std::string textBalance = "Your balance: " + std::to_string(coin_balance);
							balance.setString(textBalance);
						}
						else
						{

						}
					}

					if (Stegosavr.isClicked(mousePos)) {
						if (coin_balance >= 16) {
							coin_balance = coin_balance - 16;
							std::ofstream out;
							out.open("dino_numbers.txt", std::ios::app);
							out << 3;
							std::string textBalance = "Your balance: " + std::to_string(coin_balance);
							balance.setString(textBalance);
						}
						else
						{

						}
					}

					if (menu.isClicked(mousePos)) {
						menuScreen(window, font);
					}

				}
			}
		}

		window.clear(sf::Color::White);
		window.draw(Money);
		window.draw(balance);
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		Teranosavr.draw(window);
		Diplodog.draw(window);
		Stegosavr.draw(window);
		menu.draw(window);
		window.display();
	}
}

void adScreen(sf::RenderWindow& window, sf::Font& font) {
	sf::Texture adPicture;
	sf::Sprite adIkon;

	sf::Event event;

	if (!adPicture.loadFromFile("add.jpg")) {}
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			system("cls");
			adIkon.setTexture(adPicture);
			adIkon.setScale(7.f, 7.f);
			window.clear(sf::Color::White);
			window.draw(adIkon);
			window.display();
			Sleep(5000);
			coin_balance += 20;
			menuScreen(window, font);
		}
	}
};


void menuScreen(sf::RenderWindow& window, sf::Font& font) {

	sf::Text DINO;
	DINO.setFont(font);
	DINO.setString("DINO FIGHT");
	DINO.setCharacterSize(350);
	DINO.setPosition(50, 100);
	DINO.setFillColor(sf::Color(255, 222, 222));

	Button fight({ 250, 80 }, { 1100, 300 }, "Fight!", font);
	Button shop({ 250, 80 }, { 1100, 400 }, "Shop", font);
	Button ad({ 250, 80 }, { 1100, 500 }, "+20 coins", font);
	Button exit({ 250, 80 }, { 1100, 600 }, "Exit", font);

	sf::Texture textureIDLE1;
	sf::Texture textureIDLE2;
	sf::Texture textureIDLE3;

	textureIDLE1.loadFromFile("images/idle1.png");
	textureIDLE2.loadFromFile("images/idle2.png");
	textureIDLE3.loadFromFile("images/idle3.png");

	sf::IntRect rectSourceSprite1(0, 0, 24, 144);
	sf::IntRect rectSourceSprite2(24, 0, -24, 144);
	sf::IntRect rectSourceSprite3(24, 0, -24, 144);

	sf::Sprite sprite1(textureIDLE1, rectSourceSprite1);
	sf::Sprite sprite2(textureIDLE2, rectSourceSprite2);
	sf::Sprite sprite3(textureIDLE3, rectSourceSprite3);

	sprite1.setScale(sf::Vector2f(50.0f, 50.0f));
	sprite2.setScale(sf::Vector2f(40.0f, 40.0f));
	sprite3.setScale(sf::Vector2f(15.0f, 15.0f));

	sprite1.setPosition(0, 200);
	sprite2.setPosition(1500, 300);
	sprite3.setPosition(1350, 50);


	sf::Clock clock;

	while (true) {
		sf::Event event;

		std::ofstream out;
		out.open("cash.txt");
		if (out.is_open())
		{
			out << coin_balance << std::endl;
		}
		out.close();


		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);

					if (fight.isClicked(mousePos)) {
						chooseFighters(window, font);
					}
					if (shop.isClicked(mousePos)) {
						shopScreen(window, font);
					}
					if (ad.isClicked(mousePos)) {
						adScreen(window, font);
					}
					if (exit.isClicked(mousePos)) {
						window.close();
					}
				}
			}
			if (clock.getElapsedTime().asSeconds() > 0.5f) {
				if (rectSourceSprite1.left == 120) {
					rectSourceSprite1.left = 0;
					rectSourceSprite2.left = 0;
					rectSourceSprite3.left = 0;
				}
				else {
					rectSourceSprite1.left += 24;
					rectSourceSprite2.left += 24;
					rectSourceSprite3.left += 24;

					sprite1.setTextureRect(rectSourceSprite1);
					sprite2.setTextureRect(rectSourceSprite2);
					sprite3.setTextureRect(rectSourceSprite3);
					clock.restart();
				}
			}
		}
		window.clear(sf::Color::White);
		window.draw(DINO);
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		fight.draw(window);
		shop.draw(window);
		ad.draw(window);
		exit.draw(window);
		window.display();
	}

}


int main() {
	srand(time(NULL));
	run = true;
	num_choose1 = num_choose2 = num_choose3 = num_buy1 = num_buy2 = num_buy3 = 0;

	std::string line;
	std::ifstream cash_in("cash.txt");
	if (cash_in.is_open())
	{
		while (std::getline(cash_in, line))
		{
			coin_balance = stoi(line);
		}
	}
	cash_in.close();


	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dino");
	window.setFramerateLimit(5);
	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("HelveticaNowVar.ttf")) {
	}

	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			menuScreen(window, font);
		}

	}

	window.close();

	return 0;
}