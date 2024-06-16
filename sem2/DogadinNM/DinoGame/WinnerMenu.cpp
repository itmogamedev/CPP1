//
//  WinnerMenu.cpp
//  DinoGame
//
//  Created by Nikitoooooozy) on 17.05.2024.
//  Copyright © 2024 Nikitoooooozy). All rights reserved.
//

#include "includes.h"
#include "Graphics.h"
#include "DatabaseFunc.hpp"
void winnerWindowPrint(){
    // Create window
    sf::RenderWindow winnerWindow(sf::VideoMode(800,600,60), "Dino Wars",sf::Style::Resize);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.jpg")) {
        return EXIT_FAILURE;
    }
    winnerWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    //font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
        return EXIT_FAILURE;
    }
    //
    sf::Text text("Dino Wars", font);
    text.setCharacterSize(165);
    text.setFillColor(sf::Color(0,197,208,230));
    text.setStyle(sf::Text::Bold);

    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);
    text.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f));


    //text buttons
    sf::Text startText;
    float startButtonWidth = startText.getLocalBounds().width;
    float startButtonHeight = startText.getLocalBounds().height;
    startText.setFont( font );
    startText.setStyle( sf::Text::Regular );
    startText.setString( "You are the winner!!!" );
    startText.setPosition(150, 400);
    startText.setFillColor( sf::Color::Black );
    startText.setCharacterSize( 75 );


    //text of balance
    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setCharacterSize(50);
    balanceText.setFillColor(sf::Color::Black);
    balanceText.setStyle(sf::Text::Bold);
    balanceText.setPosition(10, 300);
    balanceText.setString("You've collected 25 coins to your balance");
    
    //image buttons
    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    if ( !exitButton.loadFromFile( resourcePath() + "exitButton.png" ) )
        std::cout << "Can't find the image" << std::endl;
    float exitButtonWidth = exitButtonImage.getLocalBounds().width;
    float exitButtonHeight = exitButtonImage.getLocalBounds().height;
    exitButtonImage.setPosition( exitButtonWidth, exitButtonHeight );

    exitButtonImage.setTexture( exitButton );
    
    while (winnerWindow.isOpen()) {
        winnerWindow.clear();
        
        winnerWindow.draw(sprite);
        winnerWindow.draw(startText);
        winnerWindow.draw(exitButtonImage);
        winnerWindow.draw(text);
        winnerWindow.draw(balanceText);
        winnerWindow.display();
        
        sf::Event Event;
        
        while (winnerWindow.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( winnerWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for exit button
                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        exitButtonImage.setColor( sf::Color( 250, 20, 20 ) );
                    }
                    else
                    {
                        exitButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( winnerWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if exit button pressed
                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        winnerWindow.close();
                        updateBalanceAfterWin();
                        menuWindowPrint();
                    }
                }
                    break;
            }
        }
    }
}
