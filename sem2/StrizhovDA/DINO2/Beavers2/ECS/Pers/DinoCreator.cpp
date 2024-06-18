#include "DinoCreator.h"
#include "random"
#include "HP.h"

Dino* DinoCreator::CreateDEXDino(Area nowArea)
{
	srand(time(0));

	Entity& dino(Manager::addEntity());


	std::vector<int> vals;
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	std::sort(vals.begin(), vals.end());
	dino.AddComponent<HP>(vals[0] * 4);

	Dino* dinoC = dino.AddComponent<Dino>(vals[0], vals[2], vals[1], nowArea);

	return dinoC;
}
Dino* DinoCreator::CreateINTDino(Area nowArea)
{
	srand(time(0) + 1);

	Entity& dino(Manager::addEntity());


	std::vector<int> vals;
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	std::sort(vals.begin(), vals.end());
	dino.AddComponent<HP>(vals[0]*4);

	Dino* dinoC = dino.AddComponent<Dino>(vals[0], vals[1], vals[2], nowArea);
	return dinoC;
}
Dino* DinoCreator::CreateSTRDino(Area nowArea)
{
	srand(time(0) + 2);

	Entity& dino(Manager::addEntity());

	std::vector<int> vals;
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	vals.push_back(rand() % (30 + 1 - 10) + 10);
	std::sort(vals.begin(), vals.end());
	dino.AddComponent<HP>(vals[2] * 4);

	Dino* dinoC = dino.AddComponent<Dino>(vals[2], vals[1], vals[0], nowArea);

	return dinoC;
}

Dino* DinoCreator::CreateDino(int _STR, int _DEX, int _INTE, Area nowArea)
{
	srand(time(0) + 1);

	Entity& dino(Manager::addEntity());
	dino.AddComponent<HP>(_STR*4);


	Dino* dinoC = dino.AddComponent<Dino>(_STR, _DEX , _INTE, nowArea);

	return dinoC;
}