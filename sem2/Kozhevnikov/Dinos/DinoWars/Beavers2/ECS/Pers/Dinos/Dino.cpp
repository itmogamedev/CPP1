#include "Dino.h"
#include "random"


Dino::Dino()
{
	HP = 100;

	STR = 10;
	DEX = 10;
	INTE = 10;

	dinoType = DinoType::NONE;
	texPath = "res/Textures/Brahiozavr.png";
}

Dino::Dino(int nowSTR, int nowDEX, int nowINTE)
{
	HP = 100;

	STR = nowSTR;
	DEX = nowDEX;
	INTE = nowINTE;

	int m = std::max(STR, std::max(INTE, DEX));

	if (m == STR)
	{
		dinoType = DinoType::STR;
		texPath  = "res/Textures/Dinos/Tiranozavr.png";
		return;
	}
	if (m == INTE)
	{
		dinoType = DinoType::INTE;
		texPath  = "res/Textures/Dinos/Brahiozavr.png";
		return;
	}
	if (m == DEX)
	{
		dinoType = DinoType::DEX;

		int n = rand() % 2;
		texPath  = (n == 1 ? "res/Textures/Dinos/Stegozavr.png" : "res/Textures/Dinos/Triceratops.png");
		return;
	}
}
Dino::Dino(int nowSTR, int nowDEX, int nowINTE, Area nowArea)
{
	HP = 100;

	STR = nowSTR;
	DEX = nowDEX;
	INTE = nowINTE;

	int m = std::max(STR, std::max(INTE, DEX));

	if (m == STR)
	{
		dinoType = DinoType::STR;
		texPath = "res/Textures/Dinos/Tiranozavr.png";
	}
	if (m == INTE)
	{
		dinoType = DinoType::INTE;
		texPath = "res/Textures/Dinos/Brahiozavr.png";
	}
	if (m == DEX)
	{
		dinoType = DinoType::DEX;

		texPath = "res/Textures/Dinos/Stegozavr.png";
	}

	STR *= (nowArea == Area::Mountain ? 2 : 1);
	DEX *= (nowArea == Area::Plain ? 2 : 1);
	INTE *= (nowArea == Area::River ? 2 : 1);
}


std::string Dino::GetSaveLog()
{
	std::string s = "";
	s = std::to_string(STR) + " " + std::to_string(DEX) + " " + std::to_string(INTE);
	return s;
}
