#include "dinogame.h"
#include "player.h"
#include "terrain.h"
#include <windows.h>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>

CP_Player player;
CP_Bot bot;

int arr[3];

const int size = 2;
int toattack[size];

const int money = 1;
int coins[money];

std::vector <CP_DinosaurBase*> DinoEnemyPool = { new CP_Smuta, new CP_SumoTatami, new CP_CS2, new CP_Chernograd, new CP_Cyberpunk2077, new CP_AlanWake2 };

void RandomGeneratorForBotTeam() {
	srand(time(NULL));

	bool alreadyThere;

	for (int i = 0; i < 3; )
	{
		alreadyThere = false;
		int newRanomValue = rand() % 6;

		for (int j = 0; j < i; j++)
		{
			if (arr[j] == newRanomValue)
			{
				alreadyThere = true;
				break;
			}
		}

		if (!alreadyThere)
		{
			arr[i] = newRanomValue;
			i++;
		}

	}
}

void RandomGeneratorForBotToAttack() {
	srand(time(NULL));
	for (int i = 0; i < size; )
	{
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, 2);

		int newRanomValue = dist(rd);

		toattack[i] = newRanomValue;
		i++;

	}
}

void RandomGeneratorForMoney() {
	srand(time(NULL));

	bool alreadyThere;

	for (int i = 0; i < money; )
	{
		alreadyThere = false;
		int newRanomValue = rand() % 50;

		for (int j = 0; j < i; j++)
		{
			if (coins[j] == newRanomValue)
			{
				alreadyThere = true;
				break;
			}
		}

		if (!alreadyThere)
		{
			coins[i] = newRanomValue;
			i++;
		}

	}
}

void CP_Game::Set_Images()
{
	if (mainhub_texture.loadFromFile(mainmenu_path)) {
		mainhub_sprite.setTexture(mainhub_texture);
	}

	if (shop_texture.loadFromFile(shop_path)) {
		shop_sprite.setTexture(shop_texture);
	}

	if (changeteam_texture.loadFromFile(changeteam_path)) {
		changeteam_sprite.setTexture(changeteam_texture);
	}

	if (irilogo_texture.loadFromFile(irilogo_path)) {
		irilogo_sprite.setTexture(irilogo_texture);
		irilogo_sprite.setPosition(50, 970);
		irilogo_sprite.setScale({ 0.05, 0.05 });
	}

	arial.loadFromFile("ArialRegular.ttf");

	Fight_Button.setPosition({ 800, 400 }, {890, 505});
	Fight_Button.setFont(arial);
	Shop_Button.setPosition({ 400, 400 }, {440, 505 });
	Shop_Button.setFont(arial);

	ChangeTeam_Button.setPosition({ 1200, 400 }, {1210, 505 });
	ChangeTeam_Button.setFont(arial);

	Vixod_Button.setPosition({ 700, 800 }, {900, 812});
	Vixod_Button.setFont(arial);

}

void CP_Game::Button_Overlap(CP_Button& Button, sf::RenderWindow& window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	Button.setBackColor(sf::Color::White);
	if (!Button.isMouseOver(mouse)) {
		Button.setBackColor(sf::Color::Green);
	}
}

void CP_Game::Make_BG_Sprite(sf::RenderWindow& window, int x, int y)
{
	Set_Images();
	window.draw(mainhub_sprite);
	window.draw(irilogo_sprite);
	Fight_Button.drawTo(window);
	Shop_Button.drawTo(window);
	ChangeTeam_Button.drawTo(window);
	Vixod_Button.drawTo(window);
	
}

void CP_Game::Button_Actions(sf::RenderWindow& window, sf::Event& event)
{
	Make_BG_Sprite(window, 0, 0);
	window.display();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				if (Fight_Button.isMouseOver(mouse)) {
					if (player.TeamSize() == 3) {
						Fight(window, event);
					}
					else {

					}
				}
				if (Shop_Button.isMouseOver(mouse)) {
					Shop(window, event);
					break;
				}
				if (ChangeTeam_Button.isMouseOver(mouse)) {
					Change_Team(window, event);
				}
				if (Vixod_Button.isMouseOver(mouse)) {
					exit(true);
				}
				break;
			}
		}
	}
}

