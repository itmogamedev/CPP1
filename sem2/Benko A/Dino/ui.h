#pragma once

class UI {
private:
    sf::RectangleShape sh;
    sf::Text t;

public:
    UI(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, int kegl, const std::string& str, sf::Font& font)
    {
        sh.setSize(size);
        sh.setPosition(position);
        sh.setFillColor(color);
        sh.setOutlineColor(color);
        sh.setOutlineThickness(4);
        t.setFont(font);
        t.setString(str);
        t.setCharacterSize(kegl);
        t.setOutlineThickness(1);
        t.setPosition(position.x + (size.x - t.getLocalBounds().width) / 2, position.y + (size.y - t.getLocalBounds().height) / 2);
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

    void text(const std::string& str, sf::RenderWindow& window)
    {
        t.setString(str);
    }
};