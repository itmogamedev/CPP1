#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RenderWindow* window_;
	sf::Texture image_;
	sf::Sprite sprite_;

public:
	Button(sf::RenderWindow* window, std::string imgPath);
	~Button() = default;
	void draw();
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setColor(sf::Color color);
	void setScale(float x, float y);
	bool isHovering();
};

inline void Button::draw() { window_->draw(sprite_); }

inline void Button::setPosition(float x, float y) { sprite_.setPosition(x, y); }

inline sf::Vector2f Button::getPosition() { return sprite_.getPosition(); }

inline void Button::setScale(float x, float y) { sprite_.setScale(x, y); }