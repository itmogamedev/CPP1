#include <SFML/Graphics.hpp>
#include "animal.h"
#include "info.h"
#include "iostream"
#include "chrono"

void updateAnimalPicture(const  sf::Texture& texture, sf::Sprite& sprite,
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
		std::cout << "Error";
	}

	sf::Texture fullButtonTexture;
	sf::Texture hydrButtonTexture;
	sf::Texture cleanButtonTexture;
	if (!fullButtonTexture.loadFromFile("fullButton.png") or !hydrButtonTexture.loadFromFile("hydrButton.png") or !cleanButtonTexture.loadFromFile("cleanButton.png")) {
		std::cout << "Error";
	}
	sf::Texture charButtonTextures[3];
	charButtonTextures[0] = fullButtonTexture;
	charButtonTextures[1] = hydrButtonTexture;
	charButtonTextures[2] = cleanButtonTexture;

	sf::Sprite fullButtonSprite;
	sf::Sprite hydrButtonSprite;
	sf::Sprite cleanButtonSprite;
	sf::Sprite charButtonSprites[3];
	charButtonSprites[0] = fullButtonSprite;
	charButtonSprites[1] = hydrButtonSprite;
	charButtonSprites[2] = cleanButtonSprite;
	sf::FloatRect buttonsCoords[3];
	for (int i = 0; i < 3; i++) {
		charButtonSprites[i].setTexture(charButtonTextures[i]);
		charButtonSprites[i].setPosition(window.getSize().x / 2 + i * 250, 3 * window.getSize().y / 10 - 50);
		buttonsCoords[i] = charButtonSprites[i].getGlobalBounds();
	}

	sf::Texture animalTexture1;
	sf::Texture animalTexture2;
	if (!animalTexture1.loadFromFile("cat1.png") or !animalTexture2.loadFromFile("cat2.png")) {
		std::cout << "Error";
	}
	sf::Sprite animalSprite;
	animalSprite.setTexture(animalTexture1);
	animalSprite.scale(sf::Vector2f(.01f, .01f));

	Animal animal(1, 100, 750, 750);
	Info info(8, animal.getSize(), animal.getMaxSize(),
		animal.getFull(), animal.getMaxFull(),
		animal.getHydr(), animal.getMaxHydr(),
		animal.getClean(), animal.getMaxClean());

	sf::Texture sizeTexture;
	sf::Texture fullTexture;
	sf::Texture hydrTexture;
	sf::Texture cleanTexture;
	if (!sizeTexture.loadFromFile("size.png") or !fullTexture.loadFromFile("full.png") or !hydrTexture.loadFromFile("hydr.png") or !cleanTexture.loadFromFile("clean.png")) {
		std::cout << "Error";
	}
	sf::Texture charTextures[4];
	charTextures[0] = sizeTexture;
	charTextures[1] = fullTexture;
	charTextures[2] = hydrTexture;
	charTextures[3] = cleanTexture;

	sf::Sprite sizeSprite;
	sf::Sprite fullSprite;
	sf::Sprite hydrSprite;
	sf::Sprite cleanSprite;
	sf::Sprite charSprites[4];
	charSprites[0] = sizeSprite;
	charSprites[1] = fullSprite;
	charSprites[2] = hydrSprite;
	charSprites[3] = cleanSprite;
	for (int i = 0; i < 4; i++) {
		charSprites[i].setTexture(charTextures[i]);
		charSprites[i].setPosition(window.getSize().x / 2 + 15 + i * 170, 2 * window.getSize().y / 10 - 50);
	}

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setString(info.getStr());
	text.setCharacterSize(35);
	text.setPosition(window.getSize().x / 2, window.getSize().y / 10);

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();

	bool is_paused = false;
	std::string chars[3];
	chars[0] = "full";
	chars[1] = "hydr";
	chars[2] = "clean";

	while (window.isOpen()) {
		if (animal.isDead())
			exit(0);
		if (animal.isSuccess())
			exit(0);

		if (!is_paused) animal.live();

		animalSprite.setScale(sf::Vector2f(float(animal.getSize()) / animal.getMaxSize(),
			float(animal.getSize()) / animal.getMaxSize()));

		while (window.pollEvent(event)) {

			std::chrono::duration<float> duration =
				std::chrono::high_resolution_clock::now() - startTime;
			if (duration.count() > 1) {
				animalSprite.setTexture(animalTexture1);
			}

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					is_paused = !is_paused;
					updateAnimalPicture(animalTexture1, animalSprite, startTime);
				}
			}
			if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left and !is_paused) {
				for (int i = 0; i < 3; i++) {
					if (buttonsCoords[i].contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						if (i == 0) {
							animal.increaseFull(50);
							updateAnimalPicture(animalTexture2, animalSprite, startTime);
						}
						else if ("hydr" == chars[i]) {
							animal.increaseHydr(50);
							updateAnimalPicture(animalTexture2, animalSprite, startTime);
						}
						else {
							animal.increaseClean(50);
							updateAnimalPicture(animalTexture2, animalSprite, startTime);
						}
					}
				}
			}
		}


		Info info(8, animal.getSize(), animal.getMaxSize(),
			animal.getFull(), animal.getMaxFull(),
			animal.getHydr(), animal.getMaxHydr(),
			animal.getClean(), animal.getMaxClean());
		text.setString(info.getStr());

		window.clear(sf::Color::White);
		window.draw(animalSprite);
		for (int i = 0; i < 4; i++) {
			window.draw(charSprites[i]);
		}
		for (int i = 0; i < 3; i++) {
			window.draw(charButtonSprites[i]);
		}
		window.draw(text);
		window.display();
	}

	return 0;
}