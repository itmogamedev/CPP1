#pragma once
#include <SFML/Graphics.hpp>

class ProgressBar
{
public:
	ProgressBar(sf::RenderWindow* window, int max, sf::Color fill);
	~ProgressBar();
	void draw();
	void setProgress(int value);
	void setText(std::string file);
	void setPos(int x, int y);

private:
	sf::RenderWindow* window_;
	sf::RectangleShape bar_;
	sf::RectangleShape outline_;
	sf::Texture textTexture;
	sf::Sprite text_;
};

ProgressBar::ProgressBar(sf::RenderWindow* window, int max, sf::Color fill)
{
	window_ = window;
	outline_.setSize(sf::Vector2f(max / 3, 10));
	bar_.setFillColor(fill);
	outline_.setOutlineThickness(1);
	outline_.setOutlineColor(sf::Color());
}

ProgressBar::~ProgressBar(){}

inline void ProgressBar::draw()
{
	window_->draw(outline_);
	window_->draw(bar_);
	window_->draw(text_);
}

inline void ProgressBar::setProgress(int value)
{
	bar_.setSize(sf::Vector2f(value / 3, 10));
}

inline void ProgressBar::setText(std::string file)
{
	textTexture.loadFromFile(file);
	text_.setTexture(textTexture);
	text_.setColor(sf::Color::Black);
	text_.setPosition(bar_.getPosition().x, bar_.getPosition().y + 15);
}

inline void ProgressBar::setPos(int x, int y)
{
	outline_.setPosition(x, y);
	bar_.setPosition(x, y);
}
