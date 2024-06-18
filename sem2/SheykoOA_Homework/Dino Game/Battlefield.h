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

class Battlefield {
private:
    Player& player;
    Player& enemy;

    sf::RenderWindow& window;

    GameState& gameState;

    sf::Vector2f gridPosition; // Позиция сетки на экране
    sf::Vector2f gridSize; // Размеры сетки
    sf::Vector2f cardSize; // Размер карточки динозавра
    sf::Vector2f cardSpacing; // Промежуток между карточками
    int cardsPerRow; // Количество карточек в строке

    void recieveReward(int reward) {
        player.balance += reward;
    }

    void showBattleResult(bool playerWon, int prize) {

        player.saveDinosToFile("dinos.txt");
        gameState = BattleResult;
        recieveReward(prize);

        sf::Texture backgroundTexture;
        backgroundTexture = TextureLoader::getInstance().getTexture("GameData/Plain.png");
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Font font;
        font.loadFromFile("GameData/FuturaMediumC.otf");

        sf::Text resultText;
        resultText.setFont(font);
        resultText.setFillColor(sf::Color::White);
        resultText.setOutlineColor(sf::Color::Black);
        resultText.setOutlineThickness(2.f);
        resultText.setCharacterSize(64);
        resultText.setString(playerWon ? "Victory!" : "Defeat!");
        resultText.setPosition(550, 200);

        sf::Text prizeText;
        prizeText.setFont(font);
        prizeText.setFillColor(sf::Color::White);
        prizeText.setOutlineColor(sf::Color::Black);
        prizeText.setOutlineThickness(2.f);
        prizeText.setCharacterSize(32);
        prizeText.setString("You won " + std::to_string(prize) + " coins!");
        prizeText.setPosition(500, 280);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/Button.png");
        Button selectDinoButton(300, 400, 300, 75, font, "Select Dinos", buttonTexture);
        Button backButton(700, 400, 300, 75, font, "Menu", buttonTexture);

        while (window.isOpen() && gameState == BattleResult) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    if (selectDinoButton.isMouseOver(window)) {
                        gameState = SelectingDinos;
                        return;
                    }

                    if (backButton.isMouseOver(window)) {
                        gameState = InMenu;
                        return;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(resultText);
            window.draw(prizeText);
            selectDinoButton.draw(window);
            backButton.draw(window);
            window.display();
        }


    }


public:

    Battlefield(Player& p1, Player& p2, sf::RenderWindow& window, GameState& gameState) : player(p1), enemy(p2), window(window), gameState(gameState) {
        enemy.randomDinoPull();
        gridPosition = sf::Vector2f(50, 100); // Позиция сетки на экране
        gridSize = sf::Vector2f(800, 600); // Размеры сетки
        cardSize = sf::Vector2f(200, 300); // Размер карточки динозавра
        cardSpacing = sf::Vector2f(70, 10); // Промежуток между карточками
        cardsPerRow = 4; // Количество карточек в строке
    }

    void drawDinoCards() {
        sf::Vector2f currentPosition = gridPosition;
        int currentColumn = 0;

        for (Dino* dino : player.dinos) {
            if (dino->isSelected)
                continue;


            dino->draw(window, currentPosition);

            currentColumn++;
            if (currentColumn >= cardsPerRow) {
                currentColumn = 0;
                currentPosition.x = gridPosition.x;
                currentPosition.y += cardSize.y + cardSpacing.y;
            }
            else {
                currentPosition.x += cardSize.x + cardSpacing.x;
            }
        }
    }


    void dinosSelection() {
        if (player.dinos.size() < 3) {
            gameState = InMenu;
            return;
        }

        sf::Texture backgroundTexture;
        backgroundTexture = TextureLoader::getInstance().getTexture("GameData/Plain.png");
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Font font;
        font.loadFromFile("GameData/FuturaMediumC.otf");

        sf::Text headerText;
        headerText.setFont(font);
        headerText.setFillColor(sf::Color::White);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);
        headerText.setString("Select 3 dinos for battle:");
        headerText.setPosition(50, 5);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/Button.png");
        Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

        while (window.isOpen() && player.selectedDinos.size() < 3) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    // Обработка нажатия на кнопку "Вернуться в меню"
                    if (backButton.isMouseOver(window)) {
                        gameState = InMenu;
                        return;
                    }

