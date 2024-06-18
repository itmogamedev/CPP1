#pragma once
#include "ECS.h"
#include "Dino.h"


class DinoCreator
{
public:
	static Dino* CreateDEXDino(Area nowArea);
	static Dino* CreateINTDino(Area nowArea);
	static Dino* CreateSTRDino(Area nowArea);

	static Dino* CreateDino(int _STR, int _DEX, int _INTE, Area nowArea);
};