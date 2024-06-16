#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class CP_Button {
public:
	CP_Button() {};

	CP_Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setFillColor(bgColor);
	}

	void setFont(sf::Font& font);
	void setScale(sf::Vector2f newpos);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	virtual void setPosition(sf::Vector2f posbut, sf::Vector2f postext);
	virtual void drawTo(sf::RenderWindow& window);
	virtual bool isMouseOver(sf::Vector2i& mouse);

protected:
	sf::RectangleShape button;
	sf::Text text;
};

class CP_ButtonImage: public CP_Button {
public:
	CP_ButtonImage() {};

	CP_ButtonImage(std::string t, sf::Vector2f size, int charSize, std::string imagepath, sf::Color textColor) {
		setPath(imagepath);
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
	}

	void setPath(std::string imagepath);
	void setSize(sf::Vector2f test);
	void setPosition(sf::Vector2f posbut, sf::Vector2f postext) override;
	void drawTo(sf::RenderWindow& window) override;
	bool isMouseOver(sf::Vector2i& mouse) override;

protected:
	std::string button_path;
	sf::Texture button_texture;
	sf::Sprite button_sprite;
};
