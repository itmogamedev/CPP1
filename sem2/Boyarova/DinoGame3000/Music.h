#pragma once
#include <string>
#include <SFML/Audio.hpp>
#ifndef MUSIC_H
#define MUSIC_H

sf::Music BestSongEver;

void load_music() {
	BestSongEver.openFromFile("music/cachemonet.ogg");
	BestSongEver.play();
}
#endif