//
//  Menu.cpp
//  DinoGame
//
//  Created by Nikitoooooozy) on 16.05.2024.
//  Copyright © 2024 Nikitoooooozy). All rights reserved.
//

#include "Graphics.h"

void menuWindowPrint(){
    
    // Create window
    sf::RenderWindow window(sf::VideoMode(800,600,60), "Dino Wars",sf::Style::Resize);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.jpg")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
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
    text.setCharacterSize(115);
    text.setFillColor(sf::Color(0,197,208,230));
    text.setStyle(sf::Text::Bold);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);
    text.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT/2.0f));
    
    //image buttons
    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    if ( !exitButton.loadFromFile( resourcePath() + "exitButton.png" ) )
        std::cout << "Can't find the image" << std::endl;
    float exitButtonWidth = exitButtonImage.getLocalBounds().width;
    float exitButtonHeight = exitButtonImage.getLocalBounds().height;
    exitButtonImage.setPosition( exitButtonWidth, exitButtonHeight );
    
    exitButtonImage.setTexture( exitButton );
    
    //text buttons
    sf::Text startText;
    float startButtonWidth = startText.getLocalBounds().width;
    float startButtonHeight = startText.getLocalBounds().height;
    startText.setFont( font );
    startText.setStyle( sf::Text::Regular );
    startText.setString( "Create New Profile" );
    startText.setFillColor( sf::Color::Black );
    startText.setCharacterSize( 55 );
    startText.setPosition( 50.0f, 320.0f );
    
    sf::Text profileText;
    float profileTextWidth = profileText.getLocalBounds().width;
    float profileTextHeight = profileText.getLocalBounds().height;
    profileText.setFont( font );
    profileText.setStyle( sf::Text::Regular );
    profileText.setString( "Profile" );
    profileText.setFillColor( sf::Color::Black );
    profileText.setCharacterSize( 55 );
    profileText.setPosition( 50.0f, 380.0f );
    
    sf::Text shopText;
    float shopButtonWidth = shopText.getLocalBounds().width;
    float shopButtonHeight = shopText.getLocalBounds().height;
    shopText.setFont( font );
    shopText.setStyle( sf::Text::Regular );
    shopText.setString( "Shop" );
    shopText.setFillColor( sf::Color::Black );
    shopText.setCharacterSize( 55 );
    shopText.setPosition( 50.0f, 440.0f );
    
    sf::Text battleText;
    float battleTextWidth = battleText.getLocalBounds().width;
    float battleTextHeight = battleText.getLocalBounds().height;
    battleText.setFont( font );
    battleText.setStyle( sf::Text::Regular );
    battleText.setString( "BATTLE" );
    battleText.setFillColor( sf::Color::Black );
    battleText.setCharacterSize( 75 );
    battleText.setPosition( 540.0f, 440.0f );
    
    
    
    
    
    // Start the game loop
    while (window.isOpen())
    {
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(sprite);
        
        //Draw the buttons
        window.draw( exitButtonImage );
        window.draw( startText );
        window.draw( profileText );
        window.draw( shopText );
        window.draw(battleText);
        // Draw the string
        window.draw(text);
        
        // Update the window
        window.display();
        
        // Process events
        sf::Event Event;
        
        
        
        while (window.pollEvent(Event))
        {
            switch ( Event.type )
            {
                    break;
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
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
                    
                    //if for start button
                    if ( startText.getGlobalBounds().contains( mousePosF ) )
                    {
                        startText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        startText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for profile button
                    if ( profileText.getGlobalBounds().contains( mousePosF ) )
                    {
                        profileText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        profileText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for shop button
                    if ( shopText.getGlobalBounds().contains( mousePosF ) )
                    {
                        shopText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        shopText.setFillColor(sf::Color::Black);
                    }
                    //if for battle button
                    if ( battleText.getGlobalBounds().contains( mousePosF ) )
                    {
                        battleText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        battleText.setFillColor(sf::Color::Black);
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if exit button pressed
                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        window.close();
                    }
                    //if user registers a new profile
                    if ( startText.getGlobalBounds().contains( mousePosF ) )
                    {
                        window.close();
                        registrationWindowPrint();
                    }
                    //if button shop pressed
                    if ( shopText.getGlobalBounds().contains( mousePosF ))
                    {
                        window.close();
                        shopWindowPrint();
                    }
                    //if button profile pressed
                    if ( profileText.getGlobalBounds().contains( mousePosF ))
                    {
                        window.close();
                        profileWindowPrint();
                    }
                    //if user starts battle
                    if (battleText.getGlobalBounds().contains(mousePosF))
                    {
                        window.close();
                        startingBattleWindowPrint();
                    }
                }
                    break;
            }
        }
    }
}
