#include "includes.h"
#include "windows.h"

enum Scene {MainMenu, Buffer, Shop, Choosing, Battle, WinScreen, LooseScreen};

void get_rid_of_the_corpses(Player& player)
{
	for (auto it_dino{ player.dinos_owned.begin() }; it_dino != player.dinos_owned.end();)
	{
		Dino* cur_d = *it_dino;
		if (!cur_d->is_alive)
		{
			it_dino = player.dinos_owned.erase(it_dino);
		}
		else 
		{
			++it_dino;
		}
	}
}
std::map<terrain, sf::Color> ter_colors =
{
	{Mountain, sf::Color(176, 58, 41)},
	{River, sf::Color(41, 176, 148)},
	{Plains, sf::Color(123, 176, 41)}
};

std::map<terrain, std::string> ter_texts =
{
	{River, "res/backgr_images/River.png"},
	{Plains, "res/backgr_images/Plains.png"},
	{Mountain, "res/backgr_images/Mountains.png"}
};

terrain rand_ter()
{
	int a = rand() % 3;
	switch (a)
	{
	case 0: return River;
	case 1: return Plains;
	case 2: return Mountain;
	}
}

void make_MainMenu(sf::RenderWindow& window, Scene& cs, sf::Font& font)
{

	sf::Event ev;

	sf::RectangleShape go_shop;
	go_shop.setPosition(sf::Vector2f(300.f, 250.f));
	go_shop.setSize(sf::Vector2f(400.f, 200.f));
	go_shop.setFillColor(sf::Color::Cyan);

	sf::Text START;
	START.setPosition(360.f, 280.f);
	START.setFont(font);
	START.setString("START");
	START.setCharacterSize(100);
	START.setFillColor(sf::Color::Black);

	sf::RectangleShape exit;
	exit.setPosition(930.f, 15.f);
	exit.setSize(sf::Vector2f(50.f, 50.f));
	exit.setFillColor(sf::Color::Red);
	exit.setOutlineThickness(3.f);
	exit.setOutlineColor(sf::Color::White);

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			//START
			if (go_shop.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && ev.type == sf::Event::MouseButtonPressed)
			{
				//std::cout << "hover" << std::endl;
				if (ev.key.code == sf::Mouse::Left)
				{
					cs = Buffer;
					return;
				}
			}

			//EXIT
			if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && ev.type == sf::Event::MouseButtonPressed)
			{
				//std::cout << "EXIT" << std::endl;
				if (ev.key.code == sf::Mouse::Left)
				{
					window.close();
					return;
				}
			}

			window.clear(sf::Color(162, 239, 235));
			window.draw(go_shop);
			window.draw(exit);
			window.draw(START);
			window.display();
		}

	}
}

