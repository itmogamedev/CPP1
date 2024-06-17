#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "windows.h"
#include "tam.h"
#include "info.h"
#include "button.h"



enum class UTam { cat, dog, chin };
UTam chTam(sf::RenderWindow& window, sf::Font& font) 
{
    Button catB({ 200, 50 }, { 1000, 300 }, sf::Color(50, 50, 50), "CAT", font);
    Button dogB({ 200, 50 }, { 1000, 400 }, sf::Color(50, 50, 50), "DOG", font);
    Button chinB({ 200, 50 }, { 1000, 500 }, sf::Color(50, 50, 50), "CHINCHILLA", font);

    while (window.isOpen()) 
    {
        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    if (catB.clicked(mPos)) 
                    { 
                        catB.color(sf::Color(30, 30, 30), window);
                        catB.draw(window);
                        window.display();
                        Sleep(500);
                        return UTam::cat;
                    }
                    if (dogB.clicked(mPos)) 
                    { 
                        dogB.color(sf::Color(30, 30, 30), window);
                        dogB.draw(window);
                        window.display();
                        Sleep(500);
                        return UTam::dog; 
                    }
                    if (chinB.clicked(mPos))
                    {
                        chinB.color(sf::Color(30, 30, 30), window);
                        chinB.draw(window);
                        window.display();
                        Sleep(500);
                        return UTam::chin;

                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        catB.draw(window);
        dogB.draw(window);
        chinB.draw(window);
        window.display();
    }
}

void end(sf::RenderWindow& window, sf::Font& font, const std::string& message) 
{
    sf::Text endT;
    endT.setFont(font);
    endT.setString(message);
    endT.setCharacterSize(150);
    endT.setFillColor(sf::Color::White);
    endT.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(endT);
        window.display();
    }
}

void upTamPic(const sf::Texture& tex, sf::Sprite& spr,          
    std::chrono::time_point<std::chrono::steady_clock>& strTime, float& texDur) 
{
    spr.setTexture(tex);
    strTime = std::chrono::high_resolution_clock::now();
    texDur = 0.25f;
}                                                                              




int main() 
{

    bool isPaused = false;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "GAMESTARTED");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {}                                                                      

    UTam UTam = chTam(window, font);

    sf::Texture tex1, tex2;
    if (UTam == UTam::cat) 
    {                  
        tex1.loadFromFile("cat1.png");
        tex2.loadFromFile("cat2.png");
    }
    else if (UTam == UTam::dog) 
    {
        tex1.loadFromFile("dog1.png");
        tex2.loadFromFile("dog2.png");
    }
    else if (UTam == UTam::chin) 
    {
        tex1.loadFromFile("chin1.png");
        tex2.loadFromFile("chin2.png");
    }
    sf::Sprite sprite;
    sprite.setTexture(tex1);
    sprite.setScale(sf::Vector2f(0.01f, 0.01f)); 


    Tam tam(1, 100, 1000, 1000); 
    Info info(
        {
        {"Size", {tam.getSize(), tam.getMaxSize()}},
        {"Fullness", {tam.getFull(), tam.getMaxFull()}},
        {"Hydration", {tam.getHydr(), tam.getMaxHydr()}},
        {"Cleanliness", {tam.getClean(), tam.getMaxClean()}}
        });                      

    sf::Text text;    
    text.setFont(font);
    text.setFillColor(sf::Color::White);
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



    Button feed({ 200, 50 }, { text.getPosition().x, 500 }, sf::Color(50, 50, 50), "Feed", font);
    Button drink({ 200, 50 }, { text.getPosition().x + 200, 500 }, sf::Color(50, 50, 50), "Drink", font);
    Button wash({ 200, 50 }, { text.getPosition().x + 400, 500 }, sf::Color(50, 50, 50), "Wash", font);
    Button pause({ 50, 50 }, { text.getPosition().x + 600, 500 }, sf::Color(50, 50, 50), "||", font);



    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::high_resolution_clock::now();
    float texDur = 0.0f;
                                                                                                             
    while (window.isOpen()) 
    {
        if (!isPaused) 
        {
            if (tam.isDead()) 
            {
                end(window, font, "YOU LOSED!(((");
                return 0;
            }
            if (tam.isSuccess()) 
            {
                end(window, font, "YOU WON!)))");
                return 0;
            }

            tam.live();
            sprite.setScale(sf::Vector2f(float(tam.getSize()) / tam.getMaxSize(), float(tam.getSize()) / tam.getMaxSize()));
        }

        while (window.pollEvent(event)) 
        {
            std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - startTime;
            if (texDur > 0.0f)
            {
                texDur -= duration.count();
                if (texDur <= 0.0f)
                {
                    sprite.setTexture(tex1);
                }
            }

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (feed.clicked(mousePos) && !isPaused) 
                    {
                        tam.increaseFull(200);
                        upTamPic(tex2, sprite, startTime, texDur);
                    }
                    if (wash.clicked(mousePos) && !isPaused) 
                    {
                        tam.increaseClean(200);
                        upTamPic(tex2, sprite, startTime, texDur);
                    }
                    if (drink.clicked(mousePos) && !isPaused) 
                    {
                        tam.increaseHydr(200);
                        upTamPic(tex2, sprite, startTime, texDur);
                    }
                    if (pause.clicked(mousePos)) 
                    {
                        isPaused = !isPaused;
                    }
                }
            }
        }

        Info info(
            {
            {"Size", {tam.getSize(), tam.getMaxSize()}},
            {"Fullness", {tam.getFull(), tam.getMaxFull()}},
            {"Hydration", {tam.getHydr(), tam.getMaxHydr()}},
            {"Cleanliness", {tam.getClean(), tam.getMaxClean()}}
            });
        text.setString(info.getStr());

        window.clear(sf::Color(30, 30, 30));
        window.draw(sprite);
        window.draw(text);
        window.draw(iSize);
        window.draw(iFull);
        window.draw(iHydr);
        window.draw(iClean);
        feed.draw(window);
        wash.draw(window);
        drink.draw(window);
        pause.draw(window);
        window.display();
    }

    return 0;
}