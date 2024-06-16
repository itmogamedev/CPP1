#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Dino.h"
#include "Player.h"

void Battle_Menu()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");

    sf::Texture img;
    img.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(img);

    sf::Text readyButton;
    readyButton.setFont(font );
    readyButton.setStyle(sf::Text::Regular );
    readyButton.setString("Ready?");
    readyButton.setFillColor(sf::Color::White);
    readyButton.setCharacterSize(75);
    readyButton.setPosition(sf::Vector2f(900, 935));

    sf::Text text;
    text.setFont(font);
    text.setString("Pick 3 your dinos");
    text.setCharacterSize(75);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(700, 935));

    sf::Text kiraText;
    kiraText.setString("Kira");
    kiraText.setFont(font);
    kiraText.setFillColor(sf::Color::Green);
    kiraText.setCharacterSize(40);
    kiraText.setPosition(710,80);

    sf::Text kuroText;
    kuroText.setString("Kuro");
    kuroText.setFont(font);
    kuroText.setFillColor(sf::Color::Green);
    kuroText.setCharacterSize(40);
    kuroText.setPosition(710,250);

    sf::Text mortText;
    mortText.setString("Mort");
    mortText.setFont(font);
    mortText.setFillColor(sf::Color::Green);
    mortText.setCharacterSize(40);
    mortText.setPosition(710,420);

    sf::Text olafText;
    olafText.setString("Olaf");
    olafText.setFont(font);
    olafText.setFillColor(sf::Color::Green);
    olafText.setCharacterSize(40);
    olafText.setPosition(710,590);

    sf::Texture dinoKiraTexture;
    dinoKiraTexture.loadFromFile( "C:/Users/Asus/CLionProjects/HelloSFML/kira/base/idle.png");
    sf::Sprite dinoKiraSprite(dinoKiraTexture,sf::IntRect(0,0,24,24));
    dinoKiraSprite.setPosition(650, 100);
    dinoKiraSprite.setScale(sf::Vector2f(7.0f,7.0f));

    sf::Texture dinoKuroTexture;
    dinoKuroTexture.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/kuro/base/idle.png" );
    sf::Sprite dinoKuroSprite(dinoKuroTexture, sf::IntRect(0, 0, 24, 24));
    dinoKuroSprite.setPosition(650, 270);
    dinoKuroSprite.setScale(sf::Vector2f(7.0f, 7.0f));

    sf::Texture dinoMortTexture;
    dinoMortTexture.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/mort/base/idle.png" );
    sf::Sprite dinoMortSprite(dinoMortTexture, sf::IntRect(0, 0, 24, 24));
    dinoMortSprite.setPosition(650, 440);
    dinoMortSprite.setScale(sf::Vector2f(7.0f, 7.0f));

    sf::Texture dinoOlafTexture;
    dinoOlafTexture.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/olaf/base/idle.png" );
    sf::Sprite dinoOlafSprite(dinoOlafTexture, sf::IntRect(0, 0, 24, 24));
    dinoOlafSprite.setPosition(650, 610);
    dinoOlafSprite.setScale(sf::Vector2f(7.0f,7.0f));

    sf::Text dinoKiraCharacteristics("Strength - " + std::to_string(Kira().STRENGTH) + "\nDexteriry - " + std::to_string(Kira().DEXTERITY) + "\nIntelegience - " + std::to_string(Kira().INTELLIGENCE), font, 40);
    dinoKiraCharacteristics.setFillColor(sf::Color::White);
    dinoKiraCharacteristics.setStyle(sf::Text::Bold);
    dinoKiraCharacteristics.setPosition(sf::Vector2f(850,115));

    sf::Text dinoKuroCharacteristics("Strength - " + std::to_string(Kuro().STRENGTH) + "\nDexteriry - " + std::to_string(Kuro().DEXTERITY) + "\nIntelegience - " + std::to_string(Kuro().INTELLIGENCE), font, 40);
    dinoKuroCharacteristics.setFillColor(sf::Color::White);
    dinoKuroCharacteristics.setStyle(sf::Text::Bold);
    dinoKuroCharacteristics.setPosition(sf::Vector2f(850, 285));

    sf::Text dinoMortCharacteristics("Strength - " + std::to_string(Mort().STRENGTH) + "\nDexteriry - " + std::to_string(Mort().DEXTERITY) + "\nIntelegience - " + std::to_string(Mort().INTELLIGENCE), font, 40);
    dinoMortCharacteristics.setFillColor(sf::Color::White);
    dinoMortCharacteristics.setStyle(sf::Text::Bold);
    dinoMortCharacteristics.setPosition(sf::Vector2f(850, 455));

    sf::Text dinoOlafCharacteristics("Strength - " + std::to_string(Olaf().STRENGTH) + "\nDexteriry - " + std::to_string(Olaf().DEXTERITY) + "\nIntelegience - " + std::to_string(Olaf().INTELLIGENCE), font, 40);
    dinoOlafCharacteristics.setFillColor(sf::Color::White);
    dinoOlafCharacteristics.setStyle(sf::Text::Bold);
    dinoOlafCharacteristics.setPosition(sf::Vector2f(850, 625));


    sf::Text pickButtonKira;
    pickButtonKira.setFont(font );
    pickButtonKira.setStyle(sf::Text::Regular );
    pickButtonKira.setString("pick");
    pickButtonKira.setFillColor(sf::Color::White);
    pickButtonKira.setCharacterSize(55 );
    pickButtonKira.setPosition(sf::Vector2f(1250, 145));

    sf::Text pickButtonKuro;
    pickButtonKuro.setFont(font );
    pickButtonKuro.setStyle(sf::Text::Regular );
    pickButtonKuro.setString("pick" );
    pickButtonKuro.setFillColor(sf::Color::White );
    pickButtonKuro.setCharacterSize(55 );
    pickButtonKuro.setPosition(sf::Vector2f(1250, 290));

    sf::Text pickButtonMort;
    pickButtonMort.setFont(font );
    pickButtonMort.setStyle(sf::Text::Regular );
    pickButtonMort.setString("pick" );
    pickButtonMort.setFillColor(sf::Color::White );
    pickButtonMort.setCharacterSize(55 );
    pickButtonMort.setPosition(sf::Vector2f(1250, 470));

    sf::Text pickButtonOlaf;
    pickButtonOlaf.setFont(font );
    pickButtonOlaf.setStyle(sf::Text::Regular );
    pickButtonOlaf.setString("pick" );
    pickButtonOlaf.setFillColor(sf::Color::White);
    pickButtonOlaf.setCharacterSize(55 );
    pickButtonOlaf.setPosition(sf::Vector2f(1250, 650));

    sf::Texture ExitButton;
    sf::Sprite ExitButtonImage;
    ExitButton.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/ExitButton.png") ;
    ExitButtonImage.setPosition(10, 10);
    ExitButtonImage.setScale(2, 2);
    ExitButtonImage.setTexture(ExitButton);

    int frameNum = 3;
    float animationDuration = 1;

    sf::Time elapsedTime;
    sf::Clock clock;
    int counter = 0;

    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();
        elapsedTime += deltaTime;
        float timeAsSecond = elapsedTime.asSeconds();
        int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;

        dinoKiraSprite.setTextureRect(sf::IntRect(animFrame * 24,0,24,24));
        dinoKuroSprite.setTextureRect(sf::IntRect(animFrame * 24, 0, 24, 24));
        dinoMortSprite.setTextureRect(sf::IntRect(animFrame * 24, 0, 24, 24));
        dinoOlafSprite.setTextureRect(sf::IntRect(animFrame * 24, 0, 24, 24));

        sf::Event Event;


        window.clear();
        window.draw(sprite);
        window.draw(ExitButtonImage);

        if (counter == 3) window.draw(readyButton);
        else window.draw(text);

        if (player.pull.count("Kira") == 1)
        {
            window.draw(pickButtonKira);
            window.draw(dinoKiraSprite);
            window.draw(dinoKiraCharacteristics);
            window.draw(kiraText);
        }

        if (player.pull.count("Kuro") == 1)
        {
            window.draw(pickButtonKuro);
            window.draw(dinoKuroSprite);
            window.draw(dinoKuroCharacteristics);
            window.draw(kuroText);
        }

        if (player.pull.count("Mort") == 1)
        {
            window.draw(pickButtonMort);
            window.draw(dinoMortSprite);
            window.draw(dinoMortCharacteristics);
            window.draw(mortText);
        }

        if (player.pull.count("Olaf") == 1)
        {
            window.draw(pickButtonOlaf);
            window.draw(dinoOlafSprite);
            window.draw(dinoOlafCharacteristics);
            window.draw(olafText);
        }

        window.display();

        while (window.pollEvent(Event))
        {
            switch ( Event.type )
            {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if (pickButtonKira.getGlobalBounds().contains(mousePosF ) && pickButtonKira.getString() == "pick" )
                    {
                        pickButtonKira.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        pickButtonKira.setFillColor(sf::Color::White);
                    }

                    if (pickButtonKuro.getGlobalBounds().contains(mousePosF ) && pickButtonKuro.getString() == "pick")
                    {
                        pickButtonKuro.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        pickButtonKuro.setFillColor(sf::Color::White);
                    }

                    if (pickButtonMort.getGlobalBounds().contains(mousePosF ) && pickButtonMort.getString() == "pick")
                    {
                        pickButtonMort.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        pickButtonMort.setFillColor(sf::Color::White);
                    }

                    if (pickButtonOlaf.getGlobalBounds().contains(mousePosF ) && pickButtonOlaf.getString() == "pick")
                    {
                        pickButtonOlaf.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        pickButtonOlaf.setFillColor(sf::Color::White);
                    }

                    if (readyButton.getGlobalBounds().contains(mousePosF ))
                    {
                        readyButton.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        readyButton.setFillColor(sf::Color::White);
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    //if exit button pressed
                    if ( ExitButtonImage.getGlobalBounds().contains(mousePosF ) )
                    {
                        window.close();
                        Main_Menu();
                    }
                    if (pickButtonKira.getGlobalBounds().contains(mousePosF) && pickButtonKira.getString() == "pick" && counter < 3 )
                    {
                        pickButtonKira.setString("picked");
                        player.vecPull.push_back(Kira().name);
                        counter++;
                    }
                    if (pickButtonKuro.getGlobalBounds().contains(mousePosF) && pickButtonKuro.getString() == "pick" && counter < 3)
                    {
                        pickButtonKuro.setString("picked");
                        player.vecPull.push_back(Kuro().name);
                        counter++;
                    }
                    if (pickButtonMort.getGlobalBounds().contains(mousePosF) && pickButtonMort.getString() == "pick" && counter < 3)
                    {
                        pickButtonMort.setString("picked");
                        player.vecPull.push_back(Mort().name);
                        counter++;
                    }
                    if (pickButtonOlaf.getGlobalBounds().contains(mousePosF) && pickButtonOlaf.getString() == "pick"&& counter < 3)
                    {
                        pickButtonOlaf.setString("picked");
                        player.vecPull.push_back(Olaf().name);
                        counter++;
                    }
                    if (readyButton.getGlobalBounds().contains(mousePosF))
                    {
                        window.close();
                        Battle();
                    }
                    break;
                }
            }
        }
    }

}