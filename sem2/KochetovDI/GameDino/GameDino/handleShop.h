#pragma once

void handleShop(sf::Event& event, sf::RenderWindow& window, sf::Font& font, sf::Text& balance,\
	sf::Text& earnedBalance, int& coinsUser, int& cntUserTyrannosaurus, int& cntUserStegosaurus, \
	int& cntUserTriceratops)
{
	//Создание текстур и загрузка картинок
	sf::Texture shopBackground, nameTyrannosaurusTexture, nameStegosaurusTexture, nameTriceratopsTexture, \
	TyrannosaurusTexture, StegosaurusTexture, TriceraptorTexture;
	shopBackground.loadFromFile("images/shop.png");
	nameTyrannosaurusTexture.loadFromFile("images/shop-nameTyrannosaurus.png");
	nameStegosaurusTexture.loadFromFile("images/shop-nameStegosaurus.png");
	nameTriceratopsTexture.loadFromFile("images/shop-nameTriceratops.png");
	TyrannosaurusTexture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
	StegosaurusTexture.loadFromFile("images/shop-Stegosaurus-compressed.png");
	TriceraptorTexture.loadFromFile("images/shop-Triceratops-compressed.png");
	sf::Sprite shopBg(shopBackground), nameTyrannosaurus(nameTyrannosaurusTexture), nameStegosaurus(nameStegosaurusTexture), nameTriceratops(nameTriceratopsTexture), \
		Tyrannosaurus(TyrannosaurusTexture), Stegosaurus(StegosaurusTexture), Triceratops(TriceraptorTexture);
	
	//Счетчик количества динозавров
	sf::Text cntUserTyrannosaurusText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserStegosaurusText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserTriceratopsText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTriceratopsText.setStyle(sf::Text::Bold);//жирный текст
	
	//Задаем координаты спрайтам
	int pickNum = 0;
	bool mousePressed = false;
	nameTyrannosaurus.setPosition(600, 50);
	Tyrannosaurus.setPosition(750, 110);
	nameStegosaurus.setPosition(600, 300);
	Stegosaurus.setPosition(750, 360);
	nameTriceratops.setPosition(600, 550);
	Triceratops.setPosition(750, 610);
	cntUserTyrannosaurusText.setPosition(50, 200);
	cntUserStegosaurusText.setPosition(50, 300);
	cntUserTriceratopsText.setPosition(50, 400);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		nameTyrannosaurus.setColor(sf::Color::White);
		nameStegosaurus.setColor(sf::Color::White);
		nameTriceratops.setColor(sf::Color::White);
		window.clear();

		//Наведение курсора на кнопку покупки
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		pickNum = 0;

		if (nameTyrannosaurus.getGlobalBounds().contains(worldPos)) {
			nameTyrannosaurus.setColor(sf::Color::Blue);
			pickNum = 1;
		}
		if (nameStegosaurus.getGlobalBounds().contains(worldPos)) {
			nameStegosaurus.setColor(sf::Color::Blue);
			pickNum = 2;
		}
		if (nameTriceratops.getGlobalBounds().contains(worldPos)) {
			nameTriceratops.setColor(sf::Color::Blue);
			pickNum = 3;
		}

		//Нажатие на кнопку покупки
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (pickNum == 1 && !mousePressed) {
				if (coinsUser >= 20) {
					nameTyrannosaurus.setColor(sf::Color::Green);
					cntUserTyrannosaurus++;
					coinsUser -= 20;
					mousePressed = true;
				}
				else { nameTyrannosaurus.setColor(sf::Color::Red); }
			}
			if (pickNum == 2 && !mousePressed) {
				if (coinsUser >= 15) {
					nameStegosaurus.setColor(sf::Color::Green);
					cntUserStegosaurus++;
					coinsUser -= 15;
					mousePressed = true;
				}
				else { nameStegosaurus.setColor(sf::Color::Red); }
			}
			if (pickNum == 3 && !mousePressed) {
				if (coinsUser >= 10) {
					nameTriceratops.setColor(sf::Color::Green);
					cntUserTriceratops++;
					coinsUser -= 10;
					mousePressed = true;
				}
				else { nameTriceratops.setColor(sf::Color::Red); }
			}
		}
		else {
			mousePressed = false; // Сбрасываем флаг, когда кнопка мыши отпущена
		}
		//Обновление баланса
		balance.setString("Balance: " + std::to_string(coinsUser));
		//Обновление количества дино
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceratopsText.setString("Triceratops: " + std::to_string(cntUserTriceratops));

		window.draw(shopBg);
		window.draw(nameTyrannosaurus);
		window.draw(Tyrannosaurus);
		window.draw(nameStegosaurus);
		window.draw(Stegosaurus);
		window.draw(nameTriceratops);
		window.draw(Triceratops);
		window.draw(balance);
		window.draw(earnedBalance);

		// Вывод количества дино в инвентаре
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceratopsText);
		window.display();

		
	}
}