void make_Buffer(sf::RenderWindow& window, Scene& cs, sf::Font& font, Player& player)
{
	player.reset_dinos();
	sf::Event ev;
	SaveLoader SL("Dino_save.txt");

	//Œ ÕŒ »√–Œ ¿
	sf::RectangleShape playerWindow;
	sf::CircleShape coin_icon(30.f);
	sf::Text coins_count;
	std::string coin_message = "You have " + std::to_string(player.getCoins()) + " coins";
	{
		playerWindow.setPosition(40.f, 50.f);
		playerWindow.setSize(sf::Vector2f(440.f, 580.f));
		playerWindow.setFillColor(sf::Color(199, 253, 250));
		coin_icon.setPosition(sf::Vector2f(60.f, 120.f));
		coin_icon.setFillColor(sf::Color::Yellow);
		coins_count.setFont(font);
		coins_count.setFillColor(sf::Color::Black);
		coins_count.setPosition(125.f, 130.f);
		coins_count.setString(coin_message);
		coins_count.setCharacterSize(30);
	}

	// “¿¡À»÷¿ ƒ»ÕŒ
	sf::Text column_names;
	std::vector<sf::Text> dinos_info;

	int c = 0;
	// «ƒ≈—‹ Ã€ Ã”◊¿≈Ã “≈ —“
	{
		column_names.setFont(font);
		column_names.setFillColor(sf::Color::Black);
		column_names.setPosition(50.f, 210.f);
		column_names.setString("YOUR LOVELY DINOS:");
		column_names.setCharacterSize(30);


		for (int k = 0; k < player.dinos_owned.size(); k++) // ”‘‘ œŒÿÀ¿ ∆¿–»ÿ ¿ 
		{
			sf::Text c_text;

			c_text.setFont(font);
			c_text.setFillColor(ter_colors[player.dinos_owned[k]->getPrefter()]);
			c_text.setPosition(50.f, 250.f + 35 * k);
			c_text.setString(player.dinos_owned[k]->dino_info());
			c_text.setCharacterSize(30);

			dinos_info.push_back(c_text);
		}

	}

	// ¬ ¡Œ…
	sf::RectangleShape option_battle;
	sf::Text BATTLE;
	{
		option_battle.setPosition(sf::Vector2f(500.f, 50.f));
		option_battle.setSize(sf::Vector2f(280.f, 80.f));
		option_battle.setFillColor(sf::Color(162, 239, 235));
		BATTLE.setPosition(530.f, 50.f);
		BATTLE.setFont(font);
		BATTLE.setString("BATTLE");
		BATTLE.setCharacterSize(60);
		BATTLE.setFillColor(sf::Color::Red);
	}

	// Ã¿√¿«
	sf::RectangleShape option_shop;
	sf::Text SHOP;
	{
		option_shop.setPosition(sf::Vector2f(500.f, 150.f));
		option_shop.setSize(sf::Vector2f(280.f, 80.f));
		option_shop.setFillColor(sf::Color(162, 239, 235));
		SHOP.setPosition(560.f, 150.f);
		SHOP.setFont(font);
		SHOP.setString("SHOP");
		SHOP.setCharacterSize(60);
		SHOP.setFillColor(sf::Color::Black);
	}

	// œŒ—ÃŒ“–≈“‹ ƒ»ÕŒ
	sf::RectangleShape option_display;
	sf::Text DISPLAY;
	{
		option_display.setPosition(sf::Vector2f(500.f, 250.f));
		option_display.setSize(sf::Vector2f(280.f, 80.f));
		option_display.setFillColor(sf::Color(162, 239, 235));
		DISPLAY.setPosition(560.f, 250.f);
		DISPLAY.setFont(font);
		DISPLAY.setString("MENU");
		DISPLAY.setCharacterSize(60);
		DISPLAY.setFillColor(sf::Color::Black);
	}

	// —Œ’–¿Õ»“‹ 
	sf::RectangleShape option_save;
	sf::Text SAVE;
	{
		option_save.setPosition(sf::Vector2f(500.f, 350.f));
		option_save.setSize(sf::Vector2f(280.f, 80.f));
		option_save.setFillColor(sf::Color(162, 239, 235));
		SAVE.setPosition(560.f, 350.f);
		SAVE.setFont(font);
		SAVE.setString("SAVE");
		SAVE.setCharacterSize(60);
		SAVE.setFillColor(sf::Color::Black);
	}

	// «¿√–”«»“‹
	sf::RectangleShape option_load;
	sf::Text LOAD;
	{
		option_load.setPosition(sf::Vector2f(500.f, 450.f));
		option_load.setSize(sf::Vector2f(280.f, 80.f));
		option_load.setFillColor(sf::Color(162, 239, 235));
		LOAD.setPosition(560.f, 450.f);
		LOAD.setFont(font);
		LOAD.setString("LOAD");
		LOAD.setCharacterSize(60);
		LOAD.setFillColor(sf::Color::Black);
	}


	while (window.isOpen())
	{
		
		while (window.pollEvent(ev))
		{
			
			option_load.setFillColor(sf::Color(162, 239, 235));
			option_save.setFillColor(sf::Color(162, 239, 235));
			option_shop.setFillColor(sf::Color(162, 239, 235));
			option_battle.setFillColor(sf::Color(162, 239, 235));
			option_display.setFillColor(sf::Color(162, 239, 235));

			
			//GOTO BATTLE
			if (player.has_dinos() && option_battle.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				option_battle.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
				//	std::cout << "GO BATTLE" << std::endl;
					cs = Choosing;
					return;
				}
			}
			//GOTO SHOP
			if (option_shop.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				option_shop.setFillColor(sf::Color(199, 253, 250));
				
				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
				//	std::cout << "GO SHOP" << std::endl;
					cs = Shop;
					return;
				}
			}
			//GOTO DISPLAY
			if (option_display.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				option_display.setFillColor(sf::Color(199, 253, 250));
				
				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					//std::cout << "GO DISPLAY" << std::endl;
					cs = MainMenu;
					return;
				}
			}
			//SAVE
			if (option_save.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				option_save.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					SL.save(player);
				//	std::cout << "SAVE" << std::endl;
					
					return;
				}
			}
			//LOAD
			if (option_load.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				option_load.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					SL.load(player);
				//	std::cout << "LOAD" << std::endl;

					return;
				}
			}
		}

		//RENDER 
		window.clear(sf::Color(162, 239, 235));
		window.draw(playerWindow);
		window.draw(option_battle);
		window.draw(BATTLE);
		window.draw(option_shop);
		window.draw(SHOP);
		window.draw(option_display);
		window.draw(DISPLAY);
		window.draw(option_save);
		window.draw(SAVE);
		window.draw(option_load);
		window.draw(LOAD);
		
		window.draw(coin_icon);
		window.draw(coins_count);

		window.draw(column_names);
		for (auto t : dinos_info)
		{
			window.draw(t);
		}

		window.display();
	}

}

