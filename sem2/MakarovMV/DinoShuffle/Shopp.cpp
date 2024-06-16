#include "Structure.h"
#include "Shopph.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<Dino*> ShopDinos() {
    return { new Tyranosaurus(), new Brahiosaurus(), new Diplodoc(), new Tryceraptops(), new Stegosaurus(), new Pterodactyl() };
}

void handleShop(sf::RenderWindow& win, const sf::Vector2i mousePoz, std::vector<int>& selectedDinos) {
    sf::Font juraFont;
    if (!juraFont.loadFromFile("Jura-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    int Moneyint = 0;
    std::ifstream money("./moneydata.data");
    std::string balance;

    if (money.is_open()) {
        while (std::getline(money, balance)) {
            Moneyint = std::stoi(balance);
        }
        money.close();
    }

    std::vector<std::string> NmDinos;
    std::ifstream Dinostream("./Dinodata.data");
    std::string dino1;

    if (Dinostream.is_open()) {
        while (std::getline(Dinostream, dino1)) {
            NmDinos.push_back(dino1);
        }
        Dinostream.close();
    }

    sf::Text MoneyText;
    MoneyText.setFont(juraFont);
    MoneyText.setCharacterSize(30);
    MoneyText.setFillColor(sf::Color::White);
    MoneyText.setPosition(1600, 80);
    MoneyText.setString("Money: " + std::to_string(Moneyint));
    win.draw(MoneyText);

    static std::vector<Dino*> dinosaurus = ShopDinos();

    float x = 350.0f, y = 150.0f;
    for (auto& dino : dinosaurus) {
        dino->setPosition(x, y);
        win.draw(dino->getSprite());

        sf::Text dinoText;
        dinoText.setFont(juraFont);
        dinoText.setCharacterSize(20);
        dinoText.setFillColor(sf::Color::White);
        dinoText.setString(dino->getinfo()[0] + " HP: " + std::to_string(dino->getHP()));
        dinoText.setPosition(x, y + dino->getSprite().getGlobalBounds().height + 10);
        win.draw(dinoText);

        x += 500.0f;
        if (x > win.getSize().x - 200) {
            x = 400.0f;
            y += 400.0f;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < dinosaurus.size(); ++i) {
            if (dinosaurus[i]->getSprite().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                int cost = dinosaurus[i]->getCost();
                std::string nm = std::to_string(dinosaurus[i]->getNum());
                if ((selectedDinos.size() < 1) && (Moneyint >= cost) && (std::find(NmDinos.begin(), NmDinos.end(), nm) == NmDinos.end())) {
                    selectedDinos.push_back(i);
                    if (selectedDinos.size() == 1) {
                        break;
                    }
                }
            }
        }
    }
}

