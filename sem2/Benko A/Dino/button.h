#pragma once

class Button {
private:
    sf::RectangleShape sh;
    sf::Texture t;
    std::string st;

public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& str)
    {
        sh.setSize(size);
        sh.setPosition(position);
        sh.setOutlineColor(color);
        sh.setOutlineThickness(4);
        sh.setFillColor(color);
        t.loadFromFile(str);
        st = str;
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sh);
        sh.setTexture(&t);
    }

    bool clicked(const sf::Vector2i& mousePos)
    {
        return sh.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void color(const sf::Color& color, sf::RenderWindow& window)
    {
        sh.setFillColor(color);
    }
    void img(const std::string& str, sf::RenderWindow& window)
    {
        t.loadFromFile(str);
    }
    std::string getImg(sf::RenderWindow& window)
    {
        return st;
    }
};