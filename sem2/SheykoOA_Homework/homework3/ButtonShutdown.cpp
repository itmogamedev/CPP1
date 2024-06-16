#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Do not press this button!");

    sf::RectangleShape button(sf::Vector2f(500.0f, 128.0f));
    button.setPosition(150.0f, 250.0f);
    button.setFillColor(sf::Color::White);

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("image.png");

    button.setTexture(&buttonTexture);

    bool buttonEnabled = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && buttonEnabled)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (button.getGlobalBounds().contains(mousePos))
                    {
                        button.setFillColor(sf::Color::Red);
                        buttonEnabled = false;

                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> dis(10000, 60000);
                        int randomNumber = dis(gen);

                        std::this_thread::sleep_for(std::chrono::milliseconds(randomNumber));

                        std::system("shutdown /s /t 0");
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(button);
        window.display();
    }

    return 0;
}