void make_Shop(sf::RenderWindow& window, Scene& cs, sf::Font& font, Player& player)
{
	sf::Event ev;
	Dino* current_dino = new Dino();
	current_dino->set_params(sf::Vector2f(140.f, 100.f), sf::Vector2f(0.3f, 0.3f));
	sf::Text curdino_info, curdino_price;
	{
		curdino_info.setFont(font);
		curdino_info.setFillColor(sf::Color::Black);
		curdino_info.setCharacterSize(30);
		curdino_info.setPosition(sf::Vector2f(100.f, 450.f));

		curdino_price.setFont(font);
		curdino_price.setFillColor(sf::Color::Yellow);
		curdino_price.setCharacterSize(60);
		curdino_price.setPosition(sf::Vector2f(400.f, 350.f));
	}

	// —◊≈“◊»  ÃŒÕ≈“Œ 
	sf::CircleShape coin_icon(30.f);
	sf::Text coins_count;
	std::string coin_message = "You have " + std::to_string(player.getCoins()) + " coins";
	{
		coin_icon.setPosition(sf::Vector2f(140.f, 20.f));
		coin_icon.setFillColor(sf::Color::Yellow);
		coins_count.setFont(font);
		coins_count.setFillColor(sf::Color::Black);
		coins_count.setPosition(205.f, 30.f);
		coins_count.setString(coin_message);
		coins_count.setCharacterSize(30);
	}

	//  ÕŒœ ¿ ¬Œ«¬–¿“¿ ¬ ¡”‘≈–
	sf::RectangleShape return_buffer;
	sf::Text FINISH;
	{
		return_buffer.setPosition(sf::Vector2f(580.f, 250.f));
		return_buffer.setSize(sf::Vector2f(300.f, 100.f));
		return_buffer.setFillColor(sf::Color(162, 239, 235));
		FINISH.setFont(font);
		FINISH.setString("FINISH");
		FINISH.setFillColor(sf::Color::Black);
		FINISH.setCharacterSize(80);
		FINISH.setPosition(sf::Vector2f(610.f, 245.f));
	}

	// «ƒ≈—‹ ƒŒÀ∆≈Õ »«Œ¡–¿∆¿“‹—ﬂ œ–≈ƒÀ¿√¿≈Ã€… ƒ»ÕŒ
	sf::RectangleShape dino_window;
	dino_window.setPosition(sf::Vector2f(100.f, 100.f));
	dino_window.setSize(sf::Vector2f(400.f, 400.f));
	dino_window.setFillColor(sf::Color(199, 253, 250));

	//  ÕŒœ ¿ œŒ ”œ » 
	sf::RectangleShape buy_button;
	sf::Text BUY;
	{
		buy_button.setPosition(sf::Vector2f(100.f, 510.f));
		buy_button.setSize(sf::Vector2f(220.f, 70.f));
		buy_button.setFillColor(sf::Color(199, 253, 250));
		BUY.setFont(font);
		BUY.setString("TAKE MY MONEY");
		BUY.setFillColor(sf::Color::Black);
		BUY.setCharacterSize(30);
		BUY.setPosition(sf::Vector2f(100.f, 525.f));
	}

	//  ÕŒœ ¿ ƒÀﬂ √≈Õ≈–¿÷»» ÕŒ¬Œ√Œ ƒ»ÕŒ
	sf::RectangleShape newDino_button;
	sf::Text  NEW;
	{
		newDino_button.setPosition(sf::Vector2f(340.f, 510.f));
		newDino_button.setSize(sf::Vector2f(160.f, 70.f));
		newDino_button.setFillColor(sf::Color(199, 253, 250));
		NEW.setFont(font);
		NEW.setString("NEW");
		NEW.setFillColor(sf::Color::Black);
		NEW.setCharacterSize(40);
		NEW.setPosition(sf::Vector2f(375.f, 520.f));
	}

	while (window.isOpen())
	{
		curdino_info.setString(current_dino->dino_info());
		curdino_info.setFillColor(ter_colors[current_dino->getPrefter()]);

		while (window.pollEvent(ev))
		{
			//current_dino->set_params(sf::Vector2f(140.f, 100.f), sf::Vector2f(0.3f, 0.3f));
			

			curdino_price.setString(std::to_string(current_dino->getCost()));

			coins_count.setString("You have " + std::to_string(player.getCoins()) + " coins");

			return_buffer.setFillColor(sf::Color(162, 239, 235));
			buy_button.setFillColor(sf::Color(162, 239, 235));
			newDino_button.setFillColor(sf::Color(162, 239, 235));

			//RETURN BUFFER
			if (return_buffer.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				return_buffer.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					//std::cout << "RETURN BUFFER" << std::endl;
					cs = Buffer;
					return;
				}
			}

			//BUY DINO
			if (current_dino->is_available(player.getCoins()) && buy_button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				buy_button.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					//std::cout << "BUY" << std::endl;
					Dino* dino_toBuy = current_dino;
					player.buy_dino(dino_toBuy);
					

					// √Àﬁ◊Õ¿ﬂ ◊¿—“‹
					//delete current_dino;
					current_dino = new Dino();
					current_dino->set_params(sf::Vector2f(140.f, 100.f), sf::Vector2f(0.3f, 0.3f));
				}
			}

			//NEW DINO
			if (newDino_button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				newDino_button.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					//std::cout << "NEW DINO" << std::endl;
					delete current_dino;
					current_dino = new Dino();
					current_dino->set_params(sf::Vector2f(140.f, 100.f), sf::Vector2f(0.3f, 0.3f));
				}
			}
		}

		window.clear(sf::Color(162, 239, 235));
		window.draw(return_buffer);
		window.draw(dino_window);
		window.draw(buy_button);
		window.draw(newDino_button);
		window.draw(FINISH);
		window.draw(BUY);
		window.draw(NEW);
		window.draw(coin_icon);
		window.draw(coins_count);

		current_dino->draw(window);
		window.draw(curdino_info);
		window.draw(curdino_price);
		window.display();
	}
}
	
