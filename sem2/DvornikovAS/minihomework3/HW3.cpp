#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "off your pc", sf::Style::Fullscreen);
sf::Event event;

void countdown();

int main() {
    
    sf::Texture btn_off, btn_on;
    sf::Sprite btn_OFF, btn_ON;

    btn_off.loadFromFile("img/btn_off.png");
    btn_on.loadFromFile("img/btn_on.png");

    btn_OFF.setTexture(btn_off);
    btn_OFF.setOrigin(btn_OFF.getLocalBounds().width / 2, btn_OFF.getLocalBounds().height / 2);
    btn_OFF.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    btn_ON.setTexture(btn_on);
    btn_ON.setOrigin(btn_ON.getLocalBounds().width / 2, btn_ON.getLocalBounds().height / 2);
    btn_ON.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();
        
        window.draw(btn_OFF);

        if (btn_OFF.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            window.draw(btn_ON);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                countdown();
        }

        window.display();
    }

}

void countdown() {

    sf::Texture countdown;
    sf::Sprite CD;

    countdown.loadFromFile("img/countdown.png");
    CD.setTexture(countdown);
    CD.setOrigin(CD.getLocalBounds().width / 2, CD.getLocalBounds().height / 2);
    CD.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10, 60);

    int time = (double) dis(gen);

    sf::Font UA;
    UA.loadFromFile("font/UA.otf");

    sf::Text btn_text(L"до отключения.. " + std::to_wstring(time), UA, 60);
    btn_text.setOrigin(btn_text.getLocalBounds().width / 2, btn_text.getLocalBounds().height / 2);
    btn_text.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    std::string shutdown_command = "shutdown /s /t " + std::to_string(time);

    system(shutdown_command.c_str());

    sf::Clock clock_countdown;

    bool flag = false;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        btn_text.setString(L"до отключения.. " + std::to_wstring(time - (int)clock_countdown.getElapsedTime().asSeconds()));
        btn_text.setOrigin(btn_text.getLocalBounds().width / 2, btn_text.getLocalBounds().height / 2);
        btn_text.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        if (time - clock_countdown.getElapsedTime().asSeconds() <= 0.8) {
            system("shutdown /a");
            btn_text.setString(L"хаха, шутка :3");
            btn_text.setOrigin(btn_text.getLocalBounds().width / 2, btn_text.getLocalBounds().height / 2);
            btn_text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            flag = true;
        }

        window.clear();

        window.draw(CD);
        window.draw(btn_text);

        window.display();

        if (flag == true) {
            sf::sleep(sf::seconds(5));
            window.close();
        }

    }

}