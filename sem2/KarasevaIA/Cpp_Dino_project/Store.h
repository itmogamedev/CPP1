#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include "Dino.h"
#include "DinoCollection.h"

class Store {
private:
	int budget;

public:
	DinoCollection collection;
	Store() = default;

	int getBudget();
	void setBudget(int newBudget);

	bool canBuy(int i);
	std::string buy(int i);
};