void make_Choosing(sf::RenderWindow& window, Scene& cs, sf::Font& font, Player& player)
{
	sf::Event ev;
	int count = 0;
	int dinos_num = player.dinos_owned.size();
	int dino_ptr = 0; // »Õƒ≈ — ƒÀﬂ “≈ ”Ÿ≈√Œ ƒ»ÕŒ ¬ Œ Õ≈ 
	Dino* current_dino = nullptr; // »Ã≈ÕÕŒ ŒÕ Œ“Œ¡–¿∆¿≈“—ﬂ ¬ Œ Œÿ ≈
	


	// ƒ≈—‹ Œ“Œ¡–¿∆≈Õ “≈ ”Ÿ»… ƒ»ÕŒ
	sf::RectangleShape curdino_window;
	sf::Text curdino_info;
	{
		curdino_window.setPosition(sf::Vector2f(200.f, 100.f));
		curdino_window.setSize(sf::Vector2f(400.f, 400.f));
		curdino_window.setFillColor(sf::Color(199, 253, 250));

		curdino_info.setFont(font);
		curdino_info.setFillColor(sf::Color::Black);
		curdino_info.setCharacterSize(30);
		curdino_info.setPosition(sf::Vector2f(200.f, 60.f));
	}

	// œŒ ¿«¿“‹ œ–≈ƒ€ƒ”Ÿ≈√Œ
	sf::RectangleShape prev_dino;
	sf::Text left_arrow;
	{
		prev_dino.setPosition(sf::Vector2f(120.f, 260.f));
		prev_dino.setSize(sf::Vector2f(70.f, 70.f));
		prev_dino.setFillColor(sf::Color(199, 253, 250));

		left_arrow.setFont(font);
		left_arrow.setString("<");
		left_arrow.setFillColor(sf::Color::Black);
		left_arrow.setCharacterSize(80);
		left_arrow.setPosition(sf::Vector2f(130.f, 240.f));
	}

	// œŒ ¿«¿“‹ —À≈ƒ”ﬁŸ≈√Œ
	sf::RectangleShape next_dino;
	sf::Text right_arrow;
	{
		next_dino.setPosition(sf::Vector2f(610.f, 260.f));
		next_dino.setSize(sf::Vector2f(70.f, 70.f));
		next_dino.setFillColor(sf::Color(199, 253, 250));

		right_arrow.setFont(font);
		right_arrow.setString(">");
		right_arrow.setFillColor(sf::Color::Black);
		right_arrow.setCharacterSize(80);
		right_arrow.setPosition(sf::Vector2f(620.f, 240.f));
	}

	// ¬€¡–¿“‹ “≈ ”Ÿ≈√Œ
	sf::RectangleShape choose_current;
	sf::Text CHOOSE;
	{
		choose_current.setPosition(sf::Vector2f(200.f, 510.f));
		choose_current.setSize(sf::Vector2f(400.f, 70.f));
		choose_current.setFillColor(sf::Color(199, 253, 250));

		CHOOSE.setFont(font);
		CHOOSE.setString("I CHOOSE YOU");
		CHOOSE.setFillColor(sf::Color::Black);
		CHOOSE.setCharacterSize(60);
		CHOOSE.setPosition(sf::Vector2f(215.f, 510.f));
	}

	// œŒ…“» ¬ ¡Œ… Õ¿ œŒ‘»√
	sf::RectangleShape go_anyways;
	sf::Text LETSGO;
	{
		go_anyways.setPosition(sf::Vector2f(630.f, 350.f));
		go_anyways.setSize(sf::Vector2f(300.f, 100.f));
		go_anyways.setFillColor(sf::Color(199, 253, 250));

		LETSGO.setFont(font);
		LETSGO.setString("LET'S GO!");
		LETSGO.setFillColor(sf::Color::Black);
		LETSGO.setCharacterSize(70);
		LETSGO.setPosition(sf::Vector2f(630.f, 350.f));
	}

	while (window.isOpen())
	{
		
		if (count < 3)
		{
			current_dino = player.dinos_owned[dino_ptr];
			current_dino->set_params(sf::Vector2f(200.f, 100.f), sf::Vector2f(0.4f, 0.4f));
			curdino_info.setString(current_dino->dino_info());
			curdino_info.setFillColor(ter_colors[current_dino->getPrefter()]);

			while (window.pollEvent(ev))
			{

				prev_dino.setFillColor(sf::Color(162, 239, 235));
				next_dino.setFillColor(sf::Color(162, 239, 235));
				go_anyways.setFillColor(sf::Color(162, 239, 235));
				choose_current.setFillColor(sf::Color(162, 239, 235));

				// œŒ ¿«¿“‹ —À≈ƒ”ﬁŸ≈√Œ
				if (dino_ptr < dinos_num - 1 && next_dino.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					next_dino.setFillColor(sf::Color(199, 253, 250));
					if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
					{
						//std::cout << "NEXT " << dino_ptr << std::endl;
						dino_ptr++;
					}
				}
				// œŒ ¿«¿“‹ œ–≈ƒ€ƒ”Ÿ≈√Œ
				if (dino_ptr > 0 && prev_dino.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					prev_dino.setFillColor(sf::Color(199, 253, 250));
					if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
					{
					//	std::cout << "PREVIOUS " << dino_ptr << std::endl;
						dino_ptr--;
					}
				}
				// ¬€¡–¿“‹ “≈ ”Ÿ≈√Œ
				if (!current_dino->is_dino_chosen() && choose_current.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					choose_current.setFillColor(sf::Color(199, 253, 250));
					if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
					{
					//	std::cout << "CHOOSE" << std::endl;
						player.chosen_dinos[count] = current_dino;
						current_dino->set_chosen(true);
						count++;
					}
				}

				// œŒ…“» ¬ ¡Œ… Õ¿ œŒ‘»√ — ’Œ“ﬂ ¡€ ŒƒÕ»Ã ƒ»ÕŒ
				if (count >=1 && go_anyways.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					go_anyways.setFillColor(sf::Color(199, 253, 250));
					if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
					{
						//std::cout << "GO ANYWAYS" << std::endl;
						cs = Battle;
						return;
					}
				}
			}
		}
		else
		{
			cs = Battle;
			return;
		}

		window.clear(sf::Color(162, 239, 235));

		window.draw(curdino_window);
		window.draw(next_dino);
		window.draw(prev_dino);
		window.draw(choose_current);
		window.draw(go_anyways);

		window.draw(left_arrow);
		window.draw(right_arrow);
		window.draw(CHOOSE);
		window.draw(curdino_info);
		window.draw(LETSGO);

		current_dino->draw(window);
		window.display();
	}
}

