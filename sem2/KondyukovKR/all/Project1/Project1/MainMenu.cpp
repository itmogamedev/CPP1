#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window)
{
	window_ = window;
	optionPlay.loadFromFile("menu_play.png"); optionQuit.loadFromFile("menu_quit.png");
	background.loadFromFile("menu_background.png");
	play.setTexture(optionPlay); quit.setTexture(optionQuit); bg.setTexture(background);

	play.setPosition(window_->getSize().x / 2 - 100, window_->getSize().y / 2 - 85);
	quit.setPosition(window_->getSize().x / 2 - 100, window_->getSize().y / 2);
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