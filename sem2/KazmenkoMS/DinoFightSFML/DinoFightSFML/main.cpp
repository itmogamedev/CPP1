#include "Resourses.h"
#include "Classes.h"
#include "Functions.h"
int main()
{
	srand(int(time(0)));
	//---------------INITIALIZATION-----------
	emptyTexture.create(100, 100);
	//---------------DINO INITIALIZATION------
	std::ifstream data("resources/dinobasa.txt");
	std::string line;
	data >> line;
	while (!data.eof())
	{
		std::string dinname;
		int dinstr, dindex, dinint, dincost, dintype; // временные переменные
		data >> dinname >> dinstr >> dindex >> dinint >> dincost >> dintype;
		dinos.push_back(new Dino(dinstr, dindex, dinint, dincost, dintype, dinname));
	}
	//--------------------------------------
	LoadTextures(Textures);
	LoadStats(player);
	CreateSound("menu", true, 50);
	CreateSound("shop", true, 40);
	CreateSound("fight", true, 50);
	CreateSound("click", false, 60);
	CreateSound("kick", false, 70);
	CreateSound("money", false, 60);
	CreateSound("victory", true, 50);
	CreateSound("lose", true, 40);
	window.setFramerateLimit(60);
	font.loadFromFile("resources/font2.ttf");
	//------------------------------

	while (window.isOpen())
	{
		switch (state)
		{
		case menu:
			MuteAll();
			Sounds["menu"].play();
			Menu(font, bg_color);
			break;
		case collection:
			MuteAll();
			Sounds["shop"].play();
			DisplayDinos(bg_color, player.dinoset, false, false);
			break;
		case shop:
			MuteAll();
			Sounds["shop"].play();
			DisplayDinos(bg_color, dinos, true, false);
			break;
		case gamePlay:
			MuteAll();
			Sounds["shop"].play();
			GamePlay(font, bg_color);
			break;
		default:
			break;
		}
	}
	return 0;
}
