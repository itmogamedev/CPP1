#include "Functions.h"
// gameplay
void GamePlay(sf::Font& font, sf::Color& bg_color)
{
	// если недостаточно динозавров чтобы начать игру - сообщение
	if (player.dinoset.size() < 3)
	{
		sf::Sprite crossSprite;
		crossSprite.setTexture(Textures["resources/cross.png"]);
		Button cross(crossSprite, sf::Text("", font, 25), sf::Vector2f(width - 50.f, 50.f), sf::Color::White, 7);

		sf::Event event;
		TextRect Message(width / 2.f, height / 2.f, 500, 100, sf::Color(0, 143, 150, 255), sf::Color::Black, 5, sf::Text("You dont have enough dinos\n\tto start this game!", font, 30), sf::Vector2f(0, 0), sf::Color::White);
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (cross.Sprite.getGlobalBounds().contains(mousePos)) // cross
					{
						state = menu;
						return;
					}
				}
				if (event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::Escape)
					{
						state = menu;
						return;
					}
			}
			window.clear(bg_color);
			window.draw(Message.Rect);
			window.draw(Message.Text);
			window.draw(cross.Sprite);
			window.display();
		}
	}
	else
	{
		// создание пула противника с рандомными динозавриками
		std::vector<Dino*>enemyteam;
		int k = 0;
		int prevchoice = -1, choice;
		while (k < 3)
		{
			choice = rand() % dinos.size();
			if (choice != prevchoice)
			{
				Dino* tmpdino = new Dino(*dinos[choice]);
				tmpdino->dinoSprite.setScale(3.5f, 3.5f);
				enemyteam.push_back(tmpdino);
				prevchoice = choice;
				k++;
			}
		}

		std::vector<Dino*>myteam;
		// создаю копию массива коллекции динозавров (потому что будем их стирать с экрана но не хочется стирать вообще)
		std::vector<Dino*>dinosetCopy;
		for (Dino* dino : player.dinoset)
		{
			dinosetCopy.push_back(new Dino(*dino));
		}
		// набор дино в пул из коллекции 
		if (!DisplayDinos(bg_color, dinosetCopy, false, true, myteam)) // if esc or cross has been pressed
		{
			state = menu;
			return;
		}
		// случайный выбор места
		int loc = rand() % 3;
		Terrain location;
		std::string location_string;
		switch (loc)
		{
		case 0:
			location = Plain;
			location_string = "Plain";
			break;
		case 1:
			location = River;
			location_string = "River";
			break;
		case 2:
			location = Mountain;
			location_string = "Mountain";
			break;
		default:
			location = Mountain;
			location_string = "Mountain";
			break;
		}
		// MY TEAM UI
		TextRect myteam_rect1(width / 3.f, 150, 100, 100, bg_color, sf::Color(0, 77, 86, 255), 5, sf::Text("", font, 30), sf::Vector2f(0, 0), text_color);
		myteam[0]->dinoSprite.setPosition(myteam_rect1.Rect.getPosition());

		TextRect myteam_rect2 = myteam_rect1;
		myteam_rect2.Move(200, 0);
		myteam[1]->dinoSprite.setPosition(myteam_rect2.Rect.getPosition());

		TextRect myteam_rect3 = myteam_rect2;
		myteam_rect3.Move(200, 0);
		myteam[2]->dinoSprite.setPosition(myteam_rect3.Rect.getPosition());

		sf::Text MyTeamName("Player\nDamage:" + std::to_string(myteam[0]->Damage(location)), font, 30);
		CenterOrigin(MyTeamName);
		MyTeamName.setPosition(myteam_rect1.Rect.getPosition() + sf::Vector2f(-140, 0));

		// ENEMY TEAM UI
		TextRect enemyteam_rect1(width / 3.f, 150, 100, 100, bg_color, sf::Color(0, 77, 86, 255), 5, sf::Text("", font, 30), sf::Vector2f(0, 0), text_color);
		enemyteam_rect1.Move(0, 400);
		enemyteam[0]->dinoSprite.setPosition(enemyteam_rect1.Rect.getPosition());

		TextRect enemyteam_rect2 = myteam_rect2;
		enemyteam_rect2.Move(0, 400);
		enemyteam[1]->dinoSprite.setPosition(enemyteam_rect2.Rect.getPosition());

		TextRect enemyteam_rect3 = myteam_rect3;
		enemyteam_rect3.Move(0, 400);
		enemyteam[2]->dinoSprite.setPosition(enemyteam_rect3.Rect.getPosition());

		sf::Text EnemyTeamName("Enemy\nDamage:" + std::to_string(enemyteam[0]->Damage(location)), font, 30);
		CenterOrigin(EnemyTeamName);
		EnemyTeamName.setPosition(enemyteam_rect3.Rect.getPosition() + sf::Vector2f(140, 0));

		// локация
		TextRect locationRect(width / 2.f, 50, 150, 30, bg_color, sf::Color(0, 77, 86, 255), 5, sf::Text(location_string, font, 30), sf::Vector2f(0, -5), sf::Color::Green);

		// ХП бары
		sf::RectangleShape MyHPbar(sf::Vector2f(100, 20));
		MyHPbar.setFillColor(sf::Color::Red);
		CenterOrigin(MyHPbar);

		sf::RectangleShape EnemyHPbar(MyHPbar);
		sf::RectangleShape BlackRect1(MyHPbar);
		BlackRect1.setFillColor(sf::Color::Black);
		sf::RectangleShape BlackRect2(BlackRect1);

		// ХП
		sf::Text myHPtext("", font, 30);
		CenterOrigin(myHPtext);
		sf::Text enemyHPtext("", font, 30);
		CenterOrigin(enemyHPtext);

		float curtime, period = 0.5f; // время и частота обновления
		int myID = 0, enemyID = 0;
		Dino* attacking;
		Dino* defending;
		bool move = 1;

		// урон
		sf::Text dmg("", font, 30);
		CenterOrigin(dmg);

		sf::Event event;
		timer.restart().asSeconds();
		// лямбда для рендера
		auto render = [&]()
			{
				window.clear(bg_color);
				locationRect.Draw(window);
				myteam_rect1.Draw(window);
				myteam_rect2.Draw(window);
				myteam_rect3.Draw(window);
				enemyteam_rect1.Draw(window);
				enemyteam_rect2.Draw(window);
				enemyteam_rect3.Draw(window);
				window.draw(MyTeamName);
				window.draw(EnemyTeamName);
				window.draw(myteam[0]->dinoSprite);
				window.draw(myteam[1]->dinoSprite);
				window.draw(myteam[2]->dinoSprite);
				window.draw(enemyteam[0]->dinoSprite);
				window.draw(enemyteam[1]->dinoSprite);
				window.draw(enemyteam[2]->dinoSprite);
				window.draw(BlackRect1);
				window.draw(MyHPbar);
				window.draw(BlackRect2);
				window.draw(EnemyHPbar);
				window.draw(myHPtext);
				window.draw(enemyHPtext);
				window.draw(dmg);
				window.display();

			};
		Sounds["shop"].stop();
		Sounds["fight"].play();
		//-----------------------------------------FIGHT----------------------------------------
		while (window.isOpen())
		{
			curtime = timer.getElapsedTime().asSeconds();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			myteam[myID]->dinoSprite.setPosition(width / 3.f, height / 2.f);
			MyHPbar.setPosition(myteam[myID]->dinoSprite.getPosition() + sf::Vector2f(-0, -50));
			BlackRect1.setPosition(MyHPbar.getPosition());

			enemyteam[enemyID]->dinoSprite.setPosition(width / 3.f * 2, height / 2.f);
			EnemyHPbar.setPosition(enemyteam[enemyID]->dinoSprite.getPosition() + sf::Vector2f(-0, -50));
			BlackRect2.setPosition(EnemyHPbar.getPosition());

			myHPtext.setString(std::to_string(myteam[myID]->HP));
			myHPtext.setPosition(MyHPbar.getPosition() + sf::Vector2f(80, -5));
			enemyHPtext.setString(std::to_string(enemyteam[enemyID]->HP));
			enemyHPtext.setPosition(EnemyHPbar.getPosition() + sf::Vector2f(80, -5));

			if (curtime > period)
			{
				MyTeamName.setString("Player\nDamage:" + std::to_string(myteam[myID]->Damage(location)));
				EnemyTeamName.setString("Enemy\nDamage:" + std::to_string(enemyteam[enemyID]->Damage(location)));
				if (!move)
				{
					attacking = enemyteam[enemyID];
					defending = myteam[myID];
				}
				else
				{
					attacking = myteam[myID];
					defending = enemyteam[enemyID];
				}
				// нанесение урона
				defending->HP -= attacking->Damage(location);
				Sounds["kick"].play();
				move = !move;

				defending->Animation("Idle", 3); // reset
				// изменение хэлфбара
				if (enemyteam[enemyID]->HP >= 0) EnemyHPbar.setSize(sf::Vector2f(float(enemyteam[enemyID]->HP), float(20)));
				else EnemyHPbar.setSize(sf::Vector2f(0, float(20)));
				if (myteam[myID]->HP >= 0) MyHPbar.setSize(sf::Vector2f(float(myteam[myID]->HP), float(20)));
				else MyHPbar.setSize(sf::Vector2f(0, float(20)));

				// отображение урона в рандомном радиусе
				dmg.setPosition(defending->dinoSprite.getPosition() + sf::Vector2f(float(rand() % 120 - 120), float(-(rand() % 100 - 50))));

				if (defending->HP <= 0) // если дино погиб
				{
					for (int i = 0; i < 5; i++) // анимация смерти
					{
						defending->Animation("Death", 5);
						render();
						Sleep(100);
					}
				}
				if (myteam[myID]->HP <= 0)
				{
					myteam[myID]->dinoSprite.setTexture(emptyTexture);
					myID++;
				}
				if (enemyteam[enemyID]->HP <= 0)
				{
					enemyteam[enemyID]->dinoSprite.setTexture(emptyTexture);
					enemyID++;
				}
				if (defending->HP <= 0 and myID < 3 and enemyID < 3) continue;
				if (myID > 2 or enemyID > 2) // конец игры
				{
					AfterFight(!move);
					// высвобождение динамической памяти
					std::cout << "myteam deletion\n";
					for (Dino* dino : myteam)
						delete dino;
					std::cout << "enemyteam deletion\n";
					for (Dino* dino : enemyteam)
						delete dino;
					std::cout << "dinosetcopy deletion\n";
					for (Dino* dino : dinosetCopy)
						delete dino;
					state = menu;
					return;
				}
				for (int i = 0; i < 4; i++) // анимация урона
				{
					dmg.setString("-" + std::to_string(attacking->Damage(location))); // отрисовка урона только во время анимации урона
					defending->Animation("Hurt", 3);
					attacking->Animation("Kick", 3);
					render();
					Sleep(50);
				}
				dmg.setString("");
				defending->Animation("Idle", 3); // reset anim
				attacking->Animation("Idle", 3); // reset anim
				timer.restart();
			}
			//------------------RENDER----------------
			render();
		}
	}
}

