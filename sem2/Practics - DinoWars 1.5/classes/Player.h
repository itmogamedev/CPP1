#pragma once
#include "sfml_stuff.h"
#include <iostream>
#include <vector>
#include "Dino.h"

class Player
{
private:
	int coins;
public:
	std::vector<Dino*> dinos_owned;
	std::vector<Dino*> chosen_dinos;

	Player(int i_coins);
	int getCoins();
	bool any_dino_alive();
	void giveCoins(int a);
	void setCoins(int a);
	void buy_dino(Dino* newDino);
	void reset_dinos();
	bool has_dinos();
	// ÄËß ÂÐÀÃÀ
	void generate_dinos();
};

