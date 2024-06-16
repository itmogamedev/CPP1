#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "Player.h"

class SaveLoader
{
private: 
	std::string filename;
public: 
	SaveLoader(std::string i_filename);
	void save(Player& player);
	void load(Player& player);
};

