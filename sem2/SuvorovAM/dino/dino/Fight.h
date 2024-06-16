#pragma once

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
#include "Dino.h"
#include "Player.h"
#include "DinoType.h"
#include "Button.h"

class FightProccess {
private:
    Player& player;
    Player& enemy;

    sf::RenderWindow& window;

    RenderPointer& current_render;

    sf::Vector2f GRID_POS, GRID_SIZE, CELLS_SIZE, CELLS_Spacing;
    int CELLS_amount;

    void GetMoney(int win_money) {
        player.current_balance += win_money;
    }

    void Fight_End_screen(bool playerWon, int prize) {                                                                         // END OF THE FIGHT

        player.DINO_save("DINO_INFO.txt");
        current_render = Fight_End;
        GetMoney(prize);

        sf::Texture t_background;
        t_background = TextureLoader::getInstance().getTexture("GameData/Terrain/Plain.png");
        sf::Sprite backgroundSprite(t_background);

        sf::Font font;
        font.loadFromFile("GameData/Arial.ttf");

        sf::Text FightResult_text;
        FightResult_text.setFont(font);
        FightResult_text.setFillColor(sf::Color::White);
        FightResult_text.setOutlineColor(sf::Color::Black);
        FightResult_text.setOutlineThickness(2.f);
        FightResult_text.setCharacterSize(64);
        FightResult_text.setString(playerWon ? "Victory!" : "Defeat!");
        FightResult_text.setPosition(550, 200);

        sf::Text prizeText;
        prizeText.setFont(font);
        prizeText.setFillColor(sf::Color::White);
        prizeText.setOutlineColor(sf::Color::Black);
        prizeText.setOutlineThickness(2.f);
        prizeText.setCharacterSize(32);
        prizeText.setString("You won " + std::to_string(prize) + " coins!");
        prizeText.setPosition(500, 280);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/temp.png");
        Button selectDinoButton(450, 350, 300, 75, font, "Select Dinos", buttonTexture);
        Button backButton(450, 450, 300, 75, font, "Menu", buttonTexture);

        while (window.isOpen() && current_render == Fight_End) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    if (selectDinoButton.isOverlapped(window)) {                                                               // NEW FIGHT
                        current_render = DINO_Selector; 
                        return;
                    }

                    if (backButton.isOverlapped(window)) {
                        current_render = Main_Menu;
                        return;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(FightResult_text);
            window.draw(prizeText);
            selectDinoButton.draw(window);
            backButton.draw(window);
            window.display();
        }


    }


public:

    FightProccess(Player& p1, Player& ENEMY, sf::RenderWindow& window, RenderPointer& gameState) : player(p1), enemy(ENEMY), window(window), current_render(gameState) {
        enemy.DINO_random_pull();
        GRID_POS = sf::Vector2f(50, 100); 
        GRID_SIZE = sf::Vector2f(800, 600);
        CELLS_SIZE = sf::Vector2f(200, 300); 
        CELLS_Spacing = sf::Vector2f(70, 10); 
        CELLS_amount = 4; 
    }

    void DINO_draw_cells() {
        sf::Vector2f currentPosition = GRID_POS;
        int currentColumn = 0;

        for (Dino* dino : player.dinos) {
            if (dino->isSelected)
                continue;


            dino->draw(window, currentPosition);

            currentColumn++;
            if (currentColumn >= CELLS_amount) {
                currentColumn = 0;
                currentPosition.x = GRID_POS.x;
                currentPosition.y += CELLS_SIZE.y + CELLS_Spacing.y;
            }
            else {
                currentPosition.x += CELLS_SIZE.x + CELLS_Spacing.x;
            }
        }
    }


    void dinosSelection() {
        if (player.dinos.size() < 3) {
            current_render = Main_Menu;
            return;
        }

        sf::Texture backgroundTexture;
        backgroundTexture = TextureLoader::getInstance().getTexture("GameData/Terrain/Plain.png");
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Font font;
        font.loadFromFile("GameData/Arial.ttf");

        sf::Text headerText;
        headerText.setFont(font);
        headerText.setFillColor(sf::Color::White);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);
        headerText.setString("Select 3 dinos for battle:");
        headerText.setPosition(50, 5);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/temp.png");
        Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

        while (window.isOpen() && player.selectedDinos.size() < 3) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    if (backButton.isOverlapped(window)) {
                        current_render = Main_Menu;
                        return;
                    }