bool CP_Game::CheckDinoInAvailable(std::string requestname)
{
	for (int i = 0; i < DinoAvailable.size(); i++) {
		if (DinoAvailable[i]->CP_GetDinoName() == requestname) {
			return true;
		}
	}
	return false;
}

CP_DinosaurBase* CP_Game::GetAvailableDino(int i)
{
	return ShopAvailableDino[i];
}

void CP_Game::Shop(sf::RenderWindow& window, sf::Event& event)
{
	bool dino1bought = false;
	bool dino2bought = false;
	bool dino3bought = false;

	arial.loadFromFile("ArialRegular.ttf");

	CP_Button BalancShow("Balanc: " + std::to_string(player.GetBalance()), {250, 120}, 30, sf::Color::Green, sf::Color::Black);

	CP_ButtonImage Dino1("", { 500, 500 }, 0, ShopAvailableDino[0]->CP_GetDinoPath() + ".png", sf::Color::Black);
	CP_Button Dino1Price("4ena: " + std::to_string(ShopAvailableDino[0]->CP_GetDinoCost()), { 500, 75 }, 20, sf::Color::Green, sf::Color::Black);

	CP_ButtonImage Dino2("", { 500, 500 }, 0, ShopAvailableDino[1]->CP_GetDinoPath() + ".png", sf::Color::Black);
	CP_Button Dino2Price("4ena: " + std::to_string(ShopAvailableDino[1]->CP_GetDinoCost()), { 500, 75 }, 20, sf::Color::Green, sf::Color::Black);

	CP_ButtonImage Dino3("", { 500, 500 }, 0, ShopAvailableDino[2]->CP_GetDinoPath() + ".png", sf::Color::Black);
	CP_Button Dino3Price("4ena: " + std::to_string(ShopAvailableDino[2]->CP_GetDinoCost()), { 500, 75 }, 20, sf::Color::Green, sf::Color::Black);

	CP_Button Obratno("Vernutsya", { 650, 75 }, 35, sf::Color::Green, sf::Color::Black);

	window.clear();
	std::vector <sf::Vector2f> Sprites_Position = { {100, 250}, {700, 250}, {1300, 250} };

	BalancShow.setPosition({ 100, 75 }, { 120, 105 });
	BalancShow.setFont(arial);

	Dino1.setPosition(Sprites_Position[0], { 0,0 });
	Dino1.setFont(arial);

	Dino1Price.setPosition({ 100, 725 }, { 150, 750 });
	Dino1Price.setFont(arial);

	Dino2.setPosition(Sprites_Position[1], { 0,0 });
	Dino2.setFont(arial);

	Dino2Price.setPosition({ 700, 725 }, { 750, 750 });
	Dino2Price.setFont(arial);

	Dino3.setPosition(Sprites_Position[2], { 0,0 });
	Dino3.setFont(arial);

	Dino3Price.setPosition({ 1300, 725 }, { 1350, 750 });
	Dino3Price.setFont(arial);

	Obratno.setPosition({ 620, 900 }, { 900, 925 });
	Obratno.setFont(arial);

	window.draw(shop_sprite);
	Dino1.drawTo(window);
	Dino1Price.drawTo(window);

	Dino2.drawTo(window);
	Dino2Price.drawTo(window);

	Dino3.drawTo(window);
	Dino3Price.drawTo(window);
	BalancShow.drawTo(window);
	Obratno.drawTo(window);

	window.display();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				if (Dino1.isMouseOver(mouse)) {
					if (!dino1bought) {
						if (player.GetBalance() >= ShopAvailableDino[0]->CP_GetDinoCost()) {
							player.ChangeMinusBalance(ShopAvailableDino[0]->CP_GetDinoCost());
							DinoAvailable.push_back(ShopAvailableDino[0]);
							dino1bought = true;
						}
					}
				}
				if (Dino2.isMouseOver(mouse)) {
					if (!dino2bought) {
						if (player.GetBalance() >= ShopAvailableDino[1]->CP_GetDinoCost()) {
							player.ChangeMinusBalance(ShopAvailableDino[1]->CP_GetDinoCost());
							DinoAvailable.push_back(ShopAvailableDino[1]);
							dino2bought = true;
						}
					}
				}
				if (Dino3.isMouseOver(mouse)) {
					if (!dino3bought) {
						if (player.GetBalance() >= ShopAvailableDino[2]->CP_GetDinoCost()) {
							player.ChangeMinusBalance(ShopAvailableDino[2]->CP_GetDinoCost());
							DinoAvailable.push_back(ShopAvailableDino[2]);
							dino3bought = true;
						}
					}
				}
				if (Obratno.isMouseOver(mouse)) {
					Button_Actions(window, event);
				}
				break;
			}
		}
	}
}

