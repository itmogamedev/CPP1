#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <set>
#include <list>

#ifndef DINO_H_
#define DINO_H_

void waitForSeconds(int inputTime);


enum Terrain { Plain, River, Mountain };

class Dino
{
protected:
	int strength;
	int agility;
	int intelligence;
	int healthPoints;
	int currentHealthPoints;

	std::string dinoName;
	int dinoCost;

public:
	int dinoID;

	virtual int damage(Terrain inputTerrain) = 0;

	std::string getDinoName()
	{
		return this->dinoName;
	}


	Dino(const Dino& dino)
	{
		this->dinoName = dino.dinoName;
		this->dinoCost = dino.dinoCost;

		this->strength = dino.strength;
		this->intelligence = dino.intelligence;
		this->agility = dino.agility;

		this->healthPoints = dino.healthPoints;
	}


	Dino()
	{
	}


	~Dino() {}


	void updateHP(int newHP)
	{
		this->currentHealthPoints = newHP;
	}

	int getHP()
	{
		return this->currentHealthPoints;
	}

	int getMaxHP()
	{
		return this->healthPoints;
	}

	virtual void showDinoImage() const {};
};



class DinoStr : public Dino
{
public:
	int damage(Terrain inputTerrain)
	{
		return inputTerrain == Terrain::Plain ?
			strength * 2 :
			inputTerrain == Terrain::River ?
			agility :
			intelligence;
	}
};


class DinoAg : public Dino
{
public:
	int damage(Terrain inputTerrain)
	{
		return inputTerrain == Terrain::River ?
			agility * 2 :
			inputTerrain == Terrain::Plain ?
			strength :
			intelligence;
	}
};


class DinoInt : public Dino
{
public:
	int damage(Terrain inputTerrain)
	{
		return inputTerrain == Terrain::Mountain ?
			intelligence * 2 :
			inputTerrain == Terrain::Plain ?
			strength :
			agility;
	}
};

// Stegosaurus
// Triceratops
// Diplodocus
// Brachiosaurus
// Tyrannosaurus

class DinoBrach : public DinoInt
{
public:
	DinoBrach()
	{
		this->intelligence = 20;
		this->strength = 15;
		this->agility = 10;
		this->healthPoints = 240;
		this->currentHealthPoints = healthPoints;

		this->dinoID = 4;
		this->dinoName = "Brachiosaurus";
		this->dinoCost = 2000;
	}
};

class DinoTyran : public DinoStr
{
public:
	DinoTyran()
	{
		this->strength = 25;
		this->agility = 20;
		this->intelligence = 15;
		this->healthPoints = 160;
		this->currentHealthPoints = healthPoints;

		this->dinoID = 5;
		this->dinoName = "Tyrannosaurus";
		this->dinoCost = 2500;
	}
};

class DinoDipl : public DinoInt
{
public:
	DinoDipl()
	{
		this->intelligence = 15;
		this->agility = 20;
		this->strength = 10;
		this->healthPoints = 260;
		this->currentHealthPoints = healthPoints;

		this->dinoID = 2;
		this->dinoName = "Diplodocus";
		this->dinoCost = 1500;
	}
};

class DinoSpin : public DinoAg
{
public:
	DinoSpin()
	{
		this->agility = 10;
		this->strength = 15;
		this->intelligence = 15;
		this->healthPoints = 180;
		this->currentHealthPoints = healthPoints;

		this->dinoID = 1;
		this->dinoName = "Spinosaurus";
		this->dinoCost = 1200;
	}
};

class DinoSteg : public DinoAg
{
public:
	DinoSteg()
	{
		this->agility = 20;
		this->strength = 15;
		this->intelligence = 20;
		this->healthPoints = 210;
		this->currentHealthPoints = healthPoints;

		this->dinoID = 3;
		this->dinoName = "Stegosaurus";
		this->dinoCost = 2000;
	}
};


std::vector<std::string> splitString(std::string inputString);

#endif
