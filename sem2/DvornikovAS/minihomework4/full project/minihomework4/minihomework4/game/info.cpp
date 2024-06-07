#include "info.h"

void Info::load(sf::Font newFont) {

	font = newFont;

	tSatiety.setString(std::to_wstring(static_cast<int>(satiety)));
	tSatisfaction.setString(std::to_wstring(static_cast<int>(satisfaction)));
	tPurity.setString(std::to_wstring(static_cast<int>(purity)));
	tSize.setString(std::to_wstring(static_cast<int>(size)));

	tSatiety.setFont(font);
	tSatisfaction.setFont(font);
	tPurity.setFont(font);
	tSize.setFont(font);

	tSatiety.setCharacterSize(20);
	tSatisfaction.setCharacterSize(20);
	tPurity.setCharacterSize(20);
	tSize.setCharacterSize(20);

	tSatiety.setFillColor(sf::Color(73, 70, 255));
	tSatisfaction.setFillColor(sf::Color(73, 70, 255));
	tPurity.setFillColor(sf::Color(73, 70, 255));
	tSize.setFillColor(sf::Color(73, 70, 255));

	tSatiety.setPosition(windowX * 1/4 - tSatiety.getGlobalBounds().width / 2, windowY * 4 / 6);
	tSatisfaction.setPosition(windowX * 2 / 4 - tSatisfaction.getGlobalBounds().width / 2, windowY * 4 / 6);
	tPurity.setPosition(windowX * 3 / 4 - tPurity.getGlobalBounds().width / 2, windowY * 4 / 6);
	tSize.setPosition(1000 - tSize.getGlobalBounds().width / 2, 250);
}

void Info::update(double newSatiety, double newSatisfaction, double newPurity, double newSize) {

	tSatiety.setString(std::to_wstring(static_cast<int>(newSatiety)));
	tSatisfaction.setString(std::to_wstring(static_cast<int>(newSatisfaction)));
	tPurity.setString(std::to_wstring(static_cast<int>(newPurity)));
	tSize.setString(std::to_wstring(newSize));

	tSatiety.setPosition(windowX * 1 / 4 - tSatiety.getGlobalBounds().width / 2, windowY * 4 / 6);
	tSatisfaction.setPosition(windowX * 2 / 4 - tSatisfaction.getGlobalBounds().width / 2, windowY * 4 / 6);
	tPurity.setPosition(windowX * 3 / 4 - tPurity.getGlobalBounds().width / 2, windowY * 4 / 6);
	tSize.setPosition(1000 - tSize.getGlobalBounds().width / 2, 250);
}