void CP_Game::Change_Team(sf::RenderWindow& window, sf::Event& event)
{
	arial.loadFromFile("ArialRegular.ttf");

	bool pos11 = false, pos12 = false, pos13 = false;
	bool dino1 = false;

	bool pos21 = false, pos22 = false, pos23 = false;
	bool dino2 = false;

	bool pos31 = false, pos32 = false, pos33 = false;
	bool dino3 = false;

	bool pos41 = false, pos42 = false, pos43 = false;
	bool dino4 = false;

	bool pos51 = false, pos52 = false, pos53 = false;
	bool dino5 = false;

	bool pos61 = false, pos62 = false, pos63 = false;
	bool dino6 = false;

	int howmuch = -1;

	std::vector <sf::Vector2f> Positions = { { 100, 150 }, { 700, 150 }, { 1300, 150 } };

	CP_Button Dino1("Smuta", {250, 50}, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Dino2("Sumo Tatami", { 250, 50 }, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Dino3("Alan Wake 2", {250, 50}, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Dino4("CHERNOGRAD", { 250, 50 }, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Dino5("Cyberpunk 2077", { 250, 50 }, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Dino6("Counter-Strike 2", { 250, 50 }, 20, sf::Color::Green, sf::Color::Black);
	CP_Button Obratno("Podtverdit vibor", { 650, 75 }, 35, sf::Color::Green, sf::Color::Black);

	CP_ButtonImage DinoPlayer1("", { 500, 500 }, 0, "images/Smuta.png", sf::Color::Black);
	CP_ButtonImage DinoPlayer2("", { 500, 500 }, 0, "images/SumoTatami.png", sf::Color::Black);
	CP_ButtonImage DinoPlayer3("", { 500, 500 }, 0, "images/AlanWake2.png", sf::Color::Black);
	CP_ButtonImage DinoPlayer4("", { 500, 500 }, 0, "images/CHERNOGRAD.png", sf::Color::Black);
	CP_ButtonImage DinoPlayer5("", { 500, 500 }, 0, "images/Cyberpunk.png", sf::Color::Black);
	CP_ButtonImage DinoPlayer6("", { 500, 500 }, 0, "images/CS2.png", sf::Color::Black);

	player.TeamClear();

	while (window.isOpen()) {

		Dino1.setPosition({ 680, 700 }, { 765, 725 });
		Dino1.setFont(arial);

		Dino2.setPosition({ 680, 775 }, { 765, 800 });
		Dino2.setFont(arial);

		Dino3.setPosition({ 680, 850 }, { 765, 875 });
		Dino3.setFont(arial);

		Dino4.setPosition({ 980, 700 }, { 1065, 725 });
		Dino4.setFont(arial);

		Dino5.setPosition({ 980, 775 }, { 1065, 800 });
		Dino5.setFont(arial);

		Dino6.setPosition({ 980, 850 }, { 1065, 875 });
		Dino6.setFont(arial);

		Obratno.setPosition({ 620, 950 }, { 840, 975 });
		Obratno.setFont(arial);

		window.draw(changeteam_sprite);
		Dino1.drawTo(window);
		Dino2.drawTo(window);
		Dino3.drawTo(window);
		Dino4.drawTo(window);
		Dino5.drawTo(window);
		Dino6.drawTo(window);
		Obratno.drawTo(window);

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				if (Dino1.isMouseOver(mouse)) {
					if (!dino1) {
						player.AddDino(DinoAvailable[0]);
						dino1 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos11 = true;
							break;
						case 1:
							pos12 = true;
							break;
						case 2:
							pos13 = true;
							break;
						}
					}
					else {

					}
				}
				if (Dino2.isMouseOver(mouse)) {
					if (!dino2) {
						player.AddDino(DinoAvailable[1]);
						dino2 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos21 = true;
							break;
						case 1:
							pos22 = true;
							break;
						case 2:
							pos23 = true;
							break;
						}
					}
					else {

					}
				}
				if (Dino3.isMouseOver(mouse)) {
					if (!dino3) {
						player.AddDino(DinoAvailable[2]);
						dino3 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos31 = true;
							break;
						case 1:
							pos32 = true;
							break;
						case 2:
							pos33 = true;
							break;
						}
					}
					else {

					}
				}
				if (Dino4.isMouseOver(mouse)) {
					if (!dino4 and CheckDinoInAvailable("CHERNOGRAD")) {
						player.AddDino(new CP_Chernograd());
						dino4 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos41 = true;
							break;
						case 1:
							pos42 = true;
							break;
						case 2:
							pos43 = true;
							break;
						}
					}
					else {

					}
				}
				if (Dino5.isMouseOver(mouse)) {
					if (!dino5 and CheckDinoInAvailable("Cyberpunk 2077")) {
						player.AddDino(new CP_Cyberpunk2077());
						dino5 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos51 = true;
							break;
						case 1:
							pos52 = true;
							break;
						case 2:
							pos53 = true;
							break;
						}
					}
					else {

					}
				}
				if (Dino6.isMouseOver(mouse)) {
					if (!dino6 and CheckDinoInAvailable("Counter-Strike 2")) {
						player.AddDino(new CP_CS2());
						dino6 = true;
						howmuch++;
						switch (howmuch) {
						case 0:
							pos61 = true;
							break;
						case 1:
							pos62 = true;
							break;
						case 2:
							pos63 = true;
							break;
						}
					}
					else {

					}
				}
				if (Obratno.isMouseOver(mouse)) {
					Button_Actions(window, event);
				}
				break;
			}
		}
		if (dino1 == true) {
			if (pos11 == true) {
				DinoPlayer1.setPosition(Positions[0], { 0,0 });
				DinoPlayer1.drawTo(window);
			}
			if (pos12 == true) {
				DinoPlayer1.setPosition(Positions[1], { 0,0 });
				DinoPlayer1.drawTo(window);
			}
			if (pos13 == true) {
				DinoPlayer1.setPosition(Positions[2], { 0,0 });
				DinoPlayer1.drawTo(window);
			}

		}
		if (dino2 == true) {
			if (pos21 == true) {
				DinoPlayer2.setPosition(Positions[0], { 0,0 });
				DinoPlayer2.drawTo(window);
			}
			if (pos22 == true) {
				DinoPlayer2.setPosition(Positions[1], { 0,0 });
				DinoPlayer2.drawTo(window);
			}
			if (pos23 == true) {
				DinoPlayer2.setPosition(Positions[2], { 0,0 });
				DinoPlayer2.drawTo(window);
			}
		}
		if (dino3 == true) {
			if (pos31 == true) {
				DinoPlayer3.setPosition(Positions[0], { 0,0 });
				DinoPlayer3.drawTo(window);
			}
			if (pos32 == true) {
				DinoPlayer3.setPosition(Positions[1], { 0,0 });
				DinoPlayer3.drawTo(window);
			}
			if (pos33 == true) {
				DinoPlayer3.setPosition(Positions[2], { 0,0 });
				DinoPlayer3.drawTo(window);
			}
		}
		if (dino4 == true) {
			if (pos41 == true) {
				DinoPlayer4.setPosition(Positions[0], { 0,0 });
				DinoPlayer4.drawTo(window);
			}
			if (pos42 == true) {
				DinoPlayer4.setPosition(Positions[1], { 0,0 });
				DinoPlayer4.drawTo(window);
			}
			if (pos43 == true) {
				DinoPlayer4.setPosition(Positions[2], { 0,0 });
				DinoPlayer4.drawTo(window);
			}
		}
		if (dino5 == true) {
			if (pos51 == true) {
				DinoPlayer5.setPosition(Positions[0], { 0,0 });
				DinoPlayer5.drawTo(window);
			}
			if (pos52 == true) {
				DinoPlayer5.setPosition(Positions[1], { 0,0 });
				DinoPlayer5.drawTo(window);
			}
			if (pos53 == true) {
				DinoPlayer5.setPosition(Positions[2], { 0,0 });
				DinoPlayer5.drawTo(window);
			}
		}
		if (dino6 == true) {
			if (pos61 == true) {
				DinoPlayer6.setPosition(Positions[0], { 0,0 });
				DinoPlayer6.drawTo(window);
			}
			if (pos62 == true) {
				DinoPlayer6.setPosition(Positions[1], { 0,0 });
				DinoPlayer6.drawTo(window);
			}
			if (pos63 == true) {
				DinoPlayer6.setPosition(Positions[2], { 0,0 });
				DinoPlayer6.drawTo(window);
			}
		}

		window.display();
	}
}

