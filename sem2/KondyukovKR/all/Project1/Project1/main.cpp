#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#include "MainMenu.h"
#include "progressBar.h"
#include "Button.h"
#include "PauseMenu.h"

// Задача: сделать игру тамагочи про котика.
// Его нужно кормить, поить, убирать.
// Он будет расти и расти пока не заполнит весь экран.

// TODO
// Кнопки [пауза, рестарт, продолжить, выход]
// Меню выигрыша и поражения

void updateCatPicture(const  sf::Texture& texture, sf::Sprite& sprite,
	std::chrono::time_point<std::chrono::steady_clock>& startTime)
{
	sprite.setTexture(texture);
	startTime = std::chrono::high_resolution_clock::now();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tamagotchi!");
	window.setFramerateLimit(60);
	sf::Event event;
	MainMenu mainMenu(&window, &event);

	if (!mainMenu.render()) exit(0);

	sf::Texture idle;
	sf::Texture eating;

	// Pet sprite
	switch (mainMenu.choosePet())
	{
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
	sprite.setPosition(window.getSize().x * 0.2, window.getSize().y / 2);
	sprite.scale(sf::Vector2f(.01f, .01f));
	float prevScale = sprite.getScale().x;
	
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

	// Buttons
	Button cleanButton(&window, "clean.png"); cleanButton.setPosition(window.getSize().x * 0.40, window.getSize().y / 3 * 2);
	Button waterButton(&window, "water.png"); waterButton.setPosition(window.getSize().x * 0.60, window.getSize().y / 3 * 2);
	Button feedButton(&window, "feed.png"); feedButton.setPosition(window.getSize().x * 0.80, window.getSize().y / 3 * 2);
	Button pause(&window, "pause.png"); pause.setPosition(window.getSize().x * 0.9, window.getSize().y * 0.05); pause.setScale(0.5, 0.5);
	int choice = 0;

	// Pause Menu
	PauseMenu pauseMenu(&window);

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;

	// Main Loop
	while (window.isOpen())	{
		prevScale = sprite.getScale().x;

		if (pet.isDead())
			exit(0);
		if (pet.isSuccess())
			exit(0);

		// Update data
		duration = std::chrono::high_resolution_clock::now() - startTime;
		cleanButton.setColor(sf::Color::Black);
		feedButton.setColor(sf::Color::Black);
		waterButton.setColor(sf::Color::Black);
		pause.setColor(sf::Color::Black);
		choice = 0;
		pet.live();

		sprite.setScale(sf::Vector2f(float(pet.getSize()) / 100,
			float(pet.getSize()) / 100));

		if (duration.count() > 2) {
			sprite.setTexture(idle);
		}

		if (window.pollEvent(event) && event.type == sf::Event::Closed) window.close();

		// Collisions
		if (cleanButton.isHovering()) { cleanButton.setColor(sf::Color(192, 223, 208)); choice = 1; }
		if (waterButton.isHovering()) { waterButton.setColor(sf::Color(153, 200, 236)); choice = 2; }
		if (feedButton.isHovering()) { feedButton.setColor(sf::Color(246, 184, 193)); choice = 3; }
		if (pause.isHovering()) { pause.setColor(sf::Color::Cyan); choice = 4; }

		// If Mouse pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice == 1) { pet.increaseClean(100); updateCatPicture(eating, sprite, startTime); }
			if (choice == 2) { pet.increaseHydr(100); updateCatPicture(eating, sprite, startTime); }
			if (choice == 3) { pet.increaseFull(100); updateCatPicture(eating, sprite, startTime); }
			if (choice == 4)
			{ 
				switch (pauseMenu.render())
				{
				case 1:
					break;
				case 2:
					window.close();
					break;
				default:
					break;
				}
			}
		}

		// bars update
		hydr.setProgress(pet.getHydr());
		hunger.setProgress(pet.getFull());
		clean.setProgress(pet.getClean());

		sprite.move(sf::Vector2f((prevScale - sprite.getScale().x) * idle.getSize().x / 2, (prevScale - sprite.getScale().y) * idle.getSize().y / 2));

		// Отрисовка
		window.clear(sf::Color::White);
		window.draw(sprite);
		hydr.draw(); clean.draw(); hunger.draw();
		cleanButton.draw(); feedButton.draw(); waterButton.draw(); pause.draw();
		window.display();
	}

	return 0;
}