#pragma once

#ifndef MAIN_CYCLE_H__
#define	MAIN_CYCLE_H__

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include "Music.h"
#include "Texts.h"
#include "Images.h"
#include "Card.h"
#include "window.h"
#include "GameData.h"

GameData gamedata;

enum STATUS {
	LOAD_SCREEN,
	MAIN_MENU,
	SETTINGS,
	PLAY,
	SHOP,
	EXIT
};

STATUS currentState = STATUS::LOAD_SCREEN;

void loadData();
void saveData();
double speed_function(double);
int load_screen();
int waiting_for_input(sf::Sprite);
int to_main();
int main_menu();
int settings();
int play();
int player_won();
int enemy_won();
int battle();
int start_battle();
int shop();
int exit_game();

static int balance;

void loadData() {
	gamedata.loadDataFromFile("data.txt");
	balance = gamedata.getBalance();
	status_cards.clear();
	for (int i = 0; i < gamedata.getStatus().size(); i++)
		status_cards.push_back(gamedata.getStatus().at(i));
	for (int i = 0; i < status_cards.size(); i++) {
		shop_cards.at(i).second.second = status_cards.at(i);
	}
	available_cards.clear();
	for (int i = 0; i < shop_cards.size(); i++) {
		if (shop_cards.at(i).second.second == true)
			available_cards.push_back(shop_cards.at(i).first);
	}
}

void saveData() {

	gamedata.setBalance(balance);
	status_cards.clear();
	for (int i = 0; i < shop_cards.size(); i++)
		status_cards.push_back(shop_cards.at(i).second.second);
	gamedata.setStatus(status_cards);
	gamedata.saveDataToFile("data.txt");
}

void main_cycle() {
	load_screen();
	loadData();
	main_menu();
}

double speed_function(double speed) {

	return log(speed) / speed;
}

int load_screen() {

	intro.play();
	intro.setVolume(50);

	double k = 0;
	double speed = 1;

	_title.setPosition(window.getSize().x / 2 - _title.getGlobalBounds().width / 2, -10 - _title.getGlobalBounds().height);

	sf::Clock timer;
	sf::Time tickRate;
	sf::Clock timer2;
	bool wait = 1;

	sf::Vector2f movement(0, 700);
	double start_speed = movement.y, current_speed;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}

		window.clear();
		
		if (!wait) {
			tickRate = timer.restart();
			current_speed = start_speed - 400 * timer2.getElapsedTime().asSeconds();
			movement.y = current_speed;
			_title.move(movement * ((float)tickRate.asSeconds()));
		}

		if (wait and timer.getElapsedTime().asSeconds() > 2) {
			wait = 0;
			timer.restart();
			timer2.restart();
		}


		window.draw(_title);

		if (movement.y <= 0) {
			waiting_for_input(_title);
			return 0;
		}


		window.display();
	}

}

int waiting_for_input(sf::Sprite sprite) {

	int visible = 256;
	std::string dir = "down";
	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else {
					currentState = STATUS::MAIN_MENU;
					to_main();
					return 0;
				}
			}
		}

		window.clear();

		window.draw(sprite);

		if (clock.getElapsedTime().asSeconds() > 2) {
			t_under.setFillColor(sf::Color(255, 255, 255, visible));
			if (dir == "down") {
				visible -= 5;
				if (visible <= 0) {
					visible = 0;
					dir = "up";
				}
			}
			else if (dir == "up") {
				visible += 5;
				if (visible >= 255) {
					visible = 255;
					dir = "down";
				}
			}
			window.draw(t_under);
		}

		window.display();
	}

}

int to_main() {

	double k = 0;
	double speed = 1;

	sf::Clock timer;
	sf::Time tickRate;
	sf::Clock timer2;

	sf::Vector2f movement(0, -200);
	double start_speed = movement.y, current_speed;

	//
	sf::Vector2f movement2(500, 0);
	double start_speed2 = movement2.x, current_speed2;

	sp_start.setPosition(-300, 450);
	sp_shop.setPosition(-300, 550);
	sp_options.setPosition(-300, 650);
	sp_exit.setPosition(-300, 750);
	//

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}

		window.clear();

		tickRate = timer.restart();

		current_speed = start_speed + 70 * timer2.getElapsedTime().asSeconds();
		movement.y = current_speed;
		_title.move(movement * ((float)tickRate.asSeconds()));

		if (movement2.x > 0) {
			current_speed2 = start_speed2 - 309 * timer2.getElapsedTime().asSeconds();
			movement2.x = current_speed2;
			sp_start.move(movement2 * ((float)tickRate.asSeconds()));
			sp_shop.move(movement2 * ((float)tickRate.asSeconds()));
			sp_options.move(movement2 * ((float)tickRate.asSeconds()));
			sp_exit.move(movement2 * ((float)tickRate.asSeconds()));
		}


		if (movement.y >= 0)
			return 0;

		window.draw(_title);
		window.draw(sp_start);
		window.draw(sp_shop);
		window.draw(sp_options);
		window.draw(sp_exit);

		window.display();
	}

}

int main_menu() {

	int visible = 0;
	std::string dir = "up";

	int num_bord = 1;

	sp_start.setPosition(100, 450);
	sp_shop.setPosition(100, 550);
	sp_options.setPosition(100, 650);
	sp_exit.setPosition(100, 750);

	sf::RectangleShape r1(sf::Vector2f(10, 100));
	r1.setPosition(100, 450);
	sf::RectangleShape r2(sf::Vector2f(10, 100));
	r2.setPosition(100, 550);
	sf::RectangleShape r3(sf::Vector2f(10, 100));
	r3.setPosition(100, 650);
	sf::RectangleShape r4(sf::Vector2f(10, 100));
	r4.setPosition(100, 750);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					exit_game();
				}
			}
		}

		window.clear();

		window.draw(_title);

		sf::FloatRect playBound = sp_start.getGlobalBounds();
		sf::FloatRect shopBound = sp_shop.getGlobalBounds();
		sf::FloatRect optionsBound = sp_options.getGlobalBounds();
		sf::FloatRect exitBound = sp_exit.getGlobalBounds();

		if (playBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			or r1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_start.setColor(sf::Color::Cyan);
			sp_start.setPosition(110, 450);
			if (event.mouseButton.button == sf::Mouse::Left) {
				play();
			}
		}
		else {
			sp_start.setColor(sf::Color::White);
			sp_start.setPosition(100, 450);
		}

		if (shopBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			or r2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_shop.setColor(sf::Color::Cyan);
			sp_shop.setPosition(110, 550);
			if (event.mouseButton.button == sf::Mouse::Left) {
				shop();
			}
		}
		else {
			sp_shop.setColor(sf::Color::White);
			sp_shop.setPosition(100, 550);
		}

		if (optionsBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			or r3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_options.setColor(sf::Color::Cyan);
			sp_options.setPosition(110, 650);
			if (event.mouseButton.button == sf::Mouse::Left) {
				settings();
			}
		}
		else {
			sp_options.setColor(sf::Color::White);
			sp_options.setPosition(100, 650);
		}

		if (exitBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
			or r4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_exit.setColor(sf::Color::Cyan);
			sp_exit.setPosition(110, 750);
			if (event.mouseButton.button == sf::Mouse::Left) {
				exit_game();
			}
		}
		else {
			sp_exit.setColor(sf::Color::White);
			sp_exit.setPosition(100, 750);
		}

		window.draw(sp_start);
		window.draw(sp_shop);
		window.draw(sp_options);
		window.draw(sp_exit);

		window.display();
	}
	return 0;
}

