#include "AssetManager.hpp"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Player.h"

void Winner(){

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Texture background;
    background.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(background);

    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");

    sf::Text text("Dino Wars", font);
    text.setCharacterSize(150);
    text.setFillColor(sf::Color(sf :: Color :: White));
    text.setStyle(sf::Text::Bold);
    sf::Vector2f centerPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2 + 400,centerPos.y - text.getGlobalBounds().height / 2 - 400);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);

    sf::Text startText;
    startText.setFont(font);
    startText.setStyle( sf::Text::Regular );
    startText.setString( "You win!\n\nFatality." );
    startText.setPosition(750, 300);
    startText.setFillColor( sf::Color::Green);
    startText.setCharacterSize(120);

    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setCharacterSize(50);
    balanceText.setFillColor(sf::Color::White);
    balanceText.setStyle(sf::Text::Bold);
    balanceText.setPosition(850, 900);
    balanceText.setString("Reward: 50$");

    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    exitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png") ;
    exitButtonImage.setPosition(10, 10);
    exitButtonImage.setScale(2, 2);
    exitButtonImage.setTexture(exitButton);

    exitButtonImage.setTexture( exitButton );

    while (window.isOpen()) {

        window.clear();
        window.draw(sprite);
        window.draw(startText);
        window.draw(exitButtonImage);
        window.draw(text);
        window.draw(balanceText);
        window.display();

        sf::Event Event;

        while (window.pollEvent(Event)) {
            switch (Event.type) {

                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        window.close();
                        player.balance += 50;
                        Main_Menu();
                    }
                }
                    break;
            }
        }
    }
}