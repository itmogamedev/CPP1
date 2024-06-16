//
//  ShopMenu.cpp
//  DinoGame
//
//  Created by Nikitoooooozy) on 16.05.2024.
//  Copyright © 2024 Nikitoooooozy). All rights reserved.
//

#include "Graphics.h"
#include "DatabaseFunc.hpp"


void shopWindowPrint(){
    
    sf::RenderWindow shopWindow(sf::VideoMode(800,600), "Dino Wars",sf::Style::Resize);

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

    //dinos names
    sf::Text kiraNamespaceText;
    kiraNamespaceText.setString(Kira().name);
    kiraNamespaceText.setFont( font );
    kiraNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    kiraNamespaceText.setCharacterSize( 40 );
    kiraNamespaceText.setPosition( 60, 80 );

    sf::Text coleNamespaceText;
    coleNamespaceText.setString(Cole().name);
    coleNamespaceText.setFont( font );
    coleNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    coleNamespaceText.setCharacterSize( 40 );
    coleNamespaceText.setPosition( 60, 250 );

    sf::Text monoNamespaceText;
    monoNamespaceText.setString(Mono().name);
    monoNamespaceText.setFont( font );
    monoNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    monoNamespaceText.setCharacterSize( 40 );
    monoNamespaceText.setPosition( 60, 420 );

    //dino sprite
    //KIRA SPRITE
    sf::Texture dinoKiraTexture;
    if ( !dinoKiraTexture.loadFromFile( resourcePath() + "dinoAssets/Kira/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoKiraSprite(dinoKiraTexture,sf::IntRect(0,0,24,24));
    dinoKiraSprite.setPosition(0, 100);
    dinoKiraSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //COLE SPRITE
    sf::Texture dinoColeTexture;
    if ( !dinoColeTexture.loadFromFile( resourcePath() + "dinoAssets/Cole/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoColeSprite(dinoColeTexture,sf::IntRect(0,0,24,24));
    dinoColeSprite.setPosition(0, 270);
    dinoColeSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //sprite MONO
    sf::Texture dinoMonoTexture;
    if ( !dinoMonoTexture.loadFromFile( resourcePath() + "dinoAssets/Mono/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoMonoSprite(dinoMonoTexture,sf::IntRect(0,0,24,24));
    dinoMonoSprite.setPosition(0, 440);
    dinoMonoSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //dino characteristics text
    //KIRA CHARACTERISTICS
    sf::Text dinoKiraCharacteristics("Strength - " + std::to_string(Kira().STRENGTH) + "\nDexteriry - " + std::to_string(Kira().DEXTERITY) + "\nIntelegience - " + std::to_string(Kira().INTELLIGENCE), font, 40);
    dinoKiraCharacteristics.setFillColor(sf::Color::Black);
    dinoKiraCharacteristics.setStyle(sf::Text::Bold);
    dinoKiraCharacteristics.setPosition(sf::Vector2f(200,115));

    //COLE CHARACTERISTICS
    sf::Text dinoColeCharacteristics("Strength - " + std::to_string(Cole().STRENGTH) + "\nDexteriry - " + std::to_string(Cole().DEXTERITY) + "\nIntelegience - " + std::to_string(Cole().INTELLIGENCE), font, 40);
    dinoColeCharacteristics.setFillColor(sf::Color::Black);
    dinoColeCharacteristics.setStyle(sf::Text::Bold);
    dinoColeCharacteristics.setPosition(sf::Vector2f(200,285));

    //MONO CHARACTERISTICS
    sf::Text dinoMonoCharacteristics("Strength - " + std::to_string(Mono().STRENGTH) + "\nDexteriry - " + std::to_string(Mono().DEXTERITY) + "\nIntelegience - " + std::to_string(Mono().INTELLIGENCE), font, 40);
    dinoMonoCharacteristics.setFillColor(sf::Color::Black);
    dinoMonoCharacteristics.setStyle(sf::Text::Bold);
    dinoMonoCharacteristics.setPosition(sf::Vector2f(200,455));


    //dino button
    //BUTTON FOR KIRA
    sf::Text buttonKiraBuyText;
    float buttonKiraBuyTextWidth = buttonKiraBuyText.getLocalBounds().width;
    float buttonKiraBuyTextHeight = buttonKiraBuyText.getLocalBounds().height;
    buttonKiraBuyText.setFont( font );
    buttonKiraBuyText.setStyle( sf::Text::Regular );
    buttonKiraBuyText.setString( "BUY" );
    buttonKiraBuyText.setFillColor( sf::Color::Black );
    buttonKiraBuyText.setCharacterSize( 55 );
    buttonKiraBuyText.setPosition(sf::Vector2f(600,145));

    //BUTTON FOR COLE
    sf::Text buttonColeBuyText;
    float buttonColeBuyTextWidth = buttonColeBuyText.getLocalBounds().width;
    float buttonColeBuyTextHeight = buttonColeBuyText.getLocalBounds().height;
    buttonColeBuyText.setFont( font );
    buttonColeBuyText.setStyle( sf::Text::Regular );
    buttonColeBuyText.setString( "BUY" );
    buttonColeBuyText.setFillColor( sf::Color::Black );
    buttonColeBuyText.setCharacterSize( 55 );
    buttonColeBuyText.setPosition(sf::Vector2f(600,290));

    //BUTTON FOR MONO
    sf::Text buttonMonoBuyText;
    float buttonMonoBuyTextWidth = buttonMonoBuyText.getLocalBounds().width;
    float buttonMonoBuyTextHeight = buttonMonoBuyText.getLocalBounds().height;
    buttonMonoBuyText.setFont( font );
    buttonMonoBuyText.setStyle( sf::Text::Regular );
    buttonMonoBuyText.setString( "BUY" );
    buttonMonoBuyText.setFillColor( sf::Color::Black );
    buttonMonoBuyText.setCharacterSize( 55 );
    buttonMonoBuyText.setPosition(sf::Vector2f(600,470));

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
    sf::Text title("Dino Shop", font);
    title.setCharacterSize(70);
    title.setFillColor(sf::Color(0,197,208,230));
    title.setStyle(sf::Text::Bold);

    //centre upper text
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.width/2,textRect.height/2);
    title.setPosition(sf::Vector2f(SCRWIDTH/2.0f,SCRHEIGHT * 0.05f));


    int frameNum = 3;
    float animationDuration = 1;

    sf::Time elapsedTime;
    sf::Clock clock;

    while (shopWindow.isOpen()) {
        
        sf::Time deltaTime = clock.restart();
        elapsedTime += deltaTime;
        float timeAsSecond = elapsedTime.asSeconds();
        
        int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;
        
        dinoKiraSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        dinoColeSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        dinoMonoSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        
        // Process events
        sf::Event Event;
        
        // Clear screen
        shopWindow.clear();
        shopWindow.draw(spriteBackground);
        std::string outInventory;
        std::string outStr;
        selectInventory(outInventory);
        selectBalance(font, outStr);
        
        //text of balance
        sf::Text balanceText("Balance: " + outStr, font, 30);
        balanceText.setFillColor(sf::Color(0,197,208,230));
        balanceText.setStyle(sf::Text::Bold);
        balanceText.setPosition(sf::Vector2f(600,40));
        
        if (outInventory == "") {
            shopWindow.draw(buttonKiraBuyText);
            shopWindow.draw(buttonColeBuyText);
            shopWindow.draw(buttonMonoBuyText);
            
        }
        std::string outputStr;
        
        std::stringstream ss(outInventory);
        
        std::vector<std::string> vector;
        
        
        while (std::getline(ss, outputStr, ' ')) {
            
            vector.push_back(outputStr);
        }
        
        for (int i = 0; i < vector.size(); i++) {
            if (vector[i] == "Kira") {
                buttonKiraBuyText.setString("Purchased");
                buttonKiraBuyText.setFillColor(sf::Color::Red);
                shopWindow.draw(buttonKiraBuyText);
            }
            else {
                shopWindow.draw(buttonKiraBuyText);
            }
            
            if (vector[i] == "Cole") {
                buttonColeBuyText.setString("Purchased");
                buttonColeBuyText.setFillColor(sf::Color::Red);
                shopWindow.draw(buttonColeBuyText);
            }
            else {
                shopWindow.draw(buttonColeBuyText);
            }
            
            if (vector[i] == "Mono") {
                buttonMonoBuyText.setString("Purchased");
                buttonMonoBuyText.setFillColor(sf::Color::Red);
                shopWindow.draw(buttonMonoBuyText);
            }
            else {
                shopWindow.draw(buttonMonoBuyText);
            }
        }
        
        
        // Draw the sprite
        shopWindow.draw( dinoKiraSprite );
        shopWindow.draw( dinoColeSprite );
        shopWindow.draw( dinoMonoSprite );
        shopWindow.draw(backButtonImage);
        
        
        // Draw the string
        shopWindow.draw(title);
        shopWindow.draw(dinoKiraCharacteristics);
        shopWindow.draw(dinoColeCharacteristics);
        shopWindow.draw(dinoMonoCharacteristics);
        shopWindow.draw(balanceText);
        shopWindow.draw(kiraNamespaceText);
        shopWindow.draw(coleNamespaceText);
        shopWindow.draw(monoNamespaceText);
        
        
        // Update the window
        shopWindow.display();
        
        while (shopWindow.pollEvent(Event))
        {
            switch ( Event.type )
            {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( shopWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for button BUY Kira
                    if ( buttonKiraBuyText.getGlobalBounds().contains( mousePosF ) && buttonKiraBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonKiraBuyText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        buttonKiraBuyText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for button BUY Cole
                    if ( buttonColeBuyText.getGlobalBounds().contains( mousePosF ) && buttonColeBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonColeBuyText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        buttonColeBuyText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for button BUY Mono
                    if ( buttonMonoBuyText.getGlobalBounds().contains( mousePosF ) && buttonMonoBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonMonoBuyText.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        buttonMonoBuyText.setFillColor(sf::Color::Black);
                    }
                    
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
                    sf::Vector2i mousePos = sf::Mouse::getPosition( shopWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if exit button pressed
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        shopWindow.close();
                        menuWindowPrint();
                    }
                    if (buttonKiraBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonKiraBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Kira().name);
                        buttonKiraBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(2));
                        
                    }
                    if (buttonColeBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonColeBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Cole().name);
                        buttonColeBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(2));
                        
                    }
                    if (buttonMonoBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonMonoBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Mono().name);
                        buttonMonoBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(2));
                        
                    }
                    break;
                }
            }
        }
    }
}
