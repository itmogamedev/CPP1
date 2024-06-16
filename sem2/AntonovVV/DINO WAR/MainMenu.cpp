#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Menu.h"

void Main_Menu() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("DINO WARS");
    text.setCharacterSize(150);
    text.setFillColor(sf::Color::White);
    sf::Vector2f centerPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2,centerPos.y - text.getGlobalBounds().height / 2 - 400);

    sf::Text Profile_button, Shop_button, Play_button;
    Profile_button.setFont(font);
    Shop_button.setFont(font);
    Play_button.setFont(font);

    Profile_button.setString("Profile");
    Shop_button.setString("Shop");
    Play_button.setString("Play");
    Profile_button.setCharacterSize(75);
    Shop_button.setCharacterSize(75);
    Play_button.setCharacterSize(75);

    Profile_button.setFillColor(sf::Color::White);
    Play_button.setFillColor(sf::Color::White);
    Shop_button.setFillColor(sf::Color::White);

    Profile_button.setPosition(centerPos.x - Profile_button.getGlobalBounds().width / 2 - 450,centerPos.y - Profile_button.getGlobalBounds().height / 2 +360);
    Shop_button.setPosition(centerPos.x - Shop_button.getGlobalBounds().width / 2 + 50,centerPos.y - Shop_button.getGlobalBounds().height / 2 + 360);
    Play_button.setPosition(centerPos.x - Play_button.getGlobalBounds().width / 2 + 550,centerPos.y - Play_button.getGlobalBounds().height / 2 + 360);


    sf::Texture img;
    img.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(img);

    sf::Texture exitButton;
    exitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png");
    sf::Sprite exitButtonImage(exitButton);
    exitButtonImage.setScale(2, 2);
    exitButtonImage.setPosition(10, 10);



    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(exitButtonImage);
        window.draw(Profile_button);
        window.draw(Shop_button);
        window.draw(Play_button);
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            switch (event.type) {
                case sf::Event::KeyPressed :
                    event.key.code = sf::Keyboard::Escape;
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Start_Menu();
                    }
                    if (Profile_button.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Profile_Menu();
                    }
                    if (Shop_button.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Shop_Menu();
                    }
                    if (Play_button.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Battle_Menu();
                    }
                }
                case sf :: Event :: MouseMoved: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));
                    if (Profile_button.getGlobalBounds().contains(mousePosF)) {
                        Profile_button.setFillColor(sf :: Color :: Green);
                    }
                    else Profile_button.setFillColor(sf :: Color :: White);
                    if (Shop_button.getGlobalBounds().contains(mousePosF)) {
                        Shop_button.setFillColor(sf :: Color :: Green);
                    }
                    else Shop_button.setFillColor(sf :: Color :: White);
                    if (Play_button.getGlobalBounds().contains(mousePosF)) {
                        Play_button.setFillColor(sf :: Color :: Green);
                    }
                    else Play_button.setFillColor(sf :: Color :: White);

                }
            }

        }
    }
}