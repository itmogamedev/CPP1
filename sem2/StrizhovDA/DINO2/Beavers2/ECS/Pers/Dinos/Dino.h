#pragma once
#include "ECS.h"
#include "string"

enum DinoType
{
	STR,
	DEX,
	INTE,
	NONE
};

enum Area
{
	River,
	Plain,
	Mountain,
	None
};


class Dino : public Component
{
private:
	int STR;
	int DEX;
	int INTE;

	int HP;

	DinoType dinoType;
	const char* texPath;
	std::string name;
public:
	Dino();
	Dino(int nowSTR, int nowDEX, int nowINTE);
	Dino(int nowSTR, int nowDEX, int nowINTE, Area nowArea);

	std::string GetSaveLog();

	inline const char* GetTexture()
	{
		return texPath;
	}

	inline int GetPrice()
	{
		return (int)(100 * (STR + DEX + INTE) / 90.0f);

	}
	inline int GetSTR()
	{
		return STR;
	}

	inline int GetDEX()
	{
		return DEX;
	}

	inline int GetINT()
	{
		return INTE;
	}

	inline int GetDamageVal()
	{
		return std::max(STR, std::max(DEX, INTE));
	}
};