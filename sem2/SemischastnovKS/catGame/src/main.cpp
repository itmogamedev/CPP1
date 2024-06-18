#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#include <unistd.h>

// Задача: сделать игру тамагочи про котика.
// Его нужно кормить, поить, убирать.
// Он будет расти и расти пока не заполнит весь экран.
//
// TODO
// Кнопки [кормить, поить, мыть]
// центровать
//
// Управление
// Рисовать кнопки на экране:
// * Покормить
// * Помыть
// * Напоить



void updateCatPicture(const  sf::Texture & texture, sf::Sprite & sprite,
                      std::chrono::time_point<std::chrono::steady_clock>& startTime) {
    sprite.setTexture(texture);
    startTime = std::chrono::high_resolution_clock::now();
}


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Cat");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/arial.ttf")) {
        // error...
    }

    sf::Texture texture1;
    sf::Texture texture2;
    if (!texture1.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/cat1.png") or !texture2.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/cat2.png")) {
        // error...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture1);
    sprite.scale(sf::Vector2f(.01f, .01f));

    // Game logic
    Cat cat( 1, 100, 1000, 1000);
    Info info(cat.getSize(), cat.getMaxSize(),
              cat.getFull(), cat.getMaxFull(),
              cat.getHydr(), cat.getMaxHydr(),
              cat.getClean(), cat.getMaxClean());

    // win/lose screens

    sf::Texture winTexture;
    winTexture.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/win.png");
    sf::Texture loseTexture;
    loseTexture.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/lose.png");

    sf::Sprite winSprite;
    winSprite.setTexture(winTexture);
    winSprite.setPosition(int(window.getSize().x / 2) - 960,int(window.getSize().y / 2) - 540); // centered
    sf::Sprite loseSprite;
    loseSprite.setTexture(loseTexture);
    loseSprite.setPosition(int(window.getSize().x / 2) - 960,int(window.getSize().y / 2) - 540); // centered

    // buttons

    sf::Texture feedT;
    feedT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/feed.png");
    sf::Texture waterT;
    waterT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/water.png");
    sf::Texture cleanT;
    cleanT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/clean.png");

    sf::Sprite feedS;
    feedS.setTexture(feedT);
    feedS.setPosition(int(window.getSize().x / 2) - 140, int(window.getSize().y / 2));
    sf::Sprite waterS;
    waterS.setTexture(waterT);
    waterS.setPosition(int(window.getSize().x / 2) - 140, int(window.getSize().y / 2) + 93);
    sf::Sprite cleanS;
    cleanS.setTexture(cleanT);
    cleanS.setPosition(int(window.getSize().x / 2) - 140, int(window.getSize().y / 2) + 186);

    // signs

    sf::Texture feedSignT;
    feedSignT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/feedSign.png");
    sf::Texture waterSignT;
    waterSignT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/waterSign.png");
    sf::Texture cleanSignT;
    cleanSignT.loadFromFile("/Users/elbias/Downloads/cmake-sfml-project-master/src/cleanSign.png");

    sf::Sprite feedSign;
    feedSign.setTexture(feedSignT);
    feedSign.setPosition(window.getSize().x/2, int(window.getSize().y/10) + 50);
    sf::Sprite waterSign;
    waterSign.setTexture(waterSignT);
    waterSign.setPosition(window.getSize().x/2 + 220, int(window.getSize().y/10) + 50);
    sf::Sprite cleanSign;
    cleanSign.setTexture(cleanSignT);
    cleanSign.setPosition(window.getSize().x/2 + 440, int(window.getSize().y/10) + 50);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(info.getStr());
    text.setCharacterSize(35); // in pixels, not points!
    text.setPosition(window.getSize().x/2, window.getSize().y/10);

    std::chrono::time_point<std::chrono::steady_clock> startTime
            = std::chrono::high_resolution_clock::now();

    while (window.isOpen())	{

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (cat.isDead()) { // TODO Окно поражения
            window.draw(loseSprite);
            window.display();
            sleep(5);
            exit(0);
        }
        if (cat.isSuccess()) { // TODO Окно победы
            window.draw(winSprite);
            window.display();
            sleep(5);
            exit(0);
        }
        cat.live();

        sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(),
                                     float(cat.getSize()) / cat.getMaxSize()));

        while (window.pollEvent(event)) {

            std::chrono::duration<float> duration =
                    std::chrono::high_resolution_clock::now() - startTime;
            if (duration.count() > 1) {
                sprite.setTexture(texture1);
            }

            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and feedS.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    cat.increaseFull(50);
                    updateCatPicture(texture2, sprite, startTime);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and waterS.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    cat.increaseHydr(50);
                    updateCatPicture(texture2, sprite, startTime);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cleanS.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    cat.increaseClean(50);
                    updateCatPicture(texture2, sprite, startTime);
                }
            }
        }


        Info info(cat.getSize(), cat.getMaxSize(),
                  cat.getFull(), cat.getMaxFull(),
                  cat.getHydr(), cat.getMaxHydr(),
                  cat.getClean(), cat.getMaxClean());
        text.setString(info.getStr());

        // Выполняем необходимые действия по отрисовке
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(text);
        window.draw(feedS);
        window.draw(waterS);
        window.draw(cleanS);
        window.draw(feedSign);
        window.draw(waterSign);
        window.draw(cleanSign);
        window.display();
    }

    return 0;
}