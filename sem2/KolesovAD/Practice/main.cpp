#include "Dino.h"
#include <Windows.h>

enum Wind { START, DINOS, BUY, FIGHT, WIN, LOSE, TIE };


void save(std::vector<DinoStr>& dinosStr, std::vector<DinoDex>& dinosDex, std::vector<DinoInt>& dinosInt, int& cash) {
	std::ofstream outStream;
	outStream.open("log.txt");
	if (outStream.is_open()) {
		outStream << "Ñash: " << cash << std::endl;
		outStream << "Dino STR DEX INT HP" << std::endl;
		for (DinoStr dinoStr : dinosStr) {
			outStream << dinoStr.info() << std::endl;
		}
		for (DinoDex dinoDex : dinosDex) {
			outStream << dinoDex.info() << std::endl;
		}
		for (DinoInt dinoInt : dinosInt) {
			outStream << dinoInt.info() << std::endl;
		}
		outStream << "end 0 0 0 0";
	}
	outStream.close();
}


Dino& chooseDino(std::vector<DinoStr>& dinosStr, std::vector<DinoDex>& dinosDex, std::vector<DinoInt>& dinosInt, int number) {
	if (number <= dinosStr.size()) {
		DinoStr& dino1 = dinosStr[number - 1];
		return dino1;
	}
	if (number <= dinosStr.size() + dinosDex.size()) {
		DinoDex& dino2 = dinosDex[number - dinosStr.size() - 1];
		return dino2;
	}
	DinoInt& dino3 = dinosInt[number - dinosStr.size() - dinosDex.size() - 1];
	return dino3;
}


Dino& chooseEnemyDino(std::vector<DinoStr>& dinosStr1, std::vector<DinoDex>& dinosDex1, std::vector<DinoInt>& dinosInt1, int number) {
	if (number <= dinosStr1.size()) {
		DinoStr& enemyDino1 = dinosStr1[number - 1];
		return enemyDino1;
	}
	if (number <= dinosStr1.size() + dinosDex1.size()) {
		DinoDex& enemyDino2 = dinosDex1[number - dinosStr1.size() - 1];
		return enemyDino2;
	}
	DinoInt& enemyDino3 = dinosInt1[number - dinosStr1.size() - dinosDex1.size() - 1];
	return enemyDino3;
}


