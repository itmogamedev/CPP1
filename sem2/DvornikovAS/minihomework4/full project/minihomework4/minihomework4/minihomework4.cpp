#include <iostream>

#include "cat/cat.h"
#include "game/info.h"
#include "game/window.h"
#include "game/game.h"

#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(windowX, windowY), "kitty");

int main() {

	Game game;

	sf::RectangleShape bg(sf::Vector2f(1200, 800));
	bg.setFillColor(sf::Color(177, 219, 235));

	sf::Font ua;
	ua.loadFromFile("src/fonts/ua-BRAND-regular.otf");

	Cat cat;

	Info info;
	info.load(ua);

	sf::Text choose(L"ВЫБЕРИ ЛЮБИМЦА", ua, 30);
	choose.setOrigin(choose.getLocalBounds().width / 2, choose.getLocalBounds().height / 2);
	choose.setPosition(windowX / 2, 220);
	choose.setFillColor(sf::Color::Black);

	sf::Text pause(L"ПАУЗА", ua, 50);
	pause.setOrigin(pause.getLocalBounds().width / 2, pause.getLocalBounds().height / 2);
	pause.setPosition(windowX / 2, windowY * 2 / 5);

	sf::Text loss(L"ПОМЕР", ua, 50);
	loss.setOrigin(loss.getLocalBounds().width / 2, loss.getLocalBounds().height / 2);
	loss.setPosition(windowX / 2, windowY * 2 / 5);
	loss.setFillColor(sf::Color::Red);

	sf::Text win(L"ВОСКРЕС", ua, 50);
	win.setOrigin(win.getLocalBounds().width / 2, win.getLocalBounds().height / 2);
	win.setPosition(windowX / 2, windowY * 2 / 5);
	win.setFillColor(sf::Color::Green);

	sf::RectangleShape lossBG(sf::Vector2f(1200, 800));
	lossBG.setFillColor(sf::Color(0, 0, 0, 230));

	sf::Texture texRestart, texRestartHold;
	texRestart.loadFromFile("src/img/btnRestart.png");
	texRestartHold.loadFromFile("src/img/btnRestartHold.png");
	sf::Texture texExit, texExitHold;
	texExit.loadFromFile("src/img/btnExit.png");
	texExitHold.loadFromFile("src/img/btnExitHold.png");

	sf::Sprite spRestart;
	spRestart.setTexture(texRestart);
	spRestart.setPosition(150, 450);
	sf::Sprite spExit;
	spExit.setTexture(texExit);
	spExit.setPosition(650, 450);

	sf::Texture texFoodIcon, texDrinkIcon, texCleanIcon, texSizeIcon;
	texFoodIcon.loadFromFile("src/img/foodIcon.png");
	texDrinkIcon.loadFromFile("src/img/drinkIcon.png");
	texCleanIcon.loadFromFile("src/img/cleanIcon.png");
	texSizeIcon.loadFromFile("src/img/sizeIcon.png");
	sf::Sprite spFoodIcon, spDrinkIcon, spCleanIcon, spSizeIcon;
	spFoodIcon.setTexture(texFoodIcon);
	spDrinkIcon.setTexture(texDrinkIcon);
	spCleanIcon.setTexture(texCleanIcon);
	spSizeIcon.setTexture(texSizeIcon);
	spFoodIcon.setPosition(250, 550);
	spDrinkIcon.setPosition(550, 550);
	spCleanIcon.setPosition(850, 550);
	spSizeIcon.setPosition(950, 150);

	sf::Texture texFeed, texDrink, texClean, texFeedHold, texDrinkHold, texCleanHold;
	texFeed.loadFromFile("src/img/btnFeed.png");
	texDrink.loadFromFile("src/img/btnDrink.png");
	texClean.loadFromFile("src/img/btnClean.png");
	texFeedHold.loadFromFile("src/img/btnFeedHold.png");
	texDrinkHold.loadFromFile("src/img/btnDrinkHold.png");
	texCleanHold.loadFromFile("src/img/btnCleanHold.png");
	sf::Sprite spFeed, spDrink, spClean;
	spFeed.setTexture(texFeed);
	spDrink.setTexture(texDrink);
	spClean.setTexture(texClean);
	spFeed.setPosition(165, 650);
	spDrink.setPosition(465, 650);
	spClean.setPosition(765, 650);

	sf::Texture texChooseCat, texChooseDog, texChooseBeaver;
	texChooseCat.loadFromFile("src/img/chooseCat.png");
	texChooseDog.loadFromFile("src/img/chooseDog.png");
	texChooseBeaver.loadFromFile("src/img/chooseBeaver.png");
	sf::Sprite spChooseCat, spChooseDog, spChooseBeaver;
	spChooseCat.setTexture(texChooseCat);
	spChooseDog.setTexture(texChooseDog);
	spChooseBeaver.setTexture(texChooseBeaver);
	spChooseCat.setPosition(475, 350);
	spChooseDog.setPosition(175, 350);
	spChooseBeaver.setPosition(775, 350);

	sf::Texture texChooseCatHold, texChooseDogHold, texChooseBeaverHold;
	texChooseCatHold.loadFromFile("src/img/chooseCatHold.png");
	texChooseDogHold.loadFromFile("src/img/chooseDogHold.png");
	texChooseBeaverHold.loadFromFile("src/img/chooseBeaverHold.png");
	sf::Sprite spChooseCatHold, spChooseDogHold, spChooseBeaverHold;
	spChooseCatHold.setTexture(texChooseCatHold);
	spChooseDogHold.setTexture(texChooseDogHold);
	spChooseBeaverHold.setTexture(texChooseBeaverHold);
	spChooseCatHold.setPosition(475, 350);
	spChooseDogHold.setPosition(175, 350);
	spChooseBeaverHold.setPosition(775, 350);

	bool clicked = false;
	sf::Clock clock;

	bool btnClicked = false;
	sf::Clock spClock;

	while (window.isOpen()) {

		sf::Event event{};

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				if (game.status == gameStatus::PLAY)
					game.pause();
				else
					game.resume();
			}
		}

		window.clear();
		window.draw(bg);

		if (game.status != gameStatus::START) {

			window.draw(cat.getSprite());

			window.draw(info.getSatiety());
			window.draw(info.getSatisfaction());
			window.draw(info.getPurity());
			window.draw(info.getSize());

			window.draw(spFoodIcon);
			window.draw(spDrinkIcon);
			window.draw(spCleanIcon);
			window.draw(spSizeIcon);

			window.draw(spFeed);
			window.draw(spDrink);
			window.draw(spClean);
		}

		if (!cat.isWon()) {

			if (game.status == gameStatus::START) {
				window.draw(choose);
				window.draw(spChooseCat);
				window.draw(spChooseDog);
				window.draw(spChooseBeaver);

				sf::FloatRect boundsDog = spChooseDog.getGlobalBounds();

				if (boundsDog.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					window.draw(spChooseDogHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							cat.setType(Animal::DOG);
							game.restart(cat);
							game.status = gameStatus::PLAY;
							cat.born();
						}
					}
				}

				sf::FloatRect boundsCat = spChooseCat.getGlobalBounds();

				if (boundsCat.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					window.draw(spChooseCatHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							cat.setType(Animal::CAT);
							game.restart(cat);
							game.status = gameStatus::PLAY;
							cat.born();
						}
					}
				}

				sf::FloatRect boundsBeaver = spChooseBeaver.getGlobalBounds();

				if (boundsBeaver.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					window.draw(spChooseBeaverHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							cat.setType(Animal::BEAVER);
							game.restart(cat);
							game.status = gameStatus::PLAY;
							cat.born();
						}
					}
				}

			}

			if (game.status == gameStatus::PLAY and cat.isAlive()) {
				cat.live();
				info.update(cat.getSatiety(), cat.getSatisfaction(), cat.getPurity(), cat.getSize());

				sf::FloatRect boundsFeed = spFeed.getGlobalBounds();

				if (boundsFeed.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					spFeed.setTexture(texFeedHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
							clicked = true;
							clock.restart();
							cat.increaseSatiety();
							btnClicked = true;
							spClock.restart();
							if (cat.getType() == Animal::CAT)
								cat.setTexture("src/img/fededCat.png");
							else if (cat.getType() == Animal::DOG)
								cat.setTexture("src/img/fededDog.png");
							else if (cat.getType() == Animal::BEAVER)
								cat.setTexture("src/img/fededBeaver.png");
						}
					}
					else if (event.type == sf::Event::MouseButtonReleased) {
						clicked = false;
					}
				}
				else {
					spFeed.setTexture(texFeed);
				}

				sf::FloatRect boundsDrink = spDrink.getGlobalBounds();

				if (boundsDrink.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					spDrink.setTexture(texDrinkHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
							clicked = true;
							clock.restart();
							cat.increaseSatisfaction();
							btnClicked = true;
							spClock.restart();
							if (cat.getType() == Animal::CAT)
								cat.setTexture("src/img/wateredCat.png");
							else if (cat.getType() == Animal::DOG)
								cat.setTexture("src/img/wateredDog.png");
							else if (cat.getType() == Animal::BEAVER)
								cat.setTexture("src/img/wateredBeaver.png");
						}
					}
					else if (event.type == sf::Event::MouseButtonReleased) {
						clicked = false;
					}
				}
				else {
					spDrink.setTexture(texDrink);
				}

				sf::FloatRect boundsClean = spClean.getGlobalBounds();

				if (boundsClean.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					spClean.setTexture(texCleanHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
							clicked = true;
							clock.restart();
							cat.increasePurity();
							btnClicked = true;
							spClock.restart();
							if (cat.getType() == Animal::CAT)
								cat.setTexture("src/img/cleanedCat.png");
							else if (cat.getType() == Animal::DOG)
								cat.setTexture("src/img/cleanedDog.png");
							else if (cat.getType() == Animal::BEAVER)
								cat.setTexture("src/img/cleanedBeaver.png");
						}
					}
					else if (event.type == sf::Event::MouseButtonReleased) {
						clicked = false;
					}
				}
				else {
					spClean.setTexture(texClean);
				}

				if (clock.getElapsedTime().asSeconds() > 1)
					clicked = false;

				if (spClock.getElapsedTime().asSeconds() > 0.5 and btnClicked == true) {
					if (cat.getType() == Animal::CAT)
						cat.setTexture("src/img/ordinaryCat.png");
					else if (cat.getType() == Animal::DOG)
						cat.setTexture("src/img/ordinaryDog.png");
					else if (cat.getType() == Animal::BEAVER)
						cat.setTexture("src/img/ordinaryBeaver.png");
					btnClicked = false;
				}

			}

			if (game.status == gameStatus::PAUSE and cat.isAlive()) {
				window.draw(lossBG);
				window.draw(pause);
			}

			if (!cat.isAlive()) {

				sf::FloatRect boundsRestart = spRestart.getGlobalBounds();

				if (boundsRestart.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					spRestart.setTexture(texRestartHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							game.restart(cat);
						}
					}
				}
				else {
					spRestart.setTexture(texRestart);
				}

				sf::FloatRect boundsExit = spExit.getGlobalBounds();

				if (boundsExit.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					spExit.setTexture(texExitHold);
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							window.close();
						}
					}
				}
				else {
					spExit.setTexture(texExit);
				}


				window.draw(lossBG);
				window.draw(loss);
				window.draw(spRestart);
				window.draw(spExit);

			}
		}
		else if (cat.isWon()) {

			sf::FloatRect boundsRestart = spRestart.getGlobalBounds();

			if (boundsRestart.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				spRestart.setTexture(texRestartHold);
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						game.restart(cat);
					}
				}
			}
			else {
				spRestart.setTexture(texRestart);
			}

			sf::FloatRect boundsExit = spExit.getGlobalBounds();

			if (boundsExit.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				spExit.setTexture(texExitHold);
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						window.close();
					}
				}
			}
			else {
				spExit.setTexture(texExit);
			}


			window.draw(lossBG);
			window.draw(win);
			window.draw(spRestart);
			window.draw(spExit);

		}

		window.display();
	}

}