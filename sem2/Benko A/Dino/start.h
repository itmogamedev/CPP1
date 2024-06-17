#pragma once

enum class Wind { play, inventory, shop, exit };
Wind chTam(sf::RenderWindow& window, sf::Font& font)
{

    Button playB({ 410, 125 }, { 700, 350 }, sf::Color(20, 230, 230), "play.png");
    Button invB({ 895, 125 }, { 700, 500 }, sf::Color(20, 230, 230), "inventoryb.png");
    Button strB({ 410, 125 }, { 700, 650 }, sf::Color(20, 230, 230), "shopb.png");
    Button extB({ 410, 125 }, { 700, 800 }, sf::Color(20, 230, 230), "exitb.png");

    while (window.isOpen())
    {
        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (playB.clicked(mPos))
                    {
                        playB.color(sf::Color(20, 180, 180), window);
                        playB.draw(window);
                        window.display();
                        Sleep(250);
                        return Wind::play;
                    }
                    if (invB.clicked(mPos))
                    {
                        invB.color(sf::Color(20, 180, 180), window);
                        invB.draw(window);
                        window.display();
                        Sleep(250);
                        return Wind::inventory;
                    }
                    if (strB.clicked(mPos))
                    {
                        strB.color(sf::Color(20, 180, 180), window);
                        strB.draw(window);
                        window.display();
                        Sleep(250);
                        return Wind::shop;
                    }
                    if (extB.clicked(mPos))
                    {
                        extB.color(sf::Color(20, 180, 180), window);
                        extB.draw(window);
                        window.display();
                        Sleep(250);
                        return Wind::exit;

                    }
                }
            }
        }
        sf::Texture start;
        start.loadFromFile("start.png");
        sf::RectangleShape HAHAShape(sf::Vector2f(window.getSize()));
        HAHAShape.setTexture(&start);
        HAHAShape.setPosition(0, 0);
        window.draw(HAHAShape);
        playB.draw(window);
        invB.draw(window);
        strB.draw(window);
        extB.draw(window);
        window.display();
    }
}