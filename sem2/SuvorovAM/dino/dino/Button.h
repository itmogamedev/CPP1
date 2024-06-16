#pragma once

#include <iostream>


#include "SFML/Graphics.hpp"

class Button {
private:
    sf::Sprite sp_button;

public:
    sf::Text text;

    Button(int x, int y, int width, int height, sf::Font& font, std::string buttonText, const sf::Texture& texture) {
        sp_button.setTexture(texture);
        sp_button.setPosition(sf::Vector2f(x, y));
        sp_button.setScale(
            static_cast<float>(width) / texture.getSize().x,
            static_cast<float>(height) / texture.getSize().y
        );

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(36);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1.0f);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sp_button);
        window.draw(text);
    }

    bool isOverlapped(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f buttonPos = sp_button.getPosition();
        sf::Vector2f buttonSize = sf::Vector2f(sp_button.getGlobalBounds().width, sp_button.getGlobalBounds().height);

        return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
            mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
    }
};