void AfterFight(bool isWin)
{
	int reward = (rand() % 6 + 5) * 100; // рандомная награда
	if (isWin)
	{
		MuteAll();
		Sounds["victory"].play();
		player.currbalance += reward;
		player.victnum++;
	}
	else
	{
		MuteAll();
		Sounds["lose"].play();
		player.losnum++;
	}
	SaveStats(player); // сохранение стат
	Dino* dino = dinos[0];
	dino->dinoSprite.setPosition(width / 2.f, height / 2.f);
	float animperiod = 0.2f;

	// cross button
	sf::Sprite crossSprite;
	crossSprite.setTexture(Textures["resources/cross.png"]);
	Button cross(crossSprite, sf::Text("", font, 25), sf::Vector2f(width - 50.f, 50.f), sf::Color::White, 7);
	// wintext
	sf::Text wintext("YOU WIN!!!", font, 50);
	wintext.setFillColor(sf::Color::Green);
	CenterOrigin(wintext);
	wintext.setPosition(width / 2.f, height / 5.f);
	// losetext
	sf::Text losetext("YOU LOST!!!", font, 50);
	losetext.setFillColor(sf::Color::Red);
	CenterOrigin(losetext);
	losetext.setPosition(width / 2.f, height / 5.f);
	// reward
	sf::Text rewardtext("+" + std::to_string(reward) + "$", font, 50);
	rewardtext.setFillColor(sf::Color::Yellow);
	CenterOrigin(rewardtext);
	rewardtext.setPosition(width / 2.f, height / 5.f + 40);

	timer.restart();
	//------------------------------GAME LOOP--------------------------------
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (cross.Sprite.getGlobalBounds().contains(mousePos))
					return;
			}
			if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
				return;
		}
		if (timer.getElapsedTime().asSeconds() >= animperiod)
		{
			dino->Animation("Idle", 3);
			timer.restart();
		}


		//--------------------RENDER-----------------------
		window.clear(bg_color);
		window.draw(dino->dinoSprite);
		window.draw(cross.Sprite);
		if (isWin)
		{
			window.draw(rewardtext);
			window.draw(wintext);
		}
		else
			window.draw(losetext);
		window.display();
		//--------------------------------------------------
	}
}