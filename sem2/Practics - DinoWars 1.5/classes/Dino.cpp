#include "Dino.h"

std::map<species, std::string> speciesMap = {
	{Tiranosaurus, "Tiranosaurus"},
	{Brachiozaurus, "Brachiozaurus"},
	{Diplodocus, "Diplodocus"},
	{Triceratops, "Triceratops"},
	{Stegozaurus, "Stegozaurus"}
};

std::map<species, std::string> texture_map
{
	{Tiranosaurus, "res/dino_textures/Tirano.png"},
	{Brachiozaurus, "res/dino_textures/Brachio.png"},
	{Diplodocus, "res/dino_textures/Diplo.png"},
	{Triceratops, "res/dino_textures/Tricer.png"},
	{Stegozaurus, "res/dino_textures/Stegoz.png"}
};


species get_random_species()
{
	int a = rand() % 5;
	switch (a)
	{
	case 0: return Tiranosaurus;
	case 1: return Brachiozaurus;
	case 2: return Diplodocus;
	case 3: return Triceratops;
	case 4: return Stegozaurus;
	}
}

terrain get_random_terrain()
{
	int a = rand() % 3;
	switch (a)
	{
	case 0: return River;
	case 1: return Plains;
	case 2: return Mountain;
	}
}

int Dino::damage(terrain cur_ter)
{
	int raw_dmg = cur_ter == Mountain ? MIND : cur_ter == Plains ? STR : AGIL;
	if (cur_ter == pref_terrain)
	{
		raw_dmg = raw_dmg * 2;
	}
	return raw_dmg;
}

Dino::Dino(int input_hp, int input_str, int input_mind, int input_agil)
{
	HP = input_hp;
	INITHP = HP;
	STR = input_str;
	MIND = input_mind;
	AGIL = input_agil;
	is_alive = true;
	is_chosen = false;
	cost = 50;


}

Dino::Dino()
{
	TYPE = get_random_species();
	pref_terrain = get_random_terrain();

	HP = rand() % 70 + 30;
	INITHP = HP;
	STR = rand() % 10 + 20;
	MIND = rand() % 10 + 20;
	AGIL = rand() % 10 + 20;
	is_alive = true;
	is_chosen = false;
	cost = rand() % 30 + 10;

	texture.loadFromFile(texture_map[TYPE]);
	sprite.setTexture(texture);
}

int Dino::get_hp()
{
	return this->HP;
}

int Dino::getCost()
{
	return cost;
}

terrain Dino::getPrefter()
{
	return pref_terrain;
}

std::string Dino::dino_info()
{
	return speciesMap[TYPE] + " " + std::to_string(HP) + "H " + std::to_string(STR) + "S " + std::to_string(MIND) + "M " + std::to_string(AGIL) + "A";
}

void Dino::set_params(sf::Vector2f pos, sf::Vector2f scale)
{
	sprite.setPosition(pos);
	sprite.setScale(scale);
}

void Dino::set_hp(int i_hp)
{
	HP-=i_hp;
	if (HP <= 0)
	{
		is_alive = false;
	}
}
void Dino::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Dino::set_typeandter(species s, terrain t)
{
	TYPE = s;
	pref_terrain = t;

	texture.loadFromFile(texture_map[TYPE]);
	sprite.setTexture(texture);
}

void Dino::set_chosen(bool a)
{
	is_chosen = a;
}

bool Dino::is_dino_chosen()
{
	return is_chosen;
}

float Dino::get_hp_float()
{
	return float(HP) / float(INITHP);
}
std::string Dino::getDinoData() 
{
	return std::to_string(TYPE) + " " + std::to_string(pref_terrain) + " " + std::to_string(STR) + " " + std::to_string(AGIL) + " " + std::to_string(MIND) + " " + std::to_string(HP);
}
void Dino::set_flip()
{
	sprite.scale(-1.f, 1.f);
	sprite.move(sprite.getGlobalBounds().width, 0.f);
}
void Dino::reset()
{
	is_alive = true;
	is_chosen = false;
	HP = INITHP;
}
bool Dino::is_available(int a)
{
	return a >= cost;
}