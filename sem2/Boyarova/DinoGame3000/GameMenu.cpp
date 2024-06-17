#pragma once
#include "Help.h"
#include "GameMenu.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Shop.h"
#include <iostream>
using namespace sf;


void DisplayMenu(sf::RenderWindow& window) {

    sf::Font MC;
    sf::Color color1 = sf::Color(4, 255, 67);
    sf::Color color2 = sf::Color(0, 202, 51);
    MC.loadFromFile("font/minecraft_title_cyrillic.ttf");

    sf::Text Start(L"Играть", MC, 40);
    Start.setFillColor(color1);
    Start.setOutlineThickness(5);
    Start.setOutlineColor(color2);
    Start.setPosition(500, 300);
    sf::RectangleShape startButton(sf::Vector2f(260, 55));
    startButton.setFillColor(sf::Color(0, 0, 0, 0));
    startButton.setPosition(490, 290);

    sf::Text Shop(L"Магазин", MC, 40);
    Shop.setFillColor(color1);
    Shop.setOutlineThickness(5);
    Shop.setOutlineColor(color2);
    Shop.setPosition(478, 370);
    sf::RectangleShape shopButton(sf::Vector2f(310, 55));
    shopButton.setFillColor(sf::Color(0, 0, 0, 0));
    shopButton.setPosition(468, 360);

    sf::Text Info(L"Об игре", MC, 40);
    Info.setFillColor(color1);
    Info.setOutlineThickness(5);
    Info.setOutlineColor(color2);
    Info.setPosition(490, 440);
    sf::RectangleShape infotButton(sf::Vector2f(280, 55));
    infotButton.setFillColor(sf::Color(0, 0, 0, 0));
    infotButton.setPosition(480, 430);

    sf::Text Exit(L"Выход", MC, 40);
    Exit.setFillColor(color1);
    Exit.setOutlineThickness(5);
    Exit.setOutlineColor(color2);
    Exit.setPosition(510, 510);
    sf::RectangleShape exitButton(sf::Vector2f(240, 55));
    exitButton.setFillColor(sf::Color(0, 0, 0, 0));
    exitButton.setPosition(500, 500);

    Text t_header(L"DinoGame3000", MC, 100);
    t_header.setFillColor(Color(0, 193, 0));
    t_header.setOutlineThickness(5);
    t_header.setOutlineColor(Color(0, 94, 0));
    t_header.setPosition(60, 50);
   

    bool isMouseOver = false;
    Vector2i pixelPos = Mouse::getPosition(window);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (startButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                startButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            if (!startButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                startButton.setFillColor(sf::Color(0, 0, 0, 0));
                isMouseOver = false;
            }

            if (shopButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                shopButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            if (!shopButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                shopButton.setFillColor(sf::Color(0, 0, 0, 0));
                isMouseOver = false;
            }

            if (infotButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                infotButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            if (!infotButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                infotButton.setFillColor(sf::Color(0, 0, 0, 0));
                isMouseOver = false;
            }

            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 150));
                isMouseOver = true;
            }
            if (!exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver)
            {
                exitButton.setFillColor(sf::Color(0, 0, 0, 0));
                isMouseOver = false;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                window.close();
            }
            if (shopButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                isMenuActive = 2;
            
            }
            if (infotButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                isMenuActive = 3;

            }
            if (startButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                isMenuActive = 4;

            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
        window.display();
    }

    window.clear(Color::Black);
    window.draw(t_header);
    window.draw(Start);
    window.draw(Shop);
    window.draw(Info);
    window.draw(Exit);
    window.draw(startButton);
    window.draw(shopButton);
    window.draw(infotButton);
    window.draw(exitButton);
  
}
