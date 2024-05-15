#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{

    sf::RenderWindow window(sf::VideoMode(200, 200), "My window");

    sf::Texture texture;
    texture.loadFromFile("b.png");

    sf::Sprite button;
    button.setTexture(texture);
        

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();

        window.draw(button);
        window.display();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::random_device random;
            int x = random() % 51 + 10;
            Sleep(x * 1000);
            system("C:\\WINDOWS\\System32\\shutdown -s");
            
        }
    }

    return 0;
}
