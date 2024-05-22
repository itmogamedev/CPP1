#include "Functions.h"
// updates player collection and stats
void LoadStats(Player& player)
{
	std::ifstream playerdata("resources/playerstats.txt");
	playerdata >> player.currbalance >> player.victnum >> player.losnum;
	while (!playerdata.eof())
	{
		std::string dinoname;
		playerdata >> dinoname;
		for (Dino* tmpdin : dinos)
		{
			if (tmpdin->getname() == dinoname)
			{
				player.dinoset.push_back(new Dino(*tmpdin));
			}
		}
	}
	std::cout << "dinoset created\n";
	playerdata.close();
}

// saves player collection and stats to resources/playerstats.txt
void SaveStats(Player& player)
{
	std::ofstream newdata("resources/playerstats.txt");
	newdata << player.currbalance << " " << player.victnum << " " << player.losnum << " ";
	for (Dino* tmp : player.dinoset)
	{
		newdata << tmp->getname() << " ";
	}
	std::cout << "SAVED";
	newdata.close();
}