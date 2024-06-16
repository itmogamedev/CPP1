#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include "dino.h"
#include "inventory.h"

class Game {
public:
	sf::RenderWindow window = { sf::VideoMode(1920, 1080), "Dino", sf::Style::Fullscreen };
	sf::Vector2i mouse_p;
	sf::Texture fon;
	sf::Font font;
	Inventory inventory;
	Rex rex;
	Raptor raptor;
	Tricer tricer;
	sf::Texture empty;
	
	int main() {
		//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dino", sf::Style::Fullscreen);

		empty.loadFromFile("image/empty.png");
		
		fon.loadFromFile("image/fon.jpg");
		
		sf::Sprite phon;
		phon.setTexture(fon);

		
		font.loadFromFile("font.ttf");

		sf::Text exit_text("Выход", font, 70);
		exit_text.setPosition(75, 720);

		sf::Text new_game_text("Новая игра", font, 70);
		new_game_text.setPosition(75, 220);

		sf::Text play_text("Загрузить игру", font, 70);
		play_text.setPosition(75, 470);

		sf::RectangleShape new_game_button(sf::Vector2f(400, 150));
		new_game_button.setFillColor(sf::Color::Green);
		new_game_button.setPosition(75, 200);

		sf::RectangleShape play_button(sf::Vector2f(550, 150));
		play_button.setFillColor(sf::Color::Blue);
		play_button.setPosition(75, 450);

		sf::RectangleShape exit_button(sf::Vector2f(300, 150));
		exit_button.setFillColor(sf::Color::Red);
		exit_button.setPosition(75, 700);

		
		

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			mouse_p = sf::Mouse::getPosition(window);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				Save();
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and new_game_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (new_game_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and new_game_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						newGame();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and play_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (play_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and play_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						Load();
						Play();
						break;
					}
				}
			}

			window.clear();

			window.draw(phon);
			//window.draw(exit_button);
			//window.draw(new_game_button);
			//window.draw(play_button);
			window.draw(exit_text);
			window.draw(new_game_text);
			window.draw(play_text);

