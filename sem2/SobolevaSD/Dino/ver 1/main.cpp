#include <iostream>
#include <string>
#include "Game.h"
#include "Dino.h"
#include <fstream>
#include <vector>
#include <string>
#include "Windows.h"

int main(int argc, char* argv[]) {

	Game* game;
	game = new Game();

	std::vector <Dino> dinos;
	std::vector <Dino> yourpull;
	std::vector <Dino> enemypull;
	std::vector <int> shopdino;
	std::vector <int> temp;

	int FPS = 4;
	int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	SDL_Event event;
	SDL_Rect rect = { 10, 10, 250, 250 };

	bool getbalance = false;
	int balance = 0;

	std::string line;
	int sum = 0;

	game->init("DinoBattle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	std::vector <int> dinochoose;

	int q = 0;
	std::ifstream in("Assets/game.txt");
	if (in.is_open()) {
		while (getline(in, line)) {
			if (!getbalance) {
				balance = stoi(line);
				std::cout << balance;
				getbalance = true;
			}
			else {
				if (q < 3) {
					temp.push_back(stoi(line));
					q++;
				}
				else {
					temp.push_back(stoi(line));
					Dino dino(temp[1], temp[2], temp[3]);
					dino.type = temp[0];
					dinos.push_back(dino);
					q = 0;
					temp.clear();
				}
				if (q == 1) {
					dinochoose.push_back(1);
				}
			}
			//Dino dinor = Dino(line);
			//dino.push_back(Dino::Dino(line));
		}
		while (dinochoose.size() < 6) {
			dinochoose.push_back(0);
		}
	}
	in.close();

	bool choose = true;
	bool init = false;
	int ch = 0, th = 0;

	SDL_Surface* DinoIntSurface = IMG_Load("Assets/intDinoUI.png");
	SDL_Texture* dinoint = SDL_CreateTextureFromSurface(game->renderer, DinoIntSurface);
	SDL_FreeSurface(DinoIntSurface);
	SDL_Surface* DinoIntaSurface = IMG_Load("Assets/intDinoUIPressed.png");
	SDL_Texture* dinointa = SDL_CreateTextureFromSurface(game->renderer, DinoIntaSurface);
	SDL_FreeSurface(DinoIntaSurface);
	SDL_Surface* DinoDexSurface = IMG_Load("Assets/dexDinoUI.png");
	SDL_Texture* dinodex = SDL_CreateTextureFromSurface(game->renderer, DinoDexSurface);
	SDL_FreeSurface(DinoDexSurface);
	SDL_Surface* DinoDexaSurface = IMG_Load("Assets/dexDinoUIPressed.png");
	SDL_Texture* dinodexa = SDL_CreateTextureFromSurface(game->renderer, DinoDexaSurface);
	SDL_FreeSurface(DinoDexaSurface);
	SDL_Surface* DinoStrSurface = IMG_Load("Assets/strDinoUI.png");
	SDL_Texture* dinostr = SDL_CreateTextureFromSurface(game->renderer, DinoStrSurface);
	SDL_FreeSurface(DinoStrSurface);
	SDL_Surface* DinoStraSurface = IMG_Load("Assets/strDinoUIPressed.png");
	SDL_Texture* dinostra = SDL_CreateTextureFromSurface(game->renderer, DinoStraSurface);
	SDL_FreeSurface(DinoStraSurface);

	SDL_Surface* DinoIntbSurface = IMG_Load("Assets/intDinoBattle.png");
	SDL_Texture* dinointb = SDL_CreateTextureFromSurface(game->renderer, DinoIntbSurface);
	SDL_FreeSurface(DinoIntbSurface);
	SDL_Surface* DinoIntbaSurface = IMG_Load("Assets/intDinoBattleAttack.png");
	SDL_Texture* dinointba = SDL_CreateTextureFromSurface(game->renderer, DinoIntbaSurface);
	SDL_FreeSurface(DinoIntbaSurface);
	SDL_Surface* DinoIntbdaSurface = IMG_Load("Assets/intDinoBattleDamaged.png");
	SDL_Texture* dinointbda = SDL_CreateTextureFromSurface(game->renderer, DinoIntbdaSurface);
	SDL_FreeSurface(DinoIntbdaSurface);
	SDL_Surface* DinoIntbdSurface = IMG_Load("Assets/intDinoBattleDie.png");
	SDL_Texture* dinointbd = SDL_CreateTextureFromSurface(game->renderer, DinoIntbdSurface);
	SDL_FreeSurface(DinoIntbdSurface);

	SDL_Surface* DinodexbSurface = IMG_Load("Assets/dexDinoBattle.png");
	SDL_Texture* dinodexb = SDL_CreateTextureFromSurface(game->renderer, DinodexbSurface);
	SDL_FreeSurface(DinodexbSurface);
	SDL_Surface* DinodexbaSurface = IMG_Load("Assets/dexDinoBattleAttack.png");
	SDL_Texture* dinodexba = SDL_CreateTextureFromSurface(game->renderer, DinodexbaSurface);
	SDL_FreeSurface(DinodexbaSurface);
	SDL_Surface* DinodexbdaSurface = IMG_Load("Assets/dexDinoBattleDamaged.png");
	SDL_Texture* dinodexbda = SDL_CreateTextureFromSurface(game->renderer, DinodexbdaSurface);
	SDL_FreeSurface(DinodexbdaSurface);
	SDL_Surface* DinodexbdSurface = IMG_Load("Assets/dexDinoBattleDie.png");
	SDL_Texture* dinodexbd = SDL_CreateTextureFromSurface(game->renderer, DinodexbdSurface);
	SDL_FreeSurface(DinodexbdSurface);

	SDL_Surface* DinostrbSurface = IMG_Load("Assets/strDinoBattle.png");
	SDL_Texture* dinostrb = SDL_CreateTextureFromSurface(game->renderer, DinostrbSurface);
	SDL_FreeSurface(DinostrbSurface);
	SDL_Surface* DinostrbaSurface = IMG_Load("Assets/strDinoBattleAttack.png");
	SDL_Texture* dinostrba = SDL_CreateTextureFromSurface(game->renderer, DinostrbaSurface);
	SDL_FreeSurface(DinostrbaSurface);
	SDL_Surface* DinostrbdaSurface = IMG_Load("Assets/strDinoBattleDamaged.png");
	SDL_Texture* dinostrbda = SDL_CreateTextureFromSurface(game->renderer, DinostrbdaSurface);
	SDL_FreeSurface(DinostrbdaSurface);
	SDL_Surface* DinostrbdSurface = IMG_Load("Assets/strDinoBattleDie.png");
	SDL_Texture* dinostrbd = SDL_CreateTextureFromSurface(game->renderer, DinostrbdSurface);
	SDL_FreeSurface(DinostrbdSurface);

	SDL_Surface* IntSurface = IMG_Load("Assets/int.png");
	SDL_Texture* intet = SDL_CreateTextureFromSurface(game->renderer, IntSurface);
	SDL_FreeSurface(IntSurface);
	SDL_Surface* DexSurface = IMG_Load("Assets/dex.png");
	SDL_Texture* dext = SDL_CreateTextureFromSurface(game->renderer, DexSurface);
	SDL_FreeSurface(DexSurface);
	SDL_Surface* StrSurface = IMG_Load("Assets/str.png");
	SDL_Texture* strt = SDL_CreateTextureFromSurface(game->renderer, StrSurface);
	SDL_FreeSurface(StrSurface);
	SDL_Surface* HPSurface = IMG_Load("Assets/health.png");
	SDL_Texture* hpt = SDL_CreateTextureFromSurface(game->renderer, HPSurface);
	SDL_FreeSurface(HPSurface);

	SDL_Surface* p1Surface = IMG_Load("Assets/place1.png");
	SDL_Texture* place1 = SDL_CreateTextureFromSurface(game->renderer, p1Surface);
	SDL_FreeSurface(p1Surface);
	SDL_Surface* p2Surface = IMG_Load("Assets/place2.png");
	SDL_Texture* place2 = SDL_CreateTextureFromSurface(game->renderer, p2Surface);
	SDL_FreeSurface(p2Surface);
	SDL_Surface* p3Surface = IMG_Load("Assets/place3.png");
	SDL_Texture* place3 = SDL_CreateTextureFromSurface(game->renderer, p3Surface);
	SDL_FreeSurface(p3Surface);


	SDL_Surface* MenuSurface = IMG_Load("Assets/Menu.png");
	SDL_Texture* menu = SDL_CreateTextureFromSurface(game->renderer, MenuSurface);
	SDL_FreeSurface(MenuSurface);
	SDL_Surface* exitButtonSurface = IMG_Load("Assets/Exit_Button.png");
	SDL_Texture* exitb = SDL_CreateTextureFromSurface(game->renderer, exitButtonSurface);
	SDL_FreeSurface(exitButtonSurface);
	SDL_Surface* exitaButtonSurface = IMG_Load("Assets/Exit_Button_Pressed.png");
	SDL_Texture* exitba = SDL_CreateTextureFromSurface(game->renderer, exitaButtonSurface);
	SDL_FreeSurface(exitaButtonSurface);
	SDL_Surface* shopButtonSurface = IMG_Load("Assets/Shop_Button.png");
	SDL_Texture* shopb = SDL_CreateTextureFromSurface(game->renderer, shopButtonSurface);
	SDL_FreeSurface(shopButtonSurface);
	SDL_Surface* shopaButtonSurface = IMG_Load("Assets/Shop_Button_Pressed.png");
	SDL_Texture* shopba = SDL_CreateTextureFromSurface(game->renderer, shopaButtonSurface);
	SDL_FreeSurface(shopaButtonSurface);
	SDL_Surface* collButtonSurface = IMG_Load("Assets/Collection_Button.png");
	SDL_Texture* collb = SDL_CreateTextureFromSurface(game->renderer, collButtonSurface);
	SDL_FreeSurface(collButtonSurface);
	SDL_Surface* collaButtonSurface = IMG_Load("Assets/Collection_Button_Pressed.png");
	SDL_Texture* collba = SDL_CreateTextureFromSurface(game->renderer, collaButtonSurface);
	SDL_FreeSurface(collaButtonSurface);
	SDL_Surface* battButtonSurface = IMG_Load("Assets/Battle_Button.png");
	SDL_Texture* battb = SDL_CreateTextureFromSurface(game->renderer, battButtonSurface);
	SDL_FreeSurface(battButtonSurface);
	SDL_Surface* battaButtonSurface = IMG_Load("Assets/Battle_Button_Pressed.png");
	SDL_Texture* battba = SDL_CreateTextureFromSurface(game->renderer, battaButtonSurface);
	SDL_FreeSurface(battaButtonSurface);
	SDL_Surface* backButtonSurface = IMG_Load("Assets/Back_Button.png");
	SDL_Texture* backb = SDL_CreateTextureFromSurface(game->renderer, backButtonSurface);
	SDL_FreeSurface(backButtonSurface);
	SDL_Surface* backaButtonSurface = IMG_Load("Assets/Back_Button_Pressed.png");
	SDL_Texture* backba = SDL_CreateTextureFromSurface(game->renderer, backaButtonSurface);
	SDL_FreeSurface(backaButtonSurface);
	SDL_Surface* goButtonSurface = IMG_Load("Assets/Go_Button.png");
	SDL_Texture* gob = SDL_CreateTextureFromSurface(game->renderer, goButtonSurface);
	SDL_FreeSurface(goButtonSurface);
	SDL_Surface* goaButtonSurface = IMG_Load("Assets/Go_Button_Pressed.png");
	SDL_Texture* goba = SDL_CreateTextureFromSurface(game->renderer, goaButtonSurface);
	SDL_FreeSurface(goaButtonSurface);


	SDL_Rect src = { 0, 0, 800, 640 }, dest = { 0, 0, 800, 640 };
	SDL_Rect dinosrc = { 0, 0, 256, 256 }, yourdinodest = { 50, 50, 256, 256 }, enemydinodest = { 400, 50, 256, 256 };
	SDL_Rect featsrc = { 0, 0, 4, 4 }, featdest = { 0, 0, 20, 20 };
	SDL_Rect dinofeatsrc = { 0, 0, 800, 640 }, dinofeatdest = { 0, 0, 800, 640 };
	SDL_Rect yhpdest = { 50, 300, 256, 30 };
	SDL_Rect ehpdest = { 400, 300, 256, 30 };
	SDL_Rect shopdest = { 250, 100, 256, 256 };
	SDL_Rect charsrc = { 0, 0, 4, 4 }, chardest = { 50, 300, 256, 30 };
	SDL_Rect shopchardest = { 250, 300, 256, 40 };

	bool you = true, flag = false, shopact = false;;
	bool battbut = false, collbut = false, shopbut = false, exitbut = false;
	bool battle = false, collection = false, shop = false, back = false, go = false, start = false;
	int place = 0;
	int time=0;

	while (game->running()) {

		frameStart = SDL_GetTicks();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		while (choose) {
			SDL_RenderClear(game->renderer);
			SDL_RenderCopy(game->renderer, menu, &src, &dest);
			if (exitbut) {
				SDL_RenderCopy(game->renderer, exitba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, exitb, &src, &dest);
			}
			if (shopbut) {
				SDL_RenderCopy(game->renderer, shopba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, shopb, &src, &dest);
			}
			if (collbut) {
				SDL_RenderCopy(game->renderer, collba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, collb, &src, &dest);
			}
			if (battbut) {
				SDL_RenderCopy(game->renderer, battba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, battb, &src, &dest);
			}
			SDL_RenderPresent(game->renderer);

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					std::ofstream out;
					out.open("game.txt");
					out << balance << std::endl;
					for (auto v : dinos) {
						out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
					}
					out.close();
					game->clean();
					return 0;
				}
				if (event.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&rect.x, &rect.y);
					std::cout << rect.x << " " << rect.y << std::endl;
					if (rect.x >= 280 && rect.x <= 520) {
						if (rect.y >= 300 && rect.y <= 340) {
							collbut = true;
							battbut = false;
							shopbut = false;
							exitbut = false;
						}
						else if (rect.y >= 400 && rect.y <= 440) {
							shopbut = true;
							collbut = false;
							exitbut = false;
							battbut = false;
						}
						else if (rect.y >= 500 && rect.y <= 540) {
							exitbut = true;
							shopbut = false;
							collbut = false;
							battbut = false;
						}
						else if (rect.y >= 100 && rect.y <= 180) {
							battbut = true;
							collbut = false;
							shopbut = false;
							exitbut = false;
						}
						else {
							exitbut = false;
							collbut = false;
							shopbut = false;
							battbut = false;
						}
					}
					else if (rect.x >= 130 && rect.x <= 670 && rect.y >= 100 && rect.y <= 180) {
						battbut = true;
						collbut = false;
						shopbut = false;
						exitbut = false;
					}
					else {
						battbut = false;
						collbut = false;
						shopbut = false;
						exitbut = false;
					}
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (battbut) {
						choose = false;
						battle = true;
					}
					if (collbut) {
						choose = false;
						collection = true;
					}
					if (shopbut) {
						choose = false;
						shop = true;
					}
					if (exitbut) {
						choose = false;
						std::ofstream out;
						out.open("game.txt");
						out << balance << std::endl;
						for (auto v : dinos) {
							out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
						}
						out.close();
						game->clean();
					}
				}
			}
		}
		while (not choose) {

			SDL_RenderClear(game->renderer);

			if (collection) {
				featsrc = { 0, 0, 4, 4 }, featdest = { 0, 0, 128, 20 };
				dinofeatsrc = { 0, 0, 128, 128 }, dinofeatdest = { 50, 50, 128, 128 };
				for (auto d : dinos) {
					//std::cout << d.size() << std::endl;
					switch (d.type) {
					case 1:
						//std::cout << "rr";
						SDL_RenderCopy(game->renderer, dinostr, &dinofeatsrc, &dinofeatdest);
						break;
					case 2:
						//std::cout << "rr";
						SDL_RenderCopy(game->renderer, dinodex, &dinofeatsrc, &dinofeatdest);
						break;
					case 3:
						//std::cout << "rr";
						SDL_RenderCopy(game->renderer, dinoint, &dinofeatsrc, &dinofeatdest);
						break;
					default:
						//std::cout << d[0] << std::endl;
						break;
					}
					featdest.w = int(128 * (d.str / 10.0));
					featdest.x = dinofeatdest.x;
					featdest.y = dinofeatdest.y + 140;
					SDL_RenderCopy(game->renderer, strt, &featsrc, &featdest);
					featdest.y += 20;
					featdest.w = int(128 * (d.dex / 10.0));
					SDL_RenderCopy(game->renderer, intet, &featsrc, &featdest);
					featdest.y += 20;
					featdest.w = int(128 * (d.inte / 10.0));
					SDL_RenderCopy(game->renderer, dext, &featsrc, &featdest);
					dinofeatdest.x += 220;
					if (dinofeatdest.x > 550) {
						dinofeatdest.y += 220;
						dinofeatdest.x = 50;
					}
				}
				if (back) {
					SDL_RenderCopy(game->renderer, backba, &src, &dest);
				}
				else {
					SDL_RenderCopy(game->renderer, backb, &src, &dest);
				}

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						std::ofstream out;
						out.open("game.txt");
						out << balance << std::endl;
						for (auto v : dinos) {
							out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
						}
						out.close();
						game->clean();
						return 0;
					}
					if (event.type == SDL_MOUSEMOTION) {
						SDL_GetMouseState(&rect.x, &rect.y);
						std::cout << rect.x << " " << rect.y << std::endl;
						if (rect.y >= 524 && rect.y <= 590 && rect.x >= 58 && rect.x <= 118) {
							back = true;
						}
						else {
							back = false;
						}
					}
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						if (back) {
							SDL_RenderClear(game->renderer);
							back = false;
							collection = false;
							choose = true;
							break;
						}

					}
				}

			}

			if (shop) {

				if (shopdino.size() == 0) {
					shopdino.push_back(rand()%3+1);
					shopdino.push_back(rand() % 10 + 1);
					shopdino.push_back(rand() % 10 + 1);
					shopdino.push_back(rand() % 10 + 1);
				}

				switch (shopdino[0]) {
				case 1:
					if (shopact = false) {
						SDL_RenderCopy(game->renderer, dinostr, &dinofeatsrc, &shopdest);
					}
					else {
						//std::cout << "ddddd";
						SDL_RenderCopy(game->renderer, dinostr, &dinofeatsrc, &shopdest);
					}
					break;
				case 2:
					if (shopact = false) {
						SDL_RenderCopy(game->renderer, dinodex, &dinofeatsrc, &shopdest);
					}
					else {
						//std::cout << "ddddd";
						SDL_RenderCopy(game->renderer, dinodex, &dinofeatsrc, &shopdest);
					}
					break;
				case 3:
					if (shopact = false) {
						SDL_RenderCopy(game->renderer, dinoint, &dinofeatsrc, &shopdest);
					}
					else {
						//std::cout << "ddddd";
						SDL_RenderCopy(game->renderer, dinoint, &dinofeatsrc, &shopdest);
					}
					break;
				default:
					//std::cout << d[0] << std::endl;
					break;
				}
				
				shopchardest.y = 400;
				shopchardest.w = int(256 * (shopdino[1] / 10.0));
				SDL_RenderCopy(game->renderer, strt, &charsrc, &shopchardest);
				shopchardest.y += 50;
				shopchardest.w = int(256 * (shopdino[2] / 10.0));
				SDL_RenderCopy(game->renderer, dext, &charsrc, &shopchardest);
				shopchardest.y += 50;
				shopchardest.w = int(256 * (shopdino[3] / 10.0));
				SDL_RenderCopy(game->renderer, intet, &charsrc, &shopchardest);

				if (back) {
					SDL_RenderCopy(game->renderer, backba, &src, &dest);
				}
				else {
					SDL_RenderCopy(game->renderer, backb, &src, &dest);
				}

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						std::ofstream out;
						out.open("game.txt");
						out << balance << std::endl;
						for (auto v : dinos) {
							out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
						}
						out.close();
						game->clean();
						return 0;
					}
					if (event.type == SDL_MOUSEMOTION) {
						SDL_GetMouseState(&rect.x, &rect.y);
						std::cout << rect.x << " " << rect.y << std::endl;
						if (rect.y >= 524 && rect.y <= 590 && rect.x >= 58 && rect.x <= 118) {
							back = true;
						}
						else {
							back = false;
						}

						if (rect.y >= 100 && rect.y <= 356 && rect.x >= 250 && rect.x <= 506) {
							shopact = true;
							//std::cout << "r";
						}
						else {
							shopact = false;
						}
					}
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						if (back) {
							SDL_RenderClear(game->renderer);
							back = false;
							shop = false;
							choose = true;
							break;
						}
						if (!shopact) {
							if (balance > 0) {

								Dino dino (shopdino[1], shopdino[2], shopdino[3]);
								dino.type = shopdino[0];
								shopdino.clear();
								balance -= 1;
							}
						}
					}
				}

			}

			if (battle) {

				featsrc = { 0, 0, 4, 4 }, featdest = { 0, 0, 128, 20 };
				dinofeatsrc = { 0, 0, 128, 128 }, dinofeatdest = { 50, 50, 128, 128 };
				for (int i = 0; i < dinos.size(); i++) {
					//std::cout << d.size() << std::endl;
					
					
					switch (dinos[i].type) {
					case 1:
						if (dinochoose.at(i) >= 3) {
							SDL_RenderCopy(game->renderer, dinostra, &dinofeatsrc, &dinofeatdest);
						}
						else {
							SDL_RenderCopy(game->renderer, dinostr, &dinofeatsrc, &dinofeatdest);
						}
						break;
					case 2:
						if (dinochoose.at(i) >= 3) {
							SDL_RenderCopy(game->renderer, dinodexa, &dinofeatsrc, &dinofeatdest);
						}
						else {
							SDL_RenderCopy(game->renderer, dinodex, &dinofeatsrc, &dinofeatdest);
						}
						break;
					case 3:
						if (dinochoose.at(i) >= 3) {
							SDL_RenderCopy(game->renderer, dinointa, &dinofeatsrc, &dinofeatdest);
						}
						else {
							SDL_RenderCopy(game->renderer, dinoint, &dinofeatsrc, &dinofeatdest);
						}
						break;
					default:
						//std::cout << d[0] << std::endl;
						break;
					}
					featdest.w = int(128 * (dinos[i].str / 10.0));
					featdest.x = dinofeatdest.x;
					featdest.y = dinofeatdest.y + 140;
					SDL_RenderCopy(game->renderer, strt, &featsrc, &featdest);
					featdest.y += 20;
					featdest.w = int(128 * (dinos[i].dex / 10.0));
					SDL_RenderCopy(game->renderer, intet, &featsrc, &featdest);
					featdest.y += 20;
					featdest.w = int(128 * (dinos[i].inte / 10.0));
					SDL_RenderCopy(game->renderer, dext, &featsrc, &featdest);
					dinofeatdest.x += 220;
					if (dinofeatdest.x > 550) {
						dinofeatdest.y += 220;
						dinofeatdest.x = 50;
					}
				}
				if (back) {
					SDL_RenderCopy(game->renderer, backba, &src, &dest);
				}
				else {
					SDL_RenderCopy(game->renderer, backb, &src, &dest);
				}
				if (go) {
					SDL_RenderCopy(game->renderer, goba, &src, &dest);
				}
				else {
					SDL_RenderCopy(game->renderer, gob, &src, &dest);
				}

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						std::ofstream out;
						out.open("game.txt");
						out << balance << std::endl;
						for (auto v : dinos) {
							out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
						}
						out.close();
						game->clean();
						return 0;
					}
					if (event.type == SDL_MOUSEMOTION) {
						SDL_GetMouseState(&rect.x, &rect.y);
						std::cout << rect.x << " " << rect.y << std::endl;
						if (rect.y >= 524 && rect.y <= 590) {
							if (rect.x >= 58 && rect.x <= 118) {
								back = true;
								go = true;
							}
							else if (rect.x >= 680 && rect.x <= 742) {
								go = true;
								back = false;
							}
						}
						else {
							back = false;
							go = false;
						}

						if (rect.y >= 50 && rect.y <= 177) {

							if (rect.x >= 50 && rect.x <= 177) {

								for (auto d : dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(0) < 3) {
									dinochoose.at(0) = 2;
									//std::cout << dinochoose.at(0);
								}
								if (dinochoose.at(0) == 3) {
									dinochoose.at(0) = 4;
								}
							}
							else {
								if (dinochoose.at(0) >= 3) {
									dinochoose.at(0) = 3;
								}
								else if (dinochoose.at(0) <= 2) {
									dinochoose.at(0) = 1;
								}
							}
							if (rect.x >= 270 && rect.x <= 397) {
								for (auto d : dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(1) < 3) {
									dinochoose.at(1) = 2;
								}
								if (dinochoose.at(1) == 3) {
									dinochoose.at(1) = 4;
								}
							}
							else {
								if (dinochoose.at(1) >= 3) {
									dinochoose.at(1) = 3;
								}
								else if (dinochoose.at(1) <= 2) {
									dinochoose.at(1) = 1;
								}
							}
							if (rect.x >= 490 && rect.x <= 617) {
								for (auto d : dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(2) < 3) {
									dinochoose.at(2) = 2;
								}
								if (dinochoose.at(2) == 3) {
									dinochoose.at(2) = 4;
								}
							}
							else {
								if (dinochoose.at(2) >= 3) {
									dinochoose.at(2) = 3;
								}
								else if (dinochoose.at(2) <= 2) {
									dinochoose.at(2) = 1;
								}
							}
						}
						else if (rect.y >= 270 && rect.y <= 400) {

							if (rect.x >= 50 && rect.x <= 177) {
								for (auto d: dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(3) < 3) {
									dinochoose.at(3) = 2;
								}
								if (dinochoose.at(3) == 3) {
									dinochoose.at(3) = 4;
								}
							}
							else {
								if (dinochoose.at(3) >= 3) {
									dinochoose.at(3) = 3;
								}
								else if (dinochoose.at(3) <= 2) {
									dinochoose.at(3) = 1;
								}
							}
							if (rect.x >= 270 && rect.x <= 397) {
								for (auto d : dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(4) < 3) {
									dinochoose.at(4) = 2;
								}
								if (dinochoose.at(4) == 3) {
									dinochoose.at(4) = 4;
								}
							}
							else {
								if (dinochoose.at(4) >= 3) {
									dinochoose.at(4) = 3;
								}
								else if (dinochoose.at(4) <= 2) {
									dinochoose.at(4) = 1;
								}
							}
							if (rect.x >= 490 && rect.x <= 617) {
								for (auto d : dinochoose) {
									if (d < 3) {
										d = 1;
									}
									if (d == 4) {
										d = 3;
									}
								}
								if (dinochoose.at(5) < 3) {
									dinochoose.at(5) = 2;
								}
								if (dinochoose.at(5) == 3) {
									dinochoose.at(5) = 4;
								}
							}
							else {
								if (dinochoose.at(5) >= 3) {
									dinochoose.at(5) = 3;
								}
								else if (dinochoose.at(5) <= 2) {
									dinochoose.at(5) = 1;
								}
							}
						}
						else {
							for (auto d : dinochoose) {
								if (d < 3) {
									d = 1;
								}
								if (d == 4) {
									d = 3;
								}
							}
						}

					}
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						if (back) {
							SDL_RenderClear(game->renderer);
							back = false;
							go = false;
							battle = false;
							choose = true;
							break;
						}
						if (go) {
							sum = 0;

							for (auto d : dinochoose) {
								if (d == 4) {
									d = 3;
								}
								if (d == 2) {
									d = 1;
								}
								sum += d;
							}
							std::cout << sum << std::endl;
							if (sum > 10) {
								for (int i = 0; i < dinochoose.size(); i++) {
									if (dinochoose.at(i) == 3) {
										Dino dino(dinos[0].str, dinos[0].dex, dinos[0].inte);
										dino.type = dinos[0].type;
										yourpull.push_back(dino);
										temp.clear();
										temp.push_back(rand() % 3 + 1);
										temp.push_back(100);
										temp.push_back(rand() % 9 + 1);
										temp.push_back(rand() % 9 + 1);
										temp.push_back(rand() % 9 + 1);
										temp.push_back(1);

										Dino dinoa(temp[2], temp[3], temp[4]);
										dinoa.type = temp[0];
										enemypull.push_back(dino);

									}
								}
								SDL_RenderClear(game->renderer);
								back = false;
								go = false;
								battle = false;
								start = true;
								flag = false;
							}
							break;
						}
						for (int i = 0; i < dinochoose.size(); i++) {
							if (dinochoose.at(i) == 2) {
								//std::cout << "eth";
								dinochoose.at(i) = 3;
							}
							else if (dinochoose.at(i) == 4) {
								//std::cout << "t";
								dinochoose.at(i) = 1;
							}
						}
					}
				}

			}
			if (start) {

				SDL_RenderClear(game->renderer);

				if (!flag) {
					place = rand() % 3 + 1;
					flag = true;
					std::cout << "enemypull " << enemypull.size();
					std::cout << "yourpull " << yourpull.size();
				}
				if (place == 1) {
					SDL_RenderCopy(game->renderer, place1, &src, &dest);
					//SDL_RenderCopy(game->renderer, place1, &src, &dest);
				}
				if (place == 2) {
					//std::cout << place;
					SDL_RenderCopy(game->renderer, place2, &src, &dest);
					//SDL_RenderCopy(game->renderer, place2, &src, &dest);
				}
				if (place == 3) {
					SDL_RenderCopy(game->renderer, place3, &src, &dest);
					//SDL_RenderCopy(game->renderer, place3, &src, &dest);
				}
				
				
				if (yourpull.size() != 0 && enemypull.size() != 0) {
					switch (yourpull[0].type) {
					case 1:
						if (yourpull[0].status==1) {
							SDL_RenderCopy(game->renderer, dinostrb, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinostrba, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinostrbda, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 4) {
							std::cout << "die";
							SDL_RenderCopy(game->renderer, dinostrbd, &dinosrc, &yourdinodest);
							Sleep(1000);
						}
						break;
					case 2:
						if (yourpull[0].status == 1) {
							SDL_RenderCopy(game->renderer, dinodexb, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinodexba, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinodexbda, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 4) {
							std::cout << "die";
							SDL_RenderCopy(game->renderer, dinodexbd, &dinosrc, &yourdinodest);
							Sleep(1000);
						}
						break;
					case 3:
						if (yourpull[0].status == 1) {
							SDL_RenderCopy(game->renderer, dinointb, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinointba, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinointbda, &dinosrc, &yourdinodest);
						}
						else if (yourpull[0].status == 4) {
							std::cout << "die";
							SDL_RenderCopy(game->renderer, dinointbd, &dinosrc, &yourdinodest);
						}
						break;
					default:
						break;
					}
					chardest.x = 50;
					chardest.y = 300;
					yhpdest.w = int(256 * (yourpull[0].hp / 100.0));
					SDL_RenderCopy(game->renderer, hpt, &charsrc, &yhpdest);
					chardest.y += 40;
					chardest.w = int(256 * (yourpull[0].str / 10.0));
					SDL_RenderCopy(game->renderer, strt, &charsrc, &chardest);
					chardest.y += 40;
					chardest.w = int(256 * (yourpull[0].dex / 10.0));
					SDL_RenderCopy(game->renderer, dext, &charsrc, &chardest);
					chardest.y += 40;
					chardest.w = int(256 * (yourpull[0].inte / 10.0));
					SDL_RenderCopy(game->renderer, intet, &charsrc, &chardest);
					switch (enemypull[0].type) {
					case 1:
						if (enemypull[0].status == 1) {
							SDL_RenderCopy(game->renderer, dinostrb, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinostrba, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinostrbda, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 4) {
							SDL_RenderCopy(game->renderer, dinostrbd, &dinosrc, &enemydinodest);
						}
						break;
					case 2:
						if (enemypull[0].status == 1) {
							SDL_RenderCopy(game->renderer, dinodexb, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinodexba, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinodexbda, &dinosrc, &enemydinodest);
						}
						else if (enemypull[0].status == 4) {
							SDL_RenderCopy(game->renderer, dinodexbd, &dinosrc, &enemydinodest);
						}
						break;
					case 3:
						if (enemypull[0].status == 1) {
							SDL_RenderCopy(game->renderer, dinointb, &dinosrc, &enemydinodest);
						}
						if (enemypull[0].status == 2) {
							SDL_RenderCopy(game->renderer, dinointba, &dinosrc, &enemydinodest);
						}
						if (enemypull[0].status == 3) {
							SDL_RenderCopy(game->renderer, dinointbda, &dinosrc, &enemydinodest);
						}
						if (enemypull[0].status == 4) {
							SDL_RenderCopy(game->renderer, dinointbd, &dinosrc, &enemydinodest);
						}
						break;
					default:
						break;
					}
					chardest.x = 400;
					chardest.y = 300;
					ehpdest.w = int(256 * (enemypull[0].hp / 100.0));
					SDL_RenderCopy(game->renderer, hpt, &charsrc, &ehpdest);
					chardest.y += 40;
					chardest.w = int(256 * (enemypull[0].str / 10.0));
					SDL_RenderCopy(game->renderer, strt, &charsrc, &chardest);
					chardest.y += 40;
					chardest.w = int(256 * (enemypull[0].dex / 10.0));
					SDL_RenderCopy(game->renderer, dext, &charsrc, &chardest);
					chardest.y += 40;
					chardest.w = int(256 * (enemypull[0].inte / 10.0));
					SDL_RenderCopy(game->renderer, intet, &charsrc, &chardest);
				}
				else {
					choose = true;
					battle = false;
					start = false;
					yourpull.clear();
					enemypull.clear();
				}
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						std::ofstream out;
						out.open("game.txt");
						out << balance << std::endl;
						for (auto v : dinos) {
							out << v.type << std::endl << v.str << std::endl << v.dex << std::endl << v.inte << std::endl;
						}
						out.close();
						game->clean();
						return 0;
					}
					if (event.type == SDL_MOUSEBUTTONDOWN) {

						//SDL_Delay(300);
						if (you) {
							//std::cout << "y";
							yourpull[0].status = 2;
							enemypull[0].status = 3;

							if (yourpull[0].type == place) {
								th = 2;
							}
							else {
								th = 1;
							}

							switch (place) {
							case 1:
								enemypull[0].hp -= yourpull[0].str * th;
								break;
							case 2:
								enemypull[0].hp -= yourpull[0].dex * th;
								break;
							case 3:
								enemypull[0].hp -= yourpull[0].inte * th;
								break;
							default:
								break;
							}
							

							you = false;

							if (enemypull[0].hp <= 0) {

								time = SDL_GetTicks();

								while (SDL_GetTicks() - time < 1000) {
									
									SDL_RenderClear(game->renderer);

									switch (enemypull[0].type) {
									case 1:
										
										SDL_RenderCopy(game->renderer, dinostrbd, &dinosrc, &enemydinodest);
										
										break;
									case 2:
										
										SDL_RenderCopy(game->renderer, dinodexbd, &dinosrc, &enemydinodest);
										
										break;
									case 3:
										
										SDL_RenderCopy(game->renderer, dinointbd, &dinosrc, &enemydinodest);
										
										break;
									default:
										break;
									}
									SDL_RenderPresent(game->renderer);

								}
							

								

								enemypull.erase(enemypull.begin());
								if (enemypull.size() == 0) {
									balance += 1;
									std::cout << balance;
									choose = true;
									battle = false;
									start = false;
									yourpull.clear();
									enemypull.clear();
									break;
								}
							}

							SDL_Delay(100);
						}
						else {
							//std::cout << "e";
							yourpull[0].status = 3;
							enemypull[0].status = 2;
							you = true;

							if (enemypull[0].type == place) {
								th = 2;
							}
							else {
								th = 1;
							}

							switch (place) {
							case 1:
								yourpull[0].hp -= enemypull[0].str * th;
								break;
							case 2:
								yourpull[0].hp -= enemypull[0].dex * th;
								break;
							case 3:
								yourpull[0].hp -= enemypull[0].inte * th;
								break;
							default:
								break;
							}

							if (yourpull[0].hp <= 0) {

								time = SDL_GetTicks();

								while (SDL_GetTicks() - time < 1000) {

									SDL_RenderClear(game->renderer);

									switch (yourpull[0].type) {
									case 1:

										SDL_RenderCopy(game->renderer, dinostrbd, &dinosrc, &yourdinodest);

										break;
									case 2:

										SDL_RenderCopy(game->renderer, dinodexbd, &dinosrc, &yourdinodest);

										break;
									case 3:

										SDL_RenderCopy(game->renderer, dinointbd, &dinosrc, &yourdinodest);

										break;
									default:
										break;
									}
									SDL_RenderPresent(game->renderer);

								}
								yourpull.erase(yourpull.begin());
							}
							if (yourpull.size() == 0) {
								choose = true;
								battle = false;
								start = false;
								yourpull.clear();
								enemypull.clear();
								break;
							}

							SDL_Delay(100);
							
						}
					}
					else {
						yourpull[0].status = 1;
						enemypull[0].status = 1;
					}
				}

			}

			/*while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					game->clean();
					return 0;
				}
				if (event.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&rect.x, &rect.y);
					std::cout << rect.x << " " << rect.y << std::endl;
					if (rect.y >= 524 && rect.y <= 590) {
						if (rect.x >= 50 && rect.x <= 118) {
							back = true;
						}
						if (rect.x >= 500 && rect.x <= 550) {
							go = true;
						}
					}
					if (rect.y >= 50 && rect.y <= 176) {
						if (rect.x >= 50 && rect.x <= 177) {

						}
						if (rect.x >= 270 && rect.x <= 397) {

						}
						if (rect.x >= 490 && rect.x <= 617) {

						}
						back = false;
						go = false;
					}
					else if (rect.y >= 270 && rect.y <= 400) {
						if (rect.x >= 50 && rect.x <= 177) {

						}
						if (rect.x >= 270 && rect.x <= 397) {

						}
						if (rect.x >= 490 && rect.x <= 617) {

						}
						back = false;
						go = false;
					}
					else {
						for (auto i : dinochoose) {

						}
						back = false;
						go = false;
					}
					for (auto i : dinochoose) {

					}
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (back) {
						SDL_RenderClear(game->renderer);
						back = false;
						go = false;
						battle = false;
						choose = true;
						break;
					}
					if (go) {
						//SDL_RenderClear(game->renderer);
						back = false;
						go = false;
						battle = false;
						choose = true;
						break;
					}
					for (auto i : dinochoose) {

					}

				}
			}
			featsrc = { 0, 0, 4, 4 }, featdest = { 0, 0, 128, 20 };
			dinofeatsrc = { 0, 0, 128, 128 }, dinofeatdest = { 50, 50, 128, 128 };
			for (int i = 0; i < dinos.size(); i++) {
				switch (dinos[i][0]) {
				case 1:
					if (dinochoose.at(i) == 3) {
						SDL_RenderCopy(game->renderer, dinostra, &dinofeatsrc, &dinofeatdest);
					}
					else {
						SDL_RenderCopy(game->renderer, dinostr, &dinofeatsrc, &dinofeatdest);
					}
					break;
				case 2:
					if (dinochoose.at(i) == 3) {
						SDL_RenderCopy(game->renderer, dinodexa, &dinofeatsrc, &dinofeatdest);
					}
					else {
						SDL_RenderCopy(game->renderer, dinodex, &dinofeatsrc, &dinofeatdest);
					}
					break;
				case 3:
					if (dinochoose.at(i) == 3) {
						SDL_RenderCopy(game->renderer, dinointa, &dinofeatsrc, &dinofeatdest);
					}
					else {
						SDL_RenderCopy(game->renderer, dinoint, &dinofeatsrc, &dinofeatdest);
					}
					break;
				default:
					break;
				}
				featdest.w = int(128 * (dinos[i][1] / 10.0));
				featdest.x = dinofeatdest.x;
				featdest.y = dinofeatdest.y + 140;
				SDL_RenderCopy(game->renderer, strt, &featsrc, &featdest);
				featdest.y += 20;
				featdest.w = int(128 * (dinos[i][2] / 10.0));
				SDL_RenderCopy(game->renderer, intet, &featsrc, &featdest);
				featdest.y += 20;
				featdest.w = int(128 * (dinos[i][3] / 10.0));
				SDL_RenderCopy(game->renderer, dext, &featsrc, &featdest);
				dinofeatdest.x += 220;
				if (dinofeatdest.x > 550) {
					dinofeatdest.y += 220;
					dinofeatdest.x = 50;
				}
			}
			if (back) {
				SDL_RenderCopy(game->renderer, backba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, backb, &src, &dest);
			}
			if (go) {
				SDL_RenderCopy(game->renderer, goba, &src, &dest);
			}
			else {
				SDL_RenderCopy(game->renderer, gob, &src, &dest);
			}

		}*/

			
			SDL_RenderPresent(game->renderer);

			/*while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					game->clean();
					return 0;
				}
				if (event.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&rect.x, &rect.y);
					std::cout << rect.x << " " << rect.y << std::endl;
					if (rect.y >= 528 && rect.y <= 623) {
						if (rect.x >= 432 && rect.x <= 527) {

						}
					}
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {


				}
			}*/
		}
	}
}