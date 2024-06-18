#include "game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : window(window), paused(false), gameOver(false), pet(nullptr), info(nullptr) {
    if (!font.loadFromFile("arial.ttf")) {
        // error...
    }
    if (!textureCat.loadFromFile("cat1.png") ||
        !textureDog.loadFromFile("dog1.jpg") ||
        !textureChinchilla.loadFromFile("chinchilla1.jpg")) {
        // error...
    }

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(35);
    text.setPosition(20, 20);

    createButtons();
}

void Game::run() {
    showStartScreen();

    while (window.isOpen()) {
        handleEvents();
        if (!paused && !gameOver) {
            update();
        }
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (isButtonClicked(buttonFeed, mousePos)) {
                pet->increaseFull(50);
                updatePetPicture(sprite.getTexture());
            }
            else if (isButtonClicked(buttonHydrate, mousePos)) {
                pet->increaseHydr(50);
                updatePetPicture(sprite.getTexture());
            }
            else if (isButtonClicked(buttonClean, mousePos)) {
                pet->increaseClean(50);
                updatePetPicture(sprite.getTexture());
            }
            else if (isButtonClicked(buttonPlay, mousePos)) {
                pet->increaseJoy(50);
                updatePetPicture(sprite.getTexture());
            }
            else if (isButtonClicked(buttonPause, mousePos)) {
                togglePause();
            }
            else if (gameOver && isGameOverButtonClicked(buttonRestart, mousePos)) {
                gameOver = false;
                showStartScreen();
            }
        }
    }
}

void Game::update() {
    if (pet) {
        pet->live();
        sprite.setScale(sf::Vector2f(float(pet->getSize()) / pet->getMaxSize(),
            float(pet->getSize()) / pet->getMaxSize()));

        if (pet->isDead()) {
            createGameOverScreen("You lost! Pet died.");
            gameOver = true;
        }
        else if (pet->isSuccess()) {
            createGameOverScreen("You won! Pet grew up.");
            gameOver = true;
        }

        Info info(pet->getSize(), pet->getMaxSize(),
            pet->getFull(), pet->getMaxFull(),
            pet->getHydr(), pet->getMaxHydr(),
            pet->getClean(), pet->getMaxClean(),
            pet->getJoy(), pet->getMaxJoy());
        text.setString(info.getStr());
    }
}

void Game::render() {
    window.clear(sf::Color::White);
    if (!gameOver) {
        window.draw(text);
        if (pet) {
            window.draw(sprite);
            drawButtons();
        }
    }
    else {
        drawGameOverScreen();
    }
    window.display();
}

void Game::showStartScreen() {
    createPetChoiceButtons();

    while (true) {
        window.clear(sf::Color::White);
        drawPetChoiceButtons();
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isPetChoiceButtonClicked(buttonCat, mousePos)) {
                    startGame("Cat");
                    return;
                }
                else if (isPetChoiceButtonClicked(buttonDog, mousePos)) {
                    startGame("Dog");
                    return;
                }
                else if (isPetChoiceButtonClicked(buttonChinchilla, mousePos)) {
                    startGame("Chinchilla");
                    return;
                }
            }
        }
    }
}

void Game::startGame(const std::string& animalType) {
    if (animalType == "Cat") {
        pet = new Cat(1, 100, 1000, 1000, 1000);
        sprite.setTexture(textureCat);
    }
    else if (animalType == "Dog") {
        pet = new Cat(1, 100, 1000, 1000, 1000); // Replace with Dog class if available
        sprite.setTexture(textureDog);
    }
    else if (animalType == "Chinchilla") {
        pet = new Cat(1, 100, 1000, 1000, 1000); // Replace with Chinchilla class if available
        sprite.setTexture(textureChinchilla);
    }
    sprite.setPosition(150, 200); // Center position under the text
    sprite.scale(sf::Vector2f(.01f, .01f));
    startTime = std::chrono::high_resolution_clock::now();
}

void Game::updatePetPicture(const sf::Texture* texture) {
    sprite.setTexture(*texture);
    pet->increaseSize(); // Увеличиваем размер питомца при взаимодействии
    startTime = std::chrono::high_resolution_clock::now();
}

void Game::togglePause() {
    paused = !paused;
}

