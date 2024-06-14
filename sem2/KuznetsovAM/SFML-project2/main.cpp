#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "windows.h"
using namespace sf;

int main()
{
    srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(1280, 720),L"Ключ от ядерки");

    Texture Button;
    Button.loadFromFile("button.jpeg");
    RectangleShape ButtonShape(Vector2f(300, 300));
    ButtonShape.setTexture(&Button);
    ButtonShape.setPosition(470, 230);
    ButtonShape.setFillColor(Color(100, 100, 100));

    while (win.isOpen())
    {
        Vector2i mouse_pos=Mouse::getPosition(win);
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    if (ButtonShape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        ButtonShape.setFillColor(Color(255, 0, 0));
                        Sleep(100);
                        const int a = rand() % 60;
                        Sleep(a);
                        system("shutdown -s");
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.key.code == Mouse::Left) {
                    if (ButtonShape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        // ButtonShape.setFillColor(Color(100, 100, 100));
                    }
                }
            }
        }

        win.clear();
        win.draw(ButtonShape);
        win.display();
    }

    return 0;
}