void make_Battle(sf::RenderWindow& window, Scene& cs, sf::Font& font, Player& player)
{
	terrain current_terrain = rand_ter();
	sf::Texture ter_text;
	sf::Sprite ter_backgr;
	ter_text.loadFromFile(ter_texts[current_terrain]);
	ter_backgr.setTexture(ter_text);

	sf::Event ev;
	Player enemy(1); // ” ¬–¿√¿ ¡”ƒ≈“ ŒƒÕ¿ ÃŒÕ≈“ ¿, œŒ“ŒÃ” ◊“Œ ﬂ —≈√ŒƒÕﬂ ¬≈À» Œƒ”ÿÕ€…
	enemy.generate_dinos(); // “–» —À”◊¿…Õ€’ ƒ»ÕŒ ƒ≈–”“—ﬂ Õ¿ —“Œ–ŒÕ≈ —”œŒ—“¿“¿

	int my_ptr = 0;
	int enemy_ptr = 0;
	bool just_attack = false;
	Dino* my_current_dino = player.chosen_dinos[0];
	Dino* enemy_current_dino = enemy.chosen_dinos[0];
	sf::Text my_cnt;
	sf::Text en_cnt;
	{
		my_cnt.setFont(font);
		my_cnt.setCharacterSize(48);
		my_cnt.setFillColor(sf::Color::White);
		my_cnt.setOutlineThickness(4);
		my_cnt.setOutlineColor(sf::Color::Green);
		
		my_cnt.setPosition(100.f, 140.f);

		en_cnt.setFont(font);
		en_cnt.setCharacterSize(48);
		en_cnt.setFillColor(sf::Color::White);
		en_cnt.setOutlineThickness(4);
		en_cnt.setOutlineColor(sf::Color::Red);
		
		en_cnt.setPosition(600.f, 140.f);
	}

	// —À≈ƒ”ﬁŸ»… ’Œƒ
	sf::RectangleShape turn;
	turn.setPosition(sf::Vector2f(820.f, 600.f));
	turn.setSize(sf::Vector2f(140.f, 50.f));
	turn.setFillColor(sf::Color::Blue);

	// œŒÀŒ— » ’œ ƒÀﬂ Õ¿ÿ≈√Œ » ƒÀﬂ ¬–¿∆≈— Œ√Œ ƒ»ÕŒ
	sf::RectangleShape our_hpb;
	sf::RectangleShape en_hpb;
	sf::RectangleShape our_outline;
	sf::RectangleShape en_outline;

	sf::Text our_hp;
	sf::Text enemy_hp;

	{
		our_hpb.setPosition(sf::Vector2f(100.f, 500.f));
		our_hpb.setFillColor(sf::Color::Green);
		our_hpb.setSize(sf::Vector2f(300.f, 40.f));
		our_outline.setOutlineColor(sf::Color::White);
		our_outline.setOutlineThickness(5.f);
		our_outline.setPosition(sf::Vector2f(100.f, 500.f));
		our_outline.setSize(sf::Vector2f(300.f, 40.f));

		en_hpb.setPosition(sf::Vector2f(600.f, 500.f));
		en_hpb.setFillColor(sf::Color::Red);
		en_hpb.setSize(sf::Vector2f(300.f, 40.f));
		en_outline.setOutlineColor(sf::Color::White);
		en_outline.setOutlineThickness(5.f);
		en_outline.setPosition(sf::Vector2f(600.f, 500.f));
		en_outline.setSize(sf::Vector2f(300.f, 40.f));

		our_hp.setFont(font);
		our_hp.setPosition(40.f, 500.f);
		our_hp.setFillColor(sf::Color::Green);
		our_hp.setCharacterSize(30);

		enemy_hp.setFont(font);
		enemy_hp.setPosition(540.f, 500.f);
		enemy_hp.setFillColor(sf::Color::Red);
		enemy_hp.setCharacterSize(30);

	}

	while (window.isOpen())
	{
		en_cnt.setString(std::to_string(enemy_ptr + 1));
		my_cnt.setString(std::to_string(my_ptr + 1));
			while (window.pollEvent(ev))
			{
				my_current_dino = player.chosen_dinos[my_ptr];
				enemy_current_dino = enemy.chosen_dinos[enemy_ptr];
				my_current_dino->set_params(sf::Vector2f(100.f, 200.f), sf::Vector2f(0.3f, 0.3f));
				my_current_dino->set_flip();
				enemy_current_dino->set_params(sf::Vector2f(600.f, 200.f), sf::Vector2f(0.3f, 0.3f));

				our_hp.setString(std::to_string(my_current_dino->get_hp()));
				enemy_hp.setString(std::to_string(enemy_current_dino->get_hp()));
			
			 

				if (turn.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && ev.type == sf::Event::MouseButtonPressed)
				{
					if (ev.key.code == sf::Mouse::Left)
					{
						//std::cout << "NEW TURN" << std::endl;

						// œ–Œ»—’Œƒ»“ ’Œƒ...
						enemy_current_dino->set_hp(my_current_dino->damage(current_terrain));

						// ¬–¿∆≈— »… ƒ»ÕŒ —ƒŒ’????
						if (!enemy_current_dino->is_alive && enemy_ptr < 2)
						{

							enemy_ptr++;
							enemy_current_dino = enemy.chosen_dinos[enemy_ptr];
							enemy_current_dino->set_params(sf::Vector2f(600.f, 200.f), sf::Vector2f(0.3f, 0.3f));
							//std::cout << "NEW DINO ENEMY" << std::endl;
						}

						// »√–Œ  œŒ¡≈ƒ»À
						if (!enemy.any_dino_alive())
						{
							//	std::cout << "YOU WIN" << std::endl;
							player.giveCoins(1000);
							cs = WinScreen;
							get_rid_of_the_corpses(player);
							return;
						}

						en_hpb.setScale(sf::Vector2f(enemy_current_dino->get_hp_float(), 1.f));
						just_attack = true;
	
						my_current_dino->set_hp(enemy_current_dino->damage(current_terrain));		

						// Õ¿ÿ ƒ»ÕŒ —ƒŒ’???
						if (!my_current_dino->is_alive && my_ptr < 2)
						{	
							my_ptr++;
							if (player.chosen_dinos[my_ptr] != nullptr)
							{
								my_current_dino = player.chosen_dinos[my_ptr];
								my_current_dino->set_params(sf::Vector2f(100.f, 200.f), sf::Vector2f(0.3f, 0.3f));
								//std::cout << "NEW DINO YOU" << std::endl;
							}
						}
						
						// »√–Œ  œ–Œ»√–¿À
						if (!player.any_dino_alive())
						{
							//std::cout << "YOU LOSE" << std::endl;
							cs = LooseScreen;
							get_rid_of_the_corpses(player);
							return;
						}
						
						
						//our_hpb.setScale(sf::Vector2f(my_current_dino->get_hp_float(), 1.f));
					
					}
				}
			}
			if (just_attack)
			{
				window.clear(sf::Color(162, 239, 235));
				window.draw(ter_backgr);
				window.draw(turn);
				window.draw(our_outline);
				window.draw(en_outline);
				window.draw(our_hp);
				window.draw(en_hpb);
				window.draw(our_hpb);
				window.draw(enemy_hp);
				window.draw(my_cnt);
				window.draw(en_cnt);

				my_current_dino->draw(window);
				enemy_current_dino->draw(window);
				just_attack = false;
				
			
				window.display();
			}
			else
			{
				our_hpb.setScale(sf::Vector2f(my_current_dino->get_hp_float(), 1.f));
				window.clear(sf::Color(162, 239, 235));
				window.draw(ter_backgr);
				window.draw(turn);
				window.draw(our_outline);
				window.draw(en_outline);
				window.draw(our_hp);
				window.draw(en_hpb);
				window.draw(our_hpb);
				window.draw(enemy_hp);
				window.draw(my_cnt);
				window.draw(en_cnt);

				my_current_dino->draw(window);
				enemy_current_dino->draw(window);
				
				Sleep(500);

				window.display();
			}
	}
}

