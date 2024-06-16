#pragma once
#include "sfml_stuff.h"
#include <random>

enum species { Tiranosaurus, Brachiozaurus, Diplodocus, Triceratops, Stegozaurus };
enum terrain { Mountain, River, Plains };

class Dino
{
private: 
	sf::Texture texture;
	sf::Sprite sprite;
	species TYPE;
	terrain pref_terrain;
	int INITHP;
	int HP;
	int STR;
	int MIND;
	int AGIL;
	int cost;

	bool is_chosen;
public:
	Dino(int input_hp, int input_str, int input_mind, int input_agil);
	Dino();
	int damage(terrain cur_ter);

	int getCost();
	terrain getPrefter();
	bool is_dino_chosen();
	float get_hp_float();
	int get_hp();
	bool is_alive;
	
	bool is_available(int a);
	std::string dino_info();

	void set_params(sf::Vector2f pos, sf::Vector2f scale);
	void set_typeandter(species s, terrain t);
	void set_chosen(bool a);
	void set_hp(int i_hp);

	void draw(sf::RenderWindow& window);
	void set_flip();

	void reset();
	std::string getDinoData();
};