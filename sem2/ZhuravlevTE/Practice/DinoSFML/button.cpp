#include "button.h"

void CP_Button::setFont(sf::Font& font) {
	text.setFont(font);
}

void CP_Button::setScale(sf::Vector2f newpos)
{
	button.setScale(newpos);
}

void CP_Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void CP_Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void CP_Button::setPosition(sf::Vector2f posbut, sf::Vector2f postext)
{
	button.setPosition(posbut);
	text.setPosition(postext);
}

void CP_Button::drawTo(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool CP_Button::isMouseOver(sf::Vector2i& mouse)
{
	if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
		return true;
	}
	return false;
}

void CP_ButtonImage::setPath(std::string imagepath)
{
	button_path = imagepath;
}

void CP_ButtonImage::setSize(sf::Vector2f test)
{
	button_sprite.setScale(test);
}

void CP_ButtonImage::setPosition(sf::Vector2f posbut, sf::Vector2f postext)
{
	button_sprite.setPosition(posbut);
}

void CP_ButtonImage::drawTo(sf::RenderWindow& window)
{
	if (button_texture.loadFromFile(button_path)) {
		button_sprite.setTexture(button_texture);
	}

	window.draw(button_sprite);
}

bool CP_ButtonImage::isMouseOver(sf::Vector2i& mouse)
{
	if (button_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
		return true;
	}
	return false;
}