int settings() {

	sp_music.setPosition(590, 459);
	sp_sound.setPosition(618, 559);
	music_button.setPosition(1175, 459);
	sound_button.setPosition(1175, 559);
	sp_back.setPosition(10, 980);

	bool clicked = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					main_menu();
				}
			}
		}

		window.clear();

		sf::FloatRect musicBound = music_button.getGlobalBounds();
		sf::FloatRect soundBound = sound_button.getGlobalBounds();
		sf::FloatRect backBound = sp_back.getGlobalBounds();

		if (musicBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			music_button.setColor(sf::Color::Cyan);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					if (music_button.getTexture() == &t_switch_yes) {
						music_button.setTexture(t_switch_no);
						intro.setVolume(0);
						clicked = true;
					}
					else {
						music_button.setTexture(t_switch_yes);
						intro.setVolume(50);
						clicked = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
		}
		else {
			music_button.setColor(sf::Color::White);
		}

		if (soundBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sound_button.setColor(sf::Color::Cyan);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					if (sound_button.getTexture() == &t_switch_yes) {
						sound_button.setTexture(t_switch_no);
						clicked = true;
					}
					else {
						sound_button.setTexture(t_switch_yes);
						clicked = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
		}
		else {
			sound_button.setColor(sf::Color::White);
		}

		if (backBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_back.setColor(sf::Color::Cyan);
			if (event.mouseButton.button == sf::Mouse::Left) {
				main_menu();
			}
		}
		else {
			sp_back.setColor(sf::Color::White);
		}

		window.draw(sp_music);
		window.draw(sp_sound);
		window.draw(sp_back);

		window.draw(music_button);
		window.draw(sound_button);

		window.display();
	}

	return 0;
}

Terrain current_terrain;

