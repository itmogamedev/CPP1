#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <random>
#define CenterOrigin(dinoSprite) dinoSprite.setOrigin((dinoSprite.getLocalBounds().left + dinoSprite.getLocalBounds().width) / 2.f, (dinoSprite.getLocalBounds().top + dinoSprite.getLocalBounds().height) / 2.f);
enum State { menu, shop, gamePlay, collection };
//--------------GLOBAL VARIABLES---------------
// window
extern const unsigned int width, height;
extern sf::ContextSettings settings;
extern sf::RenderWindow window;
extern sf::Color bg_color;
extern sf::Color text_color;
extern sf::Font font;

extern float elapsed, elapsed1;
extern sf::Clock timer, timer1;
extern State state;

extern sf::Texture emptyTexture;
extern std::unordered_map<std::string, sf::Texture>Textures;
extern std::unordered_map < std::string, sf::Sound> Sounds;
#include "Classes.h"
// векторы с динозавриками
extern std::vector<Dino*>dinos;
extern std::vector<Dino*>emptyvec;
// игрок
extern Player player;
// 





