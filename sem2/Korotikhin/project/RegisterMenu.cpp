#include "Graphics.h"
#include "DatabaseFunc.hpp"

void registrationWindowPrint(){
    
    sf::RenderWindow startWindow(sf::VideoMode(800,600), "Dino Wars",sf::Style::Resize);
    
    
    //font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
        return EXIT_FAILURE;
    }
    
    //background
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile(resourcePath() + "background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite spriteBackground(textureBackground);
    
    //button back
    sf::Texture backButton;
    sf::Sprite backButtonImage;
    if ( !backButton.loadFromFile( resourcePath() + "iconButtonBack.png" ) )
        std::cout << "Can't find the image" << std::endl;
    float backButtonWidth = backButtonImage.getLocalBounds().width;
    float backButtonHeight = backButtonImage.getLocalBounds().height;
    backButtonImage.setPosition( backButtonWidth, backButtonHeight );
    
    backButtonImage.setTexture( backButton );
    
    //title
    sf::Text title("Type your nickname", font);
    title.setCharacterSize(70);
    title.setFillColor(sf::Color(0,197,208,230));
    title.setStyle(sf::Text::Bold);
    
    //centre upper text
    title.setPosition(sf::Vector2f(SCRWIDTH/5.0f,SCRHEIGHT * 0.015f));
    
    //text of registration
    sf::Text registeredText("Yep, you've registered", font);
    registeredText.setCharacterSize(70);
    registeredText.setFillColor(sf::Color(0,197,208,230));
    registeredText.setStyle(sf::Text::Bold);
    
    //centre upper text
    registeredText.setPosition(sf::Vector2f(100,300));
    
    //textbox
    Textbox textbox(startWindow, font);
    textbox.setDimensons(100, 200, 400, 30);
    textbox.setFocus(true);
    
    
    
    while (startWindow.isOpen()) {
        // Process events
        sf::Event Event;
        startWindow.draw(spriteBackground);
        startWindow.draw(backButtonImage);
        startWindow.draw(title);
        textbox.draw();
        startWindow.display();
        
        while (startWindow.pollEvent(Event))
        {
            switch ( Event.type )
            {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( startWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for exit button
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        backButtonImage.setColor( sf::Color( 250, 20, 20 ) );
                    }
                    else
                    {
                        backButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                }break;
                    
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( startWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for exit button
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        startWindow.close();
                        menuWindowPrint();
                    }
                }break;
                    
            }
            std::string enteringText = textbox.getString();
            bool didHitReturn = textbox.pollEvent(Event);
            if(didHitReturn) {
                title.setString(enteringText);
            }
            
            if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Return) {
                startWindow.draw(registeredText);
                startWindow.display();
                sleep_until(system_clock::now() + seconds(3));
                
                insertUser(textbox);
                
                textbox.setFocus(false);
            }
        }
    }
}
