#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream> 


class Player {
private:
	int coins = 400;
	std::vector <bool> Dinos = { false, false, false, false };
public:
	void setCoins(int A);
	int getCoins();
	void buy(int A);
	std::vector <bool> getInfo();
	void setDino(std::vector <bool>B);
	void LoadGame(const std::string& filename);
	void SaveGame(const std::string& filename);
	
};
extern Player player;
#endif