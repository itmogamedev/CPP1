#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>


int main() {
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Mysterious button!");
    window.clear(sf::Color::Blue);

    sf::Texture texture;
    if (!texture.loadFromFile("Star.png")) {
        std::cout << "ERROR!!!";
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.draw(sprite);
    sprite.setPosition(sf::Vector2f(std::rand() % 600, std::rand() % 600));
    sf::FloatRect coords = sprite.getGlobalBounds();

    int tick = 0;
    bool active = false;
    int waiting = std::rand() % 10000 + 1;
    int is_active = 5000;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left and active) {
                if (coords.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    std::string line = "shutdown -s -t " + std::to_string(std::rand() % 51 + 10);
                    const char* command = line.c_str();
                    system(command);
                }
            }
        }

        std::srand(std::time(nullptr));
        tick++;
        if (not active and tick == waiting) {
            active = true;
            tick = 0;
        }
        else if (active and tick == is_active) {
            active = false;
            sprite.setPosition(sf::Vector2f(std::rand() % 600, std::rand() % 600));
            tick = 0;
        }

        window.clear(sf::Color::Blue);
        if (active) {
            window.draw(sprite);
        }
        window.display();
    }

    return 0;
}