#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "dinogame.h"

static CP_Button NewGame_Button("Novaya Igra", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button LoadGame_Button("Zagruzit Igru", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button Settings_Button("Nastroyki", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
static CP_Button Exit_Button("Vixod", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);

static CP_Game game;

enum class GameState {
	MainMenu = 0,
	Game = 1,
};

class CP_Menu {
protected:

	GameState CP_GameState = GameState::MainMenu;

	sf::Font arial;
	std::string bg_path = "images/bg_test.jpg";
	std::string logo_path = "images/logo.png";
	std::string irilogo_path = "images/iri_logo.jpg";
	std::string lublogo_path = "images/lublogo.jpeg";

	sf::Image bg_image;
	sf::Texture bg_texture;
	sf::Sprite bg_sprite;

	sf::Image logo_image;
	sf::Texture logo_texture;
	sf::Sprite logo_sprite;

	sf::Texture irilogo_texture;
	sf::Sprite irilogo_sprite;

	sf::Texture lublogo_texture;
	sf::Sprite lublogo_sprite;

public:
	void Set_Buttons();
	void Button_Overlap(CP_Button& Button, sf::RenderWindow& window);
	void Make_BG_Sprite(sf::RenderWindow& window, int x, int y);
	void Button_Actions(sf::RenderWindow& window, sf::Event& event);

	void CP_SetMenuState();
};