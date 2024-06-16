#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "cat.h"
#include "info.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

void updateCatPicture(const sf::Texture& texture, sf::Sprite& sprite,
    std::chrono::time_point<std::chrono::steady_clock>& startTime, float& textureDuration) {
    sprite.setTexture(texture);
    startTime = std::chrono::high_resolution_clock::now();
    textureDuration = 0.25f;
}


enum class PetChoice { Cat, Chinchilla, Dog };

class Button {
public:

    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& line, sf::Font& font) {
        view.setFillColor(sf::Color(255, 240, 240));
        view.setSize(size);
        view.setPosition(position);
        view.setOutlineColor(sf::Color(230, 150, 150));
        view.setOutlineThickness(1);

        text.setFont(font);
        text.setString(line);
        text.setCharacterSize(40);
        text.setPosition(
            position.x + (size.x - (text.getLocalBounds().width + 15)) / 2,
            position.y + (size.y - (text.getLocalBounds().height + 15)) / 2
        );
        text.setFillColor(sf::Color(220, 90, 100));

    }

    void draw(sf::RenderWindow& window) {
        window.draw(view);
        window.draw(text);
    }

    bool isClicked(const sf::Vector2i& mousePos) {
        return view.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

private:

    sf::RectangleShape view;
    sf::Text text;
};

PetChoice choosePet(sf::RenderWindow& window, sf::Font& font) {

    Button catButton({ 250, 80 }, { 1100, 300 }, "Cat", font);
    Button chinchillaButton({ 250, 80 }, { 1100, 400 }, "Chinchilla", font);
    Button dogButton({ 250, 80 }, { 1100, 500 }, "Dog", font);


    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (catButton.isClicked(mousePos)) {
                        return PetChoice::Cat;
                    }
                    if (chinchillaButton.isClicked(mousePos)) {
                        return PetChoice::Chinchilla;
                    }
                    if (dogButton.isClicked(mousePos)) {
                        return PetChoice::Dog;
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        catButton.draw(window);
        chinchillaButton.draw(window);
        dogButton.draw(window);
        window.display();
    }
}

void winScreen(sf::RenderWindow& window, sf::Font& font) {

    sf::Text win;
    win.setFont(font);
    win.setString("You win!!!");
    win.setCharacterSize(100);
    win.setPosition(window.getSize().x / 2 - win.getLocalBounds().width / 2, window.getSize().y / 2 - (win.getLocalBounds().height / 2 + 100));
    win.setFillColor(sf::Color(255, 222, 222));


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(win);
        window.display();
    }
}

void loseScreen(sf::RenderWindow& window, sf::Font& font) {

    sf::Text lose;
    lose.setFont(font);
    lose.setString("You lose(");
    lose.setCharacterSize(100);
    lose.setPosition(window.getSize().x / 2 - lose.getLocalBounds().width / 2, window.getSize().y / 2 - (lose.getLocalBounds().height / 2 + 100));
    lose.setFillColor(sf::Color(180, 30, 50));

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 222, 222));
        window.draw(lose);
        window.display();
    }
}


int main() {

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Cat");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("HelveticaNowVar.ttf")) {
        std::cout << "You haven't right font((" << std::endl;
    }

    PetChoice petChoice = choosePet(window, font);

    sf::Texture texture1, texture2;

    if (petChoice == PetChoice::Cat) {
        texture1.loadFromFile("cat1.png");
        texture2.loadFromFile("cat2.png");
    }
    else if (petChoice == PetChoice::Chinchilla) {
        texture1.loadFromFile("chinchilla1.jpg");
        texture2.loadFromFile("chinchilla2.jpg");
    }
    else if (petChoice == PetChoice::Dog) {
        texture1.loadFromFile("dog1.jpeg");
        texture2.loadFromFile("dog2.jpg");
    }
    sf::Sprite sprite;
    sprite.setTexture(texture1);
    sprite.setScale(sf::Vector2f(0.01f, 0.01f));

    Button feedButton({ 200, 50 }, { 1000, 250 }, "Feed", font);
    Button waterButton({ 200, 50 }, { 1000, 350 }, "Water", font);
    Button washButton({ 200, 50 }, { 1000, 450 }, "Wash", font);
    Button pauseButton({ 200, 50 }, { 1300, 550 },  "Pause", font);


    Cat cat(2, 100, 100, 100);
    Info info({
        {"Size", {cat.getSize(), cat.getMaxSize()}},
        {"Fullness", {cat.getFull(), cat.getMaxFull()}},
        {"Hydration", {cat.getHydr(), cat.getMaxHydr()}},
        {"Cleanliness", {cat.getClean(), cat.getMaxClean()}}
        });

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color(220, 90, 100));
    text.setString(info.getStr());
    text.setCharacterSize(32);
    text.setPosition(window.getSize().x / 2, window.getSize().y / 10);


    float spriteShift = 350.0f;
    sf::Texture textureSize, textureFullness, textureHydration, textureCleanliness;

    if ((!textureSize.loadFromFile("size.png")) or (!textureFullness.loadFromFile("fullness.jpg")) or (!textureHydration.loadFromFile("hydration.png")) or (!textureCleanliness.loadFromFile("cleanliness.png"))) {
        std::cout << "you haven't some files(" << std::endl;
    };

    sf::Sprite spriteSize(textureSize);
    spriteSize.setScale(sf::Vector2f(0.15f, 0.15f));

    sf::Sprite spriteFull(textureFullness);
    spriteFull.setScale(sf::Vector2f(0.09f, 0.09f));

    sf::Sprite spriteHydr(textureHydration);
    spriteHydr.setScale(sf::Vector2f(0.08f, 0.08f));

    sf::Sprite spriteClean(textureCleanliness);
    spriteClean.setScale(sf::Vector2f(0.08f, 0.08f));

    spriteSize.setPosition(text.getPosition().x + spriteShift, text.getPosition().y);
    spriteFull.setPosition(text.getPosition().x + spriteShift, text.getPosition().y + 100);
    spriteHydr.setPosition(text.getPosition().x + spriteShift, text.getPosition().y + 175);
    spriteClean.setPosition(text.getPosition().x + spriteShift, text.getPosition().y + 250);

    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    float textureDuration = 0.0f;

    bool isPaused = false;

    while (window.isOpen()) {
        if (!isPaused) {
            if (cat.isDead()) {
                loseScreen(window, font);
                return 0;
            }
            else if (cat.isSuccess()) {
                winScreen(window, font);
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

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (feedButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseFull(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }

                    if (waterButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseHydr(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }

                    if (washButton.isClicked(mousePos) && !isPaused) {
                        cat.increaseClean(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }

                    if (pauseButton.isClicked(mousePos)) {
                        isPaused = !isPaused;
                    }
                }
            }
        }

        Info info({ {"Size", {cat.getSize(), cat.getMaxSize()}}, {"Fullness", {cat.getFull(), cat.getMaxFull()}}, 
            {"Hydration", {cat.getHydr(), cat.getMaxHydr()}},{"Cleanliness", {cat.getClean(), cat.getMaxClean()}} });
        text.setString(info.getStr());

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(spriteSize);
        window.draw(spriteFull);
        window.draw(spriteHydr);
        window.draw(spriteClean);
        window.draw(text);
        feedButton.draw(window);
        washButton.draw(window);
        waterButton.draw(window);
        pauseButton.draw(window);
        window.display();
    }

    window.close();

    return 0;
}