int play() {

	picked_cards.clear();

	std::vector <std::pair<sf::Text, double>> areas;

	sf::Text area(L"", muller, 50);
	sf::Text area_type(L"местность", muller, 20);
	area_type.setFillColor(sf::Color(150, 150, 150));
	area_type.setPosition(window.getSize().x / 2 - area_type.getGlobalBounds().width / 2, 130);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 3);
	int y_position = -20;
	for (int i = 0; i < 22; i++) {
		int randomNumber = dis(gen);
		switch (randomNumber) {
		case 1:
			area.setString(L"Равнина");
			area.setFillColor(sf::Color(60, 255, 25));
			if (i == 21) {
				current_terrain = Terrain::Plain;
			}
			break;
		case 2:
			area.setString(L"Река");
			area.setFillColor(sf::Color(70, 180, 255));
			if (i == 21) {
				current_terrain = Terrain::River;
			}
			break;
		case 3:
			area.setString(L"Горы");
			area.setFillColor(sf::Color(185, 125, 90));
			if (i == 21) {
				current_terrain = Terrain::Mountain;
			}
			break;
		}
		area.setPosition(window.getSize().x / 2 - area.getGlobalBounds().width / 2, y_position);
		areas.push_back(std::make_pair(area, y_position));
		y_position -= 70;
	}

	double start_speed = 10, speed, a = -2.012;
	speed = start_speed;

	bool area_choosen = true;

	sf::Text title(L"выбери 3 динозавра для боя", muller, 25);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 250);

	sf::Text error(L"у вас менее 3 динозавров", muller, 25);
	sf::Text error2(L"\nзаберите их бесплатно в магазине", muller, 25);
	error.setFillColor(sf::Color::Green);
	error2.setFillColor(sf::Color::Green);
	error.setPosition(window.getSize().x / 2 - error.getGlobalBounds().width / 2, 400);
	error2.setPosition(window.getSize().x / 2 - error2.getGlobalBounds().width / 2, 410);

	int left_card = 0, centre_card = 1, right_card = 2;

	sp_hold_left_card.setPosition(180, 400);
	sp_hold_centre_card.setPosition(760, 400);
	sp_hold_right_card.setPosition(1340, 400);
	sp_pick_left_card.setPosition(180, 400);
	sp_pick_centre_card.setPosition(760, 400);
	sp_pick_right_card.setPosition(1340, 400);
	sp_del_left_card.setPosition(180, 400);
	sp_del_centre_card.setPosition(760, 400);
	sp_del_right_card.setPosition(1340, 400);

	sp_start_btn.setPosition(200, 950);
	sp_hold_start_btn.setPosition(200, 950);

	bool clicked = false, del_left = false, del_centre = false, del_right = false;

	sf::Clock clock;
	clock.restart();

	sf::Clock clock2;
	clock2.restart();

	while (window.isOpen()) {

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					main_menu();
				}
			}
		}

		window.clear();

		double time = clock.getElapsedTime().asSeconds();
		if (speed > 0) {
			speed = start_speed + a * time;
			if (speed <= 0) {
				speed = 0;
				area_choosen = false;
			}
		}

		if (speed > 0) {
			for (int i = 0; i < areas.size(); i++) {
				areas.at(i).second += speed;
				areas.at(i).first.setPosition(areas.at(i).first.getPosition().x, areas.at(i).second);
				if (areas.at(i).first.getPosition().y < 100)
					window.draw(areas.at(i).first);
			}
		}
		else if (speed == 0) {
			areas.at(21).first.setPosition(areas.at(21).first.getPosition().x, 70);
			window.draw(areas.at(21).first);
		}

		window.draw(sp_area);
		window.draw(area_type);

		if (area_choosen == false) {
			window.draw(title);

			if (available_cards.size() < 3) {
				window.draw(error);
				window.draw(error2);
				window.display();
				sf::sleep(sf::seconds(3));
				main_menu();
			}
			else {

				del_left = false, del_centre = false, del_right = false;

				int l = 0;
				for (int i = left_card; i < available_cards.size(); i++) {
					if (i <= right_card) {
						available_cards.at(i).setPosition(180 + 580 * l, 400);
						l++;
					
						sf::FloatRect bounds = available_cards.at(i).getSprite().getGlobalBounds();

						available_cards.at(i).draw(window);

						int flag = 0;
						int num = -1;
						for (int k = 0; k < picked_cards.size(); k++) {
							if (picked_cards.at(k).second == i) {
								flag = 1;
								num = k;
							}
						}

						if (bounds.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							if (event.type == sf::Event::MouseButtonPressed) {
								if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
									clock2.restart();
									clicked = true;
									if (picked_cards.size() < 3) {
										if (flag == 0) {
											picked_cards.push_back(std::make_pair(available_cards.at(i), i));
											if (i == left_card)
												window.draw(sp_pick_left_card);
											else if (i == centre_card)
												window.draw(sp_pick_centre_card);
											else if (i == right_card)
												window.draw(sp_pick_right_card);
										}
										else if (flag == 1)
											picked_cards.erase(picked_cards.begin() + num);
									}
									else if (picked_cards.size() == 3) {
										if (flag == 1)
											picked_cards.erase(picked_cards.begin() + num);
									}
								}
							}
							else if (event.type == sf::Event::MouseButtonReleased) {
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									clicked = false;
								}
							}

							if (clicked == false) {
								if (flag == 0) {
									if (i == left_card)
										window.draw(sp_hold_left_card);
									else if (i == centre_card)
										window.draw(sp_hold_centre_card);
									else if (i == right_card)
										window.draw(sp_hold_right_card);
								}
								if (flag == 1) {
									if (i == left_card) {
										window.draw(sp_del_left_card);
										del_left = true;
									}
									else if (i == centre_card) {
										window.draw(sp_del_centre_card);
										del_centre = true;
									}
									else if (i == right_card) {
										window.draw(sp_del_right_card);
										del_right = true;
									}
								}
							}

						}
					}
				}

				for (int j = 0; j < picked_cards.size(); j++) {
					if (left_card == picked_cards.at(j).second and del_left == false) {
						window.draw(sp_pick_left_card);
					}
					else if (centre_card == picked_cards.at(j).second and del_centre == false) {
						window.draw(sp_pick_centre_card);
					}
					else if (right_card == picked_cards.at(j).second and del_right == false) {
						window.draw(sp_pick_right_card);
					}
				}

				if (clicked == false and event.type == sf::Event::KeyPressed) {
					clock2.restart();
					clicked = true;
					if (event.key.code == sf::Keyboard::Right) {
						if (available_cards.size() - 1 > right_card)
							left_card += 3, centre_card += 3, right_card += 3;
					}
					else if (event.key.code == sf::Keyboard::Left) {
						if (left_card > 0)
							left_card -= 3, centre_card -= 3, right_card -= 3;
					}
				}

				if (clock2.getElapsedTime().asSeconds() > 0.2)
					clicked = false;

				if (picked_cards.size() == 3) {

					sf::FloatRect startBounds = sp_start_btn.getGlobalBounds();

					if (startBounds.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						window.draw(sp_hold_start_btn);
						if (clock2.getElapsedTime().asSeconds() > 1 and event.mouseButton.button == sf::Mouse::Left) {
							battle();
						}
					}
					else {
						window.draw(sp_start_btn);
					}

				}

			}
		}

		window.display();

	}

	return 0;
}

enum MOVE {
	PLAYER,
	BOT
};

MOVE current_move, next_move;