void CP_Game::Fight(sf::RenderWindow& window, sf::Event& event)
{

	window.clear();

	arial.loadFromFile("ArialRegular.ttf");

	bool player_isattack = true;

	bool dino1dead = false;
	bool dino2dead = false;
	bool dino3dead = false;
	bool dino1bdead = false;
	bool dino2bdead = false;
	bool dino3bdead = false;

	bool playerdino_choosed = false;
	bool botdino_choosed = false;

	int playerdinoid_choosed;
	int botdinoid_choosed;

	CP_ButtonImage DinoPlayer1("", { 300, 300 }, 0, player.GetDinosaurPlayer(0)->CP_GetDinoPath() + "_fight.png", sf::Color::Black);
	CP_Button Dino1HP("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino1Dead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);

	CP_ButtonImage DinoPlayer2("", { 300, 300 }, 0, player.GetDinosaurPlayer(1)->CP_GetDinoPath() + "_fight.png", sf::Color::Black);
	CP_Button Dino2HP("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino2Dead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);

	CP_ButtonImage DinoPlayer3("", { 300, 300 }, 0, player.GetDinosaurPlayer(2)->CP_GetDinoPath() + "_fight.png", sf::Color::Black);
	CP_Button Dino3HP("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino3Dead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);

	CP_Button PlayerTeamText("Tvoya biblioteka", { 250, 100 }, 20, sf::Color::Transparent, sf::Color::White);
	CP_Button BotTeamText("Biblioteka vraga", { 250, 100 }, 20, sf::Color::Transparent, sf::Color::White);

	CP_Button WinText("ESSS -3 EXUUU POBEDA!!!", { 250, 100 }, 50, sf::Color::Transparent, sf::Color::White);
	CP_Button LoseText("Mam, nu mam... Eshe 5 minutok...", { 250, 100 }, 50, sf::Color::Transparent, sf::Color::White);
	CP_Button BackToMenu("Vernutsya", { 250, 120 }, 45, sf::Color::Green, sf::Color::Black);

	BotCreateDinosaurArsenal();

	CP_ButtonImage DinoBot1("", { 300, 300 }, 0, bot.GetDinosaurBot(0)->CP_GetDinoPath() + "_fight.png", sf::Color::Black);
	CP_Button Dino1BHP ("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino1BDead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);

	CP_ButtonImage DinoBot2("", { 300, 300 }, 0, bot.GetDinosaurBot(1)->CP_GetDinoPath() + "_fight.png", sf::Color::Black);
	CP_Button Dino2BHP("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino2BDead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);

	CP_ButtonImage DinoBot3("", { 300, 300 }, 0, bot.GetDinosaurBot(2)->CP_GetDinoPath()+ "_fight.png", sf::Color::Black);
	CP_Button Dino3BHP("Is Dead!", { 300, 50 }, 15, sf::Color::Red, sf::Color::White);
	CP_Button Dino3BDead("", { 300, 300 }, 0, sf::Color::Red, sf::Color::Transparent);


	if (plain_texture.loadFromFile(plain_path)) {
		plain_sprite.setTexture(plain_texture);
	}
	if (mountain_texture.loadFromFile(mountain_path)) {
		mountain_sprite.setTexture(mountain_texture);
	}
	if (river_texture.loadFromFile(river_path)) {
		river_sprite.setTexture(river_texture);
	}

	RandomGeneratorForTerrain();

	DinoPlayer1.setPosition({ 150, 640 }, { 0,0 });
	Dino1HP.setPosition({ 150, 960 }, {160, 970});
	Dino1Dead.setPosition({ 150, 640 }, { 0,0 });

	DinoPlayer2.setPosition({ 500, 640 }, { 0,0 });
	Dino2HP.setPosition({ 500, 960 }, { 510, 970 });
	Dino2Dead.setPosition({ 500, 640 }, { 0,0 });

	DinoPlayer3.setPosition({ 850, 640 }, { 0,0 });
	Dino3HP.setPosition({ 850, 960 }, { 860, 970 });
	Dino3Dead.setPosition({ 850, 640 }, { 0,0 });

	PlayerTeamText.setPosition({ 0, 0 }, { 150, 600 });
	PlayerTeamText.setFont(arial);

	DinoBot1.setPosition({ 750, 115 }, { 0,0 });
	Dino1BHP.setPosition({ 750, 435 }, { 760, 445 });
	Dino1BDead.setPosition({ 750, 115 }, { 0,0 });

	DinoBot2.setPosition({ 1100, 115 }, { 0,0 });
	Dino2BHP.setPosition({ 1100, 435 }, { 1110, 445 });
	Dino2BDead.setPosition({ 1100, 115 }, { 0,0 });

	DinoBot3.setPosition({ 1450, 115 }, { 0,0 });
	Dino3BHP.setPosition({ 1450, 435 }, { 1460, 445 });
	Dino3BDead.setPosition({ 1450, 115 }, { 0,0 });

	BotTeamText.setPosition({ 0, 0 }, { 1605, 75 });
	BotTeamText.setFont(arial);

	BackToMenu.setPosition({ 1400, 750 }, { 1450, 765 });
	BackToMenu.setFont(arial);

	WinText.setPosition({ 525, 550 }, { 525, 550 });
	WinText.setFont(arial);

	LoseText.setPosition({ 525, 550 }, { 525, 550 });
	LoseText.setFont(arial);


	while (window.isOpen()) {
		switch (get_terrain()) {
		case Terrain::VKPlay:
			window.draw(plain_sprite);
			break;

		case Terrain::Steam:
			window.draw(river_sprite);
			break;

		case Terrain::EpicGamesStore:
			window.draw(mountain_sprite);
			break;
		}

		DinoPlayer1.drawTo(window);
		Dino1HP.drawTo(window);
		DinoPlayer2.drawTo(window);
		Dino2HP.drawTo(window);
		DinoPlayer3.drawTo(window);
		Dino3HP.drawTo(window);
		PlayerTeamText.drawTo(window);

		DinoBot1.drawTo(window);
		Dino1BHP.drawTo(window);
		DinoBot2.drawTo(window);
		Dino2BHP.drawTo(window);
		DinoBot3.drawTo(window);
		Dino3BHP.drawTo(window);
		BotTeamText.drawTo(window);

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				if (PlayerTeamWin == false && BotTeamWin == false) {
					CheckPlayerTeamDeath(dino1dead, dino2dead, dino3dead);
					CheckBotTeamDeath(dino1bdead, dino2bdead, dino3bdead);
					if (player_isattack) {
						if (DinoPlayer1.isMouseOver(mouse)) {
							if (!playerdino_choosed) {
								playerdinoid_choosed = 0;
								playerdino_choosed = true;
								DinoPlayer1.setPosition({ 150, 620 }, { 0,0 });
							}
						}
						if (DinoPlayer2.isMouseOver(mouse)) {
							if (!playerdino_choosed) {
								playerdinoid_choosed = 1;
								playerdino_choosed = true;
								DinoPlayer2.setPosition({ 500, 620 }, { 0,0 });
							}
						}
						if (DinoPlayer3.isMouseOver(mouse)) {
							if (!playerdino_choosed) {
								playerdinoid_choosed = 2;
								playerdino_choosed = true;
								DinoPlayer3.setPosition({ 850, 620 }, { 0,0 });
							}
						}
						if (DinoBot1.isMouseOver(mouse)) {
							if (!botdino_choosed and playerdino_choosed) {
								botdinoid_choosed = 0;
								botdino_choosed = true;
							}
						}
						if (DinoBot2.isMouseOver(mouse)) {
							if (!botdino_choosed and playerdino_choosed) {
								botdinoid_choosed = 1;
								botdino_choosed = true;
							}
						}
						if (DinoBot3.isMouseOver(mouse)) {
							if (!botdino_choosed and playerdino_choosed) {
								botdinoid_choosed = 2;
								botdino_choosed = true;
							}
						}
					}
					break;
				}
				if (BackToMenu.isMouseOver(mouse)) {
					if (PlayerTeamWin or BotTeamWin) {
						Button_Actions(window, event);
					}
				}
				break;
			}
		}

		if (playerdino_choosed and botdino_choosed) {
			if (bot.GetDinosaurBot(botdinoid_choosed)->CP_GetIsAlive() == true) {
				switch (get_terrain()) {
				case Terrain::Steam:
					bot.GetDinosaurBot(botdinoid_choosed)->CP_TakeDamage(player.GetDinosaurPlayer(playerdinoid_choosed)->CP_GetDinoDamage());
					break;
				case Terrain::VKPlay:
					bot.GetDinosaurBot(botdinoid_choosed)->CP_TakeDamage(player.GetDinosaurPlayer(playerdinoid_choosed)->CP_GetDinoMovement());
					break;
				case Terrain::EpicGamesStore:
					bot.GetDinosaurBot(botdinoid_choosed)->CP_TakeDamage(player.GetDinosaurPlayer(playerdinoid_choosed)->CP_GetDinoIntellect());
					break;
				}
			}
			switch (botdinoid_choosed) {
			case 0:
				Dino1BHP.setScale({ makescalevec(botdinoid_choosed), 1 });
				if (makescalevec(botdinoid_choosed) == 0) {
					dino1bdead = true;
				}
				break;
			case 1:
				Dino2BHP.setScale({ makescalevec(botdinoid_choosed), 1 });
				if (makescalevec(botdinoid_choosed) == 0) {
					dino2bdead = true;
				}
				break;
			case 2:
				Dino3BHP.setScale({ makescalevec(botdinoid_choosed), 1 });
				if (makescalevec(botdinoid_choosed) == 0) {
					dino3bdead = true;
				}
				break;
			}

			CheckPlayerTeamDeath(dino1dead, dino2dead, dino3dead);
			CheckBotTeamDeath(dino1bdead, dino2bdead, dino3bdead);

			if (!PlayerTeamWin) {
				while (bot.GetDinosaurBot(toattack[1])->CP_GetIsAlive() == false || player.GetDinosaurPlayer(toattack[0])->CP_GetIsAlive() == false) {
					RandomGeneratorForBotToAttack();
				}

				RandomGeneratorForBotToAttack();

				if (player.GetDinosaurPlayer(toattack[0])->CP_GetIsAlive() == true) {
					switch (get_terrain()) {
					case Terrain::Steam:
						player.GetDinosaurPlayer(toattack[0])->CP_TakeDamage(bot.GetDinosaurBot(toattack[1])->CP_GetDinoDamage());
						break;
					case Terrain::VKPlay:
						player.GetDinosaurPlayer(toattack[0])->CP_TakeDamage(bot.GetDinosaurBot(toattack[1])->CP_GetDinoMovement());
						break;
					case Terrain::EpicGamesStore:
						player.GetDinosaurPlayer(toattack[0])->CP_TakeDamage(bot.GetDinosaurBot(toattack[1])->CP_GetDinoIntellect());
						break;
					}
				}

				switch (playerdinoid_choosed) {
				case 0:
					Dino1HP.setScale({ makescalevecp(toattack[0]), 1 });
					DinoPlayer1.setPosition({ 150, 640 }, { 0,0 });
					if (makescalevecp(toattack[0]) == 0) {
						dino1dead = true;
					}
					break;
				case 1:
					Dino2HP.setScale({ makescalevecp(toattack[0]), 1 });
					DinoPlayer2.setPosition({ 500, 640 }, { 0,0 });
					if (makescalevecp(toattack[0]) == 0) {
						dino2dead = true;
					}
					break;
				case 2:
					Dino3HP.setScale({ makescalevecp(toattack[0]), 1 });
					DinoPlayer3.setPosition({ 850, 640 }, { 0,0 });
					if (makescalevecp(toattack[0]) == 0) {
						dino3dead = true;
					}
					break;
				}

				CheckPlayerTeamDeath(dino1dead, dino2dead, dino3dead);
				CheckBotTeamDeath(dino1bdead, dino2bdead, dino3bdead);

				playerdino_choosed = false;
				botdino_choosed = false;
			}
		}

		if (PlayerTeamWin) { WinText.drawTo(window); BackToMenu.drawTo(window); RandomGeneratorForMoney(); player.ChangePlusBalance(coins[0]);}
		if (BotTeamWin) { LoseText.drawTo(window); BackToMenu.drawTo(window); RandomGeneratorForMoney(); player.ChangePlusBalance((coins[0] * 0, 5));}

		if (dino1dead){ Dino1Dead.drawTo(window); Dino1HP.setFont(arial);}
		if (dino2dead) { Dino2Dead.drawTo(window); Dino2HP.setFont(arial); }
		if (dino3dead) { Dino3Dead.drawTo(window); Dino3HP.setFont(arial); }
		if (dino1bdead) { Dino1BDead.drawTo(window); Dino1BHP.setFont(arial); }
		if (dino2bdead) { Dino2BDead.drawTo(window); Dino2BHP.setFont(arial); }
		if (dino3bdead) { Dino3BDead.drawTo(window); Dino3BHP.setFont(arial); }

		window.display();
	}
}

void CP_Game::BotCreateDinosaurArsenal()
{
	bool DinoBotTeamCreated = false;
	RandomGeneratorForBotTeam();

	while (DinoBotTeamCreated != true) {
		for (int i = 0; i < 3; i++) {
			bot.AddBotDino(DinoEnemyPool[arr[i]]);
		}
		if (bot.BTeamSize() == 3) {
			DinoBotTeamCreated = true;
		}
	}
}

float CP_Game::makescalevec(int i)
{
	return (bot.GetDinosaurBot(i)->CP_GetDinoCurrentHP() / bot.GetDinosaurBot(i)->CP_GetDinoHealth());
}

float CP_Game::makescalevecp(int i)
{
	return (player.GetDinosaurPlayer(i)->CP_GetDinoCurrentHP() / player.GetDinosaurPlayer(i)->CP_GetDinoHealth());
}

bool CP_Game::CheckPlayerTeamDeath(bool dino1dead, bool dino2dead, bool dino3dead)
{
	if (dino1dead && dino2dead && dino3dead) {
		return BotTeamWin = true;
	}
	else {
		return BotTeamWin = false;
	}
}

bool CP_Game::CheckBotTeamDeath(bool dino1bdead, bool dino2bdead, bool dino3bdead)
{
	if (dino1bdead && dino2bdead && dino3bdead) {
		return PlayerTeamWin = true;
	}
	else {
		return PlayerTeamWin = false;
	}
}

