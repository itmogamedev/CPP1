#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "DeathButton");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Font error\n";
        return 1;
    }
    int c = 0;
    sf::Text message("ShutDown", font, 30);
    message.setFillColor(sf::Color::White);
    message.setPosition(330, 280);

    sf::CircleShape button(100);
    button.setFillColor(sf::Color(255, 0, 0));
    button.setPosition(297, 200);
    button.setOutlineThickness(10);
    button.setOutlineColor(sf::Color(200, 200, 200));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int delay = (std::rand() % 51 + 10) * 1000;
                
                sf::Clock timer;
                while (timer.getElapsedTime().asMilliseconds() < delay) {
                    
                    if (c/1000 < timer.getElapsedTime().asMilliseconds()/1000) {
                        std::system("cls");
                        std::cout << "Timer has been set. Shutdown in " << (delay - timer.getElapsedTime().asMilliseconds()) / 1000 << " seconds.\n";                       
                        sf::Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window.close();
                        }
                        c = timer.getElapsedTime().asMilliseconds();
                    }                   
                }
                std::system("shutdown /s");
            }
        }
        window.clear();
        window.draw(button);
        window.draw(message);
        window.display();
    }
    return 0;
}
