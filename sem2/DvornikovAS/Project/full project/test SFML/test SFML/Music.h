#pragma once

#ifndef MUSIC_H__
#define MUSIC_H__


#include <string>
#include <SFML/Audio.hpp>

sf::Music intro;

void load_music() {
	intro.openFromFile("music/intro.mp3");
}

#endif // !MUSIC_H__