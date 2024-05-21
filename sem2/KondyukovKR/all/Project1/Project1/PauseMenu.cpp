#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	window_ = window;
	if (!bgPic_.loadFromFile("pause_bg.png")) std::cout << "Nooo";
	menuPic_.loadFromFile("pause_menu.png");
	contPic_.loadFromFile("continue.png");
	exitPic_.loadFromFile("exit.png");
	bg_.setTexture(bgPic_); menu_.setTexture(menuPic_); menu_.setColor(sf::Color::Black);
	cont_.setTexture(contPic_); exit_.setTexture(exitPic_);

	bg_.setPosition(window_->getSize().x / 2 - 346, window_->getSize().y / 2 - 226);
	menu_.setPosition(window_->getSize().x / 2 - 346, window_->getSize().y / 2 - 226);
	cont_.setPosition(window_->getSize().x / 2 - 200, window_->getSize().y / 2);
	exit_.setPosition(window_->getSize().x / 2 + 100, window_->getSize().y / 2 - 20);
}

void PauseMenu::draw()
{
	window_->draw(bg_);
	window_->draw(menu_);
	window_->draw(cont_);
	window_->draw(exit_);
}

int PauseMenu::render()
{
	isOn_ = true;

	while (isOn_)
	{
		window_->clear(sf::Color::White);
		cont_.setColor(sf::Color::Black);
		exit_.setColor(sf::Color::Black);
		choice_ = 0;

		// Collisions
		if (sf::IntRect(cont_.getPosition().x, cont_.getPosition().y, 99, 116)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			cont_.setColor(sf::Color::Cyan);
			choice_ = 1;
		}
		if (sf::IntRect(exit_.getPosition().x, exit_.getPosition().y, 150, 197)
			.contains(sf::Mouse::getPosition(*window_)))
		{
			exit_.setColor(sf::Color::Cyan);
			choice_ = 2;
		}

		// If Mouse Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice_ == 1) { isOn_ = false; return 1; }
			if (choice_ == 2) { isOn_ = false; return 2; }
		}

		draw();
		window_->display();
	}
}

void PauseMenu::winMenu()
{
}

void PauseMenu::loseMenu()
{
}
