#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Dino.h"
#include "Brachiosaurus.h"
#include "Plesiosaurus.h"
#include "Triceratops.h"
#include "Parasaurolophus.h"
#include "Pterodactyl.h"
#include "Stegosaurus.h"
#include "Tyrannosaurus.h"

class DinoCollection {
private:
	Pterodactyl pterodactyl;
	Parasaurolophus parasaurolophus;
	Stegosaurus stegosaurus;
	Tyrannosaurus tyrannosaurus;
	Brachiosaurus brachiosaurus;
	Plesiosaurus plesiosaurus;
	Triceratops triceratops;

	std::vector<Dino*> dinos;
	std::vector<Dino*> fightDinos;
	std::vector<Dino*> allDinos = { &pterodactyl, &parasaurolophus, &stegosaurus, &tyrannosaurus, &brachiosaurus, &plesiosaurus, &triceratops };
	std::vector<Dino*> availableDinos = allDinos;

public:
	~DinoCollection();

	std::vector<Dino*>* getDinos();
	std::vector<Dino*>* getAvailableDinos();
	std::vector<Dino*>* getAllDinos();
	std::vector<Dino*>* getFightDinos();

	void addDino(Dino* d);
	void addStartDinos();
	void pushFightDino(Dino* d);
	void addFightDino(std::string input);
	void deleteFightDino(std::string input);

	int isFighter(Dino* d);
	void manageFighters(std::string input);
	void run();
};
