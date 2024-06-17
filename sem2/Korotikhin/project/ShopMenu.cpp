#include "Graphics.h"
#include "DatabaseFunc.hpp"


void shopWindowPrint(){
    
    sf::RenderWindow shopWindow(sf::VideoMode(800,600), "Dino Battle",sf::Style::Resize);

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
    sf::Text kuroNamespaceText;
    kuroNamespaceText.setString(Kuro().name);
    kuroNamespaceText.setFont( font );
    kuroNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    kuroNamespaceText.setCharacterSize( 40 );
    kuroNamespaceText.setPosition( 60, 80 );

    sf::Text lokiNamespaceText;
    lokiNamespaceText.setString(Loki().name);
    lokiNamespaceText.setFont( font );
    lokiNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    lokiNamespaceText.setCharacterSize( 40 );
    lokiNamespaceText.setPosition( 60, 250 );

    sf::Text monoNamespaceText;
    monoNamespaceText.setString(Mono().name);
    monoNamespaceText.setFont( font );
    monoNamespaceText.setFillColor( sf::Color(0,197,208,230) );
    monoNamespaceText.setCharacterSize( 40 );
    monoNamespaceText.setPosition( 60, 420 );

    //dino sprite
    //KURO SPRITE
    sf::Texture dinoKuroTexture;
    if ( !dinoKuroTexture.loadFromFile( resourcePath() + "dinoAssets/Kuro/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoKuroSprite(dinoKuroTexture,sf::IntRect(0,0,24,24));
    dinoKuroSprite.setPosition(0, 100);
    dinoKuroSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //COLE SPRITE
    sf::Texture dinoLokiTexture;
    if ( !dinoLokiTexture.loadFromFile( resourcePath() + "dinoAssets/Loki/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoLokiSprite(dinoLokiTexture,sf::IntRect(0,0,24,24));
    dinoLokiSprite.setPosition(0, 270);
    dinoLokiSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //sprite MONO
    sf::Texture dinoMonoTexture;
    if ( !dinoMonoTexture.loadFromFile( resourcePath() + "dinoAssets/Mono/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoMonoSprite(dinoMonoTexture,sf::IntRect(0,0,24,24));
    dinoMonoSprite.setPosition(0, 440);
    dinoMonoSprite.setScale(sf::Vector2f(7.0f,7.0f));

    //dino characteristics text
    //KIRA CHARACTERISTICS
    sf::Text dinoKuroCharacteristics("Strength - " + std::to_string(Kuro().STRENGTH) + "\nDexteriry - " + std::to_string(Kuro().DEXTERITY) + "\nIntelegience - " + std::to_string(Kuro().INTELLIGENCE), font, 40);
    dinoKuroCharacteristics.setFillColor(sf::Color::Black);
    dinoKuroCharacteristics.setStyle(sf::Text::Bold);
    dinoKuroCharacteristics.setPosition(sf::Vector2f(200,115));

    //COLE CHARACTERISTICS
    sf::Text dinoLokiCharacteristics("Strength - " + std::to_string(Loki().STRENGTH) + "\nDexteriry - " + std::to_string(Loki().DEXTERITY) + "\nIntelegience - " + std::to_string(Loki().INTELLIGENCE), font, 40);
    dinoLokiCharacteristics.setFillColor(sf::Color::Black);
    dinoLokiCharacteristics.setStyle(sf::Text::Bold);
    dinoLokiCharacteristics.setPosition(sf::Vector2f(200,285));

    //MONO CHARACTERISTICS
    sf::Text dinoMonoCharacteristics("Strength - " + std::to_string(Mono().STRENGTH) + "\nDexteriry - " + std::to_string(Mono().DEXTERITY) + "\nIntelegience - " + std::to_string(Mono().INTELLIGENCE), font, 40);
    dinoMonoCharacteristics.setFillColor(sf::Color::Black);
    dinoMonoCharacteristics.setStyle(sf::Text::Bold);
    dinoMonoCharacteristics.setPosition(sf::Vector2f(200,455));


    //dino button
    //BUTTON FOR KURO
    sf::Text buttonKuroBuyText;
    float buttonKuroBuyTextWidth = buttonKuroBuyText.getLocalBounds().width;
    float buttonKuroBuyTextHeight = buttonKuroBuyText.getLocalBounds().height;
    buttonKuroBuyText.setFont( font );
    buttonKuroBuyText.setStyle( sf::Text::Regular );
    buttonKuroBuyText.setString( "BUY" );
    buttonKuroBuyText.setFillColor( sf::Color::Black );
    buttonKuroBuyText.setCharacterSize( 55 );
    buttonKuroBuyText.setPosition(sf::Vector2f(600,145));

    //BUTTON FOR LOKI
    sf::Text buttonLokiBuyText;
    float buttonLokiBuyTextWidth = buttonLokiBuyText.getLocalBounds().width;
    float buttonLokiBuyTextHeight = buttonLokiBuyText.getLocalBounds().height;
    buttonLokiBuyText.setFont( font );
    buttonLokiBuyText.setStyle( sf::Text::Regular );
    buttonLokiBuyText.setString( "BUY" );
    buttonLokiBuyText.setFillColor( sf::Color::Black );
    buttonLokiBuyText.setCharacterSize( 55 );
    buttonLokiBuyText.setPosition(sf::Vector2f(600,290));

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
        
        dinoKuroSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
        dinoLokiSprite.setTextureRect(sf::IntRect(animFrame*24,0,24,24));
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
            shopWindow.draw(buttonKuroBuyText);
            shopWindow.draw(buttonLokiBuyText);
            shopWindow.draw(buttonMonoBuyText);
            
        }
        std::string outputStr;
        
        std::stringstream ss(outInventory);
        
        std::vector<std::string> vector;
        
        
        while (std::getline(ss, outputStr, ' ')) {
            
            vector.push_back(outputStr);
        }
        
        for (int i = 0; i < vector.size(); i++) {
            if (vector[i] == "Kuro") {
                buttonKuroBuyText.setString("Purchased");
                buttonKuroBuyText.setFillColor(sf::Color::Red);
                shopWindow.draw(buttonKuroBuyText);
            }
            else {
                shopWindow.draw(buttonKuroBuyText);
            }
            
            if (vector[i] == "Loki") {
                buttonLokiBuyText.setString("Purchased");
                buttonLokiBuyText.setFillColor(sf::Color::Red);
                shopWindow.draw(buttonLokiBuyText);
            }
            else {
                shopWindow.draw(buttonLokiBuyText);
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
        shopWindow.draw( dinoKuroSprite );
        shopWindow.draw( dinoLokiSprite );
        shopWindow.draw( dinoMonoSprite );
        shopWindow.draw(backButtonImage);
        
        
        // Draw the string
        shopWindow.draw(title);
        shopWindow.draw(dinoKuroCharacteristics);
        shopWindow.draw(dinoLokiCharacteristics);
        shopWindow.draw(dinoMonoCharacteristics);
        shopWindow.draw(balanceText);
        shopWindow.draw(kuroNamespaceText);
        shopWindow.draw(lokiNamespaceText);
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
                    if ( buttonKuroBuyText.getGlobalBounds().contains( mousePosF ) && buttonKuroBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonKuroBuyText.setFillColor(sf::Color(0,0,0,150));
                    }
                    else
                    {
                        buttonKuroBuyText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for button BUY Cole
                    if ( buttonLokiBuyText.getGlobalBounds().contains( mousePosF ) && buttonLokiBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonLokiBuyText.setFillColor(sf::Color(0,0,0,150));
                    }
                    else
                    {
                        buttonLokiBuyText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for button BUY Mono
                    if ( buttonMonoBuyText.getGlobalBounds().contains( mousePosF ) && buttonMonoBuyText.getString() == "BUY" && outStr != "0")
                    {
                        buttonMonoBuyText.setFillColor(sf::Color(0,0,0,150));
                    }
                    else
                    {
                        buttonMonoBuyText.setFillColor(sf::Color::Black);
                    }
                    
                    //if for exit button
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        backButtonImage.setColor( sf::Color( 255, 255, 255, 150 ) );
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
                    if (buttonKuroBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonKuroBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Kuro().name);
                        buttonKuroBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(1));
                        
                    }
                    if (buttonLokiBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonLokiBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Loki().name);
                        buttonLokiBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(1));
                        
                    }
                    if (buttonMonoBuyText.getGlobalBounds().contains(mousePosF) && outStr != "0" && buttonMonoBuyText.getString() == "BUY")
                    {
                        updateBalance(outStr, Mono().name);
                        buttonMonoBuyText.setString("Purchased");
                        sleep_until(system_clock::now() + seconds(1));
                        
                    }
                    break;
                }
            }
        }
    }
}
