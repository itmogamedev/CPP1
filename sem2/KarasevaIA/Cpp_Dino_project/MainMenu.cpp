#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font)
: font_(font)
, fight_(window, font, "FIGHT") 
, shop_(window, font, "SHOP")
, collect_(window, font, "COLLECTION")
, exit_(window, font, "EXIT")
, window_(window)
, event_(event) {

	mainText_.setFont(*font_);
	mainText_.setString("MAIN MENU");

	bgPic_.loadFromFile("pics\\bg_main.png");
	bg_.setTexture(bgPic_);
	bg_.setScale(720 / bg_.getLocalBounds().width,
				720 / bg_.getLocalBounds().height);

	fight_.setColor(sf::Color()); collect_.setColor(sf::Color());
	shop_.setColor(sf::Color()); exit_.setColor(sf::Color());
	mainText_.setColor(sf::Color());

	mainText_.setPosition(window_->getSize().x / 2 - 100, window_->getSize().y / 2 - 200);
	fight_.setPosition(window_->getSize().x / 2, window_->getSize().y / 2 - 60);
	shop_.setPosition(window_->getSize().x / 2, window_->getSize().y / 2 - 30);
	collect_.setPosition(window_->getSize().x / 2, window_->getSize().y / 2);
	exit_.setPosition(window_->getSize().x / 2, window_->getSize().y / 2 + 30);

	mainText_.setCharacterSize(40);
	fight_.setSize(25);
	shop_.setSize(25);
	collect_.setSize(25);
	exit_.setSize(25);
}

void MainMenu::draw() {
	window_->draw(bg_);
	window_-> draw(mainText_);
	fight_.draw();
	collect_.draw();
	shop_.draw();
	exit_.draw();
}

int MainMenu::render() {

	while (window_->isOpen()) {
		window_->clear();
		fight_.setColor(sf::Color()); collect_.setColor(sf::Color());
		shop_.setColor(sf::Color()); exit_.setColor(sf::Color());
		choice_ = 0;

		// collisions
		if (fight_.isHovering()) {
			fight_.setColor(sf::Color(242, 233, 228));
			choice_ = 1;
		}
		else if (collect_.isHovering()) {
			collect_.setColor(sf::Color(242, 233, 228));
			choice_ = 2;
		}
		else if (shop_.isHovering()) {
			shop_.setColor(sf::Color(242, 233, 228));
			choice_ = 3;
		}
		else if (exit_.isHovering()) {
			exit_.setColor(sf::Color(242, 233, 228));
			choice_ = 4;
		}

		// pressed keys
		if (window_->pollEvent(*event_)) {
			switch (event_->type) {
			case sf::Event::Closed: {
				window_->close();
				break;
			}
			case sf::Event::MouseButtonPressed: {
				switch (choice_)
				{
				case 1:
				case 2:
				case 3:
					return choice_;
				case 4: 
					window_->close();
					return choice_;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}

		draw();
		window_->display();
	}

	return 0;
}