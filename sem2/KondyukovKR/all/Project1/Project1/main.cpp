#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#include "MainMenu.h"
#include "progressBar.h"
#include "Button.h"

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

void updateCatPicture(const  sf::Texture& texture, sf::Sprite& sprite,
	std::chrono::time_point<std::chrono::steady_clock>& startTime) {
	sprite.setTexture(texture);
	startTime = std::chrono::high_resolution_clock::now();
}


int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tamagotchi!");
	window.setFramerateLimit(60);
	sf::Event event;
	MainMenu mainMenu(&window, &event);

	if (!mainMenu.render()) exit(0);

	sf::Texture idle;
	sf::Texture eating;

	switch (mainMenu.choosePet()) {
	case 0: exit(0);
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
	sprite.setPosition(window.getSize().x * 0.25, window.getSize().y / 2);
	sprite.scale(sf::Vector2f(.01f, .01f));
	float prevScale = sprite.getScale().x;
	
	// Game logic
	Pet pet( 1, 100, 1000, 1000);

	// Progress bars
	ProgressBar clean(&window, pet.getMaxClean(), sf::Color(192, 223, 208));
	clean.setPos(window.getSize().x * 0.6, window.getSize().y / 6);
	clean.setText("clean_bar.png");

	ProgressBar hunger(&window, pet.getMaxFull(), sf::Color(246, 184, 193));
	hunger.setPos(window.getSize().x * 0.6, window.getSize().y / 3 * 1.5);
	hunger.setText("full_bar.png");

	ProgressBar hydr(&window, pet.getMaxHydr(), sf::Color(153, 200, 236));
	hydr.setPos(window.getSize().x * 0.6, window.getSize().y / 3);
	hydr.setText("hydr_bar.png");

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;

	while (window.isOpen())	{
		prevScale = sprite.getScale().x;

		if (pet.isDead()) // TODO Окно поражения 
			exit(0);
		if (pet.isSuccess())
			exit(0); // TODO Окно победы 

		duration = std::chrono::high_resolution_clock::now() - startTime;

		pet.live();

		sprite.setScale(sf::Vector2f(float(pet.getSize()) / 100,
			float(pet.getSize()) / 100));

		if (duration.count() > 1) {
			sprite.setTexture(idle);
		}

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					pet.increaseFull(100);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					pet.increaseHydr(100);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					pet.increaseClean(100);
					updateCatPicture(eating, sprite, startTime);
				}
			}
		}


		// bars update
		hydr.setProgress(pet.getHydr());
		hunger.setProgress(pet.getFull());
		clean.setProgress(pet.getClean());

		sprite.move(sf::Vector2f((prevScale - sprite.getScale().x) * idle.getSize().x / 2, (prevScale - sprite.getScale().y) * idle.getSize().y / 2));

		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color::White);
		window.draw(sprite);
		hydr.draw();
		clean.draw();
		hunger.draw();
		window.display();
	}

	return 0;
}