#include "FightMenu.h"

void FightMenu::draw() {
	window_->draw(bg_);
	window_->draw(ally_);
	window_->draw(opp_);
	window_->draw(title_);
	window_->draw(allyDesc_);
	window_->draw(allyName_);
	window_->draw(oppDesc_);
	window_->draw(oppName_);
	window_->draw(welcome_);
	back_.draw();
}

FightMenu::FightMenu(sf::RenderWindow* window, sf::Event* event, sf::Font* font, GameState* state)
	: font_(font)
	, state_(state)
	, window_(window)
	, event_(event)
	, back_(window, font, "BACK")
{
	title_.setFont(*font_);
	title_.setString("FIGHT!");
	welcome_.setFont(*font_);
	allyName_.setFont(*font_);
	allyDesc_.setFont(*font_);
	oppName_.setFont(*font_);
	oppDesc_.setFont(*font_);

	title_.setColor(sf::Color()); welcome_.setColor(sf::Color());
	back_.setColor(sf::Color());

	title_.setPosition(360, 20);
	welcome_.setPosition(210, 225);
	allyName_.setPosition(40, 210);
	allyDesc_.setPosition(40, 520);
	oppName_.setPosition(410, 210);
	oppDesc_.setPosition(410, 520);
	back_.setPosition(20, 20);
	ally_.setPosition(40, 280);
	opp_.setPosition(400, 280);

	title_.setCharacterSize(40);
	welcome_.setCharacterSize(30);
	allyName_.setCharacterSize(20);
	oppName_.setCharacterSize(20);
	allyDesc_.setCharacterSize(30);
	oppDesc_.setCharacterSize(30);
	back_.setSize(30);
}

