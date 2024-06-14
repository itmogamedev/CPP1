#include <SFML/Graphics.hpp>
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


int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Cat");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		// error...
	}

	sf::Texture texture1;
	sf::Texture texture2;
	if (!texture1.loadFromFile("cat1.png") or !texture2.loadFromFile("cat2.png")) {
		// error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture1);
	sprite.scale(sf::Vector2f(.01f, .01f));
	
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
		if (cat.isDead()) // TODO Окно поражения 
			exit(0);
		if (cat.isSuccess())
			exit(0); // TODO Окно победы 

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
					cat.increaseFull(50);
					updateCatPicture(texture2, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					cat.increaseHydr(50);
					updateCatPicture(texture2, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					cat.increaseClean(50);
					updateCatPicture(texture2, sprite, startTime);
				}
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
		window.draw(text);
		window.display();
	}

	return 0;
}