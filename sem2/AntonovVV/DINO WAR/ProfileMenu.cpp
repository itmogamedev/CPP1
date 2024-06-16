#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Textbox.hpp"
#include "Player.h"

void Profile_Menu() {
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

    sf::Text enter_text, success;

    enter_text.setFont(font);
    success.setFont(font);

    enter_text.setString("Enter your nickname:");
    success.setString("Success!");
    enter_text.setCharacterSize(75);
    success.setCharacterSize(100);

    enter_text.setFillColor(sf::Color::White);
    success.setFillColor(sf::Color::White);

    enter_text.setPosition(centerPos.x - enter_text.getGlobalBounds().width / 2 - 500,centerPos.y - enter_text.getGlobalBounds().height / 2 + 360);
    success.setPosition(centerPos.x - success.getGlobalBounds().width / 2 - 250,centerPos.y - success.getGlobalBounds().height / 2 + 360);


    sf::Texture img;
    img.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(img);

    sf::Texture exitButton;
    exitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png");
    sf::Sprite exitButtonImage(exitButton);
    exitButtonImage.setScale(2, 2);
    exitButtonImage.setPosition(10, 10);

    Textbox textbox(window, font);
    textbox.setDimensons(1000, 870, 600, 100);
    textbox.setFocus(true);
    sf::Text title;

    bool success_flag = false;


    std::ofstream file("C:/Users/Asus/CLionProjects/HelloSFML/Nickname.txt");
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(exitButtonImage);
        if (success_flag == true) window.draw(success);
        else window.draw(enter_text);
        textbox.draw();
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            switch (event.type) {

                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Main_Menu();
                    }
                }

            }

            std::string enteringText = textbox.getString();
            if (!success_flag) {
                textbox.pollEvent(event);
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
            {
                player.nickname = enteringText;
                file << enteringText;
                success_flag = true;
                file.close();
            }
        }
    }
}
