#include "game.h"

int main()
{
	std::srand(std::time(0));
	Game game;


	while (game.running())
	{
		game.update();
		game.render();
	}
	return EXIT_SUCCESS;
}
