#pragma once
#include "End.h"
#include "Help.h"
#include "GameMenu.h"
#include <sstream>

void Victory(sf::RenderWindow& window)
{
    sf::Font MC;
    sf::Color color1 = sf::Color(4, 255, 67);
    sf::Color color2 = sf::Color(0, 202, 51);
    MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
    sf::Text Exit(L"Выход", MC, 40);
    Exit.setFillColor(color1);
    Exit.setOutlineThickness(5);
    Exit.setOutlineColor(color2);
    Exit.setPosition(1000, 620);
    sf::RectangleShape exitButton(sf::Vector2f(240, 55));
    exitButton.setFillColor(sf::Color(0, 0, 0, 0));
    exitButton.setPosition(990, 610);

    sf::Text Fail(L"Потрачено", MC, 80);
    Fail.setFillColor(sf::Color::Green);
    Fail.setOutlineThickness(5);
    Fail.setOutlineColor(sf::Color(150, 0, 3));
    Fail.setPosition(280, 290);


    bool isMouseOver = false;
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            else if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = false;
            }

        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                isMenuActive = 1;
            }

        }
        if (event.type == sf::Event::Closed)
            window.close();
        window.display();
    }

    window.clear(sf::Color::Black);
    window.draw(Exit);
    window.draw(Fail);
    window.draw(exitButton);
}


void Fail(sf::RenderWindow& window)
{
    sf::Font MC;
    sf::Color color1 = sf::Color(4, 255, 67);
    sf::Color color2 = sf::Color(0, 202, 51);
    MC.loadFromFile("font/minecraft_title_cyrillic.ttf");
    sf::Text Exit(L"Выход", MC, 40);
    Exit.setFillColor(color1);
    Exit.setOutlineThickness(5);
    Exit.setOutlineColor(color2);
    Exit.setPosition(1000, 620);
    sf::RectangleShape exitButton(sf::Vector2f(240, 55));
    exitButton.setFillColor(sf::Color(0, 0, 0, 0));
    exitButton.setPosition(990, 610);

    sf::Text Fail(L"Потрачено", MC, 80);
    Fail.setFillColor(sf::Color::Red);
    Fail.setOutlineThickness(5);
    Fail.setOutlineColor(sf::Color(150, 0, 3));
    Fail.setPosition(280, 290);


    bool isMouseOver = false;
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            else if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = false;
            }

        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                isMenuActive = 1;
            }
         
        }
        if (event.type == sf::Event::Closed)
            window.close();
        window.display();
    }

    window.clear(sf::Color::Black);
    window.draw(Exit);
    window.draw(Fail);
    window.draw(exitButton);

}