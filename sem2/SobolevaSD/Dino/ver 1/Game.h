#ifndef Game_hpp
#define Game_hpp
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {

public:
	Game();
	~Game();

	SDL_Surface* tempSurface;
	SDL_Texture* tex;
	SDL_Rect src, dest;

	/*SDL_Texture* tex;
	SDL_Surface* tempSurface = IMG_Load("Menu.png");
	SDL_Rect src = { 0, 0, 85, 90 }, dest = { 250, 150, 100, 100 };*/

	void init(const char* title, int xpos, int ypos, int wight, int hight, bool fullscreen);
	
	void handleEvents();
	void update();
	bool running() { return isRunning; };
	void render();
	void clean();
	
	static SDL_Renderer* renderer;
	

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};

#endif

