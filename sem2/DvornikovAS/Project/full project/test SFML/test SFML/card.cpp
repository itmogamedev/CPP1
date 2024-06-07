#include "Card.h"

Card::Card(std::string pt, std::string pt_mini, std::string pt_b, std::string pt_mini_b, std::wstring n, int p, Dino* d) {
	path = pt;
	path_mini = pt_mini;
	path_blocked = pt_b;
	path_mini_blocked = pt_mini_b;
	name = n;
	price = p;
	dino = d;
}

Dino* Card::getDino() { return dino; }

void Card::setPosition(double x, double y) {
	sprite_card.setPosition(x, y);
	sprite_card_mini.setPosition(x, y);
	sprite_card_blocked.setPosition(x, y);
	sprite_card_mini_blocked.setPosition(x, y);
}

void Card::setScale(const double x, const double y) {
	sprite_card.scale(x, y);
}

void Card::setColor(sf::Color color) {
	sprite_card.setColor(color);
	sprite_card_blocked.setColor(color);
	sprite_card_mini.setColor(color);
	sprite_card_mini_blocked.setColor(color);
}

sf::Sprite Card::getSprite() { return Card::sprite_card; }

sf::Sprite Card::getSpriteblocked() { return Card::sprite_card_blocked; }

sf::Sprite Card::getSpritemini() { return Card::sprite_card_mini; }

sf::Sprite Card::getSpriteminiblocked() { return Card::sprite_card_mini_blocked; }

void Card::draw(sf::RenderWindow& window) {
	texture_card.loadFromFile(path);
	sprite_card.setTexture(texture_card);
	window.draw(sprite_card);
}

void Card::draw_mini(sf::RenderWindow& window) {
	texture_card.loadFromFile(path_mini);
	sprite_card_mini.setTexture(texture_card);
	window.draw(sprite_card_mini);
}

void Card::draw_blocked(sf::RenderWindow& window) {
	texture_card.loadFromFile(path_blocked);
	sprite_card_blocked.setTexture(texture_card);
	window.draw(sprite_card_blocked);
}

void Card::draw_mini_blocked(sf::RenderWindow& window) {
	texture_card.loadFromFile(path_mini_blocked);
	sprite_card_mini_blocked.setTexture(texture_card);
	window.draw(sprite_card_mini_blocked);
}

std::wstring Card::getName() const { return name; }

int Card::getPrice() { return price; }

bool Card::getStatus() { return isBought; }

void Card::setStatus(bool b) { isBought = b; }

//common
Card pterodactile() { return Card("img/cards/ptero.png", "img/cards/ptero_mini.png",
		"img/cards/ptero_blocked.png", "img/cards/ptero_mini_blocked.png",
		L"pterodactile", 0, &dino_ptero); }
Card pterodactile2() { return Card("img/cards/ptero.png", "img/cards/ptero_mini.png",
		"img/cards/ptero_blocked.png", "img/cards/ptero_mini_blocked.png",
		L"pterodactile", 0, &dino_ptero2); }

Card brahiosaur() { return Card("img/cards/brahi.png", "img/cards/brahi_mini.png",
	"img/cards/brahi_blocked.png", "img/cards/brahi_mini_blocked.png",
	L"brahiosaur", 0, &dino_brahi); }
Card brahiosaur2() { return Card("img/cards/brahi.png", "img/cards/brahi_mini.png",
		"img/cards/brahi_blocked.png", "img/cards/brahi_mini_blocked.png",
		L"brahiosaur", 0, &dino_brahi2); }

//rare
Card stegosaur() { return Card("img/cards/stego.png", "img/cards/stego_mini.png",
	"img/cards/stego_blocked.png", "img/cards/stego_mini_blocked.png", 
	L"stegosaur", 300, &dino_stego); }
Card stegosaur2() { return Card("img/cards/stego.png", "img/cards/stego_mini.png",
		"img/cards/stego_blocked.png", "img/cards/stego_mini_blocked.png",
		L"stegosaur", 300, &dino_stego2); }

//insane
Card trex() { return Card("img/cards/trex.png", "img/cards/trex_mini.png",
	"img/cards/trex_blocked.png", "img/cards/trex_mini_blocked.png",
	L"trex", 3000, &dino_trex); }
Card trex2() { return Card("img/cards/trex.png", "img/cards/trex_mini.png",
		"img/cards/trex_blocked.png", "img/cards/trex_mini_blocked.png",
		L"trex", 3000, &dino_trex2); }