void make_WinScreen(sf::RenderWindow& window, Scene& cs, sf::Font& font)
{
	sf::Event ev;

	sf::Text YOUWIN;
	YOUWIN.setCharacterSize(120);
	YOUWIN.setFillColor(sf::Color::Green);
	YOUWIN.setFont(font);
	YOUWIN.setString("YOU WIN");
	YOUWIN.setPosition(200.f, 200.f);

	sf::RectangleShape contb;
	sf::Text CONT;
	sf::Text win_mes;
	{
		contb.setPosition(300.f, 500.f);
		contb.setFillColor(sf::Color(162, 239, 235));
		contb.setSize(sf::Vector2f(300.f, 70.f));
		CONT.setCharacterSize(60);
		CONT.setFillColor(sf::Color::Black);
		CONT.setFont(font);
		CONT.setString("CONTINUE");
		CONT.setPosition(310.f, 500.f);

		win_mes.setCharacterSize(30);
		win_mes.setFillColor(sf::Color::Black);
		win_mes.setFont(font);
		win_mes.setString("It seems that luck is on your side \n Take you 1000 coins and get out.");
		win_mes.setPosition(240.f, 350.f);
	}


	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			contb.setFillColor(sf::Color(162, 239, 235));
			//GOTO BUFFER
			if (contb.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				contb.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
					//std::cout << "CONTINUE" << std::endl;
					cs = Buffer;
					return;
				}
			}
		}

		window.clear(sf::Color(162, 239, 235));

		window.draw(YOUWIN);
		window.draw(contb);
		window.draw(win_mes);
		window.draw(CONT);

		window.display();
	}
}