int battle() {

	start_battle();

	enemy_cards.clear();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, shop_cards.size() - 1);
	std::vector <int> choose;
	for (int i = 0; i < 3; i++) {
		int randomNumber = dis(gen);
		while (std::find(choose.begin(), choose.end(), randomNumber) != choose.end())
			randomNumber = dis(gen);
		choose.push_back(randomNumber);
		enemy_cards.push_back(shop_cards2.at(randomNumber).first);
	}

	std::uniform_int_distribution<> dis2(0, 1);
	int randomNumber = dis2(gen);
	if (randomNumber == 0)
		current_move = MOVE::PLAYER;
	else if (randomNumber == 1)
		current_move = MOVE::BOT;

	std::wstring current_m = L"";

	if (current_move == MOVE::PLAYER)
		current_m = L"Ваш ход";
	else if (current_move == MOVE::BOT)
		current_m = L"Ход противника";
	
	sf::Text move(current_m, muller, 30);
	move.setPosition(1600, 500);

	sf::Text enemy(L"ОППОНЕНТ", muller, 50);
	enemy.setPosition((450 - enemy.getGlobalBounds().width) / 2, 50 + (350 - enemy.getGlobalBounds().height) / 2);
	sf::Text me(L"ВЫ", muller, 50);
	me.setPosition((450 - me.getGlobalBounds().width) / 2, 600 + (350 - enemy.getGlobalBounds().height) / 2);

	sf::Text t_terrain(L"", muller, 30);
	if (current_terrain == Terrain::Plain) {
		t_terrain.setString(L"РАВНИНА");
		t_terrain.setFillColor(sf::Color(60, 255, 25));
	}
	else if (current_terrain == Terrain::River) {
		t_terrain.setString(L"РЕКА");
		t_terrain.setFillColor(sf::Color(70, 180, 255));
	}
	else if (current_terrain == Terrain::Mountain) {
		t_terrain.setString(L"ГОРЫ");
		t_terrain.setFillColor(sf::Color(185, 125, 90));
	}
	t_terrain.setPosition(window.getSize().x / 2 - t_terrain.getGlobalBounds().width / 2,
		500);

	sp_vs.setPosition(0, 400);

	sp_border_top_left.setPosition(450, 420);
	sp_border_top_centre.setPosition(820, 420);
	sp_border_top_right.setPosition(1190, 420);
	sp_border_bottom_left.setPosition(450, 970);
	sp_border_bottom_centre.setPosition(820, 970);
	sp_border_bottom_right.setPosition(1190, 970);
	sp_bar_top_left.setPosition(453, 423.11);
	sp_bar_top_centre.setPosition(823, 423.11);
	sp_bar_top_right.setPosition(1193, 423.11);
	sp_bar_bottom_left.setPosition(453, 973.11);
	sp_bar_bottom_centre.setPosition(823, 973.11);
	sp_bar_bottom_right.setPosition(1193, 973.11);

	sf::Text health_top_left("100", muller, 20);
	sf::Text health_top_centre("100", muller, 20);
	sf::Text health_top_right("100", muller, 20);
	sf::Text health_bottom_left("100", muller, 20);
	sf::Text health_bottom_centre("100", muller, 20);
	sf::Text health_bottom_right("100", muller, 20);

	health_top_left.setPosition(sp_border_top_left.getPosition().x + (sp_border_top_left.getGlobalBounds().width - health_top_left.getGlobalBounds().width ) / 2,
		sp_border_top_left.getPosition().y + (sp_border_top_left.getGlobalBounds().height - health_top_left.getGlobalBounds().height) / 2 - 7);
	health_top_centre.setPosition(sp_border_top_centre.getPosition().x + (sp_border_top_centre.getGlobalBounds().width - health_top_centre.getGlobalBounds().width) / 2,
		sp_border_top_centre.getPosition().y + (sp_border_top_centre.getGlobalBounds().height - health_top_centre.getGlobalBounds().height) / 2 - 7);
	health_top_right.setPosition(sp_border_top_right.getPosition().x + (sp_border_top_right.getGlobalBounds().width - health_top_right.getGlobalBounds().width) / 2,
		sp_border_top_right.getPosition().y + (sp_border_top_right.getGlobalBounds().height - health_top_right.getGlobalBounds().height) / 2 - 7);
	health_bottom_left.setPosition(sp_border_bottom_left.getPosition().x + (sp_border_bottom_left.getGlobalBounds().width - health_bottom_left.getGlobalBounds().width) / 2,
		sp_border_bottom_left.getPosition().y + (sp_border_bottom_left.getGlobalBounds().height - health_bottom_left.getGlobalBounds().height) / 2 - 7);
	health_bottom_centre.setPosition(sp_border_bottom_centre.getPosition().x + (sp_border_bottom_centre.getGlobalBounds().width - health_bottom_centre.getGlobalBounds().width) / 2,
		sp_border_bottom_centre.getPosition().y + (sp_border_bottom_centre.getGlobalBounds().height - health_bottom_centre.getGlobalBounds().height) / 2 - 7);
	health_bottom_right.setPosition(sp_border_bottom_right.getPosition().x + (sp_border_bottom_right.getGlobalBounds().width - health_bottom_right.getGlobalBounds().width) / 2,
		sp_border_bottom_right.getPosition().y + (sp_border_bottom_right.getGlobalBounds().height - health_bottom_right.getGlobalBounds().height) / 2 - 7);
	
	sp_bar_top_left.setScale(1, 1);
	sp_bar_top_centre.setScale(1, 1);
	sp_bar_top_right.setScale(1, 1);
	sp_bar_bottom_left.setScale(1, 1);
	sp_bar_bottom_centre.setScale(1, 1);
	sp_bar_bottom_right.setScale(1, 1);

	sp_hold_bottom_left_card_mini.setPosition(450, 600);
	sp_hold_bottom_centre_card_mini.setPosition(820, 600);
	sp_hold_bottom_right_card_mini.setPosition(1190, 600);
	sp_pick_top_left_card_mini.setPosition(450, 50);
	sp_pick_top_centre_card_mini.setPosition(820, 50);
	sp_pick_top_right_card_mini.setPosition(1190, 50);
	sp_pick_bottom_left_card_mini.setPosition(450, 600);
	sp_pick_bottom_centre_card_mini.setPosition(820, 600);
	sp_pick_bottom_right_card_mini.setPosition(1190, 600);
	sp_del_bottom_left_card_mini.setPosition(450, 600);
	sp_del_bottom_centre_card_mini.setPosition(820, 600);
	sp_del_bottom_right_card_mini.setPosition(1190, 600);

	sp_attack_top_left_card_mini.setPosition(450, 50);
	sp_attack_top_centre_card_mini.setPosition(820, 50);
	sp_attack_top_right_card_mini.setPosition(1190, 50);

	sp_death_top_left_card_mini.setPosition(450, 50);
	sp_death_top_centre_card_mini.setPosition(820, 50);
	sp_death_top_right_card_mini.setPosition(1190, 50);
	sp_death_bottom_left_card_mini.setPosition(450, 600);
	sp_death_bottom_centre_card_mini.setPosition(820, 600);
	sp_death_bottom_right_card_mini.setPosition(1190, 600);

	sp_attack_top_left_card.setPosition(450, 50);
	sp_attack_top_centre_card.setPosition(820, 50);
	sp_attack_top_right_card.setPosition(1190, 50);
	sp_attack_bottom_left_card.setPosition(450, 600);
	sp_attack_bottom_centre_card.setPosition(820, 600);
	sp_attack_bottom_right_card.setPosition(1190, 600);
	sp_attacked_top_left_card.setPosition(450, 50);
	sp_attacked_top_centre_card.setPosition(820, 50);
	sp_attacked_top_right_card.setPosition(1190, 50);
	sp_attacked_bottom_left_card.setPosition(450, 600);
	sp_attacked_bottom_centre_card.setPosition(820, 600);
	sp_attacked_bottom_right_card.setPosition(1190, 600);

	bool clicked = false, clicked2 = false;
	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear();

		current_move = next_move;

		health_top_left.setString(std::to_string(enemy_cards.at(0).getDino()->getHealth()));
		health_top_centre.setString(std::to_string(enemy_cards.at(1).getDino()->getHealth()));
		health_top_right.setString(std::to_string(enemy_cards.at(2).getDino()->getHealth()));
		health_bottom_left.setString(std::to_string(picked_cards.at(0).first.getDino()->getHealth()));
		health_bottom_centre.setString(std::to_string(picked_cards.at(1).first.getDino()->getHealth()));
		health_bottom_right.setString(std::to_string(picked_cards.at(2).first.getDino()->getHealth()));

		window.draw(enemy);
		window.draw(sp_vs);
		window.draw(me);
		if (current_move == MOVE::PLAYER)
			current_m = L"Ваш ход";
		else if (current_move == MOVE::BOT)
			current_m = L"Ход противника";
		window.draw(t_terrain);
		move.setString(current_m);

		window.draw(move);

		if (current_move == MOVE::PLAYER) {
			bool del_left = false, del_centre = false, del_right = false;

			int l = 0;
			for (int i = 0; i < picked_cards.size(); i++) {
				picked_cards.at(i).first.setPosition(450 + 370 * l, 600);
				picked_cards.at(i).first.draw_mini(window);

				if (i == 0) {
					window.draw(sp_bar_bottom_left);
					window.draw(sp_border_bottom_left);
					window.draw(health_bottom_left);
				}
				else if (i == 1) {
					window.draw(sp_bar_bottom_centre);
					window.draw(sp_border_bottom_centre);
					window.draw(health_bottom_centre);
				}
				else if (i == 2) {
					window.draw(sp_bar_bottom_right);
					window.draw(sp_border_bottom_right);
					window.draw(health_bottom_right);
				}

				l++;

				int flag = 0, num = -1;
				for (int j = 0; j < attack_cards.size(); j++) {
					if (j == 0 and attack_cards.at(j).second == i) {
						flag = 1;
						num = j;
					}
				}

				sf::FloatRect bounds = picked_cards.at(i).first.getSpritemini().getGlobalBounds();

				if (bounds.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
							clock.restart();
							clicked = true;
							if (attack_cards.size() == 0) {
								if (flag == 0)
									attack_cards.push_back(std::make_pair(picked_cards.at(i).first, i));
								if (i == 0)
									window.draw(sp_hold_bottom_left_card_mini);
								else if (i == 1)
									window.draw(sp_hold_bottom_centre_card_mini);
								else if (i == 2)
									window.draw(sp_hold_bottom_right_card_mini);
							}
							else if (attack_cards.size() == 1) {
								if (flag == 1)
									attack_cards.erase(attack_cards.begin() + num);
							}
						}
					}
					else if (event.type == sf::Event::MouseButtonReleased) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							clicked = false;
						}
					}

					if (clicked == false) {
						if (flag == 0) {
							if (i == 0)
								window.draw(sp_hold_bottom_left_card_mini);
							else if (i == 1)
								window.draw(sp_hold_bottom_centre_card_mini);
							else if (i == 2)
								window.draw(sp_hold_bottom_right_card_mini);
						}
						if (flag == 1) {
							if (i == 0) {
								window.draw(sp_del_bottom_left_card_mini);
								del_left = true;
							}
							else if (i == 1) {
								window.draw(sp_del_bottom_centre_card_mini);
								del_centre = true;
							}
							else if (i == 2) {
								window.draw(sp_del_bottom_right_card_mini);
								del_right = true;
							}
						}
					}
				}
			}

			for (int j = 0; j < attack_cards.size(); j++) {
				if (j == 0) {
					if (0 == attack_cards.at(j).second and del_left == false) {
						window.draw(sp_pick_bottom_left_card_mini);
					}
					else if (1 == attack_cards.at(j).second and del_centre == false) {
						window.draw(sp_pick_bottom_centre_card_mini);
					}
					else if (2 == attack_cards.at(j).second and del_right == false) {
						window.draw(sp_pick_bottom_right_card_mini);
					}
				}
			}

			if (clock.getElapsedTime().asSeconds() > 0.5)
				clicked = false;


			l = 0;
			for (int i = 0; i < enemy_cards.size(); i++) {
				enemy_cards.at(i).setPosition(450 + 370 * l, 50);
				enemy_cards.at(i).draw_mini(window);

				if (i == 0) {
					window.draw(sp_bar_top_left);
					window.draw(sp_border_top_left);
					window.draw(health_top_left);
				}
				else if (i == 1) {
					window.draw(sp_bar_top_centre);
					window.draw(sp_border_top_centre);
					window.draw(health_top_centre);
				}
				else if (i == 2) {
					window.draw(sp_bar_top_right);
					window.draw(sp_border_top_right);
					window.draw(health_top_right);
				}

				l++;

				sf::FloatRect bounds = enemy_cards.at(i).getSpritemini().getGlobalBounds();

				if (bounds.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (clicked2 == false and event.mouseButton.button == sf::Mouse::Left) {
							clock2.restart();
							clicked2 = true;
							if (attack_cards.size() == 1 and enemy_cards.at(i).getDino()->getHealth() > 0)
								attack_cards.push_back(std::make_pair(enemy_cards.at(i), i + 3));
							if (attack_cards.size() == 2) {
								attack_cards.at(1).first.getDino()->setHealth(attack_cards.at(0).first.getDino()->damage(current_terrain));
								dr_cards.clear();
								dr_cards.push_back(std::make_pair(0, attack_cards.at(0).second));
								dr_cards.push_back(std::make_pair(1, attack_cards.at(1).second - 3));
								clock3.restart();
								attack_cards.clear();
								next_move = MOVE::BOT;
								switch (i) {
								case 0:
									sp_bar_top_left.setScale((double)enemy_cards.at(0).getDino()->getHealth() / 100, 1);
									break;
								case 1:
									sp_bar_top_centre.setScale((double)enemy_cards.at(1).getDino()->getHealth() / 100, 1);
									break;
								case 2:
									sp_bar_top_right.setScale((double)enemy_cards.at(2).getDino()->getHealth() / 100, 1);
									break;
								}
							}
						}
					}
					if (clicked == false and attack_cards.size() == 1 and enemy_cards.at(i).getDino()->getHealth() > 0) {
						if (i == 0)
							window.draw(sp_attack_top_left_card_mini);
						else if (i == 1)
							window.draw(sp_attack_top_centre_card_mini);
						else if (i == 2)
							window.draw(sp_attack_top_right_card_mini);
					}

				}

			}

			if (clock2.getElapsedTime().asSeconds() > 0.5)
				clicked2 = false;
		}

		else if (current_move == MOVE::BOT) {
				int l = 0;
				for (int i = 0; i < picked_cards.size(); i++) {
					picked_cards.at(i).first.setPosition(450 + 370 * l, 600);
					picked_cards.at(i).first.draw_mini(window);

					if (i == 0) {
						window.draw(sp_bar_bottom_left);
						window.draw(sp_border_bottom_left);
						window.draw(health_bottom_left);
					}
					else if (i == 1) {
						window.draw(sp_bar_bottom_centre);
						window.draw(sp_border_bottom_centre);
						window.draw(health_bottom_centre);
					}
					else if (i == 2) {
						window.draw(sp_bar_bottom_right);
						window.draw(sp_border_bottom_right);
						window.draw(health_bottom_right);
					}
					l++;
				}

				l = 0;
				for (int i = 0; i < enemy_cards.size(); i++) {
					enemy_cards.at(i).setPosition(450 + 370 * l, 50);
					enemy_cards.at(i).draw_mini(window);

					if (i == 0) {
						window.draw(sp_bar_top_left);
						window.draw(sp_border_top_left);
						window.draw(health_top_left);
					}
					else if (i == 1) {
						window.draw(sp_bar_top_centre);
						window.draw(sp_border_top_centre);
						window.draw(health_top_centre);
					}
					else if (i == 2) {
						window.draw(sp_bar_top_right);
						window.draw(sp_border_top_right);
						window.draw(health_top_right);
					}

					l++;
				}
				if (clock3.getElapsedTime().asSeconds() > 2) {
				std::uniform_int_distribution<> dis3(0, 2);
				int bot_pick = dis3(gen);

				while (enemy_cards.at(bot_pick).getDino()->getHealth() == 0)
					bot_pick = dis3(gen);

				int bot_pick2 = dis3(gen);

				while (picked_cards.at(bot_pick2).first.getDino()->getHealth() == 0)
					bot_pick2 = dis3(gen);

				dr_cards.clear();
				dr_cards.push_back(std::make_pair(1, bot_pick));
				dr_cards.push_back(std::make_pair(0, bot_pick2));
				clock3.restart();

				switch (bot_pick) {
				case 0:
					window.draw(sp_pick_top_left_card_mini);
					break;
				case 1:
					window.draw(sp_pick_top_centre_card_mini);
					break;
				case 2:
					window.draw(sp_pick_top_right_card_mini);
					break;
				}

				int damage = enemy_cards.at(bot_pick).getDino()->damage(current_terrain);
				picked_cards.at(bot_pick2).first.getDino()->setHealth(enemy_cards.at(bot_pick).getDino()->damage(current_terrain));
				next_move = MOVE::PLAYER;

				switch (bot_pick2) {
				case 0:
					sp_bar_bottom_left.setScale((double)picked_cards.at(0).first.getDino()->getHealth() / 100, 1);
					break;
				case 1:
					sp_bar_bottom_centre.setScale((double)picked_cards.at(1).first.getDino()->getHealth() / 100, 1);
					break;
				case 2:
					sp_bar_bottom_right.setScale((double)picked_cards.at(2).first.getDino()->getHealth() / 100, 1);
					break;
				}
			}
		}

		for (int i = 0; i < dr_cards.size(); i++) {
			if (clock3.getElapsedTime().asSeconds() < 2) {
				if (i == 0) {
					if (dr_cards.at(i).first == 1) {
						switch (dr_cards.at(i).second) {
						case 0:
							window.draw(sp_attack_top_left_card);
							break;
						case 1:
							window.draw(sp_attack_top_centre_card);
							break;
						case 2:
							window.draw(sp_attack_top_right_card);
							break;
						}
					}
					else if (dr_cards.at(i).first == 0) {
						switch (dr_cards.at(i).second) {
						case 0:
							window.draw(sp_attack_bottom_left_card);
							break;
						case 1:
							window.draw(sp_attack_bottom_centre_card);
							break;
						case 2:
							window.draw(sp_attack_bottom_right_card);
							break;
						}
					}
				}
				else if (i == 1) {
					if (dr_cards.at(i).first == 1) {
						switch (dr_cards.at(i).second) {
						case 0:
							window.draw(sp_attacked_top_left_card);
							break;
						case 1:
							window.draw(sp_attacked_top_centre_card);
							break;
						case 2:
							window.draw(sp_attacked_top_right_card);
							break;
						}
					}
					else if (dr_cards.at(i).first == 0) {
						switch (dr_cards.at(i).second) {
						case 0:
							window.draw(sp_attacked_bottom_left_card);
							break;
						case 1:
							window.draw(sp_attacked_bottom_centre_card);
							break;
						case 2:
							window.draw(sp_attacked_bottom_right_card);
							break;
						}
					}
				}
			}
		}

		if (enemy_cards.at(0).getDino()->getHealth() == 0)
			window.draw(sp_death_top_left_card_mini);
		if (enemy_cards.at(1).getDino()->getHealth() == 0)
			window.draw(sp_death_top_centre_card_mini);
		if (enemy_cards.at(2).getDino()->getHealth() == 0)
			window.draw(sp_death_top_right_card_mini);
		if (picked_cards.at(0).first.getDino()->getHealth() == 0)
			window.draw(sp_death_bottom_left_card_mini);
		if (picked_cards.at(1).first.getDino()->getHealth() == 0)
			window.draw(sp_death_bottom_centre_card_mini);
		if (picked_cards.at(2).first.getDino()->getHealth() == 0)
			window.draw(sp_death_bottom_right_card_mini);

		window.display();

		if (enemy_cards.at(0).getDino()->getHealth() + enemy_cards.at(1).getDino()->getHealth() + enemy_cards.at(2).getDino()->getHealth() == 0) {
			for (int i = 0; i < picked_cards.size(); i++) {
				picked_cards.at(i).first.getDino()->setHealth2(100);
			}

			for (int i = 0; i < enemy_cards.size(); i++) {
				enemy_cards.at(i).getDino()->setHealth2(100);
			}
			picked_cards.clear();
			enemy_cards.clear();
			player_won();
		}
		else if (picked_cards.at(0).first.getDino()->getHealth() + picked_cards.at(1).first.getDino()->getHealth() + picked_cards.at(2).first.getDino()->getHealth() == 0) {
			for (int i = 0; i < shop_cards.size(); i++) {
				shop_cards.at(i).first.getDino()->setHealth2(100);
			}

			for (int i = 0; i < shop_cards2.size(); i++) {
				shop_cards2.at(i).first.getDino()->setHealth2(100);
			}
			picked_cards.clear();
			enemy_cards.clear();
			enemy_won();
		}
	}

	return 0;
}

