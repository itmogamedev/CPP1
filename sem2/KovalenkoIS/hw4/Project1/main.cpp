#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include <iostream>
#include <chrono>


struct AnimalTextures {
    sf::Texture texture1;
    sf::Texture texture2;
};


void updateAnimalPicture(const sf::Texture& texture, sf::Sprite& sprite,
    std::chrono::time_point<std::chrono::steady_clock>& startTime) {
    sprite.setTexture(texture);
    startTime = std::chrono::high_resolution_clock::now();
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Choose Your Animal");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Texture catTexture1, catTexture2, dogTexture1, dogTexture2, shinshillaTexture1, shinshillaTexture2;

    if (!catTexture1.loadFromFile("cat1.png") || !catTexture2.loadFromFile("cat2.png") ||
        !dogTexture1.loadFromFile("dog1.png") || !dogTexture2.loadFromFile("dog2.png") ||
        !shinshillaTexture1.loadFromFile("shinshilla1.png") || !shinshillaTexture2.loadFromFile("shinshilla2.png")) {
        return -1;
    }

    sf::Sprite catSprite, dogSprite, shinshillaSprite;
    catSprite.setTexture(catTexture1);
    dogSprite.setTexture(dogTexture1);
    shinshillaSprite.setTexture(shinshillaTexture1);

    catSprite.setScale(0.25f, 0.25f);
    dogSprite.setScale(0.25f, 0.25f);
    shinshillaSprite.setScale(0.6f, 0.6f);

    catSprite.setPosition(200, 200);
    dogSprite.setPosition(600, 200);
    shinshillaSprite.setPosition(1000, 200);

    sf::Text chooseText("Choose your animal:", font, 50);
    chooseText.setFillColor(sf::Color::Black);
    chooseText.setPosition(500, 50);

    bool animalChosen = false;
    AnimalTextures animalTextures;
    sf::Sprite animalSprite;

    Cat cat(1, 100, 1000, 1000);
    Info info(4, cat.getSize(), cat.getMaxSize(),
        cat.getFull(), cat.getMaxFull(),
        cat.getHydr(), cat.getMaxHydr(),
        cat.getClean(), cat.getMaxClean());

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(info.getStr());
    text.setCharacterSize(20);
    text.setPosition(700+280, 500);

    sf::Texture mealTexture, washTexture, sizeTexture, hydrationTexture, pauseTexture;
    if (!mealTexture.loadFromFile("meal.png") || !washTexture.loadFromFile("wash.png") ||
        !sizeTexture.loadFromFile("size.png") || !hydrationTexture.loadFromFile("hydration.png") ||
        !pauseTexture.loadFromFile("pause.png")) {
        return -1;
    }

    sf::Sprite imageSpriteMeal, imageSpriteWash, imageSpriteSize, imageSpriteHydration, pauseSprite;
    imageSpriteMeal.setTexture(mealTexture);
    imageSpriteWash.setTexture(washTexture);
    imageSpriteSize.setTexture(sizeTexture);
    imageSpriteHydration.setTexture(hydrationTexture);
    pauseSprite.setTexture(pauseTexture);

    imageSpriteMeal.setScale(0.07f, 0.07f);
    imageSpriteWash.setScale(0.07f, 0.07f);
    imageSpriteSize.setScale(0.07f, 0.07f);
    imageSpriteHydration.setScale(0.25f, 0.25f);
    pauseSprite.setScale(0.1f, 0.1f);

    imageSpriteMeal.setPosition(789+300, 430);
    imageSpriteWash.setPosition(1031 + 300, 430);
    imageSpriteSize.setPosition(689 + 300, 430);
    imageSpriteHydration.setPosition(880 + 300, 410);
    pauseSprite.setPosition(980, 200);

    sf::Text winText("You win!", font, 50);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(700, 300);

    sf::Text loseText("You lose!", font, 50);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(700, 300);

    sf::RectangleShape feedButton(sf::Vector2f(200, 50));
    feedButton.setFillColor(sf::Color::Green);
    feedButton.setPosition(50, window.getSize().y - 200);

    sf::RectangleShape washButton(sf::Vector2f(200, 50));
    washButton.setFillColor(sf::Color::Blue);
    washButton.setPosition(300, window.getSize().y - 200);

    sf::RectangleShape waterButton(sf::Vector2f(200, 50));
    waterButton.setFillColor(sf::Color::Cyan);
    waterButton.setPosition(550, window.getSize().y - 200);

    sf::Text feedText("Feed", font, 30);
    feedText.setFillColor(sf::Color::Black);
    feedText.setPosition(100, window.getSize().y - 190);

    sf::Text washText("Wash", font, 30);
    washText.setFillColor(sf::Color::Black);
    washText.setPosition(350, window.getSize().y - 190);

    sf::Text waterText("Water", font, 30);
    waterText.setFillColor(sf::Color::Black);
    waterText.setPosition(600, window.getSize().y - 190);

    bool isPaused = false;
    bool gameWon = false;
    bool increasingSize = false;

    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (!animalChosen) {
                        if (catSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            animalTextures.texture1 = catTexture1;
                            animalTextures.texture2 = catTexture2;
                            animalSprite.setTexture(catTexture1);
                            animalChosen = true;
                        }
                        else if (dogSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            animalTextures.texture1 = dogTexture1;
                            animalTextures.texture2 = dogTexture2;
                            animalSprite.setTexture(dogTexture1);
                            animalChosen = true;
                        }
                        else if (shinshillaSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            animalTextures.texture1 = shinshillaTexture1;
                            animalTextures.texture2 = shinshillaTexture2;
                            animalSprite.setTexture(shinshillaTexture1);
                            animalChosen = true;
                        }
                        animalSprite.setScale(0.01f, 0.01f);
                    }
                    else {
                        if (pauseSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            isPaused = !isPaused;
                        }
                        if (!isPaused && !gameWon) {
                            if (feedButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                cat.increaseFull(100);
                                increasingSize = true;
                            }
                            else if (washButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                cat.increaseClean(100);
                                increasingSize = true;
                            }
                            else if (waterButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                cat.increaseHydr(100);
                                increasingSize = true;
                            }
                        }
                    }
                }
            }
        }

        if (cat.isDead()) {
            window.clear(sf::Color::White);
            window.draw(loseText);
            window.display();
            sf::sleep(sf::seconds(2));
            window.close();
        }

        if (!isPaused && !gameWon && animalChosen) {
            int previousSize = cat.getSize();
            cat.live();
            if (cat.getSize() > previousSize) {
                increasingSize = true;
            }
            else if (cat.getSize() < previousSize) {
                increasingSize = false;
            }
        }

        if (cat.isSuccess()) {
            window.clear(sf::Color::White);
            window.draw(winText);
            window.display();
            sf::sleep(sf::seconds(2));
            window.close();
        }

        if (animalChosen) {
            animalSprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(), float(cat.getSize()) / cat.getMaxSize()));

            if (increasingSize) {
                animalSprite.setTexture(animalTextures.texture1);
            }
            else {
                animalSprite.setTexture(animalTextures.texture2);
            }

            info = Info(8, cat.getSize(), cat.getMaxSize(),
                cat.getFull(), cat.getMaxFull(),
                cat.getHydr(),
                cat.getMaxHydr(),
                cat.getClean(), cat.getMaxClean());
            text.setString(info.getStr());

            window.clear(sf::Color::White);
            window.draw(animalSprite);
            window.draw(imageSpriteMeal);
            window.draw(imageSpriteWash);
            window.draw(imageSpriteSize);
            window.draw(imageSpriteHydration);
            window.draw(text);
            window.draw(feedButton);
            window.draw(washButton);
            window.draw(waterButton);
            window.draw(feedText);
            window.draw(washText);
            window.draw(waterText);
            window.draw(pauseSprite);
            if (gameWon) {
                window.draw(winText);
            }
            window.display();
        }
        else {
            window.clear(sf::Color::White);
            window.draw(chooseText);
            window.draw(catSprite);
            window.draw(dogSprite);
            window.draw(shinshillaSprite);
            window.display();
        }
    }

    return 0;
}