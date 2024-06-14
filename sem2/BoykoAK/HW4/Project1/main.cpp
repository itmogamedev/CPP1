#include <SFML/Graphics.hpp>
#include <string>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"


// Задача: сделать игру тамагочи про котика.
// Его нужно кормить, поить, убирать.
// Он будет расти и расти пока не заполнит весь экран.

// TODO
// Кнопки [кормить, поить, мыть]
// центровать

// Управление
// Рисовать кнопки на экране:
// * Покормить
// * Помыть
// * Напоить



void updateCatPicture(const  sf::Texture & texture, sf::Sprite & sprite,
	std::chrono::time_point<std::chrono::steady_clock>& startTime) {
	sprite.setTexture(texture);
	startTime = std::chrono::high_resolution_clock::now();

}


bool IsMouseOver(sf::Sprite sprite, sf::RenderWindow &window){
	float btnX = sprite.getPosition().x;
	float btnY = sprite.getPosition().y;

	float btnX_1 = sprite.getPosition().x + sprite.getLocalBounds().width;
	float btnY_1 = sprite.getPosition().y + sprite.getLocalBounds().height;


	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	if (mouseX < btnX_1 && mouseX > btnX && mouseY < btnY_1 && mouseY > btnY) {
		return true;
	}
	return false;
}



int main() {
	int x;
	sf::RenderWindow start(sf::VideoMode(480, 480), "Choose your pet!");

	sf::Font sfont;
	if (!sfont.loadFromFile("arial.ttf")) {
		// error...
	}

	sf::Text startingtext;
	startingtext.setFont(sfont);
	startingtext.setFillColor(sf::Color::White);
	startingtext.setString("Press to choose an animal:	1 = dog, 2 = cat, 3 = mouse");
	startingtext.setCharacterSize(12);

	while (start.isOpen())
	{

		sf::Event event;
		while (start.pollEvent(event))
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
				x = 3;
				start.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
				x = 2;
				start.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				x = 1;
				start.close();
			}
		}


		start.clear();

		start.draw(startingtext);
		start.display();

	}


	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Pet");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		// error...
	}

	sf::Texture texture1;
	sf::Texture texture2;

	if (x == 1) {
		texture1.loadFromFile("dog1.png");
		texture2.loadFromFile("dog2.png");
	}

	if (x == 2) {
		texture1.loadFromFile("cat1.png");
		texture2.loadFromFile("cat2.png");
	}

	if (x == 3) {
		texture1.loadFromFile("mouse1.png");
		texture2.loadFromFile("mouse2.png");
	}

	sf::Sprite sprite;
	sprite.setTexture(texture1);
	sprite.scale(sf::Vector2f(.01f, .01f));


	sf::Texture clean;
	clean.loadFromFile("clean.png");
	sf::Sprite CLN;
	CLN.setTexture(clean);
	CLN.setPosition((window.getSize().x) / 2, (window.getSize().y) / 6);

	sf::Texture hydration;
	hydration.loadFromFile("hydration.png");
	sf::Sprite HDR;
	HDR.setTexture(hydration);
	HDR.setPosition((window.getSize().x) / 10 * 8, (window.getSize().y) / 2);

	sf::Texture food;
	food.loadFromFile("food.png");
	sf::Sprite FDD;
	FDD.setTexture(food);
	FDD.setPosition((window.getSize().x) / 2, (window.getSize().y) / 2);


	sf::Texture pause;
	pause.loadFromFile("pause.png");
	sf::Sprite SLP;
	SLP.setTexture(pause);
	SLP.setPosition((window.getSize().x) / 10*8, (window.getSize().y) / 6);

	
	// Game logic
	Cat cat( 1, 100, 1000, 1000);
	Info info(cat.getSize(), cat.getMaxSize(), 
			  cat.getFull(), cat.getMaxFull(),
			  cat.getHydr(), cat.getMaxHydr(),
			  cat.getClean(), cat.getMaxClean());

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setString(info.getStr());
	text.setCharacterSize(35); // in pixels, not points!
	text.setPosition(window.getSize().x/2, window.getSize().y/10);


	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();

	while (window.isOpen())	{
		if (cat.isDead())
		{
			window.close();

			sf::RenderWindow d(sf::VideoMode(480, 480), "YOU LOST");
			sf::Texture defeat;
			defeat.loadFromFile("defeat.png");
			sf::Sprite d_screen;
			d_screen.setTexture(defeat);

			while (d.isOpen())
			{

				sf::Event event;
				while (d.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						d.close();
				}


				d.clear();
				d.draw(d_screen);
				d.display();

			}

		}
		if (cat.isSuccess()) 
		
		{
			window.close();

			sf::RenderWindow v(sf::VideoMode(480, 480), "YOU WON");
			sf::Texture victory;
			victory.loadFromFile("victory.png");
			sf::Sprite w_screen;
			w_screen.setTexture(victory);

			while (v.isOpen())
			{

				sf::Event event;
				while (v.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						v.close();
				}


				v.clear();
				v.draw(w_screen);
				v.display();

			}

		}
			//exit(0); // TODO Окно победы 

		

		cat.live();


		sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(),
			float(cat.getSize()) / cat.getMaxSize()));

		

		while (window.pollEvent(event)) {

			std::chrono::duration<float> duration = 
				std::chrono::high_resolution_clock::now() - startTime;
			if (duration.count() > 1) {
				sprite.setTexture(texture1);
			}
			

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					cat.increaseFull(1000);
					updateCatPicture(texture2, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					cat.increaseHydr(1000);
					updateCatPicture(texture2, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					cat.increaseClean(1000);
					updateCatPicture(texture2, sprite, startTime);

				}

				
			}
			if (IsMouseOver(CLN, window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				cat.increaseClean(1000);
				updateCatPicture(texture2, sprite, startTime);
			}

			if (IsMouseOver(HDR, window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				cat.increaseHydr(1000);
				updateCatPicture(texture2, sprite, startTime);
			}

			if (IsMouseOver(FDD, window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				cat.increaseFull(1000);
				updateCatPicture(texture2, sprite, startTime);
			}

		}


		Info info(cat.getSize(), cat.getMaxSize(),
			cat.getFull(), cat.getMaxFull(),
			cat.getHydr(), cat.getMaxHydr(),
			cat.getClean(), cat.getMaxClean());
		text.setString(info.getStr());

		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color::White);
		window.draw(sprite);
		window.draw(CLN);
		window.draw(FDD);
		window.draw(HDR);
		window.draw(SLP);
		window.draw(text);
		window.display();
	}

	return 0;
};