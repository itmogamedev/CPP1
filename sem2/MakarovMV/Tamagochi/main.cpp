#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include "cat.h"
#include "info.h"
#include "endscr.h"

void updatePetPicture(const sf::Texture& texture, sf::Sprite& sprite) {
    sprite.setTexture(texture);
}

void handleButtonClick(Cat& cat, const std::string& action, const sf::Texture& texture, sf::Sprite& sprite) {
    if (action == "Feed") {
        cat.increaseFull(50);
    }
    else if (action == "Water") {
        cat.increaseHydr(50);
    }
    else if (action == "Clean") {
        cat.increaseClean(50);
    }
    updatePetPicture(texture, sprite);
}

void drawButtons(sf::RenderWindow& window, const std::vector<sf::Text>& buttons) {
    for (const auto& button : buttons) {
        window.draw(button);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tamagotchi");
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Texture catTexture1, catTexture2, dogTexture1, dogTexture2, chinchillaTexture1, chinchillaTexture2;
    if (!catTexture1.loadFromFile("cat1.png") || !catTexture2.loadFromFile("cat2.png") ||
        !dogTexture1.loadFromFile("dog1.png") || !dogTexture2.loadFromFile("dog2.png") ||
        !chinchillaTexture1.loadFromFile("chinchilla1.png") || !chinchillaTexture2.loadFromFile("chinchilla2.png")) {
        std::cerr << "Error loading textures\n";
        return 1;
    }

    sf::Sprite sprite;
    sprite.setScale(sf::Vector2f(.01f, .01f));

    std::string petChoice;
    bool petChosen = false;

    sf::RectangleShape logoCat(sf::Vector2f(200, 200)), logoDog(sf::Vector2f(200, 200)), logoChinchilla(sf::Vector2f(200, 200));
    logoCat.setTexture(&catTexture1);
    logoCat.setPosition(30, 200);
    logoDog.setTexture(&dogTexture1);
    logoDog.setPosition(280, 200);
    logoChinchilla.setTexture(&chinchillaTexture1);
    logoChinchilla.setPosition(530, 200);

    while (window.isOpen() && !petChosen) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (logoCat.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petChoice = "cat";
                    sprite.setTexture(catTexture1);
                    petChosen = true;
                }
                else if (logoDog.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petChoice = "dog";
                    sprite.setTexture(dogTexture1);
                    petChosen = true;
                }
                else if (logoChinchilla.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petChoice = "chinchilla";
                    sprite.setTexture(chinchillaTexture1);
                    petChosen = true;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(logoCat);
        window.draw(logoDog);
        window.draw(logoChinchilla);
        window.display();
    }

    Cat cat(1, 100, 100, 100);
    Info info(cat.getFull(), cat.getMaxFull(), cat.getHydr(), cat.getMaxHydr(), cat.getClean(), cat.getMaxClean());

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setPosition(window.getSize().x / 7, window.getSize().y / 10);

    sf::Text feedButton, waterButton, cleanButton;
    feedButton.setFont(font);
    feedButton.setString("Feed");
    feedButton.setCharacterSize(30);
    feedButton.setFillColor(sf::Color::Black);
    feedButton.setPosition(50, window.getSize().y - 100);

    waterButton.setFont(font);
    waterButton.setString("Water");
    waterButton.setCharacterSize(30);
    waterButton.setFillColor(sf::Color::Black);
    waterButton.setPosition(200, window.getSize().y - 100);

    cleanButton.setFont(font);
    cleanButton.setString("Clean");
    cleanButton.setCharacterSize(30);
    cleanButton.setFillColor(sf::Color::Black);
    cleanButton.setPosition(350, window.getSize().y - 100);

    std::vector<sf::Text> buttons = { feedButton, waterButton, cleanButton };
    auto startTime = std::chrono::high_resolution_clock::now();
    bool isPaused = false;

    while (window.isOpen()) {
        sf::Event event;
        if (!isPaused) {
            if (cat.isDead()) {
                endscr(window, 1);
            }
            if (cat.isSuccess()) {
                endscr(window, 0);
                window.clear(sf::Color::Green);
            }
            cat.live();
            sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(), float(cat.getSize()) / cat.getMaxSize()));

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (feedButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        handleButtonClick(cat, "Feed", petChoice == "cat" ? catTexture2 : (petChoice == "dog" ? dogTexture2 : chinchillaTexture2), sprite);
                    }
                    else if (waterButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        handleButtonClick(cat, "Water", petChoice == "cat" ? catTexture2 : (petChoice == "dog" ? dogTexture2 : chinchillaTexture2), sprite);
                    }
                    else if (cleanButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        handleButtonClick(cat, "Clean", petChoice == "cat" ? catTexture2 : (petChoice == "dog" ? dogTexture2 : chinchillaTexture2), sprite);
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::P) {
                        isPaused = true;
                    }
                }
            }

            Info info(cat.getFull(), cat.getMaxFull(), cat.getHydr(), cat.getMaxHydr(), cat.getClean(), cat.getMaxClean());
            text.setString(info.getStr());

            window.clear(sf::Color::White);
            window.draw(sprite);
            window.draw(text);
            drawButtons(window, buttons);
            window.display();
        }
        else {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) {
                    isPaused = false;
                }
            }
        }
    }

    return 0;
}





