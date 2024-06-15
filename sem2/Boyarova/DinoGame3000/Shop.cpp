#pragma once
#include "Shop.h"
#include "Help.h"
#include "Player.h"
#include <sstream>
using namespace sf;


void GameShop(sf::RenderWindow& window)
{
    Player player;
    player.LoadGame("data.txt");
    static int B = player.getCoins();
    std::vector <bool> Info = player.getInfo();
    int price = 200;

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


    std::ostringstream Bal;  
    Bal << player.getCoins();	
    sf::Text Balance;
    Balance.setFont(MC);
    Balance.setString(L"Баланс: " + Bal.str());
    Balance.setCharacterSize(24);
    Balance.setPosition(50, 660);
    Balance.setOutlineThickness(4);
    Balance.setOutlineColor(sf::Color(255, 201, 14));
    Balance.setFillColor(sf::Color(255, 242, 0));

    sf::Text TDino1(L"200", MC, 20);
    TDino1.setFont(MC);
    TDino1.setPosition(170, 500);
    TDino1.setOutlineThickness(4);
    TDino1.setOutlineColor(sf::Color(255, 201, 14));
    TDino1.setFillColor(sf::Color(255, 242, 0));
    sf::Text TDino2(L"200", MC, 20);
    TDino2.setFont(MC);
    TDino2.setPosition(455, 500);
    TDino2.setOutlineThickness(4);
    TDino2.setOutlineColor(sf::Color(255, 201, 14));
    TDino2.setFillColor(sf::Color(255, 242, 0));
    sf::Text TDino3(L"200", MC, 20);
    TDino3.setFont(MC);
    TDino3.setPosition(740, 500);
    TDino3.setOutlineThickness(4);
    TDino3.setOutlineColor(sf::Color(255, 201, 14));
    TDino3.setFillColor(sf::Color(255, 242, 0));
    sf::Text TDino4(L"200", MC, 20);
    TDino4.setFont(MC);
    TDino4.setPosition(1025, 500);
    TDino4.setOutlineThickness(4);
    TDino4.setOutlineColor(sf::Color(255, 201, 14));
    TDino4.setFillColor(sf::Color(255, 242, 0));


    Texture Dino1, Dino2, Dino3, Dino4, Dino12, Dino22, Dino32, Dino42, Dino13, Dino23, Dino33, Dino43;
    Dino1.loadFromFile("images/DCyno.jpg");
    Dino2.loadFromFile("images/DNari.jpg");
    Dino3.loadFromFile("images/DKaveh.jpg");
    Dino4.loadFromFile("images/DHaitam.jpg");
    Dino12.loadFromFile("images/CCyno.jpg");
    Dino22.loadFromFile("images/CNari.jpg");
    Dino32.loadFromFile("images/CKaveh.jpg");
    Dino42.loadFromFile("images/CHaitam.jpg");
    Dino13.loadFromFile("images/BCyno.jpg");
    Dino23.loadFromFile("images/BNari.jpg");
    Dino33.loadFromFile("images/BKaveh.jpg");
    Dino43.loadFromFile("images/BHaitam.jpg");
    Sprite Sprite1, Sprite2, Sprite3, Sprite4;

    if(Info[0] == false)
        Sprite1.setTexture(Dino1);
    else Sprite1.setTexture(Dino13);
    if (Info[1] == false)
        Sprite2.setTexture(Dino2);
    else Sprite2.setTexture(Dino23);
    if (Info[2] == false)
        Sprite3.setTexture(Dino3);
    else Sprite3.setTexture(Dino33);
    if (Info[3] == false)
        Sprite4.setTexture(Dino4);
    else Sprite4.setTexture(Dino43);

    Sprite1.setPosition(100, 200);
    Sprite2.setPosition(385, 200);
    Sprite3.setPosition(670, 200);
    Sprite4.setPosition(955, 200);

    bool isMouseOver = false;
    Vector2i pixelPos = Mouse::getPosition(window);
    sf::Event event;
    while (window.pollEvent(event) && isMenuActive == 2)
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
                exitButton.setFillColor(sf::Color(0, 0, 0, 0));
                isMouseOver = false;
            }

            else if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver && Info[0] == false)
            {
                Sprite1.setTexture(Dino12);
                isMouseOver = true;
            }
            else if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver && Info[0] == false)
            {
                Sprite1.setTexture(Dino1);
                isMouseOver = false;
            }

            else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver && Info[1] == false)
            {
                Sprite2.setTexture(Dino22);
                isMouseOver = true;
            }
            else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver && Info[1] == false)
            {
                Sprite1.setTexture(Dino2);
                isMouseOver = false;
            }
            else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver && Info[2] == false)
            {
                Sprite3.setTexture(Dino32);
                isMouseOver = true;
            }
            else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver && Info[2] == false)
            {
                Sprite3.setTexture(Dino3);
                isMouseOver = false;
            }

            else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isMouseOver && Info[3] == false)
            {
                Sprite4.setTexture(Dino42);
                isMouseOver = true;
            }
            else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && isMouseOver && Info[3] == false)
            {
                Sprite4.setTexture(Dino4);
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
            else if (Sprite1.getGlobalBounds().contains(sf::Vector2f(mousePos))&& player.getCoins()>=price && Info[0] == false)
            {   
                Info[0] = true;
                player.setDino(Info);
                player.buy(price);
                player.SaveGame("data.txt");
            }
            else if (Sprite2.getGlobalBounds().contains(sf::Vector2f(mousePos)) && player.getCoins() >= price && Info[1] == false)
            {
                Info[1] = true;
                player.setDino(Info);
                player.buy(price);
                player.SaveGame("data.txt");
            }
            else if (Sprite3.getGlobalBounds().contains(sf::Vector2f(mousePos)) && player.getCoins() >= price && Info[2] == false)
            {
                Info[2] = true;
                player.setDino(Info);
                player.buy(price);
                player.SaveGame("data.txt");
            }
            else if (Sprite4.getGlobalBounds().contains(sf::Vector2f(mousePos)) && player.getCoins() >= price && Info[3] == false)
            {
                Info[3] = true;
                player.setDino(Info);
                player.buy(price);
                player.SaveGame("data.txt");
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
        window.display(); 
    }

    window.clear(Color::Black);
    window.draw(Exit);
    window.draw(exitButton);
	window.draw(Sprite1);
    window.draw(Sprite2);
    window.draw(Sprite3);
    window.draw(Sprite4);
    window.draw(Balance);
    window.draw(TDino1);
    window.draw(TDino2);
    window.draw(TDino3);
    window.draw(TDino4);

}