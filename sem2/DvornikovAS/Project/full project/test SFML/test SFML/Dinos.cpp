#include "Dinos.h"

Dino::Dino()
{
}

void Dino::setHealth(int h) {
	if ((hp - h) < 0)
		hp = 0;
	else
		hp -= h;
}

void Dino::setHealth2(int h) {
	hp = h;
}

int Dino::getHealth() { return hp; }

DinoSt::DinoSt(int s, int a, int b, TYPE_OF_CARD t) {
	strength = s;
	agility = a;
	brain = b;
	type = t;
}
int DinoSt::damage(Terrain terrain) {
	if (terrain == Terrain::Plain)
		return 2 * strength;
	else if (terrain == Terrain::River)
		return agility;
	return brain;
}

DinoAg::DinoAg(int s, int a, int b, TYPE_OF_CARD t) {
	strength = s;
	agility = a;
	brain = b;
	type = t;
}
int DinoAg::damage(Terrain terrain) {
	if (terrain == Terrain::Plain)
		return strength;
	else if (terrain == Terrain::River)
		return 2 * agility;
	return brain;
}

DinoBr::DinoBr(int s, int a, int b, TYPE_OF_CARD t) {
	strength = s;
	agility = a;
	brain = b;
	type = t;
}
int DinoBr::damage(Terrain terrain) {
	if (terrain == Terrain::Plain)
		return strength;
	else if (terrain == Terrain::River)
		return agility;
	return 2 * brain;
}

DinoSt dino_ptero(13, 24, 10, TYPE_OF_CARD::COMMON);
DinoSt dino_ptero2(13, 24, 10, TYPE_OF_CARD::COMMON);
DinoSt dino_trex(28, 11, 21, TYPE_OF_CARD::INSANE);
DinoSt dino_trex2(28, 11, 21, TYPE_OF_CARD::INSANE);
DinoAg dino_stego(16, 11, 19, TYPE_OF_CARD::RARE);
DinoAg dino_stego2(16, 11, 19, TYPE_OF_CARD::RARE);
DinoBr dino_brahi(10, 14, 29, TYPE_OF_CARD::COMMON);
DinoBr dino_brahi2(10, 14, 29, TYPE_OF_CARD::COMMON);

void load_dinos() {

	//pterodactile
	//dino_ptero(13, 24, 10, TYPE_OF_CARD::COMMON);
	//dino_ptero.set_strength(13);
	//dino_ptero.set_agility(24);
	//dino_ptero.set_brain(10);
	//dino_ptero.set_cost(0);

	//dino_ptero.set_card(sp_pterod);

	//dino_ptero.set_type(TYPE_OF_CARD::COMMON);

	//trex
	//dino_trex.set_strength(28);
	//dino_trex.set_agility(11);
	//dino_trex.set_brain(21);
	//dino_trex.set_cost(3000);
	//dino_trex.set_card(sp_trex);
	//dino_trex.set_type(TYPE_OF_CARD::INSANE);

	//stego
	
	//dino_stego.set_strength(16);
	//dino_stego.set_agility(11);
	//dino_stego.set_brain(19);
	//dino_stego.set_cost(1200);
	//dino_stego.set_card(sp_trex);
	//dino_stego.set_type(TYPE_OF_CARD::RARE);
}