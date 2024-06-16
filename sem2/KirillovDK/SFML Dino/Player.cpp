#include "Player.h"

void Player::showDinos()
{
	std::cout << "Player dinos list:\n";

	for (int i = 0; i < dinoCount; i++)
	{
		std::cout << i + 1 << ". " << playerDinos[i]->getDinoName() << "\n";
	}
	std::cout << std::endl;
}

void Player::addDino(int dinoID)
{
	if (dinoCount == 100)
		std::cout << "Not enough space!\n\n";


	switch (dinoID)
	{
	case 1:
	{
		DinoSpin* dinoAdd = new DinoSpin;
		this->playerDinos[dinoCount] = dinoAdd;
	}
	break;

	case 2:
	{
		DinoDipl* dinoAdd = new DinoDipl;
		this->playerDinos[dinoCount] = dinoAdd;
	}
	break;

	case 3:
	{
		DinoSteg* dinoAdd = new DinoSteg;
		this->playerDinos[dinoCount] = dinoAdd;
	}
	break;

	case 4:
	{
		DinoBrach* dinoAdd = new DinoBrach;
		this->playerDinos[dinoCount] = dinoAdd;
	}
	break;

	case 5:
	{
		DinoTyran* dinoAdd = new DinoTyran;
		this->playerDinos[dinoCount] = dinoAdd;
	}
	break;
	}

	dinoCount++;
}