                    for (Dino* dino : player.dinos) {
                        if (dino->sp_dino.getGlobalBounds().contains(mousePos)) {
                            if (!dino->isSelected && player.selectedDinos.size() < 3) {
                                dino->isSelected = true;
                                player.selectedDinos.push_back(dino);
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(headerText);
            DINO_draw_cells();                                                   // DRAW CELLS
            backButton.draw(window);
            window.display();
        }

        if (player.selectedDinos.size() == 3) {
            current_render = Simulation;
        }
    }

    void Inventory() {                                                                                         // MY DINOS
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("GameData/Terrain/Plain.png");
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Font font;
        font.loadFromFile("GameData/Arial.ttf");

        sf::Text headerText;
        headerText.setFont(font);
        headerText.setFillColor(sf::Color::Magenta);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);
        headerText.setString("Your Inventory:");
        headerText.setPosition(450, 5);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/temp.png");
        Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

        while (window.isOpen() && player.selectedDinos.size() < 3) {                                            // MOUSE INTERACTION
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    
                    if (backButton.isOverlapped(window)) {
                        current_render = Main_Menu;
                        return;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(headerText);
            DINO_draw_cells(); //                                                                        // DRAW CELLS
            backButton.draw(window);
            window.display();
        }
    }


    void FIGHT_PROCCESS() {                                                                                // FIGHT
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(0, 2);
        Terrain terrain = static_cast<Terrain>(distr(gen));                                                   // RANDOM TER

        sf::Texture backgroundTexture;
        switch (terrain) {
        case Plain:
            backgroundTexture.loadFromFile("GameData/Terrain/Plain.png");
            break;
        case River:
            backgroundTexture.loadFromFile("GameData/Terrain/River.png");
            break;
        case Mountain:
            backgroundTexture.loadFromFile("GameData/Terrain/Mountain.png");
            break;
        }
        sf::Sprite backgroundSprite(backgroundTexture);
        sf::Text headerText;
        sf::Font font;
        font.loadFromFile("GameData/FuturaMediumC.otf");
        headerText.setFont(font);                                                                              
        headerText.setFillColor(sf::Color::White);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);

        headerText.setPosition(50, 5); 

        sf::Clock attackClock;
        sf::Clock DeathClock;
        bool playerTurn = true;

        int enemyPullPrice = 0;
        for (Dino* dino : enemy.selectedDinos)
            enemyPullPrice += dino->cost;

        while (window.isOpen() && !player.selectedDinos.empty() && !enemy.selectedDinos.empty()) {                 // CORE-LOOP BATTLE
            headerText.setString(playerTurn ? "Enemy Turn!" : "Your Turn!");
            window.clear();
            window.draw(backgroundSprite);
            window.draw(headerText);

            for (int i = 0; i < player.selectedDinos.size() - 1; i++) {                                           // DRAW SPRITES
                player.selectedDinos[i]->draw(window, sf::Vector2f(100 + i * 150, 350), false, true, 0.7);
            }
            for (int i = 0; i < enemy.selectedDinos.size() - 1; i++) {
                enemy.selectedDinos[i]->draw(window, sf::Vector2f(900 + i * 150, 350), false, false, 0.7);
            }

            player.selectedDinos.back()->draw(window, sf::Vector2f(450, 300), false, true, 1.35);
            enemy.selectedDinos.back()->draw(window, sf::Vector2f(750, 300), false, false, 1.35);

            if (DeathClock.getElapsedTime().asSeconds() > 1) {                                                            
                if (enemy.selectedDinos.back()->isDead)                    
                    enemy.selectedDinos.pop_back();

                if (player.selectedDinos.back()->isDead) {                                         
                    player.deleteDino(player.selectedDinos.back());
                    player.selectedDinos.pop_back();
                }
                    
            }

            if (attackClock.getElapsedTime().asSeconds() > 2) {
                attackClock.restart();


                if (playerTurn) {                                                                 // TURN CHANGE
                    player.attackEnemy(enemy, enemy.selectedDinos, terrain);
                    if (enemy.selectedDinos.back()->isDead)
                        DeathClock.restart();
                }
                else {
                    enemy.attackEnemy(player, player.selectedDinos, terrain);
                    if (player.selectedDinos.back()->isDead)
                        DeathClock.restart();
                }

                playerTurn = !playerTurn; // Смена хода
            }

            window.display();
        }
        if (player.selectedDinos.empty()) {                                            // END OF FIGHT CONDITIONS
            Fight_End_screen(false, 100);
        }
        else if (enemy.selectedDinos.empty()) {
            Fight_End_screen(true, enemyPullPrice);
        }


    }




};
