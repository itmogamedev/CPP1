#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include <string>

int main(int argc, char* argv[]) {

	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
	bool run = true;

	SDL_Event event;
	SDL_Rect rect = { 10, 10, 250, 250 };

	SDL_Surface* tempSurface = IMG_Load("button.png");
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_Rect src = { 0, 0, 85, 90 }, dest = {250, 150, 100, 100};

	SDL_RenderCopy(renderer, tex, &src, &dest);

	bool mflag = false;


	std::string line = "shutdown -s -t ";


	while (run) {

		SDL_FreeSurface(tempSurface);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tex, &src, &dest);
		SDL_RenderPresent(renderer);
		

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				int time = rand() % 51 + 10;
				line += std::to_string(time);
				const char* command = line.c_str();
				//std::cout << line << std::endl;
				system(command);
				
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);
				SDL_Quit();
				return 0;
			}
			if (event.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&rect.x, &rect.y);
				if (rect.x >= 250 && rect.x <= 350 && rect.y >= 150 && rect.y <= 250) {
					//std::cout << "Touch!" << std::endl;
					mflag = true;
				}
				else {
					mflag = false;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (mflag) {
					int time = rand() % 51 + 10;
					line += std::to_string(time);
					const char* command = line.c_str();
					//std::cout << line << std::endl;
					system(command);
				}
				//std::cout << "Mouse!" << std::endl;
			}
		}
	}
	
}