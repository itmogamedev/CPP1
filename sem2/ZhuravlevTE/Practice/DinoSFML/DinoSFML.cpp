#include <iostream>
#include <string>
#include "DinoSFML.h"
#include <SFML/Audio.hpp>
#include "menu.h"
#include "player.h"
#include "dinogame.h"

CP_Menu MainMenu;

int main() {
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(Screen_HEIGHT, Screen_WIDTH), Game_Name);
    MainMenu.Button_Actions(window, event);
}