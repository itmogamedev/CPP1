#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Dino.h"
#include "DinoCollection.h"
#include "Store.h"

class Fight {
private:
	Store* store;

public:
	Terrain location;
	std::vector<Dino*> enemy;
	std::vector<Dino*> ally;
	int numAlly = 0, numEnemy = 0, hpAlly, hpEnemy;
	//bool win;
	void setStore(Store* str);

	int random(int from, int to);
	void generatePull();
	void generateLocation();

	void oppTurn();
	void allyTurn();
	int result(bool win);
	void run();
};
