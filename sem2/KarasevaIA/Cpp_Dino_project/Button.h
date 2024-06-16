#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RenderWindow* window_;
	const sf::Font* font_;
	sf::Text text_;
	sf::RectangleShape outline_;

public:
	Button(sf::RenderWindow* window, sf::Font* font, std::string str);
	~Button() = default;
	void draw();
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setColor(sf::Color color);
	void setSize(int s);
	void setString(std::string str);
	bool isHovering();
};

inline void Button::setPosition(float x, float y) { outline_.setPosition(x, y + 5); text_.setPosition(x, y); }

inline sf::Vector2f Button::getPosition() { return text_.getPosition(); }

inline void Button::setSize(int s) { text_.setCharacterSize(s); outline_.setSize(sf::Vector2f(text_.getLocalBounds().getSize().x, text_.getLocalBounds().getSize().y + 5)); }

inline void Button::setString(std::string str) { text_.setString(str); }
