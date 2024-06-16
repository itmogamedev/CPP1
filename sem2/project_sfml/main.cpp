#include <SFML/Graphics.hpp>
#include "game.h"


int main()
{
	setlocale(LC_ALL,"");
	srand(time(NULL));
	Game game;
	game.main();

	return 0;
}