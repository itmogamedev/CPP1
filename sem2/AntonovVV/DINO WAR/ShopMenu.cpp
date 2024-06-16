#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Dino.h"
#include "Player.h"

void Shop_Menu()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);

    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");

    sf::Texture img;
    img.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");
    sf::Sprite sprite(img);

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


    sf::Text BuyButtonKira;
    BuyButtonKira.setFont(font );
    BuyButtonKira.setStyle(sf::Text::Regular );
    if (player.pull.count("Kira") == 1) BuyButtonKira.setString("Purchased");
    else BuyButtonKira.setString("BUY");
    BuyButtonKira.setFillColor(sf::Color::White);
    BuyButtonKira.setCharacterSize(55 );
    BuyButtonKira.setPosition(sf::Vector2f(1250, 145));

    sf::Text BuyButtonKuro;
    BuyButtonKuro.setFont(font );
    BuyButtonKuro.setStyle(sf::Text::Regular );
    if (player.pull.count("Kuro") == 1) BuyButtonKuro.setString("Purchased");
    else BuyButtonKuro.setString("BUY");
    BuyButtonKuro.setFillColor(sf::Color::White );
    BuyButtonKuro.setCharacterSize(55 );
    BuyButtonKuro.setPosition(sf::Vector2f(1250, 290));

    sf::Text BuyButtonMort;
    BuyButtonMort.setFont(font );
    BuyButtonMort.setStyle(sf::Text::Regular );
    if (player.pull.count("Mort") == 1) BuyButtonMort.setString("Purchased");
    else BuyButtonMort.setString("BUY");
    BuyButtonMort.setFillColor(sf::Color::White );
    BuyButtonMort.setCharacterSize(55 );
    BuyButtonMort.setPosition(sf::Vector2f(1250, 470));

    sf::Text BuyButtonOlaf;
    BuyButtonOlaf.setFont(font );
    BuyButtonOlaf.setStyle(sf::Text::Regular );
    if (player.pull.count("Olaf")) BuyButtonOlaf.setString("Purchased");
    else BuyButtonOlaf.setString("BUY");
    BuyButtonOlaf.setFillColor(sf::Color::White);
    BuyButtonOlaf.setCharacterSize(55 );
    BuyButtonOlaf.setPosition(sf::Vector2f(1250, 650));

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


    std:: ofstream file("C:/Users/Asus/CLionProjects/HelloSFML/Inventory.txt");

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

        sf::Text balanceText("Balance: " + std :: to_string(player.balance) + "$", font, 30);
        balanceText.setFillColor(sf::Color :: Green);
        balanceText.setStyle(sf::Text::Bold);
        balanceText.setPosition(sf::Vector2f(800,40));

        window.draw(BuyButtonKira);
        window.draw(BuyButtonKuro);
        window.draw(BuyButtonMort);
        window.draw(BuyButtonOlaf);

        window.draw(dinoKiraSprite);
        window.draw(dinoKuroSprite);
        window.draw(dinoMortSprite);
        window.draw(dinoOlafSprite);
        window.draw(ExitButtonImage);

        window.draw(dinoKiraCharacteristics);
        window.draw(dinoKuroCharacteristics);
        window.draw(dinoMortCharacteristics);
        window.draw(dinoOlafCharacteristics);
        window.draw(balanceText);
        window.draw(kiraText);
        window.draw(kuroText);
        window.draw(mortText);
        window.draw(olafText);

        window.display();

        while (window.pollEvent(Event))
        {
            switch ( Event.type )
            {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    if (BuyButtonKira.getGlobalBounds().contains(mousePosF ) && BuyButtonKira.getString() == "BUY" )
                    {
                        BuyButtonKira.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        BuyButtonKira.setFillColor(sf::Color::White);
                    }

                    if (BuyButtonKuro.getGlobalBounds().contains(mousePosF ) && BuyButtonKuro.getString() == "BUY")
                    {
                        BuyButtonKuro.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        BuyButtonKuro.setFillColor(sf::Color::White);
                    }

                    if (BuyButtonMort.getGlobalBounds().contains(mousePosF ) && BuyButtonMort.getString() == "BUY")
                    {
                        BuyButtonMort.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        BuyButtonMort.setFillColor(sf::Color::White);
                    }

                    if (BuyButtonOlaf.getGlobalBounds().contains(mousePosF ) && BuyButtonOlaf.getString() == "BUY")
                    {
                        BuyButtonOlaf.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        BuyButtonOlaf.setFillColor(sf::Color::White);
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
                    if (BuyButtonKira.getGlobalBounds().contains(mousePosF) && BuyButtonKira.getString() == "BUY" && player.balance > 0)
                    {
                        player.balance -= 100;
                        BuyButtonKira.setString("Purchased");
                        file << Kira().name << "\n";
                        player.pull.insert(Kira().name);
                    }
                    if (BuyButtonKuro.getGlobalBounds().contains(mousePosF) && BuyButtonKuro.getString() == "BUY" && player.balance > 0)
                    {
                        player.balance -= 100;
                        BuyButtonKuro.setString("Purchased");
                        file << Kuro().name << "\n";
                        player.pull.insert(Kuro().name);
                    }
                    if (BuyButtonMort.getGlobalBounds().contains(mousePosF) && BuyButtonMort.getString() == "BUY" && player.balance > 0)
                    {
                        player.balance -= 100;
                        BuyButtonMort.setString("Purchased");
                        file << Mort().name << "\n";
                        player.pull.insert(Mort().name);
                    }
                    if (BuyButtonOlaf.getGlobalBounds().contains(mousePosF) && BuyButtonOlaf.getString() == "BUY" && player.balance > 0)
                    {
                        player.balance -= 100;
                        BuyButtonOlaf.setString("Purchased");
                        file << Olaf().name << "\n";
                        player.pull.insert(Olaf().name);
                    }
                    break;
                }
            }
        }
    }
}
