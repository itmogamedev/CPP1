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
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tamagochi");
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

	sf::Texture catButtonTexture;
	sf::Texture dogButtonTexture;
	sf::Texture chinchillaButtonTexture;
	if (!catButtonTexture.loadFromFile("catButton.png") or !dogButtonTexture.loadFromFile("dogButton.png") or !chinchillaButtonTexture.loadFromFile("chinchillaButton.png")) {
		std::cout << "Error";
	}
	sf::Texture animalButtonTextures[3];
	animalButtonTextures[0] = catButtonTexture;
	animalButtonTextures[1] = dogButtonTexture;
	animalButtonTextures[2] = chinchillaButtonTexture;

	sf::Sprite catButtonSprite;
	sf::Sprite dogButtonSprite;
	sf::Sprite chinchillaButtonSprite;
	sf::Sprite animalButtonSprites[3];
	animalButtonSprites[0] = catButtonSprite;
	animalButtonSprites[1] = dogButtonSprite;
	animalButtonSprites[2] = chinchillaButtonSprite;
	for (int i = 0; i < 3; i++) {
		animalButtonSprites[i].setTexture(animalButtonTextures[i]);
		animalButtonSprites[i].setPosition(window.getSize().x / 3 + i * 250, window.getSize().y / 3 + 100);
	}

	sf::Texture catTexture1;
	sf::Texture catTexture2;
	sf::Texture dogTexture1;
	sf::Texture dogTexture2;
	sf::Texture chinchillaTexture1;
	sf::Texture chinchillaTexture2;
	if (!catTexture1.loadFromFile("cat1.png") or !catTexture2.loadFromFile("cat2.png") or !dogTexture1.loadFromFile("dog1.png") or !dogTexture2.loadFromFile("dog2.png") or !chinchillaTexture1.loadFromFile("chinchilla1.png") or !chinchillaTexture2.loadFromFile("chinchilla2.png")) {
		std::cout << "Error";
	}

	sf::Texture animalTextures1[3];
	animalTextures1[0] = catTexture1;
	animalTextures1[1] = dogTexture1;
	animalTextures1[2] = chinchillaTexture1;
	sf::Texture animalTextures2[3];
	animalTextures2[0] = catTexture2;
	animalTextures2[1] = dogTexture2;
	animalTextures2[2] = chinchillaTexture2;

	sf::Texture animalTexture1;
	sf::Texture animalTexture2;
	sf::Sprite animalSprite;

	bool isAnimal = false;
	Animal animal(1, 30, 150, 150);
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
		charSprites[i].setPosition(window.getSize().x / 2 + 5 + i * 160, 2 * window.getSize().y / 10 - 50);
	}

	sf::Text animalText;
	animalText.setFont(font);
	animalText.setFillColor(sf::Color::Black);
	animalText.setString(info.getStr());
	animalText.setCharacterSize(35);
	animalText.setPosition(window.getSize().x / 2, window.getSize().y / 10);

	sf::Text winText;
	winText.setFont(font);
	winText.setFillColor(sf::Color::Black);
	winText.setString("You won!");
	winText.setCharacterSize(40);
	winText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 3 + 50);

	sf::Text defeatText;
	defeatText.setFont(font);
	defeatText.setFillColor(sf::Color::Black);
	defeatText.setString("You lost");
	defeatText.setCharacterSize(40);
	defeatText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 3 + 50);

	sf::Text startText;
	startText.setFont(font);
	startText.setFillColor(sf::Color::Black);
	startText.setString("Choose your animal");
	startText.setCharacterSize(40);
	startText.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 3 + 50);

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();

	bool isPaused = false;

	std::string chars[3];
	chars[0] = "full";
	chars[1] = "hydr";
	chars[2] = "clean";

	int ticks = 0;

	while (window.isOpen()) {
		if (animal.isDead()) {
			window.clear(sf::Color::White);
			window.draw(defeatText);
			window.display();
		}
		else if (animal.isSuccess()) {
			window.clear(sf::Color::White);
			window.draw(winText);
			window.display();
		}
		else if (isAnimal && !isPaused && ticks >= 7) {
			animal.live();
			ticks = 0;
		}
		else if (!isAnimal) {
			window.clear(sf::Color::White);
			window.draw(startText);
			for (int i = 0; i < 3; i++) {
				window.draw(animalButtonSprites[i]);
			}
			window.display();
		}
		animalSprite.setScale(sf::Vector2f(float(animal.getSize()) / animal.getMaxSize(),
			float(animal.getSize()) / animal.getMaxSize()));

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			std::chrono::duration<float> duration =
				std::chrono::high_resolution_clock::now() - startTime;
			if (duration.count() > 1) {
				animalSprite.setTexture(animalTexture1);
			}

			if (!isAnimal && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				for (int i = 0; i < 3; i++) {
					if (animalButtonSprites[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						animalTexture1 = animalTextures1[i];
						animalTexture2 = animalTextures2[i];
						animalSprite.setTexture(animalTexture1);
						animalSprite.scale(sf::Vector2f(.01f, .01f));
						isAnimal = true;
					}
				}
			}

			if (!animal.isDead() && !animal.isSuccess()) {
				if (isAnimal && event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						isPaused = !isPaused;
						updateAnimalPicture(animalTexture1, animalSprite, startTime);
					}
				}
				if (isAnimal && event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left and !isPaused) {
					for (int i = 0; i < 3; i++) {
						if (buttonsCoords[i].contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							if (i == 0) {
								animal.increaseFull(15);
								updateAnimalPicture(animalTexture2, animalSprite, startTime);
							}
							else if ("hydr" == chars[i]) {
								animal.increaseHydr(30);
								updateAnimalPicture(animalTexture1, animalSprite, startTime);
							}
							else {
								animal.increaseClean(30);
								updateAnimalPicture(animalTexture1, animalSprite, startTime);
							}
						}
					}
				}
			}
		}

		if (isAnimal && !animal.isDead() && !animal.isSuccess()) {
			if (!isPaused) {
				ticks++;
			}

			Info info(8, animal.getSize(), animal.getMaxSize(),
				animal.getFull(), animal.getMaxFull(),
				animal.getHydr(), animal.getMaxHydr(),
				animal.getClean(), animal.getMaxClean());
			animalText.setString(info.getStr());

			window.clear(sf::Color::White);
			window.draw(animalSprite);
			for (int i = 0; i < 4; i++) {
				window.draw(charSprites[i]);
			}
			for (int i = 0; i < 3; i++) {
				window.draw(charButtonSprites[i]);
			}

			window.draw(animalText);
			window.display();
		}
	}

	return 0;
}