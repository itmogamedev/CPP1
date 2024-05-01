#include <SFML/Graphics.hpp>
#include "cat.h"

// Задача: сделать игру тамагочи про котика.
// Его нужно кормить, поить, убирать.
// Он будет расти и расти пока не заполнит весь экран.

// Котик
// size
// maxSize
// speedGrowth
// full
// maxFull
// hydr
// maxHydr
// clean
// maxClean

// Управление
// Рисовать кнопки на экране:
// * Покормить
// * Помыть
// * Напоить

// Условие победы
// if (maxSize =< size) 

// Условие поражение 
// if (0 == size or 0 == clean or 0 == hydr)

// Отображение и рост Котика


int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Cat");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Texture texture1;
	sf::Texture texture2;
	if (!texture1.loadFromFile("cat1.png") or !texture2.loadFromFile("cat2.png"))	{
		// error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture1);
	sprite.scale(sf::Vector2f(.01f, .01f));



	// Game logic
	Cat cat( 1, 100, 100, 100);


	while (window.isOpen())	{
		if (cat.isDead())
			exit(0);
		if (cat.isSuccess())
			exit(0);


		cat.live();

		sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(), float(cat.getSize()) / cat.getMaxSize()));


		sf::Clock clock;
		while (window.pollEvent(event)) {

			if (clock.getElapsedTime().asMilliseconds() > 500) {
				sprite.setTexture(texture1);
			}

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					cat.increaseFull(50);
					sprite.setTexture(texture2);
					clock.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					cat.increaseHydr(50);
					sprite.setTexture(texture2);
					clock.restart();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					cat.increaseClean(50);
					sprite.setTexture(texture2);
					clock.restart();
				}

			}
		}


		// Выполняем необходимые действия по отрисовке
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}