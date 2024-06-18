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
    sf::Texture texture;
    sf::Texture attackTexture;
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

    std::string getDinoName(DinoType type) {
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

    void update() {
        if (isDamaged && damageClock.getElapsedTime().asSeconds() > 1) {
            sprite.setColor(originalColor);
            isDamaged = false;
        }
        if (isAttacking && attackClock.getElapsedTime().asSeconds() <= 1) {
            sprite.setTexture(attackTexture);
        }
        else {
            sprite.setTexture(texture);
            isAttacking = false;
        }
        if (isDead) {
            rotateAfterDeath();
        }
    }

protected:
    int STR = 30;
    int DEX = 15;
    int INT = 10;

public:
    int HP = 100;
    int cost = 0;
    DinoType type;
    sf::Sprite sprite;
    sf::Sprite attackSprite;
    bool isSelected = false;
    bool isDead = false;

    bool receiveDamageAndCheckDeath(int damage) {
        HP -= damage;
        isDamaged = true;
        damageClock.restart();
        sprite.setColor(sf::Color::Red);

        if (HP <= 0) {
            HP = 0;
            return true;
        }
        return false;
    }

    int attackDamage = 10;

    Dino(DinoType type) : type(type) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distr(10, 30);

        STR = distr(gen);
        DEX = distr(gen);
        INT = distr(gen);

        font.loadFromFile("GameData/FuturaMediumC.otf");

        switch (type) {
        case DinoType::Triceratops:
            texture = TextureLoader::getInstance().getTexture("GameData/DinoSprites/TRIC.png");
            attackTexture.loadFromFile("GameData/DinoSprites/TRIC_A.png");
            fileName = "Triceratops.txt";
            cost = 200;
            HP = 135;
            break;
        case DinoType::Tyrannosaur:
            texture = TextureLoader::getInstance().getTexture("GameData/DinoSprites/TREX.png");
            attackTexture.loadFromFile("GameData/DinoSprites/TREX_A.png");
            fileName = "Tyrannosaur.txt";
            cost = 150;
            HP = 110;
            break;
        case DinoType::Brachiosaur:
            texture = TextureLoader::getInstance().getTexture("GameData/DinoSprites/BRA.png");
            attackTexture.loadFromFile("GameData/DinoSprites/BRA_A.png");
            fileName = "Brachiosaur.txt";
            cost = 100;
            HP = 100;
            break;
        default:
            std::cerr << "Unknown dino type" << std::endl;
            return;
        }

        cardTexture = TextureLoader::getInstance().getTexture("GameData/Card.png");
        cardSprite.setTexture(cardTexture);
        cardSprite.setScale(1.0f, 1.1f);
        cardSprite.setPosition(0, 30);

        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f);
        sprite.setPosition(0, 40);

        attackSprite.setTexture(attackTexture);
        attackSprite.setScale(0.5f, 0.5f);
        attackSprite.setPosition(0, 40);

        isDamaged = false;
        isAttacking = false;
        originalColor = sprite.getColor();
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position) {
        organizeText(nameText, getDinoName(type), sf::Vector2f(0, 40));
        organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

        cardSprite.setPosition(position);
        sprite.setPosition(position.x, position.y + 65);
        sprite.setScale(0.5f, 0.5f);
        nameText.setPosition(sf::Vector2f(position.x + 20, position.y + 25));
        HPText.setPosition(sf::Vector2f(position.x + 20, position.y + 45));

        update();

        window.draw(cardSprite);
        window.draw(sprite);
        window.draw(nameText);
        window.draw(HPText);
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position, bool drawCard, bool invert, float scaleMultiplier) {
        organizeText(nameText, getDinoName(type), sf::Vector2f(0, 0));
        organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

        cardSprite.setPosition(position);
        sprite.setPosition(invert ? position.x + 90 : position.x, position.y + 45);
        sprite.setScale(invert ? -0.5f : 0.5f, 0.5f);
        sprite.setScale(sprite.getScale() * scaleMultiplier);

        nameText.setPosition(position);
        HPText.setPosition(sf::Vector2f(position.x, position.y + 25));

        update();

        if (drawCard) {
            window.draw(cardSprite);
        }
        window.draw(sprite);
        if (scaleMultiplier > 1.0f) {
            window.draw(nameText);
            window.draw(HPText);
        }
    }

    void triggerAttack() {
        isAttacking = true;
        attackClock.restart();
    }

    void rotateAfterDeath() {
        sprite.setColor(sf::Color::Color(0, 0, 0, 220));
    }

    virtual ~Dino() {}

    virtual int damage(Terrain terrain) = 0;
};


class DinoStr : public Dino {
public:
    DinoStr(DinoType type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = STR;
        if (terrain == Plain)
            attackDamage *= 2;
        return attackDamage;
    }

};

class DinoDex : public Dino {
public:
    DinoDex(DinoType type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = DEX;
        if (terrain == River)
            attackDamage *= 2;
        return attackDamage;
    }

};

class DinoInt : public Dino {
public:
    DinoInt(DinoType type) : Dino(type) {}

    int damage(Terrain terrain) override {
        attackDamage = INT;
        if (terrain == Mountain)
            attackDamage *= 2;
        return attackDamage;
    }

};