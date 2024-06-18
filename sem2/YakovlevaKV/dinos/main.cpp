#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "inventory.hpp"
#include "shop.hpp"
#include "fight.hpp"
#include "endoffight.hpp"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;


int main()
{
    sf::Music main;
    main.openFromFile("main.ogg");
    main.play();
    main.setLoop(true);
    sf::RenderWindow win(sf::VideoMode(1920, 1080), "DINO-FIGHT!");
    sf::Texture Texforback;
    Texforback.loadFromFile("main.png");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);
    background.setPosition(sf::Vector2f(0, 0));

    sf::Font font;
    if (!font.loadFromFile("FontOver.otf")) {
        return EXIT_FAILURE;
    }
 
    sf::Text logo("Dinosaur Fight", font);
    logo.setCharacterSize(100);
    logo.setFillColor(sf::Color(0,0,0));
    logo.setStyle(sf::Text::Bold);
    logo.setPosition(sf::Vector2f(670, 30));

    sf::Text button1("Start", font);
    button1.setCharacterSize(100);
    button1.setFillColor(sf::Color(0,0,0));
    button1.setStyle(sf::Text::Bold);
    button1.setPosition(sf::Vector2f(760, 300));
    
    sf::Text button2("Inventory", font);
    button2.setCharacterSize(100);
    button2.setFillColor(sf::Color(0,0,0));
    button2.setStyle(sf::Text::Bold);
    button2.setPosition(sf::Vector2f(760, 450));
    
    sf::Text button3("Shop", font);
    button3.setCharacterSize(100);
    button3.setFillColor(sf::Color(0,0,0));
    button3.setStyle(sf::Text::Bold);
    button3.setPosition(sf::Vector2f(760, 600));



    int a;
    while (win.isOpen())
    {
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);


        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left) {
                    if (button1.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        main.stop();
                        a = fight(win);
                        main.play();
                        endoffight(win, a);
                    }
                    if (button2.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) inventory(win);
                    if (button3.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) shop(win);
                    
                }

        }

        win.clear();
        win.draw(background);
        win.draw(logo);
        win.draw(button1);
        win.draw(button2);
        win.draw(button3);
        win.display();

    }
    win.close();
    return 0;
}
