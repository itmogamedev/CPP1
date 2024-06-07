#include "game.h"

#include <iostream>

void Game::pause() { status = gameStatus::PAUSE; }

void Game::resume() { status = gameStatus::PLAY; }

void Game::restart(Cat& _cat) {
	_cat.setAlive();
	_cat.setWon();
	_cat.setSize(0.5);
	_cat.setSatiety(50);
	_cat.setSatisfaction(50);
	_cat.setPurity(50);
	status = gameStatus::START;
}