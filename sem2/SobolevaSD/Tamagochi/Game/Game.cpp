#include "Game.h"


SDL_Renderer* Game::renderer = nullptr;

//SDL_Surface* tempSurface = IMG_Load("Assets/Menu.png");

Game::Game()
{
}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int wight, int hight, bool fullscreen)
{

	//SDL_RenderCopy(renderer, tex, &src, &dest);
	

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, wight, hight, flags);
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 215, 123, 186, 255);
			SDL_RenderCopy(renderer, tex, &src, &dest);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;

	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{}


void Game::render()
{
	/*SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, &src, &dest);
	SDL_RenderPresent(renderer);
	/*SDL_FreeSurface(tempSurface);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, &src, &dest);
	SDL_RenderPresent(renderer);*/

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}