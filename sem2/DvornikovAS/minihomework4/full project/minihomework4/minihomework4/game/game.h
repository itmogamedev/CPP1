#pragma once

#ifndef GAME_H__
#define GAME_H__

#include "../cat/cat.h"

enum gameStatus {
	START,
	PLAY,
	PAUSE,
	WON
};

class Game {
private:


public:
	gameStatus status = gameStatus::START;

	void pause();
	void resume();
	void restart(Cat&);

};

#endif