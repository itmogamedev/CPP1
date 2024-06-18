#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <string>

void turnOffPc() {

    char command_char[50], timeShutdown_char[5];
    std::string timeShutdown_str, command_str;

    int start = 10;
    int end = 60;
    int timeShutdown = rand() % (end - start + 1) + start;
    timeShutdown_str= std::to_string(timeShutdown);

    command_str = "C:\\Windows\\System32\\shutdown /s /t ";

    int i = 0;
    while (command_str[i]){

        command_char[i] = command_str[i];
        i++;
    }
    command_char[i] = '\0';

    i = 0;
    while (timeShutdown_str[i]) {

        timeShutdown_char[i] = timeShutdown_str[i];
        i++;
    }
    timeShutdown_char[i] = '\0';

    strcat_s(command_char, timeShutdown_char);
    system(command_char);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(560, 490), "turn off pc");

    sf::Font font;
    if (!font.loadFromFile("HelveticaNowVar.TTF"))
        std::cout << "Can't find the font file" << std::endl;

    sf::Texture background;
    sf::Sprite backgroundImage;

    if (!background.loadFromFile("cat.jpg"))
        std::cout << "Could not display cat image(" << std::endl;

    backgroundImage.setTexture(background);


    sf::RectangleShape turnOff(sf::Vector2f(330, 160));
    turnOff.setFillColor(sf::Color(245, 201, 211, 200));
    turnOff.setPosition(10.0f,80.0f);


    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setStyle(sf::Text::Bold);
    buttonText.setString("TURN OFF YOU PC");
    buttonText.setFillColor(sf::Color(71, 9, 9, 200));
    buttonText.setCharacterSize(30);
    buttonText.setPosition(25.0f, 140.0f);

    while (window.isOpen()) {

        sf::Vector2i mousePose = sf::Mouse::getPosition(window);

        int countClick = 0;

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();



            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    if (turnOff.getGlobalBounds().contains(mousePose.x, mousePose.y)) {

                        buttonText.setString("Good buy!");
                        turnOff.setFillColor(sf::Color(245, 225, 225, 200));

                        if (countClick < 1) {
                            turnOffPc();
                        }

                        countClick++;

                    }

                }
            }


            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.key.code == sf::Mouse::Left) {

                    turnOff.setFillColor(sf::Color(245, 201, 211, 200));

                }
            }

        }


        window.clear();

        window.draw(backgroundImage);
        window.draw(turnOff);
        window.draw(buttonText);

        window.display();

    }

    return 0;
}
