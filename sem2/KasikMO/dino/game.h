#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Dino.h"
#include <fstream>

	// Kinda Engine class
class Game
{
private:
	void initVars();
	void initWindow();
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	std::vector<Dino*> collection;
	std::vector<Dino*> forsale;
	std::vector<Dino*> mypack;
	std::vector<Dino*> enemypack;
	std::vector<bool> chosen;
	int mode; // 0 - shop, 1 - collection, 2 - battle
	int storeCap;
	int storePage;
	int money;
	int c;
	int terrain;
	int reward;
	bool myTurn;
	bool myVictory;
	sf::Font font;

	void fillStore();
	void onFight();
	void loadCollection();
	void emptyStore();
	void emptyCol();
	void showDinos(std::vector<Dino*> list);
	void showFight();
	void makeTurn();
	
		
public:
	Game();
	virtual ~Game();

	const bool running() const;

	void update();
	void render();
	void updateEvs();
};