int FightMenu::render() {
	int i = 0;

	ally_.setScale(0,0);
	allyName_.setString("");
	allyDesc_.setString("");
	opp_.setScale(0,0);
	oppName_.setString("");
	oppDesc_.setString("");

	std::string all = "Let the fight begin!\nLocation is: ...\n", s = "";
	bgPic_.loadFromFile("pics\\bg_fight.png");
	bg_.setTexture(bgPic_);
	bg_.setScale(0.5, 0.5);
	bg_.setPosition(160, 160);

	state_->getFight()->generateLocation();
	all += terrainToString(state_->getFight()->location);
	all += "!\nYour opponent is\nready.";
	bool isOn = true;

	while (window_->isOpen() && isOn) {
		window_->clear(sf::Color::White);
		back_.setColor(sf::Color());
		choice_ = 0;

		// welcome string
		if (i < all.size()) {
			s += all[i];
			i++;
			welcome_.setString(s);
		}

		// collisions
		if (back_.isHovering()) {
			back_.setColor(sf::Color(242, 233, 228));
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
				case 4:
					return choice_;
				default:
					isOn = false;
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

	// set location pic
	switch (state_->getFight()->location) {
	case Plain:
		bgPic_.loadFromFile("pics\\bg_plain.png");
		bg_.setTexture(bgPic_);
		bg_.setScale(1, 1);
		break;
	case Mountain:
		bgPic_.loadFromFile("pics\\bg_mountain.png");
		bg_.setTexture(bgPic_);
		bg_.setScale(2.1, 2.1);
		break;
	default:
		bgPic_.loadFromFile("pics\\bg_river.png");
		bg_.setTexture(bgPic_);
		bg_.setScale(2, 2);
		break;
	}

	ally_.setScale(1, 1);
	opp_.setScale(1, 1);
	bg_.setPosition(0, 0);
	welcome_.setString("");

	// generate pull
	state_->getFight()->generatePull();
	bool allyTurn = true, animDamage = false, animExplode = false;
	bool res = 0;
	int coins = 0;

	// set first textures
	allyPic_.loadFromFile("pics\\" + state_->getStore()->collection.getFightDinos()->at(state_->getFight()->numAlly - 1)->getName() + "_left.png");
	ally_.setTexture(allyPic_);
	allyName_.setString(state_->getStore()->collection.getFightDinos()->at(state_->getFight()->numAlly - 1)->getName());
	allyDesc_.setString("hp: " + std::to_string(state_->getFight()->hpAlly));
	oppPic_.loadFromFile("pics\\" + state_->getFight()->enemy[state_->getFight()->numEnemy - 1]->getName() + "_right.png");
	opp_.setTexture(oppPic_);
	oppName_.setString(state_->getFight()->enemy.at(state_->getFight()->numEnemy - 1)->getName());
	oppDesc_.setString("hp: " + std::to_string(state_->getFight()->hpEnemy));

	// set animation sprites
	sf::Clock clock1, clock2, clock3, clock4;
	sf::IntRect damageRect(0, 0, 190, 60), explodeRect(0, 0, 128, 128);
	sf::Texture damageTex, explodeTex;
	explodeTex.loadFromFile("pics\\sprite_explosion.png");
	sf::Sprite damageSprite(damageTex, damageRect), explodeSprite(explodeTex, explodeRect);
	explodeSprite.setScale(0, 0);
	damageSprite.setScale(0, 0);

	// main fight loop
	while (window_->isOpen()) {
		window_->clear();
		back_.setColor(sf::Color());
		choice_ = 0;

		// battle
		if (state_->getFight()->numAlly > 0 && state_->getFight()->numEnemy > 0) {

			// ally attacks
			if (allyTurn && clock1.getElapsedTime().asSeconds() >= 0.9f) {
				allyTurn = false;
				animDamage = true;

				damageTex.loadFromFile("pics\\sprite_right_damage.png");
				damageSprite.setTexture(damageTex);
				damageSprite.setPosition(350, 300);
				damageSprite.setScale(1, 1);
				clock1.restart();

				state_->getFight()->allyTurn();
				oppDesc_.setString("hp: " + std::to_string(state_->getFight()->hpEnemy));
			} // opponent attacks
			else if (clock1.getElapsedTime().asSeconds() >= 0.9f) {
				allyTurn = true;
				animDamage = true;

				damageTex.loadFromFile("pics\\sprite_left_damage.png");
				damageSprite.setTexture(damageTex);
				damageSprite.setPosition(200, 300);
				damageSprite.setScale(1, 1);
				clock1.restart();

				state_->getFight()->oppTurn();
				allyDesc_.setString("hp: " + std::to_string(state_->getFight()->hpAlly));
			}

			// damage animation
			if (animDamage && clock2.getElapsedTime().asSeconds() >= 0.02f) {
				if (damageRect.left == 190) {
					// check if we need to stop the animation
					if (damageRect.top == 120) {
						animDamage = false;
						damageRect.left = 0;
						damageRect.top = 0;
						damageSprite.setScale(0,0);
					}
					else {
						damageRect.left = 0;
						damageRect.top += 60;
					}
				}
				else damageRect.left += 190;

				clock2.restart();
				damageSprite.setTextureRect(damageRect);
			}

			// if ally dies
			if (state_->getFight()->hpAlly <= 0 && clock4.getElapsedTime().asSeconds() >= 0.9f)
			{
				state_->getFight()->numAlly--;
				explodeSprite.setPosition(90, 345);
				explodeSprite.setScale(1, 1);
				animExplode = true;
				clock4.restart();

				if (state_->getFight()->numAlly > 0) {
					allyPic_.loadFromFile("pics\\" + state_->getFight()->ally[state_->getFight()->numAlly - 1]->getName() + "_left.png");
					ally_.setTexture(allyPic_);
					state_->getFight()->hpAlly = state_->getFight()->ally[state_->getFight()->numAlly - 1]->getHP();
					allyName_.setString(state_->getFight()->ally[state_->getFight()->numAlly - 1]->getName());
					allyDesc_.setString("hp: " + std::to_string(state_->getFight()->hpAlly));
				}
				else {
					res = false;
					coins = state_->getFight()->result(res);
					s = "Oh... you died.\nYou've lost: " + std::to_string(coins) + " coins";
					welcome_.setString(s);
				}
			} else 
			// if enemy dies
			if (state_->getFight()->hpEnemy <= 0 && clock4.getElapsedTime().asSeconds() >= 0.9f)
			{
				state_->getFight()->numEnemy--;
				explodeSprite.setPosition(480, 345);
				explodeSprite.setScale(1, 1);
				animExplode = true;
				clock4.restart();

				if (state_->getFight()->numEnemy > 0) {
					oppPic_.loadFromFile("pics\\" + state_->getFight()->enemy[state_->getFight()->numEnemy - 1]->getName() + "_right.png");
					opp_.setTexture(oppPic_);
					oppName_.setString(state_->getFight()->enemy[state_->getFight()->numEnemy - 1]->getName());
					state_->getFight()->hpEnemy = state_->getFight()->enemy[state_->getFight()->numEnemy - 1]->getHP();
					oppDesc_.setString("hp: " + std::to_string(state_->getFight()->hpEnemy));

				}
				else { 
					res = true;
					coins = state_->getFight()->result(res);
					s = "Congrats, you won!\nYou've earned: " + std::to_string(coins) + " coins";
					welcome_.setString(s);
				}
			}

			// death animation
			if (animExplode && clock3.getElapsedTime().asSeconds() >= 0.02f) {
				if (explodeRect.left == 384) {
					if (explodeRect.top == 384) {
						// stop animation
						animExplode = false;
						explodeSprite.setScale(0, 0);
						explodeRect.left = 0;
						explodeRect.top = 0;
					}
					else {
						explodeRect.left = 0;
						explodeRect.top += 128;
					}
				}
				else {
					explodeRect.left += 128;
				}
				clock3.restart();
				explodeSprite.setTextureRect(explodeRect);
			}
		}

		// collisions
		else if (back_.isHovering()) {
			back_.setColor(sf::Color(242, 233, 228));
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
				case 4:
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
		window_->draw(damageSprite);
		window_->draw(explodeSprite);
		window_->display();
	}

	return 0;
}
