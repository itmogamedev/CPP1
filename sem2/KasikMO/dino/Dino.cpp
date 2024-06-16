#include "Dino.h"

Dino::Dino()
{
	int d = std::rand() % 20;
	if (std::rand() % 2 == 0) d *= -1;
	HP += d;
	maxHP = HP;
	STR = 7 + std::rand() % 10;
	INT = 7 + std::rand() % 10;
	AGI = 7 + std::rand() % 10;
	cost = HP * 2 / 3 + (STR + INT + AGI) / 2;
	birthplace = std::rand() % 3;
	breed = 1 + std::rand() % 4;
	name = "Dummysaurus_" + std::to_string(cost*3 / 2);
	dinoIdle.loadFromFile("resources/dino"+std::to_string(breed)+"_idle.png");
	dinoAttack.loadFromFile("resources/dino"+std::to_string(breed)+"_attack.png");
	dinoSuffer.loadFromFile("resources/dino"+std::to_string(breed)+"_damaged.png");
	dinoDead.loadFromFile("resources/dino"+std::to_string(breed)+"_dead.png");
	sprite.setTexture(dinoIdle);
	switch (birthplace)
	{
	case 0:
		bstr = "from Plains";
		break;
	case 1:
		bstr = "from River";
		break;
	case 2:
		bstr = "from Mountains";
		break;
	default:
		break;
	}

}

void Dino::takeDamage(int _damage)
{
	sprite.setTexture(dinoSuffer);
	HP -= _damage;
	if (HP <= 0) {
		sprite.setTexture(dinoDead);
	}

}

void Dino::Damage(int _damage)
{
	sprite.setTexture(dinoAttack);

}

Dino::Dino(int _bp, int _str, int _int, int _agi, int _maxhp, std::string _name, int cost, int breed) {
	birthplace = _bp;
	STR = _str;
	INT = _int;
	AGI = _agi;
	HP = _maxhp;
	maxHP = _maxhp;
	name = _name;
	this->cost = cost;
	this->breed = breed;
	dinoIdle.loadFromFile("resources/dino" + std::to_string(breed) + "_idle.png");
	dinoAttack.loadFromFile("resources/dino" + std::to_string(breed) + "_attack.png");
	dinoSuffer.loadFromFile("resources/dino" + std::to_string(breed) + "_damaged.png");
	dinoDead.loadFromFile("resources/dino" + std::to_string(breed) + "_dead.png");
	sprite.setTexture(dinoIdle);
	switch (birthplace)
	{
	case 0:
		bstr = "from Plains";
		break;
	case 1:
		bstr = "from River";
		break;
	case 2:
		bstr = "from Mountains";
		break;
	default:
		break;
	}

}


int Dino::countDmg(int terrain)
{
	int out;
	switch (terrain)
	{
	case 0:
		out = STR;
		break;
	case 1:
		out = AGI;
		break;
	case 2:
		out = INT;
		break;
	default:
		out = 0;
		break;
	}
	if (terrain == birthplace) out *= 2;
	return out;
}

void Dino::update()
{
	sprite.setTexture(dinoIdle);
}

void Dino::dump()
{
	std::ofstream out;
	out.open("resources/collection.txt", std::ios::app);
	out << std::to_string(STR) << std::endl;
	out << std::to_string(AGI) << std::endl;
	out << std::to_string(INT) << std::endl;
	out << std::to_string(maxHP) << std::endl;
	out << std::to_string(birthplace) << std::endl;
	out << name << std::endl;
	out << std::to_string(cost) << std::endl;
	out << std::to_string(breed) << std::endl;
	out << "EndOfDino" << std::endl;
	out.close();

}
