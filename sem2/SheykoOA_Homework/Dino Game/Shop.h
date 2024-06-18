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

class Shop {
private:
    std::vector<std::unique_ptr<Dino>> ShopDinos;
    Player& player;

    sf::RenderWindow& window;

    GameState& gameState;

    sf::Vector2f gridPosition; // Позиция сетки на экране
    sf::Vector2f gridSize; // Размеры сетки
    sf::Vector2f cardSize; // Размер карточки динозавра
    sf::Vector2f cardSpacing; // Промежуток между карточками
    int cardsPerRow; // Количество карточек в строке

    void drawDinoCards() {
        sf::Vector2f currentPosition = gridPosition;
        int currentColumn = 0;

        for (auto& dino : ShopDinos) {
            if (dino->isSelected)
                continue;

            sf::Font font;
            font.loadFromFile("GameData/FuturaMediumC.otf");

            sf::Text priceText;
            priceText.setFont(font);
            priceText.setCharacterSize(40);
            priceText.setFillColor(sf::Color::White);
            priceText.setStyle(sf::Text::Bold);
            priceText.setString(std::to_string(dino->cost));
            priceText.setOutlineColor(sf::Color::Black);
            priceText.setOutlineThickness(2.f);
            priceText.setPosition(currentPosition.x + cardSize.x / 2 - priceText.getLocalBounds().width / 2, currentPosition.y + cardSize.y / 2 - priceText.getLocalBounds().height / 2 + 130);

            dino->draw(window, currentPosition);
            window.draw(priceText);

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

    void clearDinoCards() {
        ShopDinos.clear();
    }

public:
    Shop(Player& p1, sf::RenderWindow& window, GameState& gameState) : player(p1), window(window), gameState(gameState) {
        gridPosition = sf::Vector2f(50, 100); // Позиция сетки на экране
        gridSize = sf::Vector2f(800, 600); // Размеры сетки
        cardSize = sf::Vector2f(200, 300); // Размер карточки динозавра
        cardSpacing = sf::Vector2f(70, 10); // Промежуток между карточками
        cardsPerRow = 4; // Количество карточек в строке
    }

    void shopDialog() {
        ShopDinos.clear();

        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < 8; i++) {
            std::uniform_int_distribution<int> choice1(1, 3);
            std::uniform_int_distribution<int> choice2(1, 3);

            DinoType dinoType;
            switch (choice1(gen)) {
            case 1:
                dinoType = Tyrannosaur;
                break;
            case 2:
                dinoType = Brachiosaur;
                break;
            case 3:
                dinoType = Triceratops;
                break;
            }

            switch (choice2(gen)) {
            case 1:
                ShopDinos.push_back(std::make_unique<DinoStr>(dinoType));
                break;
            case 2:
                ShopDinos.push_back(std::make_unique<DinoDex>(dinoType));
                break;
            case 3:
                ShopDinos.push_back(std::make_unique<DinoInt>(dinoType));
                break;
            }
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
        headerText.setString("Shop:");
        headerText.setPosition(50, 5);

        sf::Text balanceText;
        balanceText.setFont(font);
        balanceText.setFillColor(sf::Color::White);
        balanceText.setOutlineColor(sf::Color::Black);
        balanceText.setOutlineThickness(2.f);
        balanceText.setCharacterSize(64);
        balanceText.setPosition(500, 5);

        sf::Texture buttonTexture;
        buttonTexture = TextureLoader::getInstance().getTexture("GameData/Button.png");
        Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

        while (window.isOpen()) {
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

                    for (auto& dino : ShopDinos) {
                        if (dino->sprite.getGlobalBounds().contains(mousePos)) {
                            if (!dino->isSelected && dino->cost <= player.balance) {
                                dino->isSelected = true;
                                player.dinos.push_back(dino.get());
                                player.balance -= dino->cost;
                                player.saveDinosToFile("dinos.txt");
                            }
                        }
                    }
                }
            }

            balanceText.setString("Balance: " + std::to_string(player.balance));

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(headerText);
            window.draw(balanceText);
            drawDinoCards();
            backButton.draw(window);
            window.display();
        }
    }
};