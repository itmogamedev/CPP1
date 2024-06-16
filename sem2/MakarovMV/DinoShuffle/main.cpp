#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Engage.h"
#include "Shopph.h"
#include "filedata.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;

enum GameState { MainMenu, DinoSelection, Battle, Shop};

std::vector<Dino*> MainDinos() {
    return { new Tyranosaurus(), new Brahiosaurus(), new Diplodoc(), new Tryceraptops() , new Stegosaurus(), new Pterodactyl() };
}

sf::Text createText(const std::string& content, const sf::Font& font, int size, sf::Color color, sf::Vector2f position) {
    sf::Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}

sf::RectangleShape createButton(sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, sf::Vector2f position) {
    sf::RectangleShape button(size);
    button.setFillColor(fillColor);
    button.setOutlineColor(outlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setPosition(position);
    return button;
}

int main() {

    sf::RenderWindow win(sf::VideoMode(1920, 1080), "DinoGame");
    sf::Texture Texforback;

    if (!Texforback.loadFromFile("img/dinowrld.jpg")) {
        std::cerr << "Error loading background texture" << std::endl;
        return -1;
    }
    
    sf::Font dinosaurFont;
    if (!dinosaurFont.loadFromFile("DinosaurJNL.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Font rockSaltFont;
    if (!rockSaltFont.loadFromFile("RockSalt-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Font russoOneFont;
    if (!russoOneFont.loadFromFile("RussoOne-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Font pressStart2PFont;
    if (!pressStart2PFont.loadFromFile("PressStart2P-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Font juraFont;
    if (!juraFont.loadFromFile("Jura-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }
    
    sf::Font Prehis;
    if (!Prehis.loadFromFile("Prehistoric Caveman.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);

    sf::RectangleShape buttonStart = createButton(sf::Vector2f(400, 100), sf::Color(34, 139, 34), sf::Color::Black, 4, sf::Vector2f(100, 350));
    sf::RectangleShape buttonShop = createButton(sf::Vector2f(400, 100), sf::Color(255, 215, 0), sf::Color::Black, 4, sf::Vector2f(100, 500));
    sf::RectangleShape buttonExit = createButton(sf::Vector2f(120, 120), sf::Color(139, 0, 0), sf::Color::Black, 4, sf::Vector2f(1700, 850));
    sf::RectangleShape buttonRestart = createButton(sf::Vector2f(400, 100), sf::Color(0, 0, 139), sf::Color::Black, 4, sf::Vector2f(100, 650));
    sf::Text startBattleText = createText("Start Battle", rockSaltFont, 40, sf::Color::White, sf::Vector2f(130, 375));
    sf::Text openShopText = createText("Open Shop", rockSaltFont, 40, sf::Color::Black, sf::Vector2f(163, 525));
    sf::Text exitText = createText("Exit", rockSaltFont, 40, sf::Color::White, sf::Vector2f(1710, 880));
    sf::Text restartText = createText("Restart", rockSaltFont, 40, sf::Color::White, sf::Vector2f(190, 675));
    sf::Text titleText = createText("DinoShuffle", Prehis, 60, sf::Color::Green, sf::Vector2f(130, 120));
    sf::RectangleShape buttonBattle = createButton(sf::Vector2f(200, 50), sf::Color(34, 139, 34), sf::Color::Black, 4, sf::Vector2f(850, 900));
    sf::Text START = createText("ENGAGE", pressStart2PFont, 20, sf::Color::White, sf::Vector2f(888, 916));
    sf::RectangleShape buybutton = createButton(sf::Vector2f(200, 50), sf::Color(255, 215, 0), sf::Color::Black, 4, sf::Vector2f(850, 900));
    sf::Text BUY = createText("BUY", pressStart2PFont, 20, sf::Color::White, sf::Vector2f(916, 916));
    sf::RectangleShape buttonBack = createButton(sf::Vector2f(200, 50), sf::Color(0, 0, 139), sf::Color::Black, 4, sf::Vector2f(1200, 900));
    sf::Text BACK = createText("BACK", pressStart2PFont, 20, sf::Color::White, sf::Vector2f(1258, 916));
    sf::Text selectedDinosText = createText("Selected Dinos: 0/3", juraFont, 50, sf::Color::White, sf::Vector2f(100, 50));
    sf::Text MoneyText = createText("Money: " + std::to_string(Mnny), juraFont, 50, sf::Color::Yellow, sf::Vector2f(1500, 130));

    GameState state = MainMenu;

    vector<int> selectedDinos;
    std::vector<int> OwnedDinos;
   
    static std::vector<Dino*> MainD = MainDinos();
    
    while (win.isOpen()) {
        int Mnny = getmoney();
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (state == MainMenu) {
                    if (buttonStart.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        cout << "Start Battle" << std::endl;
                        state = DinoSelection;
                    }
                    if (buttonShop.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        cout << "Open Shop" << std::endl;
                        state = Shop;
                    }
                    if (buttonExit.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        win.close();
                    }
                    if (buttonRestart.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        std::ofstream file("Dinodata.data", std::ios::trunc); 
                        if (file.is_open()) {
                            
                            file << "0" << "\n" << "1" << "\n" << "2" << "\n"; 
                            
                            file.close();
                        }
                        std::ofstream filemon("moneydata.data", std::ios::trunc); 
                        if (filemon.is_open()) {
                                                            
                            filemon << "500"; 
                            
                            filemon.close();
                        }
                        state = MainMenu;
                    }
                }
                else if (state == DinoSelection) {
                    if (buttonBattle.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        state = Battle;
                    }
                    if (buttonBack.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        selectedDinos.clear();
                        state = MainMenu;
                    }
                }
                else if (state == Shop) {
                    if (buttonBack.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        selectedDinos.clear();
                        state = MainMenu;
                    }
                    if (buybutton.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        if (!selectedDinos.empty()) {
                            std::ofstream file("Dinodata.data", std::ios::app); 
                            if (file.is_open()) {
                                for (int index : selectedDinos) {
                                    file << MainD[index]->getNum()<<"\n"; 
                                }
                                file.close();
                            }
                            
                            std::ofstream filemon("moneydata.data", std::ios::trunc); 
                            if (filemon.is_open()) {
                                for (int index : selectedDinos) {
                                    Mnny = (Mnny - (MainD[index]->getCost()));
                                    filemon << Mnny; 
                                }
                                filemon.close();
                            }
                            
                            
                            selectedDinos.clear(); 
                        }

                        state = MainMenu;
                    }
                }
                
            }
        }

        win.clear();
        win.draw(background);

        if (state == MainMenu) {
            MoneyText.setString("Money: " + std::to_string(Mnny));

            win.draw(titleText);
            win.draw(MoneyText);
            win.draw(buttonStart);
            win.draw(buttonShop);
            win.draw(buttonExit);
            win.draw(buttonRestart);
            win.draw(startBattleText);
            win.draw(openShopText);
            win.draw(exitText);
            win.draw(restartText);
        }
        else if (state == DinoSelection) {
            handleDinoSelection(win, mousePoz, selectedDinos);
            selectedDinosText.setString("Selected Dinos: " + std::to_string(selectedDinos.size()) + "/3");
            win.draw(selectedDinosText);
            win.draw(buttonBack);
            win.draw(BACK);
            if (selectedDinos.size() == 3) {
                win.draw(buttonBattle);
                win.draw(START);
                
            }
        }
        else if (state == Battle) {
            Engage(win, selectedDinos);
           
            state = MainMenu;
            selectedDinos.clear(); 
        }
        else if (state == Shop) {
            selectedDinosText.setString("Selected Dinos: " + std::to_string(selectedDinos.size()) + "/1");
            win.draw(selectedDinosText);
            handleShop(win, mousePoz, selectedDinos);
            win.draw(buttonBack);
            win.draw(BACK);
            if (selectedDinos.size() == 1) {
                win.draw(buybutton);
                win.draw(BUY);
            }
            
            
        }
        win.display();
    }
    return 0;
}


