#include "ShopMenu.h"

void ShopMenu::draw() {
	window_->draw(bg_);
	window_->draw(title_);
	window_->draw(dialog_);
	window_->draw(budget_);
	back_.draw();
	for (ShopDino d : list) {
		d.draw();
	}
}

void ShopMenu::updateList()
{
	list.clear();
	for (int i = 0; i < state_->getStore()->collection.getAvailableDinos()->size(); i++) {
		ShopDino temp(window_, font_);
		Dino* dino = state_->getStore()->collection.getAvailableDinos()->at(i);

		std::string path = "pics\\icons\\" + dino->getName() + ".png";
		temp.tex.loadFromFile(path);

		temp.name.setString(dino->getName());
		temp.terrain.setString(dino->getStrType());
		temp.cost.setString(std::to_string(dino->getCost()));

		temp.name.setCharacterSize(20);
		temp.cost.setCharacterSize(20);
		temp.terrain.setCharacterSize(20);
		temp.buy.setSize(20);

		temp.setPosition(380, 100 + 80 * i);
		list.push_back(std::move(temp));
	}
}

ShopMenu::ShopMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font, GameState* state)
	: font_(font)
	, state_(state)
	, window_(window)
	, event_(event)
	, back_(window, font, "BACK") {

	title_.setFont(*font_);
	dialog_.setFont(*font_);
	budget_.setFont(*font_);
	title_.setString("SHOP");

	bgPic_.loadFromFile("pics\\bg_shop.png");
	bg_.setTexture(bgPic_);

	title_.setColor(sf::Color(201, 173, 167)); dialog_.setColor(sf::Color());
	budget_.setColor(sf::Color(201, 173, 167));
	back_.setColor(sf::Color(242, 233, 228));

	title_.setPosition(360, 20);
	dialog_.setPosition(60, 480);
	budget_.setPosition(60, 660);
	back_.setPosition(20, 20);

	title_.setCharacterSize(40);
	dialog_.setCharacterSize(25);
	budget_.setCharacterSize(30);
	back_.setSize(30);
}

int ShopMenu::render() {
	int i = 0;
	std::string all = "Oi! Wat'cha want\nto buy? We have\nplenty of stuff!", s = "";
	std::string budget = "Coins left: ";
	budget += std::to_string(state_->getStore()->getBudget());
	budget_.setString(budget);

	// set list of available dinos
	updateList();

	// main loop
	while (window_->isOpen()) {
		window_->clear();
		back_.setColor(sf::Color(242, 233, 228));

		for (int i = 0; i < list.size(); i++) {
			list[i].buy.setColor(sf::Color(242, 233, 228));
		}
		choice_ = 0;

		// dialog update
		if (i < all.size()) {
			s += all[i];
			dialog_.setString(s);
			i++;
		}

		// collisions
		if (back_.isHovering()) {
			back_.setColor(sf::Color(154, 140, 152));
			choice_ = 4;
		}
		else {
			for (int i = 0; i < list.size(); i++) {
				if (list[i].buy.isHovering()) {
					list[i].buy.setColor(sf::Color(154, 140, 152));
					choice_ = 5 + i;
				}
			}
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
				case 4:
					return choice_;
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10: {
					int j = choice_ - 5;
					if (state_->getStore()->canBuy(j)) {
						all = "Here you have it!\n" + state_->getStore()->buy(j) + " is\nall yours!";
						s = "";
						i = 0;
						budget = "Coins left: ";
						budget += std::to_string(state_->getStore()->getBudget());
						budget_.setString(budget);
						list.erase(list.begin() + i);
						updateList();
					}
					else {
						all = "No, you can't buy\nhim! You're as poor\nas my grandma!";
						s = "";
						i = 0;
					}
					break;
				}
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

ShopDino::ShopDino(sf::RenderWindow* window, sf::Font* font)
	: buy(window, font, "BUY")
	, window_(window)
{
	name.setFont(*font);
	cost.setFont(*font);
	terrain.setFont(*font);
}

void ShopDino::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
	name.setPosition(x + 50, y);
	terrain.setPosition(x + 50, y + 20);
	cost.setPosition(x + 240, y);
	buy.setPosition(x + 225, y + 20);
}

void ShopDino::draw()
{
	window_->draw(name);
	window_->draw(terrain);
	window_->draw(cost);
	buy.draw();
	sprite.setTexture(tex);
	window_->draw(sprite);
}
