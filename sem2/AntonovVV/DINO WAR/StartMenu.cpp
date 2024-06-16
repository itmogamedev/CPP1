#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

void Start_Menu() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("DINO WARS");
    text.setCharacterSize(150);
    text.setFillColor(sf::Color::White);
    sf::Vector2f centerPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2 - 450);

    sf::Texture img;
    img.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(img);

    sf::Texture exitButton;
    exitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png");
    sf::Sprite exitButtonImage(exitButton);
    exitButtonImage.setScale(2, 2);
    exitButtonImage.setPosition(10, 10);

    sf::Texture startButton;
    startButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/StartButton.png");
    sf::Sprite startButtonImage(startButton);
    startButtonImage.setPosition(centerPos.x - startButtonImage.getGlobalBounds().width / 2 - 100, centerPos.y - startButtonImage.getGlobalBounds().height / 2 + 360);
    startButtonImage.setScale(2.5, 2.5);

    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(exitButtonImage);
        window.draw(startButtonImage);
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
                    }
                    if (startButtonImage.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                        Main_Menu();
                    }
                }
            }
        }
    }
}