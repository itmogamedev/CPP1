#pragma once

#include <cassert>
#include <iostream>
#include <sstream>

#include "handleFight.h"
#include "handleShop.h"
#include "handleInventory.h"

void menu(sf::Event& event, sf::RenderWindow& window, int& coinsEarned,\
	int& coinsUser, int& cntUserTyrannosaurus, int& cntUserStegosaurus, \
	int& cntUserTriceraptor)
{
	//�������� �������
	sf::Texture menuExit, menuFight, menuShop, menuInventory, terrainTexture, menuBackground, nameTerrain;
	menuExit.loadFromFile("images/my-Exit.png");
	menuFight.loadFromFile("images/my-Fight.png");
	menuShop.loadFromFile("images/my-Shop.png");
	menuInventory.loadFromFile("images/my-Inventory.png");
	menuBackground.loadFromFile("images/menu-background.png");
	sf::Sprite menu1(menuExit), menu2(menuFight), menu3(menuShop), menu4(menuInventory), menuBg(menuBackground);
	int menuNum = 0;
	menu1.setPosition(10, 50);
	menu2.setPosition(10, 100);
	menu3.setPosition(10, 150);
	menu4.setPosition(10, 200);
	menuBg.setPosition(220, 0);

	//������� ������� �����, �������� �������
	sf::Font font;
	font.loadFromFile("Riotun2.ttf");
	sf::Text balance("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	balance.setStyle(sf::Text::Bold);//������ �����
	sf::Text earnedBalance("", font, 30);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	earnedBalance.setStyle(sf::Text::Bold);//������ �����

	//////////////////////////////����///////////////////
	while (window.isOpen()) {
		while (window.pollEvent(event))
		{

			// ����� ���������� �����
			balance.setString("Balance: " + std::to_string(coinsUser));
			balance.setPosition(5, 720);
			earnedBalance.setString("Earned coins: " + std::to_string(coinsEarned));
			earnedBalance.setPosition(5, 750);

			menu1.setColor(sf::Color::White);
			menu2.setColor(sf::Color::White);
			menu3.setColor(sf::Color::White);
			menu4.setColor(sf::Color::White);
			menuNum = 0;
			window.clear(sf::Color(129, 181, 221));

			//������ ������� �������
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

			//�������� ��������� ������� �� ������
			if (menu1.getGlobalBounds().contains(worldPos)) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
			if (menu2.getGlobalBounds().contains(worldPos)) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
			if (menu3.getGlobalBounds().contains(worldPos)) { menu3.setColor(sf::Color::Blue); menuNum = 3; }
			if (menu4.getGlobalBounds().contains(worldPos)) { menu4.setColor(sf::Color::Blue); menuNum = 4; }

			//������� �� ������
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (menuNum == 1) { window.close(); }//���� ������ ������ ������, �� ������� �� ���� 
				if (menuNum == 2) { handleFight(event, window, font, terrainTexture, \
					nameTerrain, balance, earnedBalance, \
					cntUserTyrannosaurus, cntUserStegosaurus, cntUserTriceraptor, \
				coinsUser, coinsEarned); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen()); }
				if (menuNum == 3) { handleShop(event, window, font, balance, earnedBalance, coinsUser,\
					cntUserTyrannosaurus, cntUserStegosaurus, cntUserTriceraptor); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen()); }
				if (menuNum == 4) {handleInventory(event, window, font, balance, earnedBalance, \
					cntUserTyrannosaurus, cntUserStegosaurus, cntUserTriceraptor); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen()); }

			}

			if (event.type == sf::Event::Closed) { window.close();};

			window.draw(menuBg);
			window.draw(menu1);
			window.draw(menu2);
			window.draw(menu3);
			window.draw(menu4);
			window.draw(balance);
			window.draw(earnedBalance);

			window.display();
		}
	}
	////////////////////////////////////////////////////
}