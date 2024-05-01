#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

int endscr(sf::RenderWindow& window, int result) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(50);
    endText.setFillColor(sf::Color::Red);

    if (result == 1) {
        endText.setString("Game Over");
        endText.setFillColor(sf::Color::Red);
    }
    else {
        endText.setString("Success!");
        endText.setFillColor(sf::Color::Green);
    }

    endText.setPosition(window.getSize().x / 2 - endText.getGlobalBounds().width / 2, window.getSize().y / 2 - endText.getGlobalBounds().height / 2);

    window.clear();
    window.draw(endText);
    window.display();

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 3) {
        // Wait for 3 seconds
    }

    return 0;
}



