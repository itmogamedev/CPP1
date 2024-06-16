#pragma once
#include <string>
#include <fstream>
#include "SFML/Graphics.hpp"

class Dino
{

	int breed;
	sf::Texture dinoIdle;
	sf::Texture dinoAttack;
	sf::Texture dinoSuffer;
	sf::Texture dinoDead;
	

public:
	int birthplace; // 0 - plain, 1 - river, 2 - mountain
	int STR;
	int INT;
	int AGI;
	std::string bstr;
	int HP = 100;
	int maxHP;
	std::string name; // имя
	int cost; // цена
	sf::Sprite sprite;
	Dino();
	Dino(int _bp, int _str, int _int, int _agi, int _maxhp, std::string _name, int cost, int breed);
	void takeDamage(int _damage);
	void Damage(int _damage);
	int countDmg(int terrain);
	void update();
	void dump();

};

