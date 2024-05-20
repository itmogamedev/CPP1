#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#include "MainMenu.h"

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
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tamagotchi!");
	window.setFramerateLimit(60);
	sf::Event event;
	MainMenu mainMenu(&window, &event);

	if (!mainMenu.render()) return 0;

	sf::Texture idle;
	sf::Texture eating;

	switch (mainMenu.choosePet()) {
	case 0: return 0;
	case 1:
		idle.loadFromFile("cat_idle.png");
		eating.loadFromFile("cat_eat.png");
		break;
	case 2: 
		idle.loadFromFile("dog_idle.png");
		eating.loadFromFile("dog_eat.png");
		break;
	case 3: 
		idle.loadFromFile("chin_idle.png");
		eating.loadFromFile("chin_eat.png");
		break;
	}

	sf::Sprite sprite;
	sprite.setTexture(idle);
	sprite.scale(sf::Vector2f(.01f, .01f));
	
	// Game logic
	Cat cat( 1, 100, 1000, 1000);
	Info info(&cat);

	

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;

	while (window.isOpen())	{
		if (cat.isDead()) // TODO Окно поражения 
			exit(0);
		if (cat.isSuccess())
			exit(0); // TODO Окно победы 

		duration = std::chrono::high_resolution_clock::now() - startTime;

		cat.live();

		sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(),
			float(cat.getSize()) / cat.getMaxSize()));

		while (window.pollEvent(event)) {

			if (duration.count() > 1) {
				sprite.setTexture(idle);
			}

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					cat.increaseFull(50);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					cat.increaseHydr(50);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					cat.increaseClean(50);
					updateCatPicture(eating, sprite, startTime);
				}
			}
		}


		info.update();
		//text.setString(info.getStr());

		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color::White);
		window.draw(sprite);
		//window.draw(text);
		window.display();
	}

	return 0;
}