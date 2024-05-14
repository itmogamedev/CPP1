#pragma once
#include <SFML/Graphics.hpp>

class ProgressBar
{
public:
	ProgressBar(sf::Color fill, sf::Color outline, int thickness);
	~ProgressBar();
	void setProgress(int value);
	void setText(std::string st);
	void setPos(int x, int y);

private:
	sf::RectangleShape bar;
};

ProgressBar::ProgressBar(sf::Color fill, sf::Color outline, int thickness)
{
	bar.setFillColor(fill);
	bar.setOutlineThickness(thickness);
	bar.setOutlineColor(outline);
}

ProgressBar::~ProgressBar()
{
}

inline void ProgressBar::setProgress(int value)
{
	bar.setSize(sf::Vector2f(value, 10));
}

inline void ProgressBar::setText(std::string st)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setString(st);
	text.setCharacterSize(35); // in pixels, not points!
	text.setPosition(bar.getPosition());
}

inline void ProgressBar::setPos(int x, int y)
{
	bar.setPosition(x, y);
}
