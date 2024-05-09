#pragma once

#ifndef DINOS_H__
#define DINOS_H__


#include <iostream>

#include <SFML/Graphics.hpp>

enum Terrain {
	Plain,
	River,
	Mountain
};

enum TYPE_OF_CARD {
	COMMON,
	RARE,
	INSANE
};

class Dino {
protected:
	int strength;
	int agility;
	int brain;
	int hp = 100;
	int cost = 0;
	sf::Sprite card;
	TYPE_OF_CARD type;

public:
	Dino();
	virtual int damage(Terrain terrain) = 0;
	void set_strength(int st) { strength = st; }
	void set_agility(int ag) { agility = ag; }
	void set_brain(int br) { brain = br; }
	void set_cost(int price) { cost = price; }
	void set_card(sf::Sprite cd) { card = cd; }
	void set_type(TYPE_OF_CARD t) { type = t; }
	void setHealth(int);
	void setHealth2(int);
	int getHealth();
};

class DinoSt : public Dino {
public:
	DinoSt();
	DinoSt(int, int, int, TYPE_OF_CARD);
	DinoSt(const DinoSt& other) = default;
	DinoSt& operator=(const DinoSt& other) = default;
	int damage(Terrain terrain);
};

class DinoAg : public Dino {
public:
	DinoAg();
	DinoAg(int, int, int, TYPE_OF_CARD);
	DinoAg(const DinoAg& other) = default;
	DinoAg& operator=(const DinoAg& other) = default;
	int damage(Terrain terrain);
};

class DinoBr : public Dino {
public:
	DinoBr();
	DinoBr(int, int, int, TYPE_OF_CARD);
	DinoBr(const DinoBr& other) = default;
	DinoBr& operator=(const DinoBr& other) = default;
	int damage(Terrain terrain);
};

extern DinoSt dino_ptero, dino_ptero2, dino_trex, dino_trex2;
extern DinoAg dino_stego, dino_stego2;
extern DinoBr dino_brahi, dino_brahi2;

#endif // !DINOS_H__