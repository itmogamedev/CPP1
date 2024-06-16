#include "Store.h"

int Store::getBudget()
{
	return budget;
}

void Store::setBudget(int newBudget)
{
	budget = newBudget;
}

bool Store::canBuy(int i)
{
	if (getBudget() >= collection.getAvailableDinos()->at(i)->getCost()) return true;
	return false;
}

std::string Store::buy(int i)
{
	Dino* d = collection.getAvailableDinos()->at(i);
	collection.addDino(d);
	budget -= d->getCost();
	return d->getName();
}