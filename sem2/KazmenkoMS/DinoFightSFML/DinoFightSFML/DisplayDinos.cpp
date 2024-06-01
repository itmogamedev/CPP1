#include "Functions.h"
// displays dinos from player.dinoset on screen, if isShop true displays balance and buy button
bool DisplayDinos(sf::Color bg_color, std::vector<Dino*>& dinos, bool isShop, bool isGame, std::vector<Dino*>& myTeam)
{
	auto it = dinos.begin();
	//--------------------------RECTANGLES--------------------------
	// p.s. сделал прямоугольники в дин.памяти так как VS ругался что стека может не хватить
	
	// str rect
	TextRect* STR = new TextRect
	(
		width / 3.f + 20, // position X
		height / 8.f + 80, // position Y
		120, 30,         // width, height
		sf::Color(0, 143, 150, 255), // rect fill color
		sf::Color(0, 77, 86, 255),   // rect outline color
		5,							// rect outline thickness
		sf::Text("STR: ", font, 30),  // text
		sf::Vector2f(-10, -5),		// text offset
		sf::Color::Red,				// text color
		sf::Text(std::to_string((*it)->GetStr()), font, 30), // valueText
		sf::Vector2f(35, -5)	// valueText OffSet
	);

	// int rect
	TextRect* INT = new TextRect(width / 3.f + 220, height / 8.f + 80, 120, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("INT: ", font, 30), sf::Vector2f(-10, -5), sf::Color::Cyan, sf::Text(std::to_string((*it)->GetInt()), font, 30), sf::Vector2f(35, -5));

	// dex rect
	TextRect* DEX = new TextRect(width / 3.f + 420, height / 8.f + 80, 120, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("DEX: ", font, 30), sf::Vector2f(-10, -5), sf::Color::Green, sf::Text(std::to_string((*it)->GetDex()), font, 30), sf::Vector2f(35, -5));

	// name rect
	TextRect* NAME = new TextRect(width / 2.f, height / 8.f - 40, 300, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("", font, 30), sf::Vector2f(0, 0), sf::Color::Green, sf::Text((*it)->getname(), font, 30), sf::Vector2f(0, -5));

	// type rect
	TextRect* TYPE = new TextRect(width / 2.f, height / 8.f + 10, 240, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("", font, 30), sf::Vector2f(0, 0), sf::Color::Green, sf::Text((*it)->GetType(), font, 30), sf::Vector2f(0, -5));

	// balance rect
	TextRect* BALANCE = new TextRect(150, 250, 240, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("BALANCE: ", font, 30), sf::Vector2f(-40, -5), sf::Color::Yellow, sf::Text(std::to_string(player.currbalance), font, 30), sf::Vector2f(65, -5));

	// cost rect
	TextRect* COST = new TextRect(width / 2.f, height / 8.f + 460, 240, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("COST: ", font, 30), sf::Vector2f(-52, -5), sf::Color::Yellow, sf::Text(std::to_string((*it)->GetCost()), font, 30), sf::Vector2f(48, -5));

	if (isShop and !isGame)
	{
		BALANCE->Rect.setPosition(150, 60);
		BALANCE->Text.setPosition(BALANCE->Rect.getPosition() + sf::Vector2f(-40, -5));
		BALANCE->ValueText.setPosition(BALANCE->Rect.getPosition() + sf::Vector2f(52, -5));
	}

	// wins rect
	TextRect* WINS = new TextRect(90, 300, 120, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("WINS: ", font, 30), sf::Vector2f(-10, -5), sf::Color::Green, sf::Text(std::to_string(player.victnum), font, 30), sf::Vector2f(35, -5));

	// loses rect
	TextRect* LOSES = new TextRect(90, 350, 120, 30, sf::Color(0, 143, 150, 255), sf::Color(0, 77, 86, 255), 5, sf::Text("LOSES: ", font, 30), sf::Vector2f(0, -5), sf::Color::Red, sf::Text(std::to_string(player.losnum), font, 30), sf::Vector2f(50, -5));

	// stats rect
	TextRect* STATS = new TextRect(150, 200, 300, 30, bg_color, sf::Color(0, 77, 86, 255), 0, sf::Text("STATS", font, 30), sf::Vector2f(0, 0), text_color);

	// окошки с выбранными дино
	TextRect Choice_1(1100, 200, 100, 100, bg_color, sf::Color(0, 77, 86, 255), 5, sf::Text("", font, 30), sf::Vector2f(0, 0), text_color);
	TextRect Choice_2 = Choice_1;
	Choice_2.Move(0, 150);
	TextRect Choice_3 = Choice_2;
	Choice_3.Move(0, 150);

	TextRect choices[] = { Choice_1,Choice_2,Choice_3 };

	//--------------------------BUTTONS--------------------------

	// arrow buttons
	sf::Sprite leftarrow, rightarrow;
	leftarrow.setTexture(Textures["resources/ArrowL.png"]);
	rightarrow.setTexture(Textures["resources/ArrowR.png"]);
	Button leftArrowButton(leftarrow, sf::Text("", font, 25), sf::Vector2f(width / 2.f - 300, height / 2.f + 200), sf::Color::Black, 5);
	Button rightArrowButton(rightarrow, sf::Text("", font, 25), sf::Vector2f(width / 2.f + 300, height / 2.f + 200), sf::Color::Black, 6);

	// cross button
	sf::Sprite crossSprite;
	crossSprite.setTexture(Textures["resources/cross.png"]);
	Button cross(crossSprite, sf::Text("", font, 25), sf::Vector2f(width - 50.f, 50.f), sf::Color::White, 7);

	// Buy Button
	sf::Sprite BuySprite;
	BuySprite.setTexture(Textures["resources/buyButton.png"]);
	Button buy(BuySprite, sf::Text("", font, 25), sf::Vector2f(width / 2.f, height / 2.f + 275), sf::Color::White, 7);

	// Pick Button
	sf::Sprite PickSprite;
	PickSprite.setTexture(Textures["resources/PickButton.png"]);
	Button Pick(PickSprite, sf::Text("", font, 25), sf::Vector2f(width / 2.f, height / 2.f + 275), sf::Color::White, 7);



	auto deletion = [&]()
	{
			delete STR;
			delete INT;
			delete DEX;
			delete NAME;
			delete TYPE;
			delete BALANCE;
			delete COST;
			delete WINS;
			delete LOSES;
			delete STATS;
	};




	//--------------------------GAME LOOP--------------------------
	while (window.isOpen())
	{
		elapsed = timer.getElapsedTime().asSeconds(); // таймер

		// инициализация 
		STR->ValueText.setString(std::to_string((*it)->GetStr()));
		INT->ValueText.setString(std::to_string((*it)->GetInt()));
		DEX->ValueText.setString(std::to_string((*it)->GetDex()));
		NAME->ValueText.setString((*it)->getname());
		TYPE->ValueText.setString((*it)->GetType());
		BALANCE->ValueText.setString(std::to_string(player.currbalance) + "$");
		if (isShop)
		{
			COST->ValueText.setString(std::to_string((*it)->GetCost()) + "$");
		}
		//

		if (elapsed >= 0.2f)
		{
			(*it)->Animation("Idle", 3); // анимация
			timer.restart();
		}

		sf::Event event;
		//---------------------EVENT LOOP---------------------
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // позиция мыши

				if (leftArrowButton.Sprite.getGlobalBounds().contains(mousePos))   // left arrow
				{
					Sounds["click"].play();
					if (it != dinos.begin() and dinos.size() != 0)
					{
						leftArrowButton.Sprite.setTexture(Textures["resources/PressedArrowL.png"]);
						it--;
					}
				}

				else if (rightArrowButton.Sprite.getGlobalBounds().contains(mousePos)) // right arrow
				{
					Sounds["click"].play();
					if (it + 1 != dinos.end() and dinos.size() != 0)
					{
						rightArrowButton.Sprite.setTexture(Textures["resources/PressedArrowR.png"]);
						it++;
					}
				}

				else if (cross.Sprite.getGlobalBounds().contains(mousePos) and !isGame) // cross
				{
					Sounds["click"].play();
					state = menu;
					deletion();
					return false;
				}

				else if (buy.Sprite.getGlobalBounds().contains(mousePos) and !isGame) // buy
				{
					buy.Sprite.setTexture(Textures["resources/buyButtonPressed.png"]);
					if (player.currbalance >= (*it)->GetCost())
					{
						Sounds["money"].play();
						player.dinoset.push_back(new Dino(*(*it))); // добавляем нового дино в коллекцию
						player.currbalance -= (*it)->GetCost();
						SaveStats(player);
					}
				}
				else if (Pick.Sprite.getGlobalBounds().contains(mousePos) and isGame) // pick
				{
					Sounds["click"].play();
					Pick.Sprite.setTexture(Textures["resources/PickButtonPressed.png"]);
					if (myTeam.size() < 3)
					{
						myTeam.push_back(new Dino(**it));
						myTeam[myTeam.size() - 1]->dinoSprite.setScale(3.5f, 3.5f);
						myTeam[myTeam.size() - 1]->dinoSprite.setPosition(choices[myTeam.size() - 1].Rect.getPosition());
						delete(*it);
						dinos.erase(it); 
						if (it != dinos.begin()) it--;
					}
					else
					{
						deletion();
						return true;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				buy.Sprite.setTexture(Textures["resources/buyButton.png"]);
				if (myTeam.size() < 3)
					Pick.Sprite.setTexture(Textures["resources/PickButton.png"]);
				else
					Pick.Sprite.setTexture(Textures["resources/StartButton.png"]);
				rightArrowButton.Sprite.setTexture(Textures["resources/ArrowR.png"]);
				leftArrowButton.Sprite.setTexture(Textures["resources/ArrowL.png"]);
			}
			if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
			{
				state = menu;
				deletion();
				return false;
			}
		}
		//---------------------RENDER---------------------

		window.clear(bg_color);

		STR->Draw(window);
		INT->Draw(window);
		DEX->Draw(window);
		NAME->Draw(window);
		TYPE->Draw(window);

		if (dinos.size() != 0) window.draw((*it)->dinoSprite); // отрисовка текушего дино
		if (!isGame) window.draw(cross.Sprite); // из игры выйти нельзя если начал
		window.draw(rightArrowButton.Sprite);
		window.draw(leftArrowButton.Sprite);

		if (isShop)
		{
			COST->Draw(window);
			window.draw(buy.Sprite);
			BALANCE->Draw(window);
		}
		else
		{
			WINS->Draw(window);
			LOSES->Draw(window);
			STATS->Draw(window);
			BALANCE->Draw(window);
		}
		if (isGame)
		{
			Choice_1.Draw(window);
			Choice_2.Draw(window);
			Choice_3.Draw(window);
			window.draw(Pick.Sprite);
			for (Dino* dino : myTeam)
			{
				window.draw(dino->dinoSprite);
			}
		}
		window.display();
		// -----------------------------------------------------
	}
	deletion();
	return true;
}
