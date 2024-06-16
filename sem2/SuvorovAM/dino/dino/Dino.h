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
#include "DinoType.h"
#include "TextureLoader.h"

class Dino {
private:
    std::string fileName;
    sf::Sprite cardSprite;
    sf::Font font;
    sf::Text nameText;
    sf::Text HPText;
    sf::Texture t_dino_stand;
    sf::Texture t_dino_attack;
    sf::Texture cardTexture;
    sf::Color originalColor;
    sf::Clock damageClock;
    sf::Clock attackClock;
    bool isDamaged;
    bool isAttacking;

    void organizeText(sf::Text& text, std::string textString, sf::Vector2f position) {
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(24);
        text.setPosition(position);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2.f);
    }

    std::string getDinoName(DINO_Type type) {
        switch (type) {
        case Tyrannosaur:
            return "Tyrannosaur";
        case Brachiosaur:
            return "Brachiosaur";
        case Triceratops:
            return "Triceratops";
        default:
            return "Dino";
        }
    }

    void ClockUpdate() {
        if (isDamaged && damageClock.getElapsedTime().asSeconds() > 1) {
            sp_dino.setColor(originalColor);
            isDamaged = false;
        }
        if (isAttacking && attackClock.getElapsedTime().asSeconds() <= 1) {
            sp_dino.setTexture(t_dino_attack);
        }
        else {
            sp_dino.setTexture(t_dino_stand);
            isAttacking = false;
        }
        if (isDead) {
            Rotate();
        }
    }

protected:
    int STR = 30;
    int DEX = 15;
    int INT = 10;

public:
    int HP = 100, cost = 0;
    DINO_Type type;
    sf::Sprite sp_dino;
    sf::Sprite sp_AttackPhase;
    bool isSelected = false, isDead = false;

    bool GetDamageFromEnemy(int damage) {
        HP -= damage;
        isDamaged = true;
        damageClock.restart();
        sp_dino.setColor(sf::Color::Red);

        if (HP <= 0) {
            HP = 0;
            return true;
        }
        return false;
    }

    int attackDamage = 10;

    Dino(DINO_Type type) : type(type) {                                                                             // OLD DINO
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(10, 30);

        STR = distr(gen);
        DEX = distr(gen);
        INT = distr(gen);

        font.loadFromFile("GameData/Arial.ttf");

        switch (type) {
        case DINO_Type::Triceratops:
            t_dino_stand = TextureLoader::getInstance().getTexture("GameData/DinoSprites/Dino2.png");
            t_dino_attack.loadFromFile("GameData/DinoSprites/Dino2_attack.png");
            fileName = "Triceratops.txt";
            cost = 200;
            HP = 135;
            break;
        case DINO_Type::Tyrannosaur:
            t_dino_stand = TextureLoader::getInstance().getTexture("GameData/DinoSprites/Dino3.png");
            t_dino_attack.loadFromFile("GameData/DinoSprites/Dino3_attack.png");
            fileName = "Tyrannosaur.txt";
            cost = 150;
            HP = 110;
            break;
        case DINO_Type::Brachiosaur:
            t_dino_stand = TextureLoader::getInstance().getTexture("GameData/DinoSprites/Dino1.png");
            t_dino_attack.loadFromFile("GameData/DinoSprites/Dino1_attack.png");
            fileName = "Brachiosaur.txt";
            cost = 100;
            HP = 100;
            break;
        default:
            std::cerr << "Unknown dino type" << std::endl;
            return;
        }

        cardTexture = TextureLoader::getInstance().getTexture("GameData/Dino_background.png");
        cardSprite.setTexture(cardTexture);
        cardSprite.setScale(1.0f, 1.1f);
        cardSprite.setPosition(0, 30);

        sp_dino.setTexture(t_dino_stand);
        sp_dino.setScale(0.5f, 0.5f);
        sp_dino.setPosition(0, 40);

        sp_AttackPhase.setTexture(t_dino_attack);
        sp_AttackPhase.setScale(0.5f, 0.5f);
        sp_AttackPhase.setPosition(0, 40);

        isDamaged = false;
        isAttacking = false;
        originalColor = sp_dino.getColor();
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position) {
        organizeText(nameText, getDinoName(type), sf::Vector2f(0, 40));
        organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

        cardSprite.setPosition(position);
        sp_dino.setPosition(position.x, position.y + 65);
        sp_dino.setScale(0.5f, 0.5f);
        nameText.setPosition(sf::Vector2f(position.x + 20, position.y + 25));
        HPText.setPosition(sf::Vector2f(position.x + 20, position.y + 45));

        ClockUpdate();

        window.draw(cardSprite);
        window.draw(sp_dino);
        window.draw(nameText);
        window.draw(HPText);
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position, bool drawCard, bool invert, float scaleMultiplier) {
        organizeText(nameText, getDinoName(type), sf::Vector2f(0, 0));
        organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

        cardSprite.setPosition(position);
        sp_dino.setPosition(invert ? position.x + 90 : position.x, position.y + 45);
        sp_dino.setScale(invert ? -0.5f : 0.5f, 0.5f);
        sp_dino.setScale(sp_dino.getScale() * scaleMultiplier);

        nameText.setPosition(position);
        HPText.setPosition(sf::Vector2f(position.x, position.y + 25));

        ClockUpdate();

        if (drawCard) {
            window.draw(cardSprite);
        }
        window.draw(sp_dino);
        if (scaleMultiplier > 1.0f) {
            window.draw(nameText);
            window.draw(HPText);
        }
    }

    void triggerAttack() {
        isAttacking = true;
        attackClock.restart();
    }

    void Rotate() {
        sp_dino.setColor(sf::Color::Color(0, 0, 0, 220));
    }

    virtual ~Dino() {}

    virtual int damage(Terrain terrain) = 0;
};


class DinoStr : public Dino {
public:
    DinoStr(DINO_Type type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = STR;
        if (terrain == Plain)
            attackDamage *= 2;
        return attackDamage;
    }

};

class DinoDex : public Dino {
public:
    DinoDex(DINO_Type type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = DEX;
        if (terrain == River)
            attackDamage *= 2;
        return attackDamage;
    }

};

class DinoInt : public Dino {
public:
    DinoInt(DINO_Type type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = INT;
        if (terrain == Mountain)
            attackDamage *= 2;
        return attackDamage;
    }

};