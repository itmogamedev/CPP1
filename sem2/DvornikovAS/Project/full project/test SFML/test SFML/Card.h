#pragma once

#ifndef CARD_H__
#define CARD_H__

#include <SFML/Graphics.hpp>

#include "Dinos.h"

class Card {
private:
	sf::Sprite sprite_card;
	sf::Sprite sprite_card_mini;
	sf::Sprite sprite_card_blocked;
	sf::Sprite sprite_card_mini_blocked;
	sf::Texture texture_card;
	int price = 0;
	Dino* dino;
	bool isBought = false;
	std::wstring name;
	std::string path;
	std::string path_mini;
	std::string path_blocked;
	std::string path_mini_blocked;
public:
	Card(std::string, std::string, std::string, std::string, std::wstring, int, Dino*);
	Dino* getDino();
	void setPosition(double, double);
	void setScale(const double, const double);
	void setColor(sf::Color);
	sf::Sprite getSprite();
	sf::Sprite getSpritemini();
	sf::Sprite getSpriteblocked();
	sf::Sprite getSpriteminiblocked();
	void draw(sf::RenderWindow&);
	void draw_mini(sf::RenderWindow&);
	void draw_blocked(sf::RenderWindow&);
	void draw_mini_blocked(sf::RenderWindow&);
	std::wstring getName() const;
	int getPrice();
	bool getStatus();
	void setStatus(bool);
};

static std::vector <std::pair<Card, std::pair<int, bool>>> shop_cards;
static std::vector <std::pair<Card, std::pair<int, bool>>> shop_cards2;
static std::vector <Card> available_cards;
static std::vector <std::pair<Card, int>> picked_cards;
static std::vector <Card> enemy_cards;
static std::vector <std::pair<Card, int>> attack_cards;
static std::vector <std::pair<int, int>> dr_cards;

//common
Card pterodactile(), pterodactile2();
Card brahiosaur(), brahiosaur2();

//rare
Card stegosaur(), stegosaur2();

//insane
Card trex(), trex2();

static std::vector <bool> status_cards;

#endif