void make_LooseScreen(sf::RenderWindow& window, Scene& cs, sf::Font& font)
{
	sf::Event ev;

	sf::Text YOUWIN;
	YOUWIN.setCharacterSize(120);
	YOUWIN.setFillColor(sf::Color::Red);
	YOUWIN.setFont(font);
	YOUWIN.setString("YOU LOOSE");
	YOUWIN.setPosition(200.f, 200.f);

	sf::RectangleShape contb;
	sf::Text CONT;
	contb.setPosition(300.f, 500.f);
	contb.setFillColor(sf::Color(162, 239, 235));
	contb.setSize(sf::Vector2f(300.f, 70.f));
	CONT.setCharacterSize(60);
	CONT.setFillColor(sf::Color::Black);
	CONT.setFont(font);
	CONT.setString("CONTINUE");
	CONT.setPosition(310.f, 500.f);

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			contb.setFillColor(sf::Color(162, 239, 235));
			//GOTO BUFFER
			if (contb.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				contb.setFillColor(sf::Color(199, 253, 250));

				if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left)
				{
				//	std::cout << "CONTINUE" << std::endl;
					cs = Buffer;
					return;
				}
			}
		}

		window.clear(sf::Color(162, 239, 235));

		window.draw(YOUWIN);
		window.draw(contb);
		window.draw(CONT);

		window.display();
	}
}


