#include "endoffight.hpp"





void endoffight(sf::RenderWindow& win, int a)
{
    sf::Texture Texforback;
    Texforback.loadFromFile("main.png");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);
    background.setPosition(sf::Vector2f(0, 0));



    sf::RectangleShape WinSkrin(sf::Vector2f(400, 200));
    WinSkrin.setPosition(sf::Vector2f(760, 300));
    sf::Texture WinTex;
    WinTex.loadFromFile("win.png");
    WinSkrin.setTexture(&WinTex);

    sf::RectangleShape LoseSkrin(sf::Vector2f(400, 200));
    LoseSkrin.setPosition(sf::Vector2f(760, 300));
    sf::Texture LoseTex;
    LoseTex.loadFromFile("lose.png");
    LoseSkrin.setTexture(&LoseTex);
    int c = 0;
    while (win.isOpen() and c == 0)
    {
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);


        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left) {
                    if (background.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        c = 1;
                        if (a == 1) {
                            fstream cash; string path_cash = "cash.txt"; int Scash;
                            cash.open(path_cash, fstream::in | fstream::out); cash >> Scash; cash.close();
                            cash.open(path_cash, fstream::in | fstream::out); cash << Scash + 100; cash.close();
                        }
                    }
                    
                }

        }

        win.clear();
        win.draw(background);
        if (a == 1) { win.draw(WinSkrin); }
        else win.draw(LoseSkrin);
        win.display();

    }
}

