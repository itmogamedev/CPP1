#include <iostream>
#include <string>
#include "Game.h"

int main(int argc, char* argv[]) {

	Game* game;
	game = new Game();

	int type = 0;
	bool pause = false;

	SDL_Rect PetDest = { 0, 0, 256, 128 };
	SDL_Rect PetDest1;
	SDL_Texture* PetTexture1 = nullptr;
	SDL_Surface* PetSurface1 = IMG_Load("Assets/ñat.png");
	SDL_Surface* PetSurface2 = IMG_Load("Assets/ñapy.png");
	SDL_Surface* PetSurface3 = IMG_Load("Assets/ñat.png");
	SDL_Surface* PetSurface;

	const int FPS = 4;
	const int frameDelay = 1000 / 4;

	Uint32 frameStart;
	int frameTime;

	SDL_Event event;
	SDL_Rect rect = { 10, 10, 250, 250 };

	SDL_Rect hudest = { 688, 528, 96, 96 };
	SDL_Rect hydest = { 560, 528, 96, 96 };
	SDL_Rect didest = { 432, 528, 96, 96 };

	game->init("Tamagochi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	bool choose = true;
	bool init = false;

	SDL_Surface* backSurface = IMG_Load("Assets/Background.png");
	SDL_Texture* back = SDL_CreateTextureFromSurface(game->renderer, backSurface);
	SDL_FreeSurface(backSurface);
	SDL_Surface* backgameSurface = IMG_Load("Assets/back.png");
	SDL_Texture* backgame = SDL_CreateTextureFromSurface(game->renderer, backgameSurface);
	SDL_FreeSurface(backgameSurface);
	SDL_Surface* winSurface = IMG_Load("Assets/win.png");
	SDL_Texture* win = SDL_CreateTextureFromSurface(game->renderer, winSurface);
	SDL_FreeSurface(winSurface);
	SDL_Surface* defeatSurface = IMG_Load("Assets/defeat.png");
	SDL_Texture* defeat = SDL_CreateTextureFromSurface(game->renderer, defeatSurface);
	SDL_FreeSurface(defeatSurface);
	SDL_Surface* HuButtonSurface = IMG_Load("Assets/Hunger_UI.png");
	SDL_Texture* hub = SDL_CreateTextureFromSurface(game->renderer, HuButtonSurface);
	SDL_FreeSurface(HuButtonSurface);
	SDL_Surface* HyButtonSurface = IMG_Load("Assets/Hydro_UI.png");
	SDL_Texture* hyb = SDL_CreateTextureFromSurface(game->renderer, HyButtonSurface);
	SDL_FreeSurface(HyButtonSurface);
	SDL_Surface* DiButtonSurface = IMG_Load("Assets/Dirty_UI.png");
	SDL_Texture* dib = SDL_CreateTextureFromSurface(game->renderer, DiButtonSurface);
	SDL_FreeSurface(DiButtonSurface);
	SDL_Surface* catButtonSurface = IMG_Load("Assets/CatButton.png");
	SDL_Texture* catb = SDL_CreateTextureFromSurface(game->renderer, catButtonSurface);
	SDL_FreeSurface(catButtonSurface);
	SDL_Surface* cataButtonSurface = IMG_Load("Assets/CatButtonA.png");
	SDL_Texture* catba = SDL_CreateTextureFromSurface(game->renderer, cataButtonSurface);
	SDL_FreeSurface(cataButtonSurface);
	SDL_Surface* capyButtonSurface = IMG_Load("Assets/CapyButton.png");
	SDL_Texture* capyb = SDL_CreateTextureFromSurface(game->renderer, capyButtonSurface);
	SDL_FreeSurface(capyButtonSurface);
	SDL_Surface* capyaButtonSurface = IMG_Load("Assets/CapyButtonA.png");
	SDL_Texture* capyba = SDL_CreateTextureFromSurface(game->renderer, capyaButtonSurface);
	SDL_FreeSurface(capyaButtonSurface);
	SDL_Surface* whoButtonSurface = IMG_Load("Assets/WhoButton.png");
	SDL_Texture* whob = SDL_CreateTextureFromSurface(game->renderer, whoButtonSurface);
	SDL_FreeSurface(whoButtonSurface);
	SDL_Surface* whoaButtonSurface = IMG_Load("Assets/WhoButtonA.png");
	SDL_Texture* whoba = SDL_CreateTextureFromSurface(game->renderer, whoaButtonSurface);
	SDL_FreeSurface(whoaButtonSurface);

	SDL_Rect src = { 0, 0, 800, 640 }, dest = { 0, 0, 800, 640 };

	bool catbut = false, capybut = false, whobut = false;

	while (game->running()) {

		frameStart = SDL_GetTicks();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		while (choose) {
			SDL_RenderClear(game->renderer);
			SDL_RenderCopy(game->renderer, back, &src, &dest);
			if (catbut) {

				SDL_RenderCopy(game->renderer, catba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, catb, &src, &dest);
			}
			if (capybut) {
				SDL_RenderCopy(game->renderer, capyba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, capyb, &src, &dest);
			}
			if (whobut) {
				SDL_RenderCopy(game->renderer, whoba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, whob, &src, &dest);
			}
			SDL_RenderPresent(game->renderer);

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					game->clean();
					return 0;
				}
				if (event.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&rect.x, &rect.y);
					//std::cout << rect.x << " " << rect.y << std::endl;
					if (rect.y >= 200 && rect.y <= 380) {
						if (rect.x >= 50 && rect.x <= 240) {
							catbut = true;
							capybut = false;
							whobut = false;
						}
						else if (rect.x >= 300 && rect.x <= 490) {
							capybut = true;
							catbut = false;
							whobut = false;
						}
						else if (rect.x >= 560 && rect.x <= 750) {
							whobut = true;
							catbut = false;
							capybut = false;
						}
						else {
							catbut = false;
							capybut = false;
							whobut = false;
						}
					}
					else {
						catbut = false;
						capybut = false;
						whobut = false;
					}
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (catbut) {
						type = 0;
						choose = false;
					}
					if (capybut) {
						type = 1;
						choose = false;
					}
					if (whobut) {
						type = 2;
						choose = false;
					}
				}
			}
		}

		if (not choose) {

			SDL_RenderClear(game->renderer);
			SDL_RenderCopy(game->renderer, backgame, &src, &dest);
			SDL_RenderCopy(game->renderer, hub, &src, &hudest);
			SDL_RenderCopy(game->renderer, hyb, &src, &hydest);
			SDL_RenderCopy(game->renderer, dib, &src, &didest);

			switch (type) {
			case 0:
				PetSurface = IMG_Load("Assets/cat.png");
				break;
			case 1:
				PetSurface = IMG_Load("Assets/capy.png");
				break;
			default:
				PetSurface = IMG_Load("Assets/cat.png");
				break;
			}

			PetTexture1 = SDL_CreateTextureFromSurface(game->renderer, PetSurface);
			SDL_FreeSurface(PetSurface);
			SDL_RenderCopy(game->renderer, PetTexture1, &src, &PetDest);

			if (not pause) {

				hudest.w--;
				hudest.h--;
				hydest.w--;
				hydest.h--;
				didest.w--;
				didest.h--;
				PetDest.h = PetDest.h - 1;
				PetDest.w = PetDest.w - 2;

			}

			if (hydest.w < 1 || hudest.w < 1 || didest.w < 1) {
				SDL_RenderClear(game->renderer);
				SDL_RenderCopy(game->renderer, defeat, &src, &dest);
				pause = true;

			}

			if (PetDest.w >= 830) {
				//win
				SDL_RenderClear(game->renderer);
				SDL_RenderCopy(game->renderer, win, &src, &dest);
				pause = true;
			}

			SDL_RenderPresent(game->renderer);

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					game->clean();
					return 0;
				}
				if (event.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&rect.x, &rect.y);
					//std::cout << rect.x << " " << rect.y << std::endl;
					if (rect.y >= 528 && rect.y <= 623) {
						if (rect.x >= 432 && rect.x <= 527) {
							if (didest.w >= 91) {
								didest.w = 96;
								didest.h = 96;
							}
							else {
								didest.w += 5;
								didest.h += 5;
							}
						}
						if (rect.x >= 688 && rect.x <= 783) {
							if (hudest.w >= 91) {
								hudest.w = 96;
								hudest.h = 96;
							}
							else {
								hudest.w += 5;
								hudest.h += 5;
							}
							PetDest.h = PetDest.h + 5;
							PetDest.w = PetDest.w + 10;

						}
						if (rect.x >= 560 && rect.x <= 655) {
							if (hydest.w >= 91) {
								hydest.w = 96;
								hydest.h = 96;
							}
							else {
								hydest.w += 5;
								hydest.h += 5;
							}
						}
						if (rect.y <= 639 && rect.y >= 560 && rect.x <= 399 && rect.x >= 336) {
							pause = true;
						}
						else {
							pause = false;
						}
					}
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {


				}
			}

		}
	}
}