int player_won() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(50, 180);
	int money = dis(gen);
	balance += money;
	std::wstring mon = L"+ " + std::to_wstring(money);

	sf::Text m(mon, muller, 20);
	m.setFillColor(sf::Color::Yellow);
	m.setPosition(window.getSize().x / 2 - m.getGlobalBounds().width / 2, 570);

	sf::Text t(L"Победа!", muller, 30);
	t.setFillColor(sf::Color::Green);
	t.setPosition(window.getSize().x / 2 - t.getGlobalBounds().width/2, window.getSize().y / 2 - t.getGlobalBounds().height / 2);

	sf::Clock clock;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					main_menu();
				}
			}
		}


		window.clear();

		window.draw(t);
		window.draw(m);

		window.display();

		if (clock.getElapsedTime().asSeconds() > 3) {
			saveData();
			main_menu();
		}

	}

	return 0;
}

int enemy_won() {

	sf::Text t(L"Поражение!", muller, 30);
	t.setFillColor(sf::Color::Red);
	t.setPosition(window.getSize().x / 2 - t.getGlobalBounds().width / 2, window.getSize().y / 2 - t.getGlobalBounds().height / 2);

	sf::Clock clock;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					main_menu();
				}
			}
		}


		window.clear();

		window.draw(t);

		window.display();

		if (clock.getElapsedTime().asSeconds() > 3)
			main_menu();

	}

	return 0;
}