			window.display();

		}

		return 0;
	}

	void newGame() {
		Save();
		Play();
	}

	void Play() {

		
		fon.loadFromFile("image/fon.jpg");

		font.loadFromFile("font.ttf");

		sf::RectangleShape exit_button(sf::Vector2f(500, 150));
		exit_button.setFillColor(sf::Color::Red);
		exit_button.setPosition(75, 700);

		sf::RectangleShape fight_button(sf::Vector2f(300, 150));
		fight_button.setFillColor(sf::Color::Black);
		fight_button.setPosition(75, 200);

		sf::RectangleShape shop_button(sf::Vector2f(350, 150));
		shop_button.setFillColor(sf::Color::Yellow);
		shop_button.setPosition(75, 450);

		sf::Text exit_text("Выйти в меню", font, 70);
		exit_text.setPosition(75, 720);

		sf::Text fight_text("Бой", font, 70);
		fight_text.setPosition(75, 220);

		sf::Text shop_text("Магазин", font, 70);
		shop_text.setPosition(75, 470);

		sf::Text your_dino_text("Ваши динозавры:", font, 70);
		your_dino_text.setPosition(1300, 100);


		sf::Sprite phon;
		phon.setTexture(fon);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			mouse_p = sf::Mouse::getPosition(window);
			///
			sf::Sprite sprite_rex = rex.getSprite();
			sprite_rex.setPosition(1300, 200);
			sf::Text text_rex("X" + std::to_string(inventory.getRex()), font, 70);
			text_rex.setPosition(1600, 250);

			sf::Sprite sprite_raptor = raptor.getSprite();
			sprite_raptor.setPosition(1300, 500);
			sf::Text text_raptor("X" + std::to_string(inventory.getRaptor()), font, 70);
			text_raptor.setPosition(1600, 550);

			sf::Sprite sprite_tricer = tricer.getSprite();
			sprite_tricer.setPosition(1300, 800);
			sf::Text text_tricer("X" + std::to_string(inventory.getTricer()), font, 70);
			text_tricer.setPosition(1600, 850);
			///
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						return;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and shop_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (shop_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and shop_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						Shop();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						fight_menu();
						break;
					}
				}
			}



			
			window.clear();
			window.draw(phon);
			//window.draw(exit_button);
			//window.draw(fight_button);
			//window.draw(shop_button);
			window.draw(your_dino_text);
			window.draw(fight_text);
			window.draw(shop_text);
			window.draw(exit_text);
			window.draw(sprite_rex);
			window.draw(sprite_raptor);
			window.draw(sprite_tricer);
			window.draw(text_rex);
			window.draw(text_raptor);
			window.draw(text_tricer);
			window.display();

			
			
			
			
		}

		
	}

	void Shop() {
		fon.loadFromFile("image/fon.jpg");

		font.loadFromFile("font.ttf");

		sf::Sprite phon;
		phon.setTexture(fon);

		sf::RectangleShape exit_button(sf::Vector2f(500, 150));
		exit_button.setFillColor(sf::Color::Blue);
		exit_button.setPosition(75, 700);

		sf::RectangleShape buy_rex_button(sf::Vector2f(600, 200));
		buy_rex_button.setFillColor(sf::Color::Blue);
		buy_rex_button.setPosition(1300, 200);

		sf::RectangleShape buy_raptor_button(sf::Vector2f(600, 200));
		buy_raptor_button.setFillColor(sf::Color::Blue);
		buy_raptor_button.setPosition(1300, 500);

		sf::RectangleShape buy_tricer_button(sf::Vector2f(600, 200));
		buy_tricer_button.setFillColor(sf::Color::Blue);
		buy_tricer_button.setPosition(1300, 800);


		sf::Text buy_text("Купить:", font, 70);
		buy_text.setPosition(1500, 50);

		sf::Text sotka1("100 золотых", font, 70);
		sotka1.setPosition(1500, 240);
		sf::Text sotka2("100 золотых", font, 70);
		sotka2.setPosition(1500, 540);
		sf::Text sotka3("100 золотых", font, 70);
		sotka3.setPosition(1500, 840);

		sf::Sprite shop_rex = rex.getSprite();
		shop_rex.setPosition(1300, 200);
		sf::Sprite shop_raptor = raptor.getSprite();
		shop_raptor.setPosition(1300, 500);
		sf::Sprite shop_tricer = tricer.getSprite();
		shop_tricer.setPosition(1300, 800);

		sf::Text exit_text("Выйти в меню", font, 70);
		exit_text.setPosition(75, 720);



		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			mouse_p = sf::Mouse::getPosition(window);

			sf::Text your_gold_text("Ваше золото: " + std::to_string(inventory.getGold()), font, 70);
			your_gold_text.setPosition(50, 50);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						return;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (buy_rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						inventory.shop_rex();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (buy_raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						inventory.shop_raptor();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (buy_tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and buy_tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						inventory.shop_tricer();
						break;
					}
				}
			}

			window.clear();
			window.draw(phon);
			window.draw(your_gold_text);
			window.draw(buy_text);
			window.draw(shop_rex);
			window.draw(shop_raptor);
			window.draw(shop_tricer);
			window.draw(sotka1);
			window.draw(sotka2);
			window.draw(sotka3);
			window.draw(exit_text);
			window.display();
		}
	}

	void fight_menu() {

		sf::Sprite phon;
		phon.setTexture(fon);

		sf::Sprite fight_rex = rex.getSprite();
		fight_rex.setPosition(1500, 200);
		sf::Sprite fight_raptor = raptor.getSprite();
		fight_raptor.setPosition(1500, 500);
		sf::Sprite fight_tricer = tricer.getSprite();
		fight_tricer.setPosition(1500, 800);


		sf::Text exit_text("Выйти в меню", font, 70);
		exit_text.setPosition(75, 720);


		

		sf::RectangleShape cell1(sf::Vector2f(200, 200));
		cell1.setFillColor(sf::Color::Transparent);
		cell1.setPosition(600, 200);
		cell1.setOutlineThickness(20);
		cell1.setOutlineColor(sf::Color::Red);

		sf::RectangleShape cell2(sf::Vector2f(200, 200));
		cell2.setFillColor(sf::Color::Transparent);
		cell2.setPosition(900, 200);
		cell2.setOutlineThickness(20);
		cell2.setOutlineColor(sf::Color::Red);

		sf::RectangleShape cell3(sf::Vector2f(200, 200));
		cell3.setFillColor(sf::Color::Transparent);
		cell3.setPosition(1200, 200);
		cell3.setOutlineThickness(20);
		cell3.setOutlineColor(sf::Color::Red);

		sf::RectangleShape exit_button(sf::Vector2f(500, 150));
		exit_button.setFillColor(sf::Color::Red);
		exit_button.setPosition(75, 700);

		sf::RectangleShape fight_button(sf::Vector2f(450, 150));
		fight_button.setFillColor(sf::Color::Black);
		fight_button.setPosition(75, 150);

		sf::Text fight_text("Начать битву", font, 70);
		fight_text.setPosition(75, 150);
		fight_text.setFillColor(sf::Color(127,127,127));

		sf::Text dino_for_fight_text("Выберите динозавров для боя:", font, 70);
		dino_for_fight_text.setPosition(550, 50);

		sf::RectangleShape rex_button(sf::Vector2f(200, 200));
		rex_button.setFillColor(sf::Color::Red);
		rex_button.setPosition(1500, 200);

		sf::RectangleShape raptor_button(sf::Vector2f(200, 200));
		raptor_button.setFillColor(sf::Color::Red);
		raptor_button.setPosition(1500, 500);

		sf::RectangleShape tricer_button(sf::Vector2f(200, 200));
		tricer_button.setFillColor(sf::Color::Red);
		tricer_button.setPosition(1500, 800);

		std::vector<int> vector = {0,0,0};

		sf::Sprite sp0;
		sf::Sprite sp1;
		sf::Sprite sp2;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			mouse_p = sf::Mouse::getPosition(window);


			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						for (int ip = 0; ip < 3; ip++) {
							if (vector[ip] == 1) {
								inventory.push_rex();
							}
							if (vector[ip] == 2) {
								inventory.push_raptor();
							}
							if (vector[ip] == 3) {
								inventory.push_tricer();
							}
						}
						return;
					}
				}
			} 

			
			/////////////////////////////////////////////////////////ДАЛЬШЕ БОГА НЕТ///////////////////////////////////////////////////////
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and inventory.getRex() > 0) {
				while (rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and rex_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[0] == 0) {
							inventory.pop_rex();
							sp0 = rex.getSprite();
							cell1.setOutlineColor(sf::Color::Green);
							vector[0] = 1;
							break;
						}
						if (vector[1] == 0) {
							inventory.pop_rex();
							sp1 = rex.getSprite();
							cell2.setOutlineColor(sf::Color::Green);
							vector[1] = 1;
							break;
						}
						if (vector[2] == 0) {
							inventory.pop_rex();
							sp2 = rex.getSprite();
							cell3.setOutlineColor(sf::Color::Green);
							vector[2] = 1;
							break;
						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and inventory.getRaptor() > 0) {
				while (raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and raptor_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[0] == 0) {
							inventory.pop_raptor();
							sp0 = raptor.getSprite();
							cell1.setOutlineColor(sf::Color::Green);
							vector[0] = 2;
							break;
						}
						if (vector[1] == 0) {
							inventory.pop_raptor();
							sp1 = raptor.getSprite();
							cell2.setOutlineColor(sf::Color::Green);
							vector[1] = 2;
							break;
						}
						if (vector[2] == 0) {
							inventory.pop_raptor();
							sp2 = raptor.getSprite();
							cell3.setOutlineColor(sf::Color::Green);
							vector[2] = 2;
							break;
						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and inventory.getTricer() > 0) {
				while (tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and tricer_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[0] == 0) {
							inventory.pop_tricer();
							sp0 = tricer.getSprite();
							cell1.setOutlineColor(sf::Color::Green);
							vector[0] = 3;
							break;
						}
						if (vector[1] == 0) {
							inventory.pop_tricer();
							sp1 = tricer.getSprite();
							cell2.setOutlineColor(sf::Color::Green);
							vector[1] = 3;
							break;
						}
						if (vector[2] == 0) {
							inventory.pop_tricer();
							sp2 = tricer.getSprite();
							cell3.setOutlineColor(sf::Color::Green);
							vector[2] = 3;
							break;
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (cell2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[1] == 1) {
							vector[1] = 0;
							sp1.setTexture(empty);
							inventory.push_rex();
							cell2.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[1] == 2) {
							vector[1] = 0;
							sp1.setTexture(empty);
							inventory.push_raptor();
							cell2.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[1] == 3) {
							vector[1] = 0;
							sp1.setTexture(empty);
							inventory.push_tricer();
							cell2.setOutlineColor(sf::Color::Red);
							break;
						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (cell3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[2] == 1) {
							vector[2] = 0;
							sp2.setTexture(empty);
							inventory.push_rex();
							cell3.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[2] == 2) {
							vector[2] = 0;
							sp2.setTexture(empty);
							inventory.push_raptor();
							cell3.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[2] == 3) {
							vector[2] = 0;
							sp2.setTexture(empty);
							inventory.push_tricer();
							cell3.setOutlineColor(sf::Color::Red);
							break;
						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (cell1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (vector[0] == 1) {
							vector[0] = 0;
							sp0.setTexture(empty);
							inventory.push_rex();
							cell1.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[0] == 2) {
							vector[0] = 0;
							sp0.setTexture(empty);
							inventory.push_raptor();
							cell1.setOutlineColor(sf::Color::Red);
							break;
						}
						if (vector[0] == 3) {
							vector[0] = 0;
							sp0.setTexture(empty);
							inventory.push_tricer();
							cell1.setOutlineColor(sf::Color::Red);
							break;
						}
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (vector[0] != 0 and vector[1] != 0 and vector[2] != 0) {
				fight_text.setFillColor(sf::Color::White);
			}
			else {
				fight_text.setFillColor(sf::Color(127,127,127));
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and vector[0] != 0 and vector[1] != 0 and vector[2] != 0) {
				while (fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and fight_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						Fight(vector);
					}
				}
			}


			sf::Text cout_rex_text(std::to_string(inventory.getRex()), font, 70);
			cout_rex_text.setPosition(1750, 240);
			sf::Text cout_raptor_text(std::to_string(inventory.getRaptor()), font, 70);
			cout_raptor_text.setPosition(1750, 540);
			sf::Text cout_tricer_text(std::to_string(inventory.getTricer()), font, 70);
			cout_tricer_text.setPosition(1750, 840);

			sp0.setPosition(600,200);
			sp1.setPosition(900, 200);
			sp2.setPosition(1200, 200);

			window.clear();
			window.draw(phon);
			window.draw(fight_text);
			window.draw(dino_for_fight_text);
			window.draw(cell1);
			window.draw(cell2);
			window.draw(cell3);
			window.draw(fight_rex);
			window.draw(fight_raptor);
			window.draw(fight_tricer);
			window.draw(cout_rex_text);
			window.draw(cout_raptor_text);
			window.draw(cout_tricer_text);
			window.draw(sp0);
			window.draw(sp1);
			window.draw(sp2);
			window.draw(exit_text);
			window.display();
		}

		
	}

	void Fight(std::vector<int> vector) {
		sf::Sprite phon;
		phon.setTexture(fon);

		std::string land;
		int m = rand() % 3;

		if (m == 0) {
			land = "равнина";
		}
		if (m == 1) {
			land = "река";
		}
		if (m == 2) {
			land = "горы";
		}

		sf::Text land_text("Местность: " + land, font, 70);
		land_text.setPosition(700, 100);

		sf::RectangleShape your_dino1(sf::Vector2f(200, 200));
		your_dino1.setFillColor(sf::Color::Transparent);
		your_dino1.setPosition(1500, 200);
		your_dino1.setOutlineThickness(20);
		your_dino1.setOutlineColor(sf::Color::Red);

		sf::RectangleShape your_dino2(sf::Vector2f(200, 200));
		your_dino2.setFillColor(sf::Color::Transparent);
		your_dino2.setPosition(1500, 500);
		your_dino2.setOutlineThickness(20);
		your_dino2.setOutlineColor(sf::Color::Red);

		sf::RectangleShape your_dino3(sf::Vector2f(200, 200));
		your_dino3.setFillColor(sf::Color::Transparent);
		your_dino3.setPosition(1500, 800);
		your_dino3.setOutlineThickness(20);
		your_dino3.setOutlineColor(sf::Color::Red);

		sf::RectangleShape enemies_dino1(sf::Vector2f(200, 200));
		enemies_dino1.setFillColor(sf::Color::Transparent);
		enemies_dino1.setPosition(200, 200);
		enemies_dino1.setOutlineThickness(20);
		enemies_dino1.setOutlineColor(sf::Color::Red);

		sf::RectangleShape enemies_dino2(sf::Vector2f(200, 200));
		enemies_dino2.setFillColor(sf::Color::Transparent);
		enemies_dino2.setPosition(200, 500);
		enemies_dino2.setOutlineThickness(20);
		enemies_dino2.setOutlineColor(sf::Color::Red);

		sf::RectangleShape enemies_dino3(sf::Vector2f(200, 200));
		enemies_dino3.setFillColor(sf::Color::Transparent);
		enemies_dino3.setPosition(200, 800);
		enemies_dino3.setOutlineThickness(20);
		enemies_dino3.setOutlineColor(sf::Color::Red);

		sf::Sprite sp0;
		sf::Sprite sp1;
		sf::Sprite sp2;
		sf::Sprite enemies0;
		sf::Sprite enemies1;
		sf::Sprite enemies2;
		std::vector<int> vector_enemies = {0,0,0};

		Dino* dino1 = &rex;
		Dino* dino2 = &rex;
		Dino* dino3 = &rex;
		Dino* E_dino1 = &rex;
		Dino* E_dino2 = &rex;
		Dino* E_dino3 = &rex;

		Rex rex1;
		Rex rex2;
		Rex rex3;
		Rex rex4;
		Rex rex5;
		Rex rex6;
		Raptor raptor1;
		Raptor raptor2;
		Raptor raptor3;
		Raptor raptor4;
		Raptor raptor5;
		Raptor raptor6;
		Tricer tricer1;
		Tricer tricer2;
		Tricer tricer3;
		Tricer tricer4;
		Tricer tricer5;
		Tricer tricer6;
		/////////////////////////////////////
		if (vector[0] == 1) {
			dino1 = &rex1;
			sp0 = rex.getSprite();
		}
		if (vector[0] == 2) {
			dino1 = &raptor1;
			sp0 = raptor.getSprite();
		}
		if (vector[0] == 3) {
			dino1 = &tricer1;
			sp0 = tricer.getSprite();
		}
		if (vector[1] == 1) {
			dino2 = &rex2;
			sp1 = rex.getSprite();
		}
		if (vector[1] == 2) {
			dino2 = &raptor2;
			sp1 = raptor.getSprite();
		}
		if (vector[1] == 3) {
			dino2 = &tricer2;
			sp1 = tricer.getSprite();
		}
		if (vector[2] == 1) {
			dino3 = &rex3;
			sp2 = rex.getSprite();
		}
		if (vector[2] == 2) {
			dino3 = &raptor3;
			sp2 = raptor.getSprite();
		}
		if (vector[2] == 3) {
			dino3 = &tricer3;
			sp2 = tricer.getSprite();
		}
		int r;
		r = rand() % 3;
		vector_enemies[0] = r + 1;
		if (r == 0) {
			E_dino1 = &rex4;
			enemies0 = rex.getSprite();
		}
		if (r == 1) {
			E_dino1 = &raptor4;
			enemies0 = raptor.getSprite();
		}
		if (r == 2) {
			E_dino1 = &tricer4;
			enemies0 = tricer.getSprite();
		}
		r = rand() % 3;
		vector_enemies[1] = r + 1;
		if (r == 0) {
			E_dino2 = &rex5;
			enemies1 = rex.getSprite();
		}
		if (r == 1) {
			E_dino2 = &raptor5;
			enemies1 = raptor.getSprite();
		}
		if (r == 2) {
			E_dino2 = &tricer5;
			enemies1 = tricer.getSprite();
		}
		r = rand() % 3;
		vector_enemies[2] = r + 1;
		if (r == 0) {
			E_dino3 = &rex6;
			enemies2 = rex.getSprite();
		}
		if (r == 1) {
			E_dino3 = &raptor6;
			enemies2 = raptor.getSprite();
		}
		if (r == 2) {
			E_dino3 = &tricer6;
			enemies2 = tricer.getSprite();
		}
		//////////////////////////////////////
		sp0.setPosition(1500, 200);
		sp1.setPosition(1500, 500);
		sp2.setPosition(1500, 800);
		enemies0.setPosition(200, 200);
		enemies1.setPosition(200, 500);
		enemies2.setPosition(200, 800);

		sf::Text dino1_HP(std::to_string(dino1->getHP()), font, 70);
		dino1_HP.setPosition(1750, 240);
		sf::Text dino2_HP(std::to_string(dino2->getHP()), font, 70);
		dino2_HP.setPosition(1750, 540);
		sf::Text dino3_HP(std::to_string(dino3->getHP()), font, 70);
		dino3_HP.setPosition(1750, 840);

		sf::Text E_dino1_HP(std::to_string(E_dino1->getHP()), font, 70);
		E_dino1_HP.setPosition(50, 240);
		sf::Text E_dino2_HP(std::to_string(E_dino2->getHP()), font, 70);
		E_dino2_HP.setPosition(50, 540);
		sf::Text E_dino3_HP(std::to_string(E_dino3->getHP()), font, 70);
		E_dino3_HP.setPosition(50, 840);

		int y1 = 0;
		int y2 = 0;
		int y3 = 0;

		int e1 = 0;
		int e2 = 0;
		int e3 = 0;

		int code = 0;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			mouse_p = sf::Mouse::getPosition(window);

			sf::Text dino1_HP(std::to_string(dino1->getHP()), font, 70);
			dino1_HP.setPosition(1750, 240);
			sf::Text dino2_HP(std::to_string(dino2->getHP()), font, 70);
			dino2_HP.setPosition(1750, 540);
			sf::Text dino3_HP(std::to_string(dino3->getHP()), font, 70);
			dino3_HP.setPosition(1750, 840);

			sf::Text E_dino1_HP(std::to_string(E_dino1->getHP()), font, 70);
			E_dino1_HP.setPosition(50, 240);
			sf::Text E_dino2_HP(std::to_string(E_dino2->getHP()), font, 70);
			E_dino2_HP.setPosition(50, 540);
			sf::Text E_dino3_HP(std::to_string(E_dino3->getHP()), font, 70);
			E_dino3_HP.setPosition(50, 840);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (your_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y1 == 0) {
							your_dino1.setOutlineColor(sf::Color::Yellow);
							if (y2 == 1) {
								y2 = 0;
							}
							if (y3 == 1) {
								y3 = 0;
							}
							y1 = 1;
							break;
						}
						if (y1 == 1) {
							
							y1 = 0;
							break;
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (your_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y2 == 0) {
							your_dino2.setOutlineColor(sf::Color::Yellow);
							if (y1 == 1) {
								y1 = 0;
							}
							if (y3 == 1) {
								y3 = 0;
							}
							y2 = 1;
							break;
						}
						if (y2 == 1) {
							
							y2 = 0;
							break;
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (your_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and your_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y3 == 0) {
							your_dino3.setOutlineColor(sf::Color::Yellow);
							if (y2 == 1) {
								y2 = 0;
							}
							if (y1 == 1) {
								y1 = 0;
							}
							y3 = 1;
							break;
						}
						if (y3 == 1) {
							
							y3 = 0;
							break;
						}
					}
				}
			}

			////ЦВЕТА ИКОНОК////
			if (y1 == 0) {
				your_dino1.setOutlineColor(sf::Color::Red);
			}
			if (y2 == 0) {
				your_dino2.setOutlineColor(sf::Color::Red);
			}
			if (y3 == 0) {
				your_dino3.setOutlineColor(sf::Color::Red);
			}
			if (y1 == 2) {
				your_dino1.setOutlineColor(sf::Color::Green);
			}
			if (y2 == 2) {
				your_dino2.setOutlineColor(sf::Color::Green);
			}
			if (y3 == 2) {
				your_dino3.setOutlineColor(sf::Color::Green);
			}
			if (y1 == -1) {
				your_dino1.setOutlineColor(sf::Color::Black);
			}
			if (y2 == -1) {
				your_dino2.setOutlineColor(sf::Color::Black);
			}
			if (y3 == -1) {
				your_dino3.setOutlineColor(sf::Color::Black);
			}
			if (e1 == -1) {
				enemies_dino1.setOutlineColor(sf::Color::Black);
			}
			if (e2 == -1) {
				enemies_dino2.setOutlineColor(sf::Color::Black);
			}
			if (e3 == -1) {
				enemies_dino3.setOutlineColor(sf::Color::Black);
			}
			/////////////////////////////////////////////////ИНДУСКИЙ КОД/////////////////////////////////////////////////////////////////
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and e1 != -1) {
				while (enemies_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino1.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y1 == 1) {
							int x = (enemies0.getPosition().x - sp0.getPosition().x) / 50;
							int y = (enemies0.getPosition().y - sp0.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp0.getPosition().x - enemies0.getPosition().x) {
								sp0.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino1->setHP(dino1->getDamage(m));
							if (E_dino1->getHP() <= 0) {
								e1 = -1;
								enemies_dino1.setOutlineColor(sf::Color::Black);
							}
							E_dino1_HP.setString(std::to_string(E_dino1->getHP()));
							while (move_x or move_y) {
								sp0.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y1 = 2;
							
						}
						if (y2 == 1) {
							int x = (enemies0.getPosition().x - sp1.getPosition().x) / 50;
							int y = (enemies0.getPosition().y - sp1.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp1.getPosition().x - enemies0.getPosition().x) {
								sp1.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino1->setHP(dino2->getDamage(m));
							if (E_dino1->getHP() <= 0) {
								e1 = -1;
								enemies_dino1.setOutlineColor(sf::Color::Black);
							}
							E_dino1_HP.setString(std::to_string(E_dino1->getHP()));
							while (move_x or move_y) {
								sp1.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y2 = 2;
							
						}
						if (y3 == 1) {
							int x = (enemies0.getPosition().x - sp2.getPosition().x) / 50;
							int y = (enemies0.getPosition().y - sp2.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp2.getPosition().x - enemies0.getPosition().x) {
								sp2.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino1->setHP(dino3->getDamage(m));
							if (E_dino1->getHP() <= 0) {
								e1 = -1;
								enemies_dino1.setOutlineColor(sf::Color::Black);
							}
							E_dino1_HP.setString(std::to_string(E_dino1->getHP()));
							while (move_x or move_y) {
								sp2.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y3 = 2;
							
						}
						////////////////////////
						if (y1 == 0) {
							your_dino1.setOutlineColor(sf::Color::Red);
						}
						if (y2 == 0) {
							your_dino2.setOutlineColor(sf::Color::Red);
						}
						if (y3 == 0) {
							your_dino3.setOutlineColor(sf::Color::Red);
						}
						if (y1 == 2) {
							your_dino1.setOutlineColor(sf::Color::Green);
						}
						if (y2 == 2) {
							your_dino2.setOutlineColor(sf::Color::Green);
						}
						if (y3 == 2) {
							your_dino3.setOutlineColor(sf::Color::Green);
						}
						if (y1 == -1) {
							your_dino1.setOutlineColor(sf::Color::Black);
						}
						if (y2 == -1) {
							your_dino2.setOutlineColor(sf::Color::Black);
						}
						if (y3 == -1) {
							your_dino3.setOutlineColor(sf::Color::Black);
						}
						if (e1 == -1) {
							enemies_dino1.setOutlineColor(sf::Color::Black);
						}
						if (e2 == -1) {
							enemies_dino2.setOutlineColor(sf::Color::Black);
						}
						if (e3 == -1) {
							enemies_dino3.setOutlineColor(sf::Color::Black);
						}
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and e2 != -1) {
				while (enemies_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino2.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y1 == 1) {
							int x = (enemies1.getPosition().x - sp0.getPosition().x) / 50;
							int y = (enemies1.getPosition().y - sp0.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp0.getPosition().x - enemies1.getPosition().x) {
								sp0.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino2->setHP(dino1->getDamage(m));
							if (E_dino2->getHP() <= 0) {
								e2 = -1;
								enemies_dino2.setOutlineColor(sf::Color::Black);
							}
							E_dino2_HP.setString(std::to_string(E_dino2->getHP()));
							while (move_x or move_y) {
								sp0.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y1 = 2;

						}
						if (y2 == 1) {
							int x = (enemies1.getPosition().x - sp1.getPosition().x) / 50;
							int y = (enemies1.getPosition().y - sp1.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp1.getPosition().x - enemies1.getPosition().x) {
								sp1.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino2->setHP(dino2->getDamage(m));
							if (E_dino2->getHP() <= 0) {
								e2 = -1;
								enemies_dino2.setOutlineColor(sf::Color::Black);
							}
							E_dino2_HP.setString(std::to_string(E_dino2->getHP()));
							while (move_x or move_y) {
								sp1.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y2 = 2;

						}
						if (y3 == 1) {
							int x = (enemies1.getPosition().x - sp2.getPosition().x) / 50;
							int y = (enemies1.getPosition().y - sp2.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp2.getPosition().x - enemies1.getPosition().x) {
								sp2.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino2->setHP(dino3->getDamage(m));
							if (E_dino2->getHP() <= 0) {
								e2 = -1;
								enemies_dino2.setOutlineColor(sf::Color::Black);
							}
							E_dino2_HP.setString(std::to_string(E_dino2->getHP()));
							while (move_x or move_y) {
								sp2.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y3 = 2;

						}
						////////////////////////
						if (y1 == 0) {
							your_dino1.setOutlineColor(sf::Color::Red);
						}
						if (y2 == 0) {
							your_dino2.setOutlineColor(sf::Color::Red);
						}
						if (y3 == 0) {
							your_dino3.setOutlineColor(sf::Color::Red);
						}
						if (y1 == 2) {
							your_dino1.setOutlineColor(sf::Color::Green);
						}
						if (y2 == 2) {
							your_dino2.setOutlineColor(sf::Color::Green);
						}
						if (y3 == 2) {
							your_dino3.setOutlineColor(sf::Color::Green);
						}
						if (y1 == -1) {
							your_dino1.setOutlineColor(sf::Color::Black);
						}
						if (y2 == -1) {
							your_dino2.setOutlineColor(sf::Color::Black);
						}
						if (y3 == -1) {
							your_dino3.setOutlineColor(sf::Color::Black);
						}
						if (e1 == -1) {
							enemies_dino1.setOutlineColor(sf::Color::Black);
						}
						if (e2 == -1) {
							enemies_dino2.setOutlineColor(sf::Color::Black);
						}
						if (e3 == -1) {
							enemies_dino3.setOutlineColor(sf::Color::Black);
						}
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
						break;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y) and e3 != -1) {
				while (enemies_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and enemies_dino3.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						if (y1 == 1) {
							int x = (enemies2.getPosition().x - sp0.getPosition().x) / 50;
							int y = (enemies2.getPosition().y - sp0.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp0.getPosition().x - enemies2.getPosition().x) {
								sp0.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino3->setHP(dino1->getDamage(m));
							if (E_dino3->getHP() <= 0) {
								e3 = -1;
								enemies_dino3.setOutlineColor(sf::Color::Black);
							}
							E_dino3_HP.setString(std::to_string(E_dino3->getHP()));
							while (move_x or move_y) {
								sp0.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y1 = 2;

						}
						if (y2 == 1) {
							int x = (enemies2.getPosition().x - sp1.getPosition().x) / 50;
							int y = (enemies2.getPosition().y - sp1.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp1.getPosition().x - enemies2.getPosition().x) {
								sp1.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino3->setHP(dino2->getDamage(m));
							if (E_dino3->getHP() <= 0) {
								e3 = -1;
								enemies_dino3.setOutlineColor(sf::Color::Black);
							}
							E_dino3_HP.setString(std::to_string(E_dino3->getHP()));
							while (move_x or move_y) {
								sp1.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y2 = 2;

						}
						if (y3 == 1) {
							int x = (enemies2.getPosition().x - sp2.getPosition().x) / 50;
							int y = (enemies2.getPosition().y - sp2.getPosition().y) / 50;
							int move_x = 0;
							int move_y = 0;
							while (sp2.getPosition().x - enemies2.getPosition().x) {
								sp2.move(x, y);
								move_x += x;
								move_y += y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							E_dino3->setHP(dino3->getDamage(m));
							if (E_dino3->getHP() <= 0) {
								e3 = -1;
								enemies_dino3.setOutlineColor(sf::Color::Black);
							}
							E_dino3_HP.setString(std::to_string(E_dino3->getHP()));
							while (move_x or move_y) {
								sp2.move(-x, -y);
								move_x -= x;
								move_y -= y;
								window.clear();
								window.draw(phon);
								window.draw(your_dino1);
								window.draw(your_dino2);
								window.draw(your_dino3);
								window.draw(enemies_dino1);
								window.draw(enemies_dino2);
								window.draw(enemies_dino3);
								window.draw(land_text);
								window.draw(sp0);
								window.draw(sp1);
								window.draw(sp2);
								window.draw(enemies0);
								window.draw(enemies1);
								window.draw(enemies2);
								window.draw(dino1_HP);
								window.draw(dino2_HP);
								window.draw(dino3_HP);
								window.draw(E_dino1_HP);
								window.draw(E_dino2_HP);
								window.draw(E_dino3_HP);
								window.display();
							}
							y3 = 2;

						}
						////////////////////////
						if (y1 == 0) {
							your_dino1.setOutlineColor(sf::Color::Red);
						}
						if (y2 == 0) {
							your_dino2.setOutlineColor(sf::Color::Red);
						}
						if (y3 == 0) {
							your_dino3.setOutlineColor(sf::Color::Red);
						}
						if (y1 == 2) {
							your_dino1.setOutlineColor(sf::Color::Green);
						}
						if (y2 == 2) {
							your_dino2.setOutlineColor(sf::Color::Green);
						}
						if (y3 == 2) {
							your_dino3.setOutlineColor(sf::Color::Green);
						}
						if (y1 == -1) {
							your_dino1.setOutlineColor(sf::Color::Black);
						}
						if (y2 == -1) {
							your_dino2.setOutlineColor(sf::Color::Black);
						}
						if (y3 == -1) {
							your_dino3.setOutlineColor(sf::Color::Black);
						}
						if (e1 == -1) {
							enemies_dino1.setOutlineColor(sf::Color::Black);
						}
						if (e2 == -1) {
							enemies_dino2.setOutlineColor(sf::Color::Black);
						}
						if (e3 == -1) {
							enemies_dino3.setOutlineColor(sf::Color::Black);
						}
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
						break;
					}
				}
			}


			E_dino1_HP.setString(std::to_string(E_dino1->getHP()));
			E_dino2_HP.setString(std::to_string(E_dino2->getHP()));
			E_dino3_HP.setString(std::to_string(E_dino3->getHP()));

			if ((y1 == 2 or y1 == -1) and (y2 == 2 or y2 == -1) and (y3 == 2 or y3 == -1)) {
				if (y1 != -1 and e1 != -1) {
					int x = (sp0.getPosition().x - enemies0.getPosition().x) / 50;
					int y = (sp0.getPosition().y - enemies0.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies0.getPosition().x - sp0.getPosition().x) {
						enemies0.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino1->setHP(E_dino1->getDamage(m));
					if (dino1->getHP() <= 0) {
						y1 = -1;
						your_dino1.setOutlineColor(sf::Color::Black);
					}
					dino1_HP.setString(std::to_string(dino1->getHP()));
					while (move_x or move_y) {
						enemies0.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}

				}
				else if (y2 != -1 and e1 != -1) {
					int x = (sp1.getPosition().x - enemies0.getPosition().x) / 50;
					int y = (sp1.getPosition().y - enemies0.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies0.getPosition().x - sp1.getPosition().x) {
						enemies0.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino2->setHP(E_dino1->getDamage(m));
					if (dino2->getHP() <= 0) {
						y2 = -1;
						your_dino2.setOutlineColor(sf::Color::Black);
					}
					dino2_HP.setString(std::to_string(dino2->getHP()));
					while (move_x or move_y) {
						enemies0.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				else if (y3 != -1 and e1 != -1) {
					int x = (sp2.getPosition().x - enemies0.getPosition().x) / 50;
					int y = (sp2.getPosition().y - enemies0.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies0.getPosition().x - sp2.getPosition().x) {
						enemies0.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino3->setHP(E_dino1->getDamage(m));
					if (dino3->getHP() <= 0) {
						y3 = -1;
						your_dino3.setOutlineColor(sf::Color::Black);
					}
					dino3_HP.setString(std::to_string(dino3->getHP()));
					while (move_x or move_y) {
						enemies0.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				////////////
				if (y1 != -1 and e2 != -1) {
					int x = (sp0.getPosition().x - enemies1.getPosition().x) / 50;
					int y = (sp0.getPosition().y - enemies1.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies1.getPosition().x - sp0.getPosition().x) {
						enemies1.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino1->setHP(E_dino2->getDamage(m));
					if (dino1->getHP() <= 0) {
						y1 = -1;
						your_dino1.setOutlineColor(sf::Color::Black);
					}
					dino1_HP.setString(std::to_string(dino1->getHP()));
					while (move_x or move_y) {
						enemies1.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}

				}
				else if (y2 != -1 and e2 != -1) {
					int x = (sp1.getPosition().x - enemies1.getPosition().x) / 50;
					int y = (sp1.getPosition().y - enemies1.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies1.getPosition().x - sp1.getPosition().x) {
						enemies1.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino2->setHP(E_dino2->getDamage(m));
					if (dino2->getHP() <= 0) {
						your_dino2.setOutlineColor(sf::Color::Black);
						y2 = -1;
					}
					dino2_HP.setString(std::to_string(dino2->getHP()));
					while (move_x or move_y) {
						enemies1.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				else if (y3 != -1 and e2 != -1) {
					int x = (sp2.getPosition().x - enemies1.getPosition().x) / 50;
					int y = (sp2.getPosition().y - enemies1.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies1.getPosition().x - sp2.getPosition().x) {
						enemies1.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino3->setHP(E_dino2->getDamage(m));
					if (dino3->getHP() <= 0) {
						y3 = -1;
						your_dino3.setOutlineColor(sf::Color::Black);
					}
					dino3_HP.setString(std::to_string(dino3->getHP()));
					while (move_x or move_y) {
						enemies1.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				///////////////////
				if (y1 != -1 and e3 != -1) {
					int x = (sp0.getPosition().x - enemies2.getPosition().x) / 50;
					int y = (sp0.getPosition().y - enemies2.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies2.getPosition().x - sp0.getPosition().x) {
						enemies2.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino1->setHP(E_dino3->getDamage(m));
					if (dino1->getHP() <= 0) {
						y1 = -1;
						your_dino1.setOutlineColor(sf::Color::Black);
					}
					dino1_HP.setString(std::to_string(dino1->getHP()));
					while (move_x or move_y) {
						enemies2.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}

				}
				else if (y2 != -1 and e3 != -1) {
					int x = (sp1.getPosition().x - enemies2.getPosition().x) / 50;
					int y = (sp1.getPosition().y - enemies2.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies2.getPosition().x - sp1.getPosition().x) {
						enemies2.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino2->setHP(E_dino3->getDamage(m));
					if (dino2->getHP() <= 0) {
						y2 = -1;
						your_dino2.setOutlineColor(sf::Color::Black);
					}
					dino2_HP.setString(std::to_string(dino2->getHP()));
					while (move_x or move_y) {
						enemies2.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				else if (y3 != -1 and e3 != -1) {
					int x = (sp2.getPosition().x - enemies2.getPosition().x) / 50;
					int y = (sp2.getPosition().y - enemies2.getPosition().y) / 50;
					int move_x = 0;
					int move_y = 0;
					while (enemies2.getPosition().x - sp2.getPosition().x) {
						enemies2.move(x, y);
						move_x += x;
						move_y += y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
					dino3->setHP(E_dino3->getDamage(m));
					if (dino3->getHP() <= 0) {
						y3 = -1;
						your_dino3.setOutlineColor(sf::Color::Black);
					}
					dino3_HP.setString(std::to_string(dino3->getHP()));
					while (move_x or move_y) {
						enemies2.move(-x, -y);
						move_x -= x;
						move_y -= y;
						window.clear();
						window.draw(phon);
						window.draw(your_dino1);
						window.draw(your_dino2);
						window.draw(your_dino3);
						window.draw(enemies_dino1);
						window.draw(enemies_dino2);
						window.draw(enemies_dino3);
						window.draw(land_text);
						window.draw(sp0);
						window.draw(sp1);
						window.draw(sp2);
						window.draw(enemies0);
						window.draw(enemies1);
						window.draw(enemies2);
						window.draw(dino1_HP);
						window.draw(dino2_HP);
						window.draw(dino3_HP);
						window.draw(E_dino1_HP);
						window.draw(E_dino2_HP);
						window.draw(E_dino3_HP);
						window.display();
					}
				}
				if (y1 == 2) {
					y1 = 0;
				}
				if (y2 == 2) {
					y2 = 0;
				}
				if (y3 == 2) {
					y3 = 0;
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			

			window.clear();
			window.draw(phon);
			window.draw(your_dino1);
			window.draw(your_dino2);
			window.draw(your_dino3);
			window.draw(enemies_dino1);
			window.draw(enemies_dino2);
			window.draw(enemies_dino3);
			window.draw(land_text);
			window.draw(sp0);
			window.draw(sp1);
			window.draw(sp2);
			window.draw(enemies0);
			window.draw(enemies1);
			window.draw(enemies2);
			window.draw(dino1_HP);
			window.draw(dino2_HP);
			window.draw(dino3_HP);
			window.draw(E_dino1_HP);
			window.draw(E_dino2_HP);
			window.draw(E_dino3_HP);
			window.display();

			if (e1 == -1 and e2 == -1 and e3 == -1) {
				inventory.setGold(100);
				return;
			}
			if (y1 == -1 and y2 == -1 and y3 == -1) {
				You_lose();
			}
		}
		
	}

	void You_lose() {

		sf::Sprite phon;
		phon.setTexture(fon);

		sf::RectangleShape exit_button(sf::Vector2f(500, 150));
		exit_button.setFillColor(sf::Color::Red);
		exit_button.setPosition(600, 720);

		sf::Text exit_text("Выйти в меню", font, 100);
		exit_text.setPosition(600, 720);

		sf::Text you_lose_text("Вы проиграли", font, 100);
		you_lose_text.setPosition(600, 50);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			mouse_p = sf::Mouse::getPosition(window);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
				while (exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
					mouse_p = sf::Mouse::getPosition(window);
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and exit_button.getGlobalBounds().contains(mouse_p.x, mouse_p.y)) {
						Load();
						main();
					}
				}
			}

			window.clear();
			window.draw(phon);
			window.draw(exit_text);
			window.draw(you_lose_text);
			window.display();
		}
	}

	void Load() {
		nlohmann::json data;
		std::fstream file("save.json");
		file >> data;
		inventory.setRex(data["Rex"]);
		inventory.setRaptor(data["Raptor"]);
		inventory.setTricer(data["Tricer"]);
		inventory.setGold(-inventory.getGold() + data["Gold"]);
		file.close();
	}

	void Save() {
		nlohmann::json data;
		data["Rex"] = inventory.getRex();
		data["Raptor"] = inventory.getRaptor();
		data["Tricer"] = inventory.getTricer();
		data["Gold"] = inventory.getGold();
		std::ofstream file("save.json");
		file << data;
		file.close();
	}
	
};