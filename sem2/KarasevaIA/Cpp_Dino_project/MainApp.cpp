#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "FileManager.h"
#include "DinoCollection.h"
#include "Dino.h"
#include "Stegosaurus.h"
#include "Tyrannosaurus.h"
#include "Parasaurolophus.h"
#include "Pterodactyl.h"
#include "MainMenu.h"
#include "CollectMenu.h"
#include "ShopMenu.h"
#include "FightMenu.h"
#include "Button.h"

int main() {
    srand((unsigned)time(NULL));
    // 1 - fight menu
    // 2 - collection
    // 3 - shop
    int currMenu = 0;

    sf::RenderWindow window(sf::VideoMode::VideoMode(720, 720), "Dino Fight", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(600, 135));
    window.setSize(sf::Vector2u(720, 720));

    sf::Font font;
    font.loadFromFile("pixel_sans.ttf");
    sf::Event event;

    GameState gameState;
    gameState.getFight()->setStore(gameState.getStore());
    MainMenu menu(&window, &event, &font);
    ShopMenu shop(&window, &event, &font, &gameState);
    CollectMenu collect(&window, &event, &font, &gameState);
    FightMenu fight(&window, &event, &font, &gameState);

    std::string fileName = "SaveData.txt";

    FileManager fileManager;
    
    // loads data
    std::ifstream f(fileName);
    if (f.good())
    {
        fileManager.load(fileName);
        if (!(*fileManager.getLines()).empty())
        {
            fileManager.parseLine(gameState.getStore());
        }
        else
        {
            gameState.getStore()->collection.addStartDinos();
            gameState.getStore()->setBudget(5);
        }
        std::ofstream out(fileName);
        out << "";
    }

    // main loop
    while (window.isOpen()) {
        switch (currMenu)
        {
        case 1:
            currMenu = fight.render();
            break;
        case 2:
            currMenu = collect.render();
            break;
        case 3: 
            currMenu = shop.render();
            break;
        default:
            currMenu = menu.render();
            break;
        }
    }

    // saves data
    fileManager.save(fileName, gameState.getStore());
}
