#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Windows.h>
int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Sumo Tatami GOTY Edition", sf::Style::Titlebar | sf::Style::Close);
	
	sf::Event ev;

	sf::RectangleShape button;
	button.setSize(sf::Vector2f(300, 300));
	button.setOrigin(sf::Vector2f(150, 150));
	button.setPosition(sf::VideoMode::getDesktopMode().width / 2.f, sf::VideoMode::getDesktopMode().height / 2.f);
	button.setFillColor(sf::Color::Cyan);
	button.setOutlineThickness(17);
	button.setOutlineColor(sf::Color::Black);


	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text("Power off", font);
	text.setCharacterSize(60);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(sf::Vector2f(140.f, 50.f));
	text.setPosition(button.getPosition());
	text.setFillColor(sf::Color::Black);
	

	sf::Text text2("SFML TOP", font);
	text2.setCharacterSize(90);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(sf::VideoMode::getDesktopMode().width / 8.f, sf::VideoMode::getDesktopMode().height / 8.f);
	text2.setFillColor(sf::Color::Black);

	int a = 0, t = 0;
	bool isRed = 0, isPressed = 0;
	
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
			case sf::Event::MouseButtonPressed:
				if (ev.mouseButton.button == sf::Mouse::Left) {
					if ( button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) ) {
						text.setString("THX. BYE!");
						isPressed = 1;
					}
				}
				break;
			}
		}
		if (isRed) {
			t += 1;
			if (t >= 100) {
				a += 1;
				t = 0;
			}
			if (a >= 255) {
				isRed = 0;
			}
		}
		else
		{
			t += 1;
			if (t >= 100) {
				a = a - 1;
				t = 0;
			}
			if (a <= 0) {
				isRed = 1;
			}
		}
		
		window.clear(sf::Color(a, 0, 255 - a, 255));
		window.draw(button);
		window.draw(text);
		window.draw(text2);
		window.display();

		if (isPressed) {
			Sleep(2000);
			system("C:\\WINDOWS\\System32\\shutdown /s /t 0");
			isPressed = 0;
		}
	}
    std::cout << "done\n";
}