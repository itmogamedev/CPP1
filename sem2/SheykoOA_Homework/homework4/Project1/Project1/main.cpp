#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include <iostream>
#include <chrono>

enum class PetType { Cat, Dog, Chinchilla };

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& str, sf::Font& font) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1);

        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setPosition(
            position.x + (size.x - text.getLocalBounds().width) / 2,
            position.y + (size.y - text.getLocalBounds().height) / 2
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(const sf::Vector2i& mousePos) {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
};

PetType choosePet(sf::RenderWindow& window, sf::Font& font) {
    Button catButton({ 200, 50 }, { 100, 100 }, sf::Color(169, 169, 169), "Cat", font);
    Button dogButton({ 200, 50 }, { 100, 200 }, sf::Color(169, 169, 169), "Dog", font);
    Button chinchillaButton({ 200, 50 }, { 100, 300 }, sf::Color(169, 169, 169), "Chinchilla", font);

    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (catButton.isClicked(mousePos)) return PetType::Cat;
                    if (dogButton.isClicked(mousePos)) return PetType::Dog;
                    if (chinchillaButton.isClicked(mousePos)) return PetType::Chinchilla;
                }
            }
        }

        window.clear(sf::Color::White);
        catButton.draw(window);
        dogButton.draw(window);
        chinchillaButton.draw(window);
        window.display();
    }
}

void showEndScreen(sf::RenderWindow& window, sf::Font& font, const std::string& message) {
    sf::Text endText;
    endText.setFont(font);
    endText.setString(message);
    endText.setCharacterSize(50);
    endText.setFillColor(sf::Color::Red);
    endText.setPosition(window.getSize().x / 2 - endText.getLocalBounds().width / 2, window.getSize().y / 2 - endText.getLocalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::White);
        window.draw(endText);
        window.display();
    }
}

void updateCatPicture(const sf::Texture& texture, sf::Sprite& sprite,
    std::chrono::time_point<std::chrono::steady_clock>& startTime, float& textureDuration) {
    sprite.setTexture(texture);
    startTime = std::chrono::high_resolution_clock::now();
    textureDuration = 0.25f;
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Pet");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
    }

    PetType petType = choosePet(window, font);

    sf::Texture texture1, texture2;
    if (petType == PetType::Cat) {
        texture1.loadFromFile("cat1.png");
        texture2.loadFromFile("cat2.png");
    }
    else if (petType == PetType::Dog) {
        texture1.loadFromFile("dog1.png");
        texture2.loadFromFile("dog2.png");
    }
    else if (petType == PetType::Chinchilla) {
        texture1.loadFromFile("chinchilla1.png");
        texture2.loadFromFile("chinchilla2.png");
    }
    sf::Sprite sprite;
    sprite.setTexture(texture1);
    sprite.setScale(sf::Vector2f(0.01f, 0.01f));

    Button feedButton({ 200, 50 }, { 900, 400 }, sf::Color(169, 169, 169), "Feed", font);
    Button washButton({ 200, 50 }, { 1150, 400 }, sf::Color(169, 169, 169), "Wash", font);
    Button drinkButton({ 200, 50 }, { 1400, 400 }, sf::Color(169, 169, 169), "Drink", font);
    Button pauseButton({ 50, 50 }, { 1650, 400 }, sf::Color(169, 169, 169), "||", font);

    bool isPaused = false;

    Cat cat(1, 100, 1000, 1000);
    Info info({
        {"Size", {cat.getSize(), cat.getMaxSize()}},
        {"Fullness", {cat.getFull(), cat.getMaxFull()}},
        {"Hydration", {cat.getHydr(), cat.getMaxHydr()}},
        {"Cleanliness", {cat.getClean(), cat.getMaxClean()}}
        });

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(info.getStr());
    text.setCharacterSize(35);
    text.setPosition(window.getSize().x / 2, window.getSize().y / 10);

    sf::Texture iconTextureSize, iconTextureFullness, iconTextureHydration, iconTextureCleanliness;
    if (!iconTextureSize.loadFromFile("icon_size.png") ||
        !iconTextureFullness.loadFromFile("icon_fullness.png") ||
        !iconTextureHydration.loadFromFile("icon_hydration.png") ||
        !iconTextureCleanliness.loadFromFile("icon_cleanliness.png")) {
    }


    sf::Sprite iconSize(iconTextureSize);
    sf::Sprite iconFullness(iconTextureFullness);
    sf::Sprite iconHydration(iconTextureHydration);
    sf::Sprite iconCleanliness(iconTextureCleanliness);


    iconSize.setScale(sf::Vector2f(0.75f, 0.75f));
    iconFullness.setScale(sf::Vector2f(0.75f, 0.75f));
    iconHydration.setScale(sf::Vector2f(0.75f, 0.75f));
    iconCleanliness.setScale(sf::Vector2f(0.75f, 0.75f));


    float iconOffset = 100.0f;
    iconSize.setPosition(text.getPosition().x - iconOffset, text.getPosition().y);
    iconFullness.setPosition(text.getPosition().x - iconOffset, text.getPosition().y + 70);
    iconHydration.setPosition(text.getPosition().x - iconOffset, text.getPosition().y + 140);
    iconCleanliness.setPosition(text.getPosition().x - iconOffset, text.getPosition().y + 210);

    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    float textureDuration = 0.0f; 

    while (window.isOpen()) {
        if (!isPaused) {
            if (cat.isDead()) {
                showEndScreen(window, font, "You Lose!");
                return 0;
            }
            if (cat.isSuccess()) {
                showEndScreen(window, font, "You Win!");
                return 0;
            }

            cat.live();
            sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(), float(cat.getSize()) / cat.getMaxSize()));
        }

        while (window.pollEvent(event)) {
            std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - startTime;
            if (textureDuration > 0.0f) {
                textureDuration -= duration.count();
                if (textureDuration <= 0.0f) {
                    sprite.setTexture(texture1);
                }
            }

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (feedButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseFull(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (washButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseClean(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (drinkButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseHydr(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (pauseButton.isClicked(mousePos)) {
                        isPaused = !isPaused;
                    }
                }
            }
        }

        Info info({
            {"Size", {cat.getSize(), cat.getMaxSize()}},
            {"Fullness", {cat.getFull(), cat.getMaxFull()}},
            {"Hydration", {cat.getHydr(), cat.getMaxHydr()}},
            {"Cleanliness", {cat.getClean(), cat.getMaxClean()}}
            });
        text.setString(info.getStr());

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(text);
        window.draw(iconSize);
        window.draw(iconFullness);
        window.draw(iconHydration);
        window.draw(iconCleanliness);
        feedButton.draw(window);
        washButton.draw(window);
        drinkButton.draw(window);
        pauseButton.draw(window);
        window.display();
    }

    return 0;
}
