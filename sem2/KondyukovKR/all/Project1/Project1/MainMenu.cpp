#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window, sf::Event* event)
{
	window_ = window;
	event_ = event;
	winX = window->getSize().x; winY = window->getSize().y;
	optionPlay.loadFromFile("menu_play.png"); optionQuit.loadFromFile("menu_quit.png");
	background.loadFromFile("menu_background.png");
	play.setTexture(optionPlay); quit.setTexture(optionQuit); bg.setTexture(background);

	play.setPosition(winX / 2 - 170, winY / 2 - 85);
	quit.setPosition(winX / 2 - 170, winY / 2);
	bg.setPosition(0, 0);
}

bool MainMenu::render()
{
	isOn = true;

	while (isOn)
	{
		play.setColor(sf::Color::Black);
		quit.setColor(sf::Color::Black);
		choice = 0;
		window_->clear(sf::Color::White);

		// collisions
		if (sf::IntRect(play.getPosition().x, play.getPosition().y, 355, 83)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			play.setColor(sf::Color::Cyan);
			choice = 1;
		}
		if (sf::IntRect(quit.getPosition().x, quit.getPosition().y, 355, 83)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			quit.setColor(sf::Color::Cyan);
			choice = 2;
		}

		// if pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice == 1) { isOn = false; return true; }
			if (choice == 2) { isOn = false; return false; }
		}

		window_->draw(bg);
		window_->draw(play);
		window_->draw(quit);
		window_->display();
	}
}

int MainMenu::choosePet()
{
	isOn = true;

	optionCat.loadFromFile("choose_menu_cat.png"); optionDog.loadFromFile("choose_menu_dog.png");
	optionChin.loadFromFile("choose_menu_chin.png"); optionText.loadFromFile("choose_menu1.png");
	cat.setTexture(optionCat); dog.setTexture(optionDog);  chin.setTexture(optionChin); text.setTexture(optionText);
	text.setScale(0.5, 0.5); cat.setScale(0.5, 0.5); dog.setScale(0.5, 0.5); chin.setScale(0.5, 0.5);
	cat.setPosition(winX / 2 - 400, winY / 2); dog.setPosition(winX / 2 - 170, winY / 2);
	chin.setPosition(winX / 2 + 170, winY / 2); text.setPosition(winX / 2 - 312, winY / 2 - 300);

	text.setColor(sf::Color::Black);

	while (isOn && window_->isOpen())
	{
		cat.setColor(sf::Color::Black);
		dog.setColor(sf::Color::Black);
		chin.setColor(sf::Color::Black);
		window_->clear(sf::Color::White);
		choice = 0;

		// collisions
		if (sf::IntRect(cat.getPosition().x, cat.getPosition().y, 121, 43)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			cat.setColor(sf::Color::Cyan);
			choice = 1;
		}
		if (sf::IntRect(dog.getPosition().x, dog.getPosition().y, 274, 44)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			dog.setColor(sf::Color::Cyan);
			choice = 2;
		}
		if (sf::IntRect(chin.getPosition().x, chin.getPosition().y, 420, 42)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			chin.setColor(sf::Color::Cyan);
			choice = 3;
		}
		if (window_->pollEvent(*event_)&& event_->type == sf::Event::Closed) { isOn = false; window_->close(); return 0; }

		// if pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice == 1) { isOn = false; return 1; }
			if (choice == 2) { isOn = false; return 2; }
			if (choice == 3) { isOn = false; return 3; }
		}

		window_->draw(text); window_->draw(cat); window_->draw(dog); window_->draw(chin);
		window_->display();
	}

	return 0;
}
