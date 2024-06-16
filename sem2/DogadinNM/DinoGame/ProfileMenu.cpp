//
//  ProfileMenu.cpp
//  DinoGame
//
//  Created by Nikitoooooozy) on 16.05.2024.
//  Copyright © 2024 Nikitoooooozy). All rights reserved.
//

#include "Graphics.h"
#include "DatabaseFunc.hpp"
void profileWindowPrint(){
    sf::RenderWindow profileWindow(sf::VideoMode(800,600), "Dino Wars",sf::Style::Resize);
    
    //background
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile(resourcePath() + "background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite spriteBackground(textureBackground);
    
    //font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
        return EXIT_FAILURE;
    }
    
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
    sf::Text title("Your profile: ", font);
    title.setCharacterSize(70);
    title.setFillColor(sf::Color(0,197,208,230));
    title.setStyle(sf::Text::Bold);
    
    //centre upper text
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.width/2,textRect.height/2);
    title.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT * 2.0f));
    
    //dino background sprite
    //DINOS BACKGROUND SPRITE
    sf::Texture backgroundTextureForDinos;
    if ( !backgroundTextureForDinos.loadFromFile( resourcePath() + "dinoAssets/dinosBackground.jpg" ) )
        std::cout << "Can't find the image" << std::endl;
    
    //
    int frameNum = 3;
    float animationDuration = 1;
    sf::Time elapsedTime;
    sf::Clock clock;
    
    
    //dino sprite
    //KIRA SPRITE
    sf::Texture dinoKiraTexture;
    if ( !dinoKiraTexture.loadFromFile( resourcePath() + "dinoAssets/Kira/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoKiraSprite(dinoKiraTexture,sf::IntRect(0,0,24,24));
    dinoKiraSprite.setPosition(50, 270);
    dinoKiraSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Sprite backgroundKiraSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    sf::Text kiraTextName("Kira ", font);
    kiraTextName.setCharacterSize(70);
    kiraTextName.setFillColor(sf::Color(0,197,208,230));
    kiraTextName.setStyle(sf::Text::Bold);
    kiraTextName.setPosition(85, 190);
    backgroundKiraSpriteForDinos.setPosition(70, 270);
    backgroundKiraSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    
    //COLE SPRITE
    sf::Texture dinoColeTexture;
    if ( !dinoColeTexture.loadFromFile( resourcePath() + "dinoAssets/Cole/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoColeSprite(dinoColeTexture,sf::IntRect(0,0,24,24));
    dinoColeSprite.setPosition(305, 270);
    dinoColeSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Text coleTextName("Cole ", font);
    coleTextName.setCharacterSize(70);
    coleTextName.setFillColor(sf::Color(0,197,208,230));
    coleTextName.setStyle(sf::Text::Bold);
    coleTextName.setPosition(340, 190);
    sf::Sprite backgroundColeSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    backgroundColeSpriteForDinos.setPosition(325, 270);
    backgroundColeSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    
    //sprite MONO
    sf::Texture dinoMonoTexture;
    if ( !dinoMonoTexture.loadFromFile( resourcePath() + "dinoAssets/Mono/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoMonoSprite(dinoMonoTexture,sf::IntRect(0,0,24,24));
    dinoMonoSprite.setPosition(550, 270);
    dinoMonoSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Sprite backgroundMonoSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    sf::Text monoTextName("Mono ", font);
    monoTextName.setCharacterSize(70);
    monoTextName.setFillColor(sf::Color(0,197,208,230));
    monoTextName.setStyle(sf::Text::Bold);
    monoTextName.setPosition(585, 190);
    backgroundMonoSpriteForDinos.setPosition(570, 270);
    backgroundMonoSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    
    //text of namespace
    std::string outStrNamespace;
    selectNamespace(outStrNamespace);
    //text of namespace
    sf::Text namespaceText("Namespace: " + outStrNamespace + "  ", font, 60);
    namespaceText.setFillColor(sf::Color::White);
    namespaceText.setStyle(sf::Text::Bold);
    namespaceText.setPosition(sf::Vector2f(30,100));
    //text of balance
    std::string outStrBalance;
    selectBalance(font, outStrBalance);
    sf::Text balanceText("Balance: " + outStrBalance, font, 60);
    balanceText.setFillColor(sf::Color::White);
    balanceText.setStyle(sf::Text::Bold);
    balanceText.setPosition(sf::Vector2f(485,100));
    
        
    
    while (profileWindow.isOpen()) {
        
        sf::Event Event;
        sf::Time deltaTime = clock.restart();
        elapsedTime += deltaTime;
        float timeAsSecond = elapsedTime.asSeconds();
        
        int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;
        
        dinoKiraSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        dinoColeSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        dinoMonoSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        profileWindow.clear();
        profileWindow.draw(spriteBackground);
        profileWindow.draw(backgroundKiraSpriteForDinos);
        profileWindow.draw(backgroundColeSpriteForDinos);
        profileWindow.draw(backgroundMonoSpriteForDinos);
        
        std::string outputStr;
        std::string outInventory;
        selectInventory(outInventory);
        std::stringstream ss(outInventory);
        
        std::vector<std::string> vector;
        
        
        while (std::getline(ss, outputStr, ' ')) {
            
            vector.push_back(outputStr);
        }
        
        for (int i = 0; i < vector.size(); i++) {
            if (vector[i] == "Kira") {
                profileWindow.draw(dinoKiraSprite);
            }
            
            if (vector[i] == "Cole") {
                profileWindow.draw(dinoColeSprite);
            }
            
            if (vector[i] == "Mono") {
                profileWindow.draw(dinoMonoSprite);
            }
            
        }
        
        
        profileWindow.draw(backButtonImage);
        profileWindow.draw(namespaceText);
        profileWindow.draw(balanceText);
        profileWindow.draw(kiraTextName);
        profileWindow.draw(coleTextName);
        profileWindow.draw(monoTextName);
        
        profileWindow.display();
        
        while (profileWindow.pollEvent(Event)) {
            
            switch (Event.type) {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( profileWindow );
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
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( profileWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if exit button pressed
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        profileWindow.close();
                        menuWindowPrint();
                    }
                    break;
                }
            }
        }
    }
    
}
