#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sstream>

#include "SFML/graphics.hpp"

void turnOffSystem () {
	int sec, i;
	std::string strOne, strTwo;
	char str_One[50], str_Two[10];
	std::ostringstream intToStr;

	// Pick random number
	srand(time(NULL));
	sec = 10 + rand() % 51;
	std::cout << "The computer will turn off after " << sec << " seconds" << std::endl;


	intToStr << sec;
	strOne = "C:\\Windows\\System32\\shutdown /s /t ";
	strTwo = intToStr.str();
	i = 0;

	// Converting str to char
	while (strOne[i])
	{
		str_One[i] = strOne[i];
		i++;
	}
	str_One[i] = '\0';
	i = 0;
	while (strTwo[i])
	{
		str_Two[i] = strTwo[i];
		i++;
	}
	str_Two[i] = '\0';

	// Replacing the last character of the computer shutdown command with the resulting time in seconds
	strcat_s(str_One, str_Two);
	system(str_One);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Press button");
	int buttonWidth, buttonHeight;
	
	buttonWidth = 800;
	buttonHeight = 400;

	// Creating button
	sf::RectangleShape buttonTurnOffSystem(sf::Vector2f(buttonWidth, buttonHeight));
	buttonTurnOffSystem.setPosition(window.getSize().x / 2 - (buttonWidth / 2), window.getSize().y / 2 - (buttonHeight / 2));
	buttonTurnOffSystem.setFillColor(sf::Color(0, 255, 0));

	while (window.isOpen()) {

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
					if (buttonTurnOffSystem.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						
						turnOffSystem();
						buttonTurnOffSystem.setFillColor(sf::Color(255, 0, 0));
					}
		}
			window.clear();

			window.draw(buttonTurnOffSystem);
			window.display();
	}
	return 0;
}