int start_battle() {
	
	sf::RectangleShape r(sf::Vector2f(1920, 1080));
	r.setFillColor(sf::Color(0, 0, 0, 0));
	double visible = 0;

	sf::Clock clock;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		sp_battle.scale(1.0001, 1.0001);
		sp_battle.setPosition(window.getSize().x / 2 - sp_battle.getGlobalBounds().width / 2,
			window.getSize().y / 2 - sp_battle.getGlobalBounds().height / 2);

		if (clock.getElapsedTime().asSeconds() > 0.8) {
			visible += 5;
			if (visible > 255)
				visible = 255;
		}
		r.setFillColor(sf::Color(0, 0, 0, visible));

		window.clear();

		window.draw(sp_battle);
		window.draw(r);

		window.display();

		if (visible == 255)
			return 0;

	}

	return 0;
}

int shop() {

	sf::sleep(sf::milliseconds(200));

	sp_magaz.setPosition(0, 50);
	sf::Text sp_balance(std::to_string(balance), muller, 40);
	sp_balance.setFillColor(sf::Color::Yellow);
	sp_coin.setPosition(1720, 60);
	sp_magaz_left.setPosition(35, 465);
	sp_magaz_right.setPosition(1820, 465);
	sp_back.setPosition(10, 980);

	int left_card = 0, current_card = 1, right_card = 2;

	sf::Text left_price("W", muller, 20), current_price("W", muller, 20), right_price("W", muller, 20);

	bool clicked = false;
	sf::Clock clock;

	sf::RectangleShape left(sf::Vector2f(280, 350)), centre(sf::Vector2f(400, 500)), right(sf::Vector2f(280, 350));
	left.setPosition(250, 365);
	centre.setPosition(760, 250);
	right.setPosition(1390, 365);

	sp_small_left.setPosition(250, 365);
	sp_small_bought_left.setPosition(250, 365);
	sp_fault_small_left.setPosition(250, 365);
	sp_big.setPosition(760, 250);
	sp_big_bought.setPosition(760, 250);
	sp_fault_big.setPosition(760, 250);
	sp_small_right.setPosition(1390, 365);
	sp_small_bought_right.setPosition(1390, 365);
	sp_fault_small_right.setPosition(1390, 365);

	sf::Text error(L"Недостаточно средств", muller, 20);
	error.setPosition(window.getSize().x / 2 - error.getGlobalBounds().width / 2, 1000);
	error.setFillColor(sf::Color::Red);
	bool fault_flag = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					while (shop_cards.at(0).first.getName() != L"pterodactile") {
						std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(0);
						for (int i = 0; i < shop_cards.size(); i++)
							if (i == shop_cards.size() - 1)
								shop_cards.at(i) = pre;
							else
								shop_cards.at(i) = shop_cards.at(i + 1);
					}
					saveData();
					main_menu();
				}
				
			}
		}

		sp_balance.setString(std::to_string(balance));
		sp_balance.setPosition(sp_coin.getPosition().x - sp_balance.getGlobalBounds().width, 50 + (sp_coin.getGlobalBounds().height - sp_balance.getGlobalBounds().height) / 2);

		sf::FloatRect backBound = sp_back.getGlobalBounds();

		if (backBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_back.setColor(sf::Color::Cyan);
			if (event.mouseButton.button == sf::Mouse::Left) {
				while (shop_cards.at(0).first.getName() != L"pterodactile") {
					std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(0);
					for (int i = 0; i < shop_cards.size(); i++)
						if (i == shop_cards.size() - 1)
							shop_cards.at(i) = pre;
						else
							shop_cards.at(i) = shop_cards.at(i + 1);
				}
				saveData();
				return 0;
			}
		}
		else {
			sp_back.setColor(sf::Color::White);
		}

		sf::FloatRect leftBound = sp_magaz_left.getGlobalBounds();
		sf::FloatRect rightBound = sp_magaz_right.getGlobalBounds();

		if (leftBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_magaz_left.setColor(sf::Color::Cyan);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					clock.restart();
					clicked = true;
					std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(shop_cards.size() - 1);
					for (int i = shop_cards.size() - 1; i > -1; i--)
						if (i == 0)
							shop_cards.at(i) = pre;
						else
							shop_cards.at(i) = shop_cards.at(i - 1);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
		}
		else {
			sp_magaz_left.setColor(sf::Color::White);
		}

		if (rightBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_magaz_right.setColor(sf::Color::Cyan);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					clock.restart();
					clicked = true;
					std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(0);
					for (int i = 0; i < shop_cards.size(); i++)
						if (i == shop_cards.size() - 1)
							shop_cards.at(i) = pre;
						else
							shop_cards.at(i) = shop_cards.at(i + 1);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
		}
		else {
			sp_magaz_right.setColor(sf::Color::White);
		}

		if (clicked == true and clock.getElapsedTime().asSeconds() >= 0.2)
			clicked = false;

		if (clicked == false and event.type == sf::Event::KeyPressed) {
			clock.restart();
			clicked = true;
			if (event.key.code == sf::Keyboard::Right) {
				sp_magaz_right.setColor(sf::Color::Cyan);
				std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(0);
				for (int i = 0; i < shop_cards.size(); i++)
					if (i == shop_cards.size() - 1)
						shop_cards.at(i) = pre;
					else
						shop_cards.at(i) = shop_cards.at(i + 1);
			}
			else if (event.key.code == sf::Keyboard::Left) {
				sp_magaz_left.setColor(sf::Color::Cyan);
				std::pair <Card, std::pair<int, bool>> pre = shop_cards.at(shop_cards.size() - 1);
				for (int i = shop_cards.size() - 1; i > -1; i--)
					if (i == 0)
						shop_cards.at(i) = pre;
					else
						shop_cards.at(i) = shop_cards.at(i - 1);
			}
		}

		shop_cards.at(0).first.setPosition(250, 365);
		shop_cards.at(1).first.setPosition(760, 250);
		shop_cards.at(2).first.setPosition(1390, 365);

		window.clear();

		window.draw(sp_magaz);
		window.draw(sp_balance);
		window.draw(sp_coin);
		window.draw(sp_magaz_left);
		window.draw(sp_magaz_right);
		window.draw(sp_back);

		for (int i = 0; i < shop_cards.size(); i++) {
			if (left_card == i) {
				if (shop_cards.at(i).second.second) {
					left_price.setString(L"Уже у вас");
					left_price.setFillColor(sf::Color::Green);
					shop_cards.at(i).first.draw_mini(window);
				}
				else {
					left_price.setString(std::to_string(shop_cards.at(i).second.first));
					left_price.setFillColor(sf::Color::White);
					shop_cards.at(i).first.draw_mini_blocked(window);
				}
				left_price.setPosition(250 + (280 - left_price.getLocalBounds().width) / 2,
					715 + 50);
			}
			else if (current_card == i) {
				if (shop_cards.at(i).second.second) {
					current_price.setString(L"Уже у вас");
					current_price.setFillColor(sf::Color::Green);
					shop_cards.at(i).first.draw(window);
				}
				else {
					current_price.setString(std::to_string(shop_cards.at(i).second.first));
					current_price.setFillColor(sf::Color::White);
					shop_cards.at(i).first.draw_blocked(window);
				}
				current_price.setPosition(760 + (400 - current_price.getLocalBounds().width) / 2,
					750 + 50);
			}
			else if (right_card == i) {
				if (shop_cards.at(i).second.second) {
					right_price.setString(L"Уже у вас");
					right_price.setFillColor(sf::Color::Green);
					shop_cards.at(i).first.draw_mini(window);
				}
				else {
					right_price.setString(std::to_string(shop_cards.at(i).second.first));
					right_price.setFillColor(sf::Color::White);
					shop_cards.at(i).first.draw_mini_blocked(window);
				}
				right_price.setPosition(1390 + (280 - right_price.getLocalBounds().width) / 2,
					715 + 50);
			}
		}

		sf::FloatRect leftcardBound = left.getGlobalBounds();
		sf::FloatRect centrecardBound = centre.getGlobalBounds();
		sf::FloatRect rightcardBound = right.getGlobalBounds();

		if (!shop_cards.at(left_card).second.second and leftcardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					clock.restart();
					clicked = true;
					if (!shop_cards.at(left_card).second.second and balance >= shop_cards.at(left_card).second.first) {
						shop_cards.at(left_card).second.second = true;
						balance -= shop_cards.at(left_card).second.first;
						available_cards.push_back(shop_cards.at(left_card).first);
					}
					else if (balance < shop_cards.at(left_card).second.first) {
						window.draw(sp_fault_small_left);
						window.draw(error);
						fault_flag = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
			if (fault_flag == false)
				window.draw(sp_small_left);
		}
		else if (shop_cards.at(left_card).second.second and leftcardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			window.draw(sp_small_bought_left);
		}

		if (!shop_cards.at(current_card).second.second and centrecardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					clock.restart();
					clicked = true;
					if (!shop_cards.at(current_card).second.second and balance >= shop_cards.at(current_card).second.first) {
						shop_cards.at(current_card).second.second = true;
						balance -= shop_cards.at(current_card).second.first;
						available_cards.push_back(shop_cards.at(current_card).first);
					}
					else if (balance < shop_cards.at(current_card).second.first) {
						window.draw(sp_fault_big);
						window.draw(error);
						fault_flag = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
			if (fault_flag == false)
				window.draw(sp_big);
		}
		else if (shop_cards.at(current_card).second.second and centrecardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			window.draw(sp_big_bought);
		}

		if (!shop_cards.at(right_card).second.second and rightcardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (clicked == false and event.mouseButton.button == sf::Mouse::Left) {
					clock.restart();
					clicked = true;
					if (!shop_cards.at(right_card).second.second and balance >= shop_cards.at(right_card).second.first) {
						shop_cards.at(right_card).second.second = true;
						balance -= shop_cards.at(right_card).second.first;
						available_cards.push_back(shop_cards.at(right_card).first);

					}
					else if (balance < shop_cards.at(right_card).second.first) {
						window.draw(sp_fault_small_right);
						window.draw(error);
						fault_flag = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicked = false;
				}
			}
			if (fault_flag == false)
				window.draw(sp_small_right);
		}
		else if (shop_cards.at(right_card).second.second and rightcardBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			window.draw(sp_small_bought_right);
		}

		window.draw(left_price);
		window.draw(current_price);
		window.draw(right_price);

		window.display();

		if (fault_flag) {
			sf::sleep(sf::milliseconds(500));
			fault_flag = false;
		}
	}

	return 0;
}

int exit_game() {

	sp_question.setPosition(700, 330);
	sp_yes.setPosition(600, 650);
	sp_no.setPosition(1150, 650);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
			}
		}

		window.clear();

		sf::FloatRect yesBound = sp_yes.getGlobalBounds();
		sf::FloatRect noBound = sp_no.getGlobalBounds();

		if (yesBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_yes.setColor(sf::Color::Cyan);
			if (event.mouseButton.button == sf::Mouse::Left) {
				window.close();
				return 0;
			}
		}
		else {
			sp_yes.setColor(sf::Color::White);
		}

		if (noBound.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			sp_no.setColor(sf::Color::Cyan);
			if (event.mouseButton.button == sf::Mouse::Left) {
				main_menu();
			}
		}
		else {
			sp_no.setColor(sf::Color::White);
		}

		window.draw(sp_question);
		window.draw(sp_yes);
		window.draw(sp_no);

		window.display();
	}

	return 0;
}

#endif // !MAIN_CYCLE_H__