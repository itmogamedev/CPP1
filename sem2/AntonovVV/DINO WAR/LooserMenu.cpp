#include "AssetManager.hpp"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Player.h"

void Looser(){

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Texture background;
    background.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");;
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
    startText.setFont( font );
    startText.setStyle( sf::Text::Regular );
    startText.setString( "Wasted." );
    startText.setFillColor( sf::Color::Green);
    startText.setCharacterSize(120);
    startText.setPosition(700, 300);

    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    exitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png") ;
    exitButtonImage.setPosition(10, 10);
    exitButtonImage.setScale(2, 2);
    exitButtonImage.setTexture(exitButton);

    sf::Texture ghost;
    sf::Sprite ghostSprite;
    ghost.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Olaf/ghost/idle.png");
    ghostSprite.setPosition(800, 450 );
    ghostSprite.setScale(sf::Vector2f(10.0f, 10.0f));
    ghostSprite.setTexture(ghost );

    int frameNum = 3;
    float animationDuration = 1;
    sf::Time elapsedTime;
    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();
        elapsedTime += deltaTime;
        float timeAsSecond = elapsedTime.asSeconds();

        int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;

        ghostSprite.setTextureRect(sf::IntRect(animFrame * 24,0,24,24));

        window.clear();
        window.draw(sprite);
        window.draw(startText);
        window.draw(exitButtonImage);
        window.draw(ghostSprite);
        window.draw(text);
        window.display();

        sf::Event Event;

        while (window.pollEvent(Event)) {
            switch (Event.type) {

                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        window.close();
                        Main_Menu();
                    }
                }
                    break;
            }
        }
    }
}