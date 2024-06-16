#include "Fight.h"


void Fight::setStore(Store* str)
{
	store = str;
}

int Fight::random(int from, int to)
{
	return from + rand() % to;
}

void Fight::generatePull()
{
	numAlly = 0; numEnemy = 0;
	int num = store->collection.getFightDinos()->size();

	for (int i = 0; i < num; i++)
	{
		ally.push_back((*store->collection.getFightDinos())[i]);
		int rand = random(0, (*store->collection.getAllDinos()).size() - 1);
		enemy.push_back((*store->collection.getAllDinos())[rand]);
		numAlly++;
		numEnemy++;
	}

	hpAlly = ally[numAlly - 1]->getHP();
	hpEnemy = enemy[numEnemy - 1]->getHP();
}

void Fight::generateLocation()
{
	int rand = random(0, 3);
	location = static_cast<Terrain>(rand);
}

void Fight::oppTurn()
{
	int r1;
	if (hpAlly > 0)
	{
		r1 = random(0, 8);
		hpAlly -= enemy[numEnemy - 1]->damage(location) + r1;
	}
}

void Fight::allyTurn()
{
	int r1;
	if (hpEnemy > 0)
	{
		r1 = random(0, 8);
		hpEnemy -= ally[numAlly - 1]->damage(location) + r1;
	}
}

int Fight::result(bool win)
{
	if (win) {
		int coins = random(4, 7);
		store->setBudget(store->getBudget() + coins);
		return coins;
	}
	else {
		int coins = random(0, 6);
		store->setBudget(store->getBudget() - coins);
		if (store->getBudget() <= 0) {
			store->setBudget(0);
		}
		return coins;
	}
}

void Fight::run()
{
	enemy.clear();
	ally.clear();
}
