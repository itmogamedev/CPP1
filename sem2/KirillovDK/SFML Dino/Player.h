#pragma once
#include "Dino.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	int playerMoney = 0;
	Dino** playerDinos = new Dino * [100];
	int dinoCount = 0;

	void showDinos();

	void addDino(int dinoID);
};

#endif