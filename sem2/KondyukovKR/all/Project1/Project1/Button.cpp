#include "Button.h"

Button::Button(sf::RenderWindow* window, std::string imgPath)
{
	window_ = window;
	image_.loadFromFile(imgPath);
	sprite_.setTexture(image_);
}

void Button::setColor(sf::Color color)
{
	sprite_.setColor(color);
}

bool Button::isHovering()
{
	if (sf::IntRect(sprite_.getPosition().x, sprite_.getPosition().y, image_.getSize().x, image_.getSize().y)
		.contains(sf::Mouse::getPosition(*window_))) return true;
	return false;
}