int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dino Fight");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Error";
	}

	Terrain terrain;

	sf::Texture brachioTexture1;
	sf::Texture brachioTexture2;
	sf::Texture tirexTexture1;
	sf::Texture tirexTexture2;
	sf::Texture stegoTexture1;
	sf::Texture stegoTexture2;
	sf::Texture triceraTexture1;
	sf::Texture triceraTexture2;
	sf::Texture diploTexture1;
	sf::Texture diploTexture2;
	sf::Texture tombTexture;

	if (!brachioTexture1.loadFromFile("img/brachio1.png") or !brachioTexture2.loadFromFile("img/brachio2.png") or
		!tirexTexture1.loadFromFile("img/tirex1.png") or !tirexTexture2.loadFromFile("img/tirex2.png") or
		!stegoTexture1.loadFromFile("img/stego1.png") or !stegoTexture2.loadFromFile("img/stego2.png") or
		!triceraTexture1.loadFromFile("img/tricera1.png") or !triceraTexture2.loadFromFile("img/tricera2.png") or
		!diploTexture1.loadFromFile("img/diplo1.png") or !diploTexture2.loadFromFile("img/diplo2.png") or
		!tombTexture.loadFromFile("img/tomb.png")) {
		std::cout << "Error";
	}

	sf::Texture textures1[5];
	textures1[0] = brachioTexture1;
	textures1[1] = tirexTexture1;
	textures1[2] = stegoTexture1;
	textures1[3] = triceraTexture1;
	textures1[4] = diploTexture1;

	sf::Texture textures2[5];
	textures2[0] = brachioTexture2;
	textures2[1] = tirexTexture2;
	textures2[2] = stegoTexture2;
	textures2[3] = triceraTexture2;
	textures2[4] = diploTexture2;

	sf::Texture buyButtonTexture;
	sf::Texture fightButtonTexture;
	sf::Texture dinosButtonTexture;
	sf::Texture exitButtonTexture;
	if (!buyButtonTexture.loadFromFile("img/buyButton.png") or !fightButtonTexture.loadFromFile("img/fightButton.png") or
		!dinosButtonTexture.loadFromFile("img/dinosButton.png") or !exitButtonTexture.loadFromFile("img/exitButton.png")) {
		std::cout << "Error";
	}
	sf::Texture menuButtonTextures[4];
	menuButtonTextures[0] = buyButtonTexture;
	menuButtonTextures[1] = fightButtonTexture;
	menuButtonTextures[2] = dinosButtonTexture;
	menuButtonTextures[3] = exitButtonTexture;

	sf::Sprite buyButtonSprite;
	sf::Sprite fightButtonSprite;
	sf::Sprite dinosButtonSprite;
	sf::Sprite exitButtonSprite;
	sf::Sprite menuButtonSprites[4];
	menuButtonSprites[0] = buyButtonSprite;
	menuButtonSprites[1] = fightButtonSprite;
	menuButtonSprites[2] = dinosButtonSprite;
	menuButtonSprites[3] = exitButtonSprite;
	sf::FloatRect menuButtonsCoords[4];
	for (int i = 0; i < 4; i++) {
		menuButtonSprites[i].setTexture(menuButtonTextures[i]);
		menuButtonSprites[i].setPosition(window.getSize().x / 2 - 100, (i + 1) * window.getSize().y / 6 - 50);
		menuButtonsCoords[i] = menuButtonSprites[i].getGlobalBounds();
	}

	sf::Texture backButtonTexture;
	if (!backButtonTexture.loadFromFile("img/backButton.png")) {
		std::cout << "Error";
	}
	sf::Sprite backButtonSprite;
	backButtonSprite.setTexture(backButtonTexture);
	backButtonSprite.setPosition(window.getSize().x / 2 - 100, 4 * window.getSize().y / 6 - 50);

	std::fstream inStream("log.txt", std::ios_base::in);
	std::string cashText;
	int cash;
	inStream >> cashText >> cash;
	std::vector<DinoStr> dinosStr;
	std::vector<DinoDex> dinosDex;
	std::vector<DinoInt> dinosInt;
	std::vector<bool> activeDinos;

	std::vector<DinoStr> dinosStr1;
	std::vector<DinoDex> dinosDex1;
	std::vector<DinoInt> dinosInt1;

	std::string dinoNameText, strengthText, dexterityText, intelligenceText, hpText;
	inStream >> dinoNameText >> strengthText >> dexterityText >> intelligenceText >> hpText;
	std::string dinoName;
	int strength, dexterity, intelligence, hp;
	int i = 0;
	while (!inStream.eof()) {
		inStream >> dinoName >> strength >> dexterity >> intelligence >> hp;
		if (dinoName != "end") {
			if (dinoName == "Tyrannosaurus") {
				DinoStr newDino(dinoName, tirexTexture1, 100, 100 + i * 130, 100, strength, dexterity, intelligence, hp);
				dinosStr.push_back(newDino);
				activeDinos.push_back(false);
			}
			else if (dinoName == "Brachiosaurus") {
				DinoStr newDino(dinoName, brachioTexture1, 100, 100 + i * 130, 100, strength, dexterity, intelligence, hp);
				dinosStr.push_back(newDino);
				activeDinos.push_back(false);
			}
			else if (dinoName == "Stegosaurus") {
				DinoDex newDino(dinoName, stegoTexture1, 100, 100 + i * 130, 100, strength, dexterity, intelligence, hp);
				dinosDex.push_back(newDino);
				activeDinos.push_back(false);
			}
			else if (dinoName == "Triceratops") {
				DinoDex newDino(dinoName, triceraTexture1, 100, 100 + i * 130, 100, strength, dexterity, intelligence, hp);
				dinosDex.push_back(newDino);
				activeDinos.push_back(false);
			}
			else {
				DinoInt newDino(dinoName, diploTexture1, 100, 100 + i * 130, 100, strength, dexterity, intelligence, hp);
				dinosInt.push_back(newDino);
				activeDinos.push_back(false);
			}
			i++;
		}
	}

	Wind wind = START;
	int activeCount = 0;
	int activeDinosIndexes[3];

	sf::Text cashText_;
	cashText_.setFont(font);
	cashText_.setFillColor(sf::Color::Magenta);
	cashText_.setString("Your cash: " + std::to_string(cash));
	cashText_.setCharacterSize(30);
	cashText_.setPosition(3 * window.getSize().x / 4 + 150, window.getSize().y / 3);


	std::vector<std::string> names;
	names.push_back("Brachiosaurus");
	names.push_back("Tyrannosaurus");
	names.push_back("Stegosaurus");
	names.push_back("Triceratops");
	names.push_back("Diplodocus");

	std::vector<DinoStr> baseDinosStr;
	std::vector<DinoDex> baseDinosDex;
	std::vector<DinoInt> baseDinosInt;
	std::vector<sf::Text*> buyDinoTexts;

	sf::Text winText;
	winText.setFont(font);
	winText.setFillColor(sf::Color::Magenta);
	winText.setString("You won!");
	winText.setCharacterSize(40);
	winText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 3 + 50);

	sf::Text defeatText;
	defeatText.setFont(font);
	defeatText.setFillColor(sf::Color::Magenta);
	defeatText.setString("You lost");
	defeatText.setCharacterSize(40);
	defeatText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 3 + 50);

	sf::Text tieText;
	tieText.setFont(font);
	tieText.setFillColor(sf::Color::Magenta);
	tieText.setString("It's a tie!");
	tieText.setCharacterSize(40);
	tieText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 3 + 50);

	sf::Text dinoText;
	dinoText.setFont(font);
	dinoText.setFillColor(sf::Color::Magenta);
	dinoText.setCharacterSize(30);

	sf::Text fightText;
	fightText.setFont(font);
	fightText.setFillColor(sf::Color::Magenta);
	fightText.setCharacterSize(30);

	sf::Text terrainText;
	terrainText.setFont(font);
	terrainText.setFillColor(sf::Color::Magenta);
	terrainText.setCharacterSize(40);
	terrainText.setPosition(7 * window.getSize().x / 8, window.getSize().y / 3);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (wind == START) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < 4; i++) {
						if (menuButtonsCoords[i].contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							if (i == 0) {
								for (int i = 0; i < 5; i++) {
									buyDinoTexts.push_back(new sf::Text);
								}

								for (sf::Text* buyDinoText : buyDinoTexts) {
									buyDinoText->setFont(font);
									buyDinoText->setFillColor(sf::Color::Magenta);
									buyDinoText->setCharacterSize(30);
								}
								for (int i = 0; i < 2; i++) {
									DinoStr newBaseDinoStr(names[i], textures1[i], 100, 100 + i * 130, 100 * (i + 1));
									baseDinosStr.push_back(newBaseDinoStr);
									buyDinoTexts[i]->setString(baseDinosStr[i].buyInfo());
									buyDinoTexts[i]->setPosition(350, 100 + i * 130);
								}
								for (int i = 0; i < 2; i++) {
									DinoDex newBaseDinoDex(names[i + 2], textures1[i + 2], 100, 360 + i * 130, 100 * (i + 1));
									baseDinosDex.push_back(newBaseDinoDex);
									buyDinoTexts[i + 2]->setString(baseDinosDex[i].buyInfo());
									buyDinoTexts[i + 2]->setPosition(350, 360 + i * 130);
								}
								DinoInt newBaseDinoInt(names[4], textures1[4], 100, 620, 100);
								baseDinosInt.push_back(newBaseDinoInt);
								buyDinoTexts[4]->setString(baseDinosInt[0].buyInfo());
								buyDinoTexts[4]->setPosition(350, 620);
								wind = BUY;
							}

							else if (i == 1) {
								dinosStr1.clear();
								DinoStr brachio("Brachiosaurus", brachioTexture2, 2 * window.getSize().x / 3, 5 * window.getSize().y / 6);
								DinoStr tirex("Tyrannosaurus", tirexTexture2, 2 * window.getSize().x / 3, 5 * window.getSize().y / 6);
								dinosStr1.push_back(brachio);
								dinosStr1.push_back(tirex);

								dinosDex1.clear();
								DinoDex stego("Stegosaurus", stegoTexture2, 2 * window.getSize().x / 3, 5 * window.getSize().y / 6);
								DinoDex tricera("Triceratops", triceraTexture2, 2 * window.getSize().x / 3, 5 * window.getSize().y / 6);
								dinosDex1.push_back(stego);
								dinosDex1.push_back(tricera);

								dinosInt1.clear();
								DinoInt diplo("Diplodocus", diploTexture2, 2 * window.getSize().x / 3, 5 * window.getSize().y / 6);
								dinosInt1.push_back(diplo);

								for (int i = 0; i < dinosStr.size() + dinosDex.size() + dinosInt.size(); i++) {
									activeDinos[i] = false;
								}
								activeCount = 0;
								wind = FIGHT;
							}

							else if (i == 2) {
								wind = DINOS;
							}

							else {
								window.close();
							}
						}
					}
				}
			}

			else if (wind == FIGHT) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
					backButtonSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					for (int i = 0; i < dinosStr.size() + dinosDex.size() + dinosInt.size(); i++) {
						activeDinos[i] = false;
					}
					activeCount = 0;
					wind = START;
				}
				else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					int i = 0;
					for (DinoStr dinoStr : dinosStr) {
						if (dinoStr.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							activeDinos[i] = true;
							activeCount++;
							if (dinoStr.getName() == "Brachiosaurus") {
								dinoStr.changeTexture(brachioTexture1, 100, 3 * window.getSize().y / 4);
							}
							else {
								dinoStr.changeTexture(tirexTexture1, 100, 3 * window.getSize().y / 4);
							}
						}
						i++;
					}
					for (DinoDex dinoDex : dinosDex) {
						if (dinoDex.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							activeDinos[i] = true;
							activeCount++;
							if (dinoDex.getName() == "Stegosaurus") {
								dinoDex.changeTexture(stegoTexture1, 100, 3 * window.getSize().y / 4);
							}
							else {
								dinoDex.changeTexture(triceraTexture1, 100, 3 * window.getSize().y / 4);
							}
						}
						i++;
					}
					for (DinoInt dinoInt : dinosInt) {
						if (dinoInt.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							activeDinos[i] = true;
							activeCount++;
							dinoInt.changeTexture(diploTexture1, 100, 4 * window.getSize().y / 5);
						}
						i++;
					}
				}
			}

			else if (wind == BUY) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
					backButtonSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					wind = START;
				}
				else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					int i = 0;
					for (DinoStr baseDinoStr : baseDinosStr) {
						if (baseDinoStr.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) &&
							cash >= baseDinoStr.getCost()) {
							cash -= baseDinoStr.getCost();
							cashText_.setString("Your cash: " + std::to_string(cash));
							dinosStr.push_back(baseDinoStr);
							activeDinos.push_back(false);
						}
						i++;
					}
					for (DinoDex baseDinoDex : baseDinosDex) {
						if (baseDinoDex.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) &&
							cash >= baseDinoDex.getCost()) {
							cash -= baseDinoDex.getCost();
							cashText_.setString("Your cash: " + std::to_string(cash));
							activeDinos.push_back(false);
							dinosDex.push_back(baseDinoDex);
						}
						i++;
					}
					for (DinoInt baseDinoInt : baseDinosInt) {
						if (baseDinoInt.sprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) &&
							cash >= baseDinoInt.getCost()) {
							cash -= baseDinoInt.getCost();
							cashText_.setString("Your cash: " + std::to_string(cash));
							activeDinos.push_back(false);
							dinosInt.push_back(baseDinoInt);
						}
						i++;
					}
					save(dinosStr, dinosDex, dinosInt, cash);
				}
			}

			else {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
					backButtonSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					wind = START;
				}
			}
		}

		if (wind == START) {
			window.clear(sf::Color::Cyan);
			for (int i = 0; i < 4; i++) {
				window.draw(menuButtonSprites[i]);
			}
			window.display();
		}

		if (wind == BUY) {
			window.clear(sf::Color::Cyan);
			window.draw(cashText_);
			int i = 0;
			for (DinoStr baseDinoStr : baseDinosStr) {
				if (cash >= baseDinoStr.getCost()) {
					window.draw(baseDinoStr.sprite());
					window.draw(*buyDinoTexts[i]);
				}
				i++;
			}
			for (DinoDex baseDinoDex : baseDinosDex) {
				if (cash >= baseDinoDex.getCost()) {
					window.draw(baseDinoDex.sprite());
					window.draw(*buyDinoTexts[i]);
				}
				i++;
			}
			for (DinoInt baseDinoInt : baseDinosInt) {
				if (cash >= baseDinoInt.getCost()) {
					window.draw(baseDinoInt.sprite());
					window.draw(*buyDinoTexts[i]);
				}
				i++;
			}

			window.draw(backButtonSprite);
			window.display();
		}

		if (wind == FIGHT) {
			if (dinosStr.size() + dinosDex.size() + dinosInt.size() < 3) {
				wind = START;
			}
			else if (activeCount == 3) {
				int j_ = 0;
				for (int i = 0; i < dinosStr.size() + dinosDex.size() + dinosInt.size(); i++) {
					if (activeDinos[i]) {
						activeDinosIndexes[j_] = i;
						j_++;
					}
					activeDinos[i] = false;
				}
				int dino1 = activeDinosIndexes[0] + 1;
				int dino2 = activeDinosIndexes[1] + 1;
				int dino3 = activeDinosIndexes[2] + 1;
				auto& firstDino = chooseDino(dinosStr, dinosDex, dinosInt, dino1);
				auto& secondDino = chooseDino(dinosStr, dinosDex, dinosInt, dino2);
				auto& thirdDino = chooseDino(dinosStr, dinosDex, dinosInt, dino3);

				DinoStr brachio("Brachiosaurus", brachioTexture2, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);
				DinoStr tirex("Tyrannosaurus", tirexTexture2, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);
				dinosStr1.push_back(brachio);
				dinosStr1.push_back(tirex);

				DinoDex stego("Stegosaurus", stegoTexture2, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);
				DinoDex tricera("Triceratops", triceraTexture2, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);
				dinosDex1.push_back(stego);
				dinosDex1.push_back(tricera);

				DinoInt diplo("Diplodocus", diploTexture2, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);
				dinosInt1.push_back(diplo);

				int enemyDino1 = rand() % 5 + 1;
				auto& firstEnemyDino = chooseEnemyDino(dinosStr1, dinosDex1, dinosInt1, enemyDino1);

				int enemyDino2 = rand() % 5 + 1;
				while (enemyDino2 == enemyDino1) {
					enemyDino2 = rand() % 5 + 1;
				}
				auto& secondEnemyDino = chooseEnemyDino(dinosStr1, dinosDex1, dinosInt1, enemyDino2);

				int enemyDino3 = rand() % 5 + 1;
				while (enemyDino3 == enemyDino1 || enemyDino3 == enemyDino2) {
					enemyDino3 = rand() % 5 + 1;
				}
				auto& thirdEnemyDino = chooseEnemyDino(dinosStr1, dinosDex1, dinosInt1, enemyDino3);

				int i = 0;
				int j = 0;
				int terr = rand() % 3;

				if (terr == 0) {
					terrain = PLAIN;
					terrainText.setString("PLAIN");
				}
				else if (terr == 1) {
					terrain = RIVER;
					terrainText.setString("RIVER");
				}
				else {
					terrain = MOUNTAIN;
					terrainText.setString("MOUNTAIN");
				}
				window.clear(sf::Color::Cyan);
				window.draw(firstDino.sprite());
				fightText.setString("HP: " + std::to_string(firstDino.getHP()));
				fightText.setPosition(350, 4 * window.getSize().y / 5);
				window.draw(firstEnemyDino.sprite());
				fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
				fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
				window.display();
				Sleep(1000);

				int damage, enemyDamage;

				while (i < 3 && j < 3) {
					if (i == 0) {
						damage = firstDino.damage(terrain);
					}

					else if (i == 1) {
						damage = secondDino.damage(terrain);
					}

					else {
						damage = thirdDino.damage(terrain);
					}

					if (j == 0) {
						enemyDamage = firstEnemyDino.damage(terrain);
					}

					else if (j == 1) {
						enemyDamage = secondEnemyDino.damage(terrain);
					}

					else {
						enemyDamage = thirdEnemyDino.damage(terrain);
					}

					window.clear(sf::Color::Cyan);
					fightText.setFillColor(sf::Color::Red);
					if (i == 0) {
						window.draw(firstDino.sprite());
						fightText.setString("HP: " + std::to_string(firstDino.getHP()));
					}
					else if (i == 1) {
						window.draw(secondDino.sprite());
						fightText.setString("HP: " + std::to_string(secondDino.getHP()));
					}
					else {
						window.draw(thirdDino.sprite());
						fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
					}
					fightText.setPosition(350, 4 * window.getSize().y / 5);
					window.draw(fightText);

					if (i == 0) {
						window.draw(firstEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
					}
					else if (i == 1) {
						window.draw(secondEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
					}
					else {
						window.draw(thirdEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
					}
					fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
					window.draw(fightText);
					window.display();
					Sleep(500);

					window.clear(sf::Color::Cyan);
					fightText.setFillColor(sf::Color::Magenta);
					if (i == 0) {
						window.draw(firstDino.sprite());
						fightText.setString("HP: " + std::to_string(firstDino.getHP()));
					}
					else if (i == 1) {
						window.draw(secondDino.sprite());
						fightText.setString("HP: " + std::to_string(secondDino.getHP()));
					}
					else {
						window.draw(thirdDino.sprite());
						fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
					}
					fightText.setPosition(350, 4 * window.getSize().y / 5);
					window.draw(fightText);

					if (i == 0) {
						window.draw(firstEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
					}
					else if (i == 1) {
						window.draw(secondEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
					}
					else {
						window.draw(thirdEnemyDino.sprite());
						fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
					}
					fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
					window.draw(fightText);
					window.display();
					Sleep(500);

					if (i == 0) {
						firstDino.takeDamage(enemyDamage);
					}

					else if (i == 1) {
						secondDino.takeDamage(enemyDamage);
					}

					else {
						thirdDino.takeDamage(enemyDamage);
					}

					if (j == 0) {
						firstEnemyDino.takeDamage(damage);
					}

					else if (j == 1) {
						secondEnemyDino.takeDamage(damage);
					}

					else {
						thirdEnemyDino.takeDamage(damage);
					}

					if (i == 0 && firstDino.getHP() == 0) {
						firstDino.changeTexture(tombTexture, 100, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (dino1 <= dinosStr.size()) {
							dinosStr.erase(dinosStr.begin() + (dino1 - 1));
						}
						else if (dino1 <= dinosStr.size() + dinosDex.size()) {
							dinosDex.erase(dinosDex.begin() + (dino1 - dinosStr.size() - 1));
						}
						else {
							dinosInt.erase(dinosInt.begin() + (dino1 - dinosStr.size() - dinosDex.size() - 1));
						}

						if (dino2 > dino1) {
							dino2 -= 1;
						}

						if (dino3 > dino1) {
							dino3 -= 1;
						}

						i += 1;
					}

					else if (i == 1 && secondDino.getHP() == 0) {
						secondDino.changeTexture(tombTexture, 100, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (dino2 <= dinosStr.size()) {
							dinosStr.erase(dinosStr.begin() + (dino2 - 1));
						}
						else if (dino2 <= dinosStr.size() + dinosDex.size()) {
							dinosDex.erase(dinosDex.begin() + (dino2 - dinosStr.size() - 1));
						}
						else {
							dinosInt.erase(dinosInt.begin() + (dino2 - dinosStr.size() - dinosDex.size() - 1));
						}

						if (dino3 > dino2) {
							dino3 -= 1;
						}

						i += 1;
					}

					else if (i == 2 && thirdDino.getHP() == 0) {
						thirdDino.changeTexture(tombTexture, 100, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (dino3 <= dinosStr.size()) {
							dinosStr.erase(dinosStr.begin() + (dino3 - 1));
						}
						else if (dino3 <= dinosStr.size() + dinosDex.size()) {
							dinosDex.erase(dinosDex.begin() + (dino3 - dinosStr.size() - 1));
						}
						else {
							dinosInt.erase(dinosInt.begin() + (dino3 - dinosStr.size() - dinosDex.size() - 1));
						}

						i += 1;
					}

					if (j == 0 && firstEnemyDino.getHP() == 0) {
						firstEnemyDino.changeTexture(tombTexture, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (enemyDino1 <= dinosStr1.size()) {
							dinosStr1.erase(dinosStr1.begin() + (enemyDino1 - 1));
						}
						else if (enemyDino1 <= dinosStr1.size() + dinosDex1.size()) {
							dinosDex1.erase(dinosDex1.begin() + (enemyDino1 - dinosStr1.size() - 1));
						}
						else {
							dinosInt1.erase(dinosInt1.begin() + (enemyDino1 - dinosStr1.size() - dinosDex1.size() - 1));
						}

						if (enemyDino2 > enemyDino1) {
							enemyDino2 -= 1;
						}

						if (enemyDino3 > enemyDino1) {
							enemyDino3 -= 1;
						}

						j += 1;
					}

					else if (j == 1 && secondEnemyDino.getHP() == 0) {
						secondEnemyDino.changeTexture(tombTexture, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (enemyDino2 <= dinosStr1.size()) {
							dinosStr1.erase(dinosStr1.begin() + (enemyDino2 - 1));
						}
						else if (enemyDino2 <= dinosStr1.size() + dinosDex1.size()) {
							dinosDex1.erase(dinosDex1.begin() + (enemyDino2 - dinosStr1.size() - 1));
						}
						else {
							dinosInt1.erase(dinosInt1.begin() + (enemyDino2 - dinosStr1.size() - dinosDex1.size() - 1));
						}

						if (enemyDino3 > enemyDino2) {
							enemyDino3 -= 1;
						}

						j += 1;
					}

					else if (j == 2 && thirdEnemyDino.getHP() == 0) {
						thirdEnemyDino.changeTexture(tombTexture, 4 * window.getSize().x / 5, 4 * window.getSize().y / 5);

						window.clear(sf::Color::Cyan);
						if (i == 0) {
							window.draw(firstDino.sprite());
							fightText.setString("HP: " + std::to_string(firstDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondDino.sprite());
							fightText.setString("HP: " + std::to_string(secondDino.getHP()));
						}
						else {
							window.draw(thirdDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdDino.getHP()));
						}
						fightText.setPosition(350, 4 * window.getSize().y / 5);
						window.draw(fightText);

						if (i == 0) {
							window.draw(firstEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(firstEnemyDino.getHP()));
						}
						else if (i == 1) {
							window.draw(secondEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(secondEnemyDino.getHP()));
						}
						else {
							window.draw(thirdEnemyDino.sprite());
							fightText.setString("HP: " + std::to_string(thirdEnemyDino.getHP()));
						}
						fightText.setPosition(4 * window.getSize().x / 5 + 250, 4 * window.getSize().y / 5);
						window.draw(fightText);
						window.display();
						Sleep(500);

						if (enemyDino3 <= dinosStr1.size()) {
							dinosStr1.erase(dinosStr1.begin() + (enemyDino3 - 1));
						}
						else if (enemyDino3 <= dinosStr1.size() + dinosDex1.size()) {
							dinosDex1.erase(dinosDex1.begin() + (enemyDino3 - dinosStr1.size() - 1));
						}
						else {
							dinosInt1.erase(dinosInt1.begin() + (enemyDino3 - dinosStr1.size() - dinosDex1.size() - 1));
						}

						j += 1;
					}

					if (i == 3 && j == 3) {
						wind = TIE;
						cash += 700;
					}

					else if (i == 3) {
						wind = LOSE;
						cash += 500;
					}

					else if (j == 3) {
						wind = WIN;
						cash += 1000;
					}
				}

				save(dinosStr, dinosDex, dinosInt, cash);
			}
			else {
				window.clear(sf::Color::Cyan);
				if (!dinosStr.empty() || !dinosDex.empty() || !dinosInt.empty()) {
					int i = 0;
					for (DinoStr dinoStr : dinosStr) {
						if (!activeDinos[i]) {
							dinoStr.sprite().setPosition(100, 100 + 130 * i);
							window.draw(dinoStr.sprite());
							dinoText.setString(dinoStr.dinoInfo());
							dinoText.setPosition(350, 100 + 130 * i);
							window.draw(dinoText);
						}
						i++;
					}
					for (DinoDex dinoDex : dinosDex) {
						if (!activeDinos[i]) {
							dinoDex.sprite().setPosition(100, 100 + 130 * i);
							window.draw(dinoDex.sprite());
							dinoText.setString(dinoDex.dinoInfo());
							dinoText.setPosition(350, 100 + 130 * i);
							window.draw(dinoText);
						}
						i++;
					}
					for (DinoInt dinoInt : dinosInt) {
						if (!activeDinos[i]) {
							dinoInt.sprite().setPosition(100, 100 + 130 * i);
							window.draw(dinoInt.sprite());
							dinoText.setString(dinoInt.dinoInfo());
							dinoText.setPosition(350, 100 + 130 * i);
							window.draw(dinoText);
						}
						i++;
					}
				}
				window.draw(backButtonSprite);
				window.display();
			}
		}

		if (wind == DINOS) {
			window.clear(sf::Color::Cyan);
			if (!dinosStr.empty() || !dinosDex.empty() || !dinosInt.empty()) {
				int i = 0;
				for (DinoStr dinoStr : dinosStr) {
					dinoStr.sprite().setPosition(100, 100 + 130 * i);
					window.draw(dinoStr.sprite());
					dinoText.setString(dinoStr.dinoInfo());
					dinoText.setPosition(350, 100 + 130 * i);
					window.draw(dinoText);
					i++;
				}
				for (DinoDex dinoDex : dinosDex) {
					dinoDex.sprite().setPosition(100, 100 + 130 * i);
					window.draw(dinoDex.sprite());
					dinoText.setString(dinoDex.dinoInfo());
					dinoText.setPosition(350, 100 + 130 * i);
					window.draw(dinoText);
					i++;
				}
				for (DinoInt dinoInt : dinosInt) {
					dinoInt.sprite().setPosition(100, 100 + 130 * i);
					window.draw(dinoInt.sprite());
					dinoText.setString(dinoInt.dinoInfo());
					dinoText.setPosition(350, 100 + 130 * i);
					window.draw(dinoText);
					i++;
				}
			}
			window.draw(backButtonSprite);
			window.display();
		}

		if (wind == WIN) {
			window.clear(sf::Color::Cyan);
			window.draw(winText);
			window.draw(backButtonSprite);
			window.display();
		}

		if (wind == LOSE) {
			window.clear(sf::Color::Cyan);
			window.draw(defeatText);
			window.draw(backButtonSprite);
			window.display();
		}

		if (wind == TIE) {
			window.clear(sf::Color::Cyan);
			window.draw(tieText);
			window.draw(backButtonSprite);
			window.display();
		}
	}
	inStream.close();
}