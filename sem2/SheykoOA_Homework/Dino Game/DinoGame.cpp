#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <memory>

#include "SFML/Graphics.hpp"

#include "Button.h"
#include "Player.h"
#include "Shop.h"
#include "Battlefield.h"
#include "TextureLoader.h"


using namespace std;


void drawMainMenu(sf::RenderWindow& window, sf::Font& font, std::vector<Button>& buttons, sf::Sprite& backgroundSprite, sf::Sprite& foregroundSprite) {
    window.draw(backgroundSprite);
    window.draw(foregroundSprite);
    for (Button& button : buttons) {
        button.draw(window);
    }
}



int main()
{
    setlocale(LC_ALL, "ru");

 

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Dino Game");

    GameState gameState = InMenu;

    Player p1;
    Player p2;
    Shop shop(p1, window, gameState);
    Battlefield battlefield(p1, p2, window, gameState);

    p1.loadDinosFromFile("dinos.txt");

    sf::Sprite backgroundSprite(TextureLoader::getInstance().getTexture("GameData/Plain.png"));
	sf::Sprite foregroundSprite(TextureLoader::getInstance().getTexture("GameData/MainMenuDinos.png"));
    foregroundSprite.setPosition(600, 75);

    sf::Font font;
    if (!font.loadFromFile("GameData/FuturaMediumC.otf")) {
        std::cerr << "Ошибка загрузки шрифта." << std::endl;
        return 1;
    }

    std::vector<Button> buttons;
    sf::Texture buttonTexture;
    buttonTexture = TextureLoader::getInstance().getTexture("GameData/Button.png");
    buttons.emplace_back(100, 100, 300, 75, font, "Start Battle", buttonTexture);
    buttons.emplace_back(100, 250, 300, 75, font, "See my Dinos", buttonTexture);
    buttons.emplace_back(100, 400, 300, 75, font, "Shop", buttonTexture);
    buttons.emplace_back(100, 550, 300, 75, font, "Quit", buttonTexture);


    while (window.isOpen()) {
       
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (Button& button : buttons) {
                        if (button.isMouseOver(window)) {
                            if (button.text.getString() == "See my Dinos") {
                                gameState = Showcase;
                            }
                            else if (button.text.getString() == "Shop") {
                                gameState = InShop;
                            }
                            else if (button.text.getString() == "Start Battle") {
                                gameState = SelectingDinos;
                            }
                            else if (button.text.getString() == "Quit") {
                                
                                window.close();
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        if (gameState == InMenu) {
			drawMainMenu(window, font, buttons, backgroundSprite, foregroundSprite);
        }
        else if (gameState == SelectingDinos) {
            battlefield.dinosSelection();
        }
        else if (gameState == Showcase) {
            battlefield.dinosShowcase();
        }
        else if (gameState == InShop) {
            shop.shopDialog();
        }
        else if (gameState == Battle) {
            battlefield.battleProcess();
            p1.selectedDinos.clear();
            p2.selectedDinos.clear();
            p2.randomDinoPull();
        }
        
        window.display();
    }
    
    
    
}


