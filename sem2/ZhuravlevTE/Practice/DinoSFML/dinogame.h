#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "dinosaur.h"

static CP_Button Fight_Button("GOYDA!", { 250, 250 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button Shop_Button("Lavka Uncle Shell", { 250, 250 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button ChangeTeam_Button("Provesti uvolneniya v komande", { 250, 250 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button Vixod_Button("Vixod", { 450, 50 }, 20, sf::Color::Green, sf::Color::Black);

class CP_Game {
protected:
	sf::Font arial;
	std::string mainmenu_path = "images/mainmenu.jpg";
	std::string shop_path = "images/shop.jpg";
	std::string changeteam_path = "images/changeteam.jpg";
	std::string irilogo_path = "images/iri_logo.jpg";

	std::string plain_path = "images/VKPlay.jpg";
	std::string mountain_path = "images/EpicGamesStore.png";
	std::string river_path = "images/Steam.jpg";

	sf::Texture mainhub_texture;
	sf::Sprite mainhub_sprite;

	sf::Texture shop_texture;
	sf::Sprite shop_sprite;

	sf::Texture changeteam_texture;
	sf::Sprite changeteam_sprite;

	sf::Texture irilogo_texture;
	sf::Sprite irilogo_sprite;

	// TERRAINS
	sf::Texture plain_texture;
	sf::Sprite plain_sprite;

	sf::Texture mountain_texture;
	sf::Sprite mountain_sprite;

	sf::Texture river_texture;
	sf::Sprite river_sprite;
	
	std::vector<CP_DinosaurBase*> DinoAvailable = { new CP_Smuta, new CP_SumoTatami, new CP_AlanWake2 };
	std::vector<CP_DinosaurBase*> ShopAvailableDino = { new CP_Chernograd, new CP_Cyberpunk2077, new CP_CS2};

	bool BotTeamWin;
	bool PlayerTeamWin;
public:
	void Set_Images();
	void Button_Overlap(CP_Button& Button, sf::RenderWindow& window);
	void Make_BG_Sprite(sf::RenderWindow& window, int x, int y);
	void Button_Actions(sf::RenderWindow& window, sf::Event& event);

	bool CheckDinoInAvailable(std::string requestname);

	CP_DinosaurBase* GetAvailableDino(int i);

	void Shop(sf::RenderWindow& window, sf::Event& event);
	void Change_Team(sf::RenderWindow& window, sf::Event& event);

	void Fight(sf::RenderWindow& window, sf::Event& event);
	void BotCreateDinosaurArsenal();

	float makescalevec(int i);
	float makescalevecp(int i);

	bool CheckPlayerTeamDeath(bool dino1dead, bool dino2dead, bool dino3dead);

	bool CheckBotTeamDeath(bool dino1bdead, bool dino2bdead, bool dino3bdead);
};

class CP_FightSystem {

};