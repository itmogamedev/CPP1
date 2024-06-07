#pragma once

#ifndef TEXTS_H__
#define TEXTS_H__

#include <string>
#include <SFML/Graphics.hpp>

#include "Fonts.h"
#include "window.h"

sf::Text t_header(L"Dinosaurs 2", inkfree, 0);
sf::Text t_under(L"Для продолжения нажмите любую клавишу", muller, 20);

void load_texts() {
	t_under.setPosition(window.getSize().x / 2 - t_under.getGlobalBounds().width / 2, window.getSize().y * 5 / 6);
}

#endif