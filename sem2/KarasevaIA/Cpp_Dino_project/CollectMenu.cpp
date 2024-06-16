#include "CollectMenu.h"

void CollectMenu::draw() {
	window_->draw(bg_);
	window_->draw(title_);
	back_.draw();
	leftArrow_.draw();
	rightArrow_.draw();
}

void CollectMenu::updateList(int i)
{
	list.clear();
	int num;
	maxListSize = state_->getStore()->collection.getDinos()->size();
	for (int j = 0; (j < 2) && (j + i < maxListSize); j++) {
		Dino* dino = state_->getStore()->collection.getDinos()->at(j + i);
		CollectDino d(window_, font_);

		d.tex.loadFromFile("pics\\collect\\" + dino->getName() + ".png");
		d.name.setString(dino->getName());
		d.type.setString(dino->getStrType());
		d.params.setString("Hp: " + std::to_string(dino->getHP()) + ", atk: " + dino->getAtk());
		d.setPosition(80 + 320 * j, 200);

		list.push_back(std::move(d));
		list[j].sprite.setTexture(list[j].tex);

		num = state_->getStore()->collection.isFighter(dino);
		if (num)
			list[j].isFighter.setString("Fighter #" + std::to_string(state_->getStore()->collection.getFightDinos()->size() - num + 1));
		else
			list[j].isFighter.setString("Not in a team");
	}
}

CollectMenu::CollectMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font, GameState* state)
: font_(font)
, window_(window)
, state_(state)
, event_(event)
, back_(window, font, "BACK")
, leftArrow_(window, font, "<")
, rightArrow_(window, font, ">")
{
	title_.setFont(*font_);
	title_.setString("COLLECTION");

	bgPic_.loadFromFile("pics\\bg_collect.png");
	bg_.setTexture(bgPic_);

	title_.setColor(sf::Color());
	back_.setColor(sf::Color());
	leftArrow_.setColor(sf::Color()); rightArrow_.setColor(sf::Color());

	title_.setPosition(360, 20);
	back_.setPosition(20, 20);
	leftArrow_.setPosition(20, 320);
	rightArrow_.setPosition(690, 320);

	title_.setCharacterSize(40);
	back_.setSize(30);
	leftArrow_.setSize(40);
	rightArrow_.setSize(40);
}

int CollectMenu::render() {
	int i = 0;

	while (window_->isOpen()) {
		window_->clear();
		updateList(i);
		back_.setColor(sf::Color());
		leftArrow_.setColor(sf::Color()); rightArrow_.setColor(sf::Color());
		for (CollectDino d : list)
			d.isFighter.setColor(sf::Color(242, 233, 228));
		choice_ = 0;

		// collisions
		if (rightArrow_.isHovering()) {
			rightArrow_.setColor(sf::Color(242, 233, 228));
			choice_ = 2;
		}
		else if (leftArrow_.isHovering()) {
			leftArrow_.setColor(sf::Color(242, 233, 228));
			choice_ = 3;
		}
		else if (back_.isHovering()) {
			back_.setColor(sf::Color(242, 233, 228));
			choice_ = 4;
		}
		else {
			int k = 0;
			for (CollectDino d : list) {
				if (d.isFighter.isHovering()) {
					d.isFighter.setColor(sf::Color(201, 173, 167));
					choice_ = 5 + k;
					break;
				}
				k++;
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
				case 2:
					if (i < maxListSize - 2)
						i++;
					break;
				case 3:
					if (i > 0)
						i--;
					break;
				case 4:
					return choice_;
				case 5:
				case 6: {
					int k = choice_ - 5;
					state_->getStore()->collection.manageFighters(list.at(k).name.getString());
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
		if (!list.empty())
			for (CollectDino d : list)
				d.draw();
		window_->display();
	}

	return 0;
}

CollectDino::CollectDino(sf::RenderWindow* window, sf::Font* font)
	: isFighter(window, font, "NOT IN A TEAM")
	, window_(window)
{
	name.setFont(*font);
	type.setFont(*font);
	params.setFont(*font);

	name.setCharacterSize(20);
	type.setCharacterSize(20);
	params.setCharacterSize(20);
	isFighter.setSize(20);
}

void CollectDino::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
	name.setPosition(x, y + 250);
	type.setPosition(x, y + 270);
	params.setPosition(x, y + 290);
	isFighter.setPosition(x, y + 310);
}

void CollectDino::draw()
{
	window_->draw(sprite);
	window_->draw(name);
	window_->draw(type);
	window_->draw(params);
	isFighter.draw();
}
