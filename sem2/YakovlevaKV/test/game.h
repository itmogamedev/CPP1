#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include "cat.h"
#include "info.h"

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text text;
    sf::Texture textureCat, textureDog, textureChinchilla;
    sf::Sprite sprite;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    Cat* pet;
    Info* info;
    bool paused;
    bool gameOver;

    sf::RectangleShape buttonFeed;
    sf::RectangleShape buttonHydrate;
    sf::RectangleShape buttonClean;
    sf::RectangleShape buttonPlay;

    sf::Text textFeed;
    sf::Text textHydrate;
    sf::Text textClean;
    sf::Text textPlay;

    sf::RectangleShape buttonPause;
    sf::Text textPause;

    sf::RectangleShape buttonCat;
    sf::RectangleShape buttonDog;
    sf::RectangleShape buttonChinchilla;

    sf::Text textCat;
    sf::Text textDog;
    sf::Text textChinchilla;

    sf::Text gameOverText;
    sf::RectangleShape buttonRestart;
    sf::Text textRestart;

    void handleEvents();
    void update();
    void render();
    void showStartScreen();
    void startGame(const std::string& animalType);
    void updatePetPicture(const sf::Texture* texture);
    void togglePause();

    void createButtons();
    void drawButtons();
    void createPetChoiceButtons();
    void drawPetChoiceButtons();
    void createGameOverScreen(const std::string& message);
    void drawGameOverScreen();
    bool isButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos);
    bool isPetChoiceButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos);
    bool isGameOverButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos);
};