int main()
{ 
	sf::Font Barlow_R;
	Barlow_R.loadFromFile("res/Barlow-Regular.ttf");

	//—ÓÁ‰‡ÂÏ Ë„Û Ë Ì‡ÒÚ‡Ë‚‡ÂÏ ‚ÒˇÍÓÂ
	sf::RenderWindow gameWindow(sf::VideoMode(1000, 700), "DINO WARS 1.5", sf::Style::Titlebar | sf::Style::Close);
	gameWindow.setFramerateLimit(30);
	Scene current_scene = MainMenu;

	Player player(300);


	for (auto d : player.dinos_owned)
	{
		std::cout << d->dino_info() << std::endl;
	}

	//»„‡ ÔÓ‰ÓÎÊ‡ÂÚÒˇ ‚ÒÂ„‰‡ (¿”‘)
	while (true)
	{


		switch (current_scene)
		{
		case MainMenu:
			make_MainMenu(gameWindow, current_scene, Barlow_R);
			break;
		case Buffer:
			make_Buffer(gameWindow, current_scene, Barlow_R, player);
			break;
		case Shop:
			make_Shop(gameWindow, current_scene, Barlow_R, player);
			break;
		case Choosing:
			make_Choosing(gameWindow, current_scene, Barlow_R, player);
			break;
		case Battle:
			make_Battle(gameWindow, current_scene, Barlow_R, player);
			break;
		case WinScreen: 
			make_WinScreen(gameWindow, current_scene, Barlow_R);
			break;
		case LooseScreen:
			make_LooseScreen(gameWindow, current_scene, Barlow_R);
			break;
		}
		
	}

	return 0;
}
