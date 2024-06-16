#include "Button.h"

Button::Button(sf::RenderWindow* window, sf::Font* font, std::string str)
{
	window_ = window;
	font_ = font;
	text_.setFont(*font_);
	text_.setString(str);
	outline_.setFillColor(sf::Color::Transparent);
	outline_.setOutlineThickness(1);
}

void Button::draw() { window_->draw(outline_); window_->draw(text_); }

void Button::setColor(sf::Color color)
{
	text_.setColor(color);
}

bool Button::isHovering()
{
	if (sf::IntRect(outline_.getPosition().x, outline_.getPosition().y, outline_.getSize().x, outline_.getSize().y)
		.contains(sf::Mouse::getPosition(*window_))) return true;
	return false;
}
