#pragma once

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape sh;
    sf::Text t;

public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& str, sf::Font& font)
    {
        sh.setSize(size);
        sh.setPosition(position);
        sh.setFillColor(color);
        sh.setOutlineColor(sf::Color::White);
        sh.setOutlineThickness(1);
        t.setFont(font);
        t.setString(str);
        t.setCharacterSize(32);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1);
        t.setPosition( position.x + (size.x - t.getLocalBounds().width) / 2, position.y + (size.y - t.getLocalBounds().height) / 2 );
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sh);
        window.draw(t);
    }

    bool clicked(const sf::Vector2i& mousePos)
    {
        return sh.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void color(const sf::Color& color, sf::RenderWindow& window)
    {
        sh.setFillColor(color);
    }
};