void Game::createButtons() {
    buttonFeed.setSize(sf::Vector2f(100, 50));
    buttonFeed.setFillColor(sf::Color::Green);
    buttonFeed.setPosition(50, 500);

    textFeed.setFont(font);
    textFeed.setString("Food");
    textFeed.setCharacterSize(20);
    textFeed.setFillColor(sf::Color::Black);
    textFeed.setPosition(buttonFeed.getPosition().x, buttonFeed.getPosition().y - 30);

    buttonHydrate.setSize(sf::Vector2f(100, 50));
    buttonHydrate.setFillColor(sf::Color::Blue);
    buttonHydrate.setPosition(200, 500);

    textHydrate.setFont(font);
    textHydrate.setString("Water");
    textHydrate.setCharacterSize(20);
    textHydrate.setFillColor(sf::Color::Black);
    textHydrate.setPosition(buttonHydrate.getPosition().x, buttonHydrate.getPosition().y - 30);

    buttonClean.setSize(sf::Vector2f(100, 50));
    buttonClean.setFillColor(sf::Color::Yellow);
    buttonClean.setPosition(350, 500);

    textClean.setFont(font);
    textClean.setString("Clean");
    textClean.setCharacterSize(20);
    textClean.setFillColor(sf::Color::Black);
    textClean.setPosition(buttonClean.getPosition().x, buttonClean.getPosition().y - 30);

    buttonPlay.setSize(sf::Vector2f(100, 50));
    buttonPlay.setFillColor(sf::Color::Red);
    buttonPlay.setPosition(500, 500);

    textPlay.setFont(font);
    textPlay.setString("Play");
    textPlay.setCharacterSize(20);
    textPlay.setFillColor(sf::Color::Black);
    textPlay.setPosition(buttonPlay.getPosition().x, buttonPlay.getPosition().y - 30);

    // Добавление кнопки паузы
    buttonPause.setSize(sf::Vector2f(100, 50));
    buttonPause.setFillColor(sf::Color::Cyan);
    buttonPause.setPosition(650, 500);

    textPause.setFont(font);
    textPause.setString("Pause");
    textPause.setCharacterSize(20);
    textPause.setFillColor(sf::Color::Black);
    textPause.setPosition(buttonPause.getPosition().x, buttonPause.getPosition().y - 30);
}

void Game::drawButtons() {
    window.draw(buttonFeed);
    window.draw(textFeed);
    window.draw(buttonHydrate);
    window.draw(textHydrate);
    window.draw(buttonClean);
    window.draw(textClean);
    window.draw(buttonPlay);
    window.draw(textPlay);
    window.draw(buttonPause);
    window.draw(textPause);
}

void Game::createPetChoiceButtons() {
    buttonCat.setSize(sf::Vector2f(100, 50));
    buttonCat.setFillColor(sf::Color::Green);
    buttonCat.setPosition(100, 300);

    textCat.setFont(font);
    textCat.setString("Cat");
    textCat.setCharacterSize(20);
    textCat.setFillColor(sf::Color::Black);
    textCat.setPosition(buttonCat.getPosition().x, buttonCat.getPosition().y - 30);

    buttonDog.setSize(sf::Vector2f(100, 50));
    buttonDog.setFillColor(sf::Color::Blue);
    buttonDog.setPosition(300, 300);

    textDog.setFont(font);
    textDog.setString("Dog");
    textDog.setCharacterSize(20);
    textDog.setFillColor(sf::Color::Black);
    textDog.setPosition(buttonDog.getPosition().x, buttonDog.getPosition().y - 30);

    buttonChinchilla.setSize(sf::Vector2f(100, 50));
    buttonChinchilla.setFillColor(sf::Color::Yellow);
    buttonChinchilla.setPosition(500, 300);

    textChinchilla.setFont(font);
    textChinchilla.setString("Chinchilla");
    textChinchilla.setCharacterSize(20);
    textChinchilla.setFillColor(sf::Color::Black);
    textChinchilla.setPosition(buttonChinchilla.getPosition().x, buttonChinchilla.getPosition().y - 30);
}

void Game::drawPetChoiceButtons() {
    window.draw(buttonCat);
    window.draw(textCat);
    window.draw(buttonDog);
    window.draw(textDog);
    window.draw(buttonChinchilla);
    window.draw(textChinchilla);
}

bool Game::isPetChoiceButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Game::isButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Game::createGameOverScreen(const std::string& message) {
    gameOverText.setFont(font);
    gameOverText.setString(message);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(100, 200);

    buttonRestart.setSize(sf::Vector2f(200, 50));
    buttonRestart.setFillColor(sf::Color::Green);
    buttonRestart.setPosition(300, 400);

    textRestart.setFont(font);
    textRestart.setString("Play again");
    textRestart.setCharacterSize(20);
    textRestart.setFillColor(sf::Color::Black);
    textRestart.setPosition(buttonRestart.getPosition().x + 10, buttonRestart.getPosition().y + 10);
}

void Game::drawGameOverScreen() {
    window.draw(gameOverText);
    window.draw(buttonRestart);
    window.draw(textRestart);
}

bool Game::isGameOverButtonClicked(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
