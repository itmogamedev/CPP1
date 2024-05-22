#include "Functions.h"
// menu
void Menu(sf::Font& font, sf::Color& bg_color)
{
	// два динозавра из менюшки
	sf::Sprite dino1, dino2;

	sf::Sprite Logo(Textures["resources/logo.png"]);
	CenterOrigin(Logo);
	Logo.setPosition(width / 2.f, height / 4.f);

	// спрайт кнопки
	sf::Sprite ButtonSprite;
	ButtonSprite.setTexture(Textures["resources/Button.png"]);
	// вектор менюшных кнопок
	std::vector<Button>menu_buttons = {
		Button(ButtonSprite, sf::Text("Play", font, 60),sf::Vector2f(width / 2.f,300), sf::Color::White,1),
		Button(ButtonSprite, sf::Text("Shop", font, 60),sf::Vector2f(width / 2.f,300) + sf::Vector2f(0,100), sf::Color::White,2),
		Button(ButtonSprite, sf::Text("Stat", font, 60),sf::Vector2f(width / 2.f,300) + sf::Vector2f(0,100 * 2), sf::Color::White,3),
		Button(ButtonSprite, sf::Text("Exit", font, 60),sf::Vector2f(width / 2.f,300) + sf::Vector2f(0,100 * 3), sf::Color::White,4)
	};

	float x = -200; // где начинает бежать дино
	//--------------------------GAME LOOP--------------------------
	while (window.isOpen())
	{
		// два таймера так как параллельные анимации
		elapsed = timer.getElapsedTime().asSeconds(); 
		elapsed1 = timer1.getElapsedTime().asSeconds(); 
		if (elapsed >= 0.04f) // бег
		{
			dino1 = dinos[0]->dinoSprite;
			dino1.setScale(dinos[0]->dinoSprite.getScale() * 0.5f);
			dinos[0]->Animation("Run", 6); 
			timer.restart();
		}
		if (elapsed1 >= 0.2f) // idle
		{
			dino2 = dinos[2]->dinoSprite;
			dino1.setScale(dinos[2]->dinoSprite.getScale() * 0.5f);
			dinos[2]->Animation("Idle", 3);
			timer1.restart();
		}
		x += 7;
		dino1.setPosition(x, 80);
		dino2.setPosition(180, 450);
		if (dino1.getPosition().x > width + 10)
			x = -200;
		sf::Event event;
		//---------------------EVENT LOOP---------------------
		while (window.pollEvent(event))
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (Button& button : menu_buttons)
			{
				if (button.Sprite.getGlobalBounds().contains(mousePos))
				{
					button.Sprite.setTexture(Textures["resources/PressedButton.png"]);
				}
				else
					button.Sprite.setTexture(Textures["resources/Button.png"]);
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				for (Button button : menu_buttons)
				{
					if (button.Sprite.getGlobalBounds().contains(mousePos))
					{
						Sounds["click"].play();
						button.Sprite.setTexture(Textures["resources/PressedButton.png"]);

						(dinos[0])->Animation("Idle", 3); // сбросить анимацию для бегущего дино
						switch (button.ButtonId) // выход в main и смена гейм мода
						{
						case 1:
							state = gamePlay;
							return;
							break;
						case 2:
							state = shop;
							return;
							break;
						case 3:
							state = collection;
							return;
							break;
						case 4:
							std::cout << "dinos deleted!\n";
							for (Dino* dino : dinos)
								delete dino;
							std::cout << "dinoset deleted!\n";
							for (Dino* dino : player.dinoset)
								delete dino;
							window.close();
							break;
						default:
							break;
						}
					}
				}

			}
		}
		//---------------------RENDER---------------------
		window.clear(bg_color);
		for (Button button : menu_buttons)
		{
			window.draw(button.Sprite);
			window.draw(button.Text);
		}
		window.draw(dino1);
		window.draw(dino2);
		window.draw(Logo);
		window.display();
		// -----------------------------------------------------

	}

}
