#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "windows.h"

int main()
{
    bool GLFUNC = 1;
    srand(time(NULL));

    sf::RenderWindow death(sf::VideoMode(600, 600), L"Пикачу я выбираю тебя <3");
    sf::Texture ShutDownBall;
    ShutDownBall.loadFromFile("shutdownball.jpg"); // A Picture of pokeball (600x600) https://ih1.redbubble.net/image.2008927970.7248/ur,pin_large_front,square,600x600.jpg
    sf::RectangleShape ballShape(sf::Vector2f(600, 600));
    ballShape.setTexture(&ShutDownBall);
    ballShape.setPosition(0,0);
    ballShape.setFillColor(sf::Color(200, 200, 200));


    while (death.isOpen()) {

        sf::Vector2i mPos = sf::Mouse::getPosition(death);
        sf::Event ev1;

        while (death.pollEvent(ev1)) {

            if (ev1.type == sf::Event::Closed) {
                death.close();
            }

            if (ev1.type == sf::Event::MouseButtonPressed) {
                if (ev1.key.code == sf::Mouse::Left) {
                    if (ballShape.getGlobalBounds().contains(mPos.x, mPos.y)) {
                        ballShape.setFillColor(sf::Color(150, 50, 50));
                        Sleep(100);
                        const int a = rand() % 60;
                        Sleep(a);
                        //system("shutdown -s"); //BE CAREFULL
                    }
                }
            }

            if (ev1.type == sf::Event::MouseButtonReleased) {
                if (ev1.key.code == sf::Mouse::Left) {
                    if (ballShape.getGlobalBounds().contains(mPos.x, mPos.y)) {
                         ballShape.setFillColor(sf::Color(200, 200, 200));
                         GLFUNC = 0;
                         break;
                    }
                }
            }
        }

        death.clear();
        death.draw(ballShape);
        death.display();

        if (GLFUNC == 0) {
            death.close();
            break;
        }
    }

    if (GLFUNC == 0) {

        srand(time(NULL));

        sf::RenderWindow rofl(sf::VideoMode(600, 600), L"LOL");
        sf::Texture haha;
        haha.loadFromFile("haha.jpg"); // A picture of a man laughing at you (600x600) https://litbes.com/wp-content/uploads/2023/10/dbc2d0d925fa3422d16a192f74f650dc.jpg
        sf::RectangleShape HAHAShape(sf::Vector2f(600, 600));
        HAHAShape.setTexture(&haha);
        HAHAShape.setPosition(0, 0);
        HAHAShape.setFillColor(sf::Color(200, 200, 200));

        while (rofl.isOpen()) {

            sf::Vector2i mPos = sf::Mouse::getPosition(rofl);
            sf::Event ev2;

            while (rofl.pollEvent(ev2)) {
                if (ev2.type == sf::Event::Closed)
                    rofl.close();
            }

            rofl.clear();
            rofl.draw(HAHAShape);
            rofl.display();
        }
    }
    return 0;
}
