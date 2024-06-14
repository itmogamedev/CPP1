#pragma once

#include <random>
#include <cstdlib>
#include <ctime>
#include <windows.h>


enum Dinosaurus { Tyrannosaurus = 1, Stegosaurus = 2, Triceratops = 3};
int damageValue;

class Dino {
protected:
	int strength = std::rand() % 5 + 1;
	int agility = std::rand() % 5 + 1;
	int intelligence = std::rand() % 5 + 1;
public:
	virtual double damage() = 0;
};

class DinoTyrannosaurus : public Dino {
public:
	double damage() override {
		damageValue = damageValue + strength * 0.5;
		return damageValue;
	}
};

class DinoStegosaurus : public Dino {
public:
	double damage() override {
		damageValue = damageValue + agility * 0.3;
		return damageValue;
	}
};

class DinoTriceratops : public Dino {
public:
	double damage() override {
		damageValue = damageValue + intelligence * 0.2;
		return damageValue;
	}
};

class Player {
public:
	double damage(Dino* dino) {
		return dino->damage(); // return results of method damage()
	}
};

enum Terrain { Plane, River, Mountain };
Terrain getRandomTerrain() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 2);

	return static_cast<Terrain>(distrib(gen));
}

void loadingTexture(int& cntSelected, int& pickNum, sf::Texture& selectedDino1Texture, \
	sf::Texture& selectedDino2Texture, sf::Texture& selectedDino3Texture) {
	if (cntSelected == 0) {
		if (pickNum == 1) {
			selectedDino1Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino1Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino1Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
	if (cntSelected == 1) {
		if (pickNum == 1) {
			selectedDino2Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino2Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino2Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
	if (cntSelected == 2) {
		if (pickNum == 1) {
			selectedDino3Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino3Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino3Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
}

void loadingTextureBot(int& i, int pullBot[3], sf::Texture& botDino1Texture, sf::Texture& botDino2Texture, sf::Texture& botDino3Texture) {
	if (pullBot[i] == 1) {
		if (i == 0) {
			botDino1Texture.loadFromFile("images/TyrannosaurusFightBot.png");
		}
		if (i == 1) {
			botDino2Texture.loadFromFile("images/TyrannosaurusFightBot.png");
		}
		if (i == 2) {
			botDino3Texture.loadFromFile("images/TyrannosaurusFightBot.png");
		}
	}
	if (pullBot[i] == 2) {
		if (i == 0) {
			botDino1Texture.loadFromFile("images/StegosaurusFightBot.png");
		}
		if (i == 1) {
			botDino2Texture.loadFromFile("images/StegosaurusFightBot.png");
		}
		if (i == 2) {
			botDino3Texture.loadFromFile("images/StegosaurusFightBot.png");
		}
	}
	if (pullBot[i] == 3) {
		if (i == 0) {
			botDino1Texture.loadFromFile("images/TriceratopsFightBot.png");
		}
		if (i == 1) {
			botDino2Texture.loadFromFile("images/TriceratopsFightBot.png");
		}
		if (i == 2) {
			botDino3Texture.loadFromFile("images/TriceratopsFightBot.png");
		}
	}
	
}


void actionFight(sf::Event& event, sf::RenderWindow& window, sf::Font& font, sf::Sprite& terrainSprite, \
	sf::Sprite& nameTerrainSprite, sf::Text& balance, sf::Text& earnedBalance, \
	std::string& pullUser, Terrain& randomTerrain, int& coinsUser, int& coinsEarned, \
	int& cntUserTyrannosaurus, int& cntUserStegosaurus, int& cntUserTriceratops) {

	bool mousePressed = false;
	bool flagBreak = false;
	int wasAttacked = 0;
	int dinoUser, dinoBot, userAttack, botAttack, userDinoHealth, botDinoHealth;
	std::string dinoBot1, dinoBot2, dinoBot3, pullBot;
	sf::Texture dinoUserTexture, dinoBotTexture;

	sf::Text damageTaken("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	damageTaken.setStyle(sf::Text::Bold);//������ �����
	damageTaken.setFillColor(sf::Color::Black);
	sf::Text damageGiven("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	damageGiven.setStyle(sf::Text::Bold);//������ �����
	damageGiven.setFillColor(sf::Color::Black);
	sf::Text userDinoHealthText("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	userDinoHealthText.setStyle(sf::Text::Bold);//������ �����
	userDinoHealthText.setFillColor(sf::Color::Black);
	sf::Text botDinoHealthText("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	botDinoHealthText.setStyle(sf::Text::Bold);//������ �����
	botDinoHealthText.setFillColor(sf::Color::Black);
	sf::Text fightFinallyText("", font, 80);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	fightFinallyText.setStyle(sf::Text::Bold);//������ �����
	fightFinallyText.setFillColor(sf::Color::Black);
	fightFinallyText.setPosition(470, 400);
	
	//�������� ����������� �������
	userDinoHealth = 100;
	botDinoHealth = 100;
	Player player;
	DinoTyrannosaurus dinoTyrannosaurus;
	DinoStegosaurus dinoStegosaurus;
	DinoTriceratops dinoTriceratops;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	dinoBot1 = std::to_string(std::rand() % 3 + 1);
	dinoBot2 = std::to_string(std::rand() % 3 + 1);
	dinoBot3 = std::to_string(std::rand() % 3 + 1);
	pullBot = dinoBot1 + dinoBot2 + dinoBot3;

	
	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (pullUser.length() == 0) { fightFinallyText.setString("YOU LOSE"); fightFinallyText.setFillColor(sf::Color::Red); flagBreak = true; }
		if (pullBot.length() == 0) { fightFinallyText.setString("YOU WON"); fightFinallyText.setFillColor(sf::Color::Green); flagBreak = true; }
		
		window.clear();
		dinoUser = pullUser[0] - '0';
		dinoBot = pullBot[0] - '0';

		//�������� ������� ��
		sf::RectangleShape userDinoHealthIndicator(sf::Vector2f(4 * userDinoHealth, 20));
		userDinoHealthIndicator.setFillColor(sf::Color::Green);
		userDinoHealthIndicator.setPosition(100, 300);
		sf::RectangleShape botDinoHealthIndicator(sf::Vector2f(4 * botDinoHealth, 20));
		botDinoHealthIndicator.setFillColor(sf::Color::Green);
		botDinoHealthIndicator.setPosition(700, 300);

		//������� ���������� ���������� ����� �������
		switch (dinoUser) {
		case Dinosaurus::Tyrannosaurus:
			userAttack = player.damage(&dinoTyrannosaurus);
			break;
		case Dinosaurus::Stegosaurus:
			userAttack = player.damage(&dinoStegosaurus);
			break;
		case Dinosaurus::Triceratops:
			userAttack = player.damage(&dinoTriceratops);
			break;
		}

		switch (dinoUser) {
		case Dinosaurus::Tyrannosaurus:
			dinoUserTexture.loadFromFile("images/TyrannosaurusFightUser.png");
			break;
		case Dinosaurus::Stegosaurus:
			dinoUserTexture.loadFromFile("images/StegosaurusFightUser.png");
			break;
		case Dinosaurus::Triceratops:
			dinoUserTexture.loadFromFile("images/TriceratopsFightUser.png");
			break;
		}
		switch (dinoBot) {
		case Dinosaurus::Tyrannosaurus:
			dinoBotTexture.loadFromFile("images/TyrannosaurusFightBot.png");
			break;
		case Dinosaurus::Stegosaurus:
			dinoBotTexture.loadFromFile("images/StegosaurusFightBot.png");
			break;
		case Dinosaurus::Triceratops:
			dinoBotTexture.loadFromFile("images/TriceratopsFightBot.png");
			break;
		}

		sf::Sprite dinoUserSprite(dinoUserTexture), dinoBotSprite(dinoBotTexture);
		dinoUserSprite.setPosition(100, 300);
		dinoBotSprite.setPosition(800, 300);
		dinoUserSprite.setRotation(0);
		dinoBotSprite.setRotation(0);
		//������� �� ���������� � ��������� �����
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		wasAttacked = 0;
		if (dinoBotSprite.getGlobalBounds().contains(worldPos)) {
			wasAttacked = 1;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (wasAttacked == 1 && !mousePressed) {
				mousePressed = true;
				dinoUserSprite.move(200, 0);
				Sleep(100);
				dinoUserSprite.setRotation(30);
				dinoBotSprite.setColor(sf::Color::Magenta);
				if ((randomTerrain == Terrain::Plane && dinoUser == 1) || (randomTerrain == Terrain::River && dinoUser == 2) || (randomTerrain == Terrain::Mountain && dinoUser == 3)) {
					botDinoHealth -= (userAttack * 2) % 30;
				}
				else {
					botDinoHealth -= (userAttack) % 20;
				}
				Sleep(100);
				botAttack = std::rand() % 10 + 5;
				userDinoHealth -= botAttack;
				dinoBotSprite.move(-200, 0);
				Sleep(100);
				dinoBotSprite.setRotation(-30);
				dinoUserSprite.setColor(sf::Color::Magenta);
			}
		}
		else {
			mousePressed = false; // ���������� ����, ����� ������ ���� ��������
		}
		if (userDinoHealth < 0) { userDinoHealth = 0; }
		if (botDinoHealth < 0) { botDinoHealth = 0; }
		//���������� ���������� ��
		userDinoHealthText.setString(std::to_string(userDinoHealth));
		botDinoHealthText.setString(std::to_string(botDinoHealth));
		userDinoHealthText.setPosition(100, 300);
		botDinoHealthText.setPosition(700, 300);
		//��������� �����, ������� � ����
		window.draw(terrainSprite);
		window.draw(nameTerrainSprite);
		window.draw(userDinoHealthIndicator);
		window.draw(botDinoHealthIndicator);
		window.draw(userDinoHealthText);
		window.draw(botDinoHealthText);
		
		if (userDinoHealth <= 0) {
			dinoUserSprite.setPosition(100, 300);
			dinoUserSprite.setRotation(0);
			dinoUserSprite.setColor(sf::Color::Red);
			// erase - delete symbols from the line
			// begin - pointer to the start of massive
			dinoUserSprite.setRotation(-90);
			pullUser.erase(pullUser.begin());
			if (!pullUser.length() == 0) {
				userDinoHealth = 100;
			}
			Sleep(100);
		}
		if (botDinoHealth <= 0) {
			dinoBotSprite.setPosition(800, 300);
			dinoBotSprite.setRotation(0);
			dinoBotSprite.setColor(sf::Color::Red);
			dinoBotSprite.setRotation(90);
			pullBot.erase(pullBot.begin());
			coinsEarned = coinsEarned + (std::rand() % 10 + 10);
			coinsUser = coinsUser + coinsEarned;
			if (!pullBot.length() == 0) {
				botDinoHealth = 100;
			}
			Sleep(100);
		}
		window.draw(dinoUserSprite);
		window.draw(dinoBotSprite);
		window.draw(fightFinallyText);
		//���������� ������� �����
		balance.setString("Balance: " + std::to_string(coinsUser));
		earnedBalance.setString("Earned coins: " + std::to_string(coinsEarned));
		window.draw(balance);
		window.draw(earnedBalance);

		window.display();
		Sleep(100);
		if (flagBreak) {
			if (pullUser.length() != 0) {
				for (int k = 0; k < pullUser.length(); ++k) {
					if (pullUser[k] == '1') {
						cntUserTyrannosaurus++;
					}
					else if (pullUser[k] == '2') {
						cntUserStegosaurus++;
					}
					else if (pullUser[k] == '3') {
						cntUserTriceratops++;
					}
				}
			}
			break; 
			
		}
	}
}

void handleFight(sf::Event& event, sf::RenderWindow& window, sf::Font& font,\
	sf::Texture& terrainTexture, sf::Texture& nameTerrain, \
	sf::Text& balance, sf::Text& earnedBalance, int& cntUserTyrannosaurus, \
	int& cntUserStegosaurus, int& cntUserTriceratops, int& coinsUser, \
	int& coinsEarned) {
	Terrain randomTerrain = getRandomTerrain();
	std::string pullUser;
	int pickNum = 0, cntSelected = 0;
	bool mousePressed = false;

	sf::Texture selectedDino1Texture, selectedDino2Texture, selectedDino3Texture;
	
	// �������� ������ ��� ������ ����
	sf::RectangleShape select1(sf::Vector2f(50, 50));
	select1.setFillColor(sf::Color::White);
	select1.setPosition(400, 210);
	sf::RectangleShape select2(sf::Vector2f(50, 50));
	select2.setFillColor(sf::Color::White);
	select2.setPosition(400, 310);
	sf::RectangleShape select3(sf::Vector2f(50, 50));
	select3.setFillColor(sf::Color::White);
	select3.setPosition(400, 410);
	sf::RectangleShape buttonFight(sf::Vector2f(150, 60));
	buttonFight.setFillColor(sf::Color::White);
	buttonFight.setPosition(1050, 740);

	//������� ���������� ����������
	sf::Text cntUserTyrannosaurusText("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserStegosaurusText("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserTriceratopsText("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTriceratopsText.setStyle(sf::Text::Bold);//������ �����
	//������� ���� ������
	sf::Text userPull("YOUR PULL", font, 80);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	userPull.setFillColor(sf::Color::Green);
	userPull.setStyle(sf::Text::Bold);//������ �����
	sf::Text buttonFightText("Fight!", font, 60);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	buttonFightText.setFillColor(sf::Color::Black);
	buttonFightText.setStyle(sf::Text::Bold);

	cntUserTyrannosaurusText.setPosition(20, 200);
	cntUserStegosaurusText.setPosition(20, 300);
	cntUserTriceratopsText.setPosition(20, 400);
	userPull.setPosition(800, 20);
	buttonFightText.setPosition(1070, 730);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//����� ��������� ���������
		switch (randomTerrain) {
		case Terrain::Plane:
			terrainTexture.loadFromFile("images/plane.png");
			nameTerrain.loadFromFile("images/name-plain.png");
			break;
		case Terrain::River:
			terrainTexture.loadFromFile("images/river.png");
			nameTerrain.loadFromFile("images/name-river.png");
			break;
		case Terrain::Mountain:
			terrainTexture.loadFromFile("images/mountain.png");
			nameTerrain.loadFromFile("images/name-mountain.png");
		}
		//��������� ���������
		sf::Sprite terrainSprite(terrainTexture), nameTerrainSprite(nameTerrain);
		nameTerrainSprite.setPosition(550, 10);
		nameTerrainSprite.setColor(sf::Color::White);

		//����� ����� ������
		select1.setFillColor(sf::Color::White);
		select2.setFillColor(sf::Color::White);
		select3.setFillColor(sf::Color::White);
		buttonFight.setFillColor(sf::Color::White);

		window.clear();
		window.draw(terrainSprite);
		window.draw(nameTerrainSprite);
		window.draw(balance);
		window.draw(earnedBalance);

		//��������� ������� �� ������ ������
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		pickNum = 0;
		if (select1.getGlobalBounds().contains(worldPos)) {
			pickNum = 1;
		}
		if (select2.getGlobalBounds().contains(worldPos)) {
			pickNum = 2;
		}
		if (select3.getGlobalBounds().contains(worldPos)) {
			pickNum = 3;
		}
		if (buttonFight.getGlobalBounds().contains(worldPos)) {
			buttonFight.setFillColor(sf::Color::Blue);
			pickNum = 4;
		}

		//������� �� ������ ������
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			if (pickNum == 1 && !mousePressed) {
				if (cntUserTyrannosaurus > 0 && cntSelected < 3) {
					select1.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					cntUserTyrannosaurus--;
					pullUser += "1";
					cntSelected++;
					mousePressed = true;
				}
				else { select1.setFillColor(sf::Color::Red); }
			}
			if (pickNum == 2 && !mousePressed) {
				if (cntUserStegosaurus > 0 && cntSelected < 3) {
					select2.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					cntUserStegosaurus--;
					pullUser += "2";
					cntSelected++;
					mousePressed = true;
				}
				else { select2.setFillColor(sf::Color::Red); }
			}
			if (pickNum == 3 && !mousePressed) {
				if (cntUserTriceratops > 0 && cntSelected < 3) {
					select3.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					cntUserTriceratops--;
					pullUser += "3";
					cntSelected++;
					mousePressed = true;
				}
				else { select3.setFillColor(sf::Color::Red); }
			}
			
		}
		else {
			mousePressed = false; // ���������� ����, ����� ������ ���� ��������
		}
		//���������� ���������� ����
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceratopsText.setString("Triceratops: " + std::to_string(cntUserTriceratops));
		//�������� �������� ��� �������� ��������� ����
		sf::Sprite selectedDino1(selectedDino1Texture), selectedDino2(selectedDino2Texture), selectedDino3(selectedDino3Texture);
		selectedDino1.setPosition(800, 100);
		selectedDino2.setPosition(800, 300);
		selectedDino3.setPosition(800, 500);
		// ����� ���������� ���� � ���������
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceratopsText);
		window.draw(userPull);
		window.draw(select1);
		window.draw(select2);
		window.draw(select3);
		window.draw(buttonFight);
		window.draw(buttonFightText);
		window.draw(selectedDino1);
		window.draw(selectedDino2);
		window.draw(selectedDino3);

		window.display();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (pickNum == 4) {
				actionFight(event, window, font, terrainSprite, \
					nameTerrainSprite, balance, earnedBalance, pullUser, randomTerrain, \
					coinsUser, coinsEarned, cntUserTyrannosaurus, \
					cntUserStegosaurus, cntUserTriceratops); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen());
			}
		}
	}
}