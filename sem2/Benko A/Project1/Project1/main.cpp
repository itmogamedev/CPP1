#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "cat.h"
#include "info.h"


class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& str, sf::Font& font) 
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::White);
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

    void draw(sf::RenderWindow& window) 
    {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(const sf::Vector2i& mousePos) 
    {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
};

enum class PetType { cat, dog, chinchilla };

PetType choosePet(sf::RenderWindow& window, sf::Font& font) 
{
    int x = window.getSize().x / 2 - 100;
    int y = window.getSize().y / 10;
    Button catButton({ 200, 50 }, { 1000, 300 }, sf::Color(0, 0, 0), "CAT", font);
    Button dogButton({ 200, 50 }, { 1000, 400 }, sf::Color(0, 0, 0), "DOG", font);
    Button chinchillaButton({ 200, 50 }, { 1000, 500 }, sf::Color(0, 0, 0), "CHINCHILLA", font);

    while (true) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (catButton.isClicked(mousePos)) return PetType::cat;
                    if (dogButton.isClicked(mousePos)) return PetType::dog;
                    if (chinchillaButton.isClicked(mousePos)) return PetType::chinchilla;
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

void showEnd(sf::RenderWindow& window, sf::Font& font, const std::string& message) 
{
    sf::Text endText;
    endText.setFont(font);
    endText.setString(message);
    endText.setCharacterSize(150);
    endText.setFillColor(sf::Color::Black);
    endText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::White);
        window.draw(endText);
        window.display();
    }
}

void updateCatPicture(const sf::Texture& texture, sf::Sprite& sprite,          
    std::chrono::time_point<std::chrono::steady_clock>& startTime, float& textureDuration) 
{
    sprite.setTexture(texture);
    startTime = std::chrono::high_resolution_clock::now();
    textureDuration = 0.25f;
}                                                                              




int main() 
{

    bool isPaused = false;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "GAMESTARTED");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {}                                                                      

    PetType petType = choosePet(window, font);

    sf::Texture texture1, texture2;
    if (petType == PetType::cat) 
    {                  
        texture1.loadFromFile("cat1.png");
        texture2.loadFromFile("cat2.png");
    }
    else if (petType == PetType::dog) 
    {
        texture1.loadFromFile("dog1.png");
        texture2.loadFromFile("dog2.png");
    }
    else if (petType == PetType::chinchilla) 
    {
        texture1.loadFromFile("chinchilla1.png");
        texture2.loadFromFile("chinchilla2.png");
    }
    sf::Sprite sprite;
    sprite.setTexture(texture1);
    sprite.setScale(sf::Vector2f(0.01f, 0.01f)); 


    Cat cat(1, 100, 1000, 1000); 
    Info info(
        {
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

    sf::Texture iTexSize, iTexFull, iTexHydr, iTexClean;
    if (!iTexSize.loadFromFile("iSize.png") || !iTexFull.loadFromFile("iFull.png") || !iTexHydr.loadFromFile("iHydr.png") || !iTexClean.loadFromFile("iClean.png")) 
    {
    }
    sf::Sprite iSize(iTexSize);
    sf::Sprite iFull(iTexFull);
    sf::Sprite iHydr(iTexHydr);
    sf::Sprite iClean(iTexClean);
    iSize.setScale(sf::Vector2f(0.8f, 0.8f));
    iFull.setScale(sf::Vector2f(0.8f, 0.8f));
    iHydr.setScale(sf::Vector2f(0.8f, 0.8f));
    iClean.setScale(sf::Vector2f(0.8f, 0.8f));


    float iOff = 100.0f;
    iSize.setPosition(text.getPosition().x - iOff, text.getPosition().y);
    iFull.setPosition(text.getPosition().x - iOff, text.getPosition().y + 75);
    iHydr.setPosition(text.getPosition().x - iOff, text.getPosition().y + 150);
    iClean.setPosition(text.getPosition().x - iOff, text.getPosition().y + 225);

    Button feedButton({ 200, 50 }, { text.getPosition().x, 500 }, sf::Color(0, 0, 0), "Feed", font);
    Button washButton({ 200, 50 }, { text.getPosition().x+200, 500 }, sf::Color(0, 0, 0), "Wash", font);
    Button drinkButton({ 200, 50 }, { text.getPosition().x+400, 500 }, sf::Color(0, 0, 0), "Drink", font);
    Button pauseButton({ 50, 50 }, { text.getPosition().x+600, 500 }, sf::Color(0, 0, 0), "||", font);


    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    float textureDuration = 0.0f;
                                                                                                             
    while (window.isOpen()) 
    {
        if (!isPaused) 
        {
            if (cat.isDead()) 
            {
                showEnd(window, font, "YOU LOSED!(((");
                return 0;
            }
            if (cat.isSuccess()) 
            {
                showEnd(window, font, "YOU WON!)))");
                return 0;
            }

            cat.live();
            sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(), float(cat.getSize()) / cat.getMaxSize()));
        }

        while (window.pollEvent(event)) 
        {
            std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - startTime;
            if (textureDuration > 0.0f) 
            {
                textureDuration -= duration.count();
                if (textureDuration <= 0.0f) 
                {
                    sprite.setTexture(texture1);
                }
            }

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (feedButton.isClicked(mousePos) && !isPaused) 
                    {
                        cat.increaseFull(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (washButton.isClicked(mousePos) && !isPaused) 
                    {
                        cat.increaseClean(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (drinkButton.isClicked(mousePos) && !isPaused) 
                    {
                        cat.increaseHydr(50);
                        updateCatPicture(texture2, sprite, startTime, textureDuration);
                    }
                    if (pauseButton.isClicked(mousePos)) 
                    {
                        isPaused = !isPaused;
                    }
                }
            }
        }

        Info info(
            {
            {"Size", {cat.getSize(), cat.getMaxSize()}},
            {"Fullness", {cat.getFull(), cat.getMaxFull()}},
            {"Hydration", {cat.getHydr(), cat.getMaxHydr()}},
            {"Cleanliness", {cat.getClean(), cat.getMaxClean()}}
            });
        text.setString(info.getStr());

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(text);
        window.draw(iSize);
        window.draw(iFull);
        window.draw(iHydr);
        window.draw(iClean);
        feedButton.draw(window);
        washButton.draw(window);
        drinkButton.draw(window);
        pauseButton.draw(window);
        window.display();
    }

    return 0;
}