                    for (Dino* dino : player.dinos) {
                        if (dino->sprite.getGlobalBounds().contains(mousePos)) {
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
            drawDinoCards(); // Отрисовка карточек динозавров
            backButton.draw(window);
            window.display();
        }

        if (player.selectedDinos.size() == 3) {
            gameState = Battle;
        }
    }

    void dinosShowcase() {
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("GameData/Plain.png");
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Font font;
        font.loadFromFile("GameData/FuturaMediumC.otf");

        sf::Text headerText;
        headerText.setFont(font);
        headerText.setFillColor(sf::Color::White);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);
        headerText.setString("My Dinos:");
        headerText.setPosition(50, 5);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/Button.png");
        Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

        while (window.isOpen() && player.selectedDinos.size() < 3) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                    // Обработка нажатия на кнопку "Вернуться в меню"
                    if (backButton.isMouseOver(window)) {
                        gameState = InMenu;
                        return;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(headerText);
            drawDinoCards(); // Отрисовка карточек динозавров
            backButton.draw(window);
            window.display();
        }
    }


    void battleProcess() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(0, 2);
        Terrain terrain = static_cast<Terrain>(distr(gen));

        sf::Texture backgroundTexture;
        switch (terrain) {
        case Plain:
            backgroundTexture.loadFromFile("GameData/Plain.png");
            break;
        case River:
            backgroundTexture.loadFromFile("GameData/River.png");
            break;
        case Mountain:
            backgroundTexture.loadFromFile("GameData/Mountain.png");
            break;
        }
        sf::Sprite backgroundSprite(backgroundTexture);
        sf::Text headerText;
        sf::Font font;
        font.loadFromFile("GameData/FuturaMediumC.otf");
        headerText.setFont(font); // Здесь font - ваш шрифт
        headerText.setFillColor(sf::Color::White);
        headerText.setOutlineColor(sf::Color::Black);
        headerText.setOutlineThickness(2.f);
        headerText.setCharacterSize(64);

        headerText.setPosition(50, 5); // Расположение текста на экране

        sf::Clock attackClock;
        sf::Clock agonyClock;
        bool playerTurn = true;

        int enemyPullPrice = 0;
        for (Dino* dino : enemy.selectedDinos)
            enemyPullPrice += dino->cost;

        while (window.isOpen() && !player.selectedDinos.empty() && !enemy.selectedDinos.empty()) {
            headerText.setString(playerTurn ? "Enemy Turn!" : "Your Turn!");
            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(headerText);

            for (int i = 0; i < player.selectedDinos.size() - 1; i++) {
                player.selectedDinos[i]->draw(window, sf::Vector2f(100 + i * 150, 350), false, true, 0.7);
            }
            for (int i = 0; i < enemy.selectedDinos.size() - 1; i++) {
                enemy.selectedDinos[i]->draw(window, sf::Vector2f(900 + i * 150, 350), false, false, 0.7);
            }

            player.selectedDinos.back()->draw(window, sf::Vector2f(450, 300), false, true, 1.35);
            enemy.selectedDinos.back()->draw(window, sf::Vector2f(750, 300), false, false, 1.35);

            if (agonyClock.getElapsedTime().asSeconds() > 1) {
                if (enemy.selectedDinos.back()->isDead)
                    enemy.selectedDinos.pop_back();

                if (player.selectedDinos.back()->isDead) {
                    player.deleteDino(player.selectedDinos.back());
                    player.selectedDinos.pop_back();
                }
                    
            }

            if (attackClock.getElapsedTime().asSeconds() > 2) {
                attackClock.restart();


                if (playerTurn) {
                    player.attackEnemy(enemy, enemy.selectedDinos, terrain);
                    if (enemy.selectedDinos.back()->isDead)
                        agonyClock.restart();
                }
                else {
                    enemy.attackEnemy(player, player.selectedDinos, terrain);
                    if (player.selectedDinos.back()->isDead)
                        agonyClock.restart();
                }

                playerTurn = !playerTurn; // Смена хода
            }

            window.display();
        }
        if (player.selectedDinos.empty()) {
            showBattleResult(false, 100);
        }
        else if (enemy.selectedDinos.empty()) {
            showBattleResult(true, enemyPullPrice);
        }


    }




};
