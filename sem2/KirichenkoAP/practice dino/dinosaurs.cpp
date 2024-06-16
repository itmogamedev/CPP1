#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <random>

void PrintPicture(sf::RenderWindow& window, std::string file, int x, int y, sf::Vector2f targetSize) {

    sf::Texture t;
    t.loadFromFile(file);
    sf::Sprite s;
    s.setTexture(t);
    s.setScale(targetSize.x / s.getLocalBounds().width, targetSize.y / s.getLocalBounds().height);
    s.setPosition(x, y);
    window.draw(s);
}

void PrintText(sf::RenderWindow& window, std::string writed, int x, int y, int size, sf::Color color) {

    sf::Font font;
    font.loadFromFile("Montserrat-Medium.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(writed);
    text.setPosition(x, y);
    text.setCharacterSize(size);
    text.setFillColor(color);
    window.draw(text);
}

void PrintSquare(sf::RenderWindow& window, int x, int y) {

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(250.0f, 250.0f));
    square.setPosition(x, y);
    square.setFillColor(sf::Color::Black);
    square.setOutlineThickness(4);
    square.setOutlineColor(sf::Color::White);
    window.draw(square);
}

void Error(std::string line) {
    sf::RenderWindow window(sf::VideoMode(1400, 300), "error");
    window.clear();
    PrintText(window, line, 200, 100, 60, sf::Color::Cyan);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

void Menu(sf::RenderWindow& window);

bool IsDead(int hp, int enemy_hp) {

    if (hp <= 0) {
        return true;
    }
    if (enemy_hp <= 0) {
        return false;
    }
}

bool Round(sf::RenderWindow& window, std::string pool, std::string enemy_pool) {

    int dino1, dino2;
    std::string file_dino1_1, file_dino1_2, file_dino1_3, file_dino1_4, file_dino2_1, file_dino2_2, file_dino2_3, file_dino2_4;

    dino1 = pool[0] - 48;
    dino2 = enemy_pool[0] - 48;

    switch (dino1) {
    case 1:
        file_dino1_1 = "Tyr1.png";
        file_dino1_2 = "Tyr2.png";
        file_dino1_3 = "Tyr3.png";
        file_dino1_4 = "Tyr4.png";
        break;
    case 2:
        file_dino1_1 = "Bra1.png";
        file_dino1_2 = "Bra2.png";
        file_dino1_3 = "Bra3.png";
        file_dino1_4 = "Bra4.png";
        break;
    case 3:
        file_dino1_1 = "Tri1.png";
        file_dino1_2 = "Tri2.png";
        file_dino1_3 = "Tri3.png";
        file_dino1_4 = "Tri4.png";
        break;
    }

    switch (dino2) {
    case 1:
        file_dino2_1 = "Tyr1.png";
        file_dino2_2 = "Tyr2.png";
        file_dino2_3 = "Tyr3.png";
        file_dino2_4 = "Tyr4.png";
        break;
    case 2:
        file_dino2_1 = "Bra1.png";
        file_dino2_2 = "Bra2.png";
        file_dino2_3 = "Bra3.png";
        file_dino2_4 = "Bra4.png";
        break;
    case 3:
        file_dino2_1 = "Tri1.png";
        file_dino2_2 = "Tri2.png";
        file_dino2_3 = "Tri3.png";
        file_dino2_4 = "Tri4.png";
        break;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 3);
    int randomTerrain = distr(gen);

    int hp = 100;
    int enemy_hp = 100;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();

        switch (randomTerrain) {
        case 1:
            PrintText(window, "TERRAIN: PLAIN", 730, 90, 60, sf::Color::Cyan);
            break;
        case 2:
            PrintText(window, "TERRAIN: RIVER", 730, 90, 60, sf::Color::Cyan);
            break;
        case 3:
            PrintText(window, "TERRAIN: MOUNTAIN", 650, 90, 60, sf::Color::Cyan);
            break;
        }

        PrintText(window, "Your Dino:", 500, 200, 50, sf::Color::White);
        PrintText(window, "Enemy's Dino:", 1150, 200, 50, sf::Color::White);

        if (hp <= 100 && hp > 66) {
            PrintPicture(window, file_dino1_1, 400, 300, sf::Vector2f(450.0f, 450.0f));
        }
        else if (hp <= 66 && hp > 33) {
            PrintPicture(window, file_dino1_2, 400, 300, sf::Vector2f(450.0f, 450.0f));
        }
        else if (hp <= 33 && hp > 0) {
            PrintPicture(window, file_dino1_3, 400, 300, sf::Vector2f(450.0f, 450.0f));
        }

        if (enemy_hp <= 100 && enemy_hp > 66) {
            PrintPicture(window, file_dino2_1, 1100, 300, sf::Vector2f(450.0f, 450.0f));
        }
        else if (enemy_hp <= 66 && enemy_hp > 33) {
            PrintPicture(window, file_dino2_2, 1100, 300, sf::Vector2f(450.0f, 450.0f));
        }
        else if (enemy_hp <= 33 && enemy_hp > 0) {
            PrintPicture(window, file_dino2_3, 1100, 300, sf::Vector2f(450.0f, 450.0f));
        }

        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_int_distribution<int> distr1(10, 20);
        int damage1 = distr1(gen1);

        std::random_device rd2;
        std::mt19937 gen2(rd2());
        std::uniform_int_distribution<int> distr2(10, 20);
        int damage2 = distr2(gen2);

        hp = hp - damage1;

        if ((randomTerrain == 1 and dino1 == 1) or (randomTerrain == 2 and dino1 == 2) or (randomTerrain == 3 and dino1 == 3)) {
            enemy_hp = enemy_hp - (damage2 * 2);
        }
        else {
            enemy_hp = enemy_hp - damage2;
        }

        Sleep(1000);

        if (hp <= 0 || enemy_hp <= 0) {
            if (IsDead(hp, enemy_hp)) {
                PrintPicture(window, file_dino1_4, 400, 300, sf::Vector2f(450.0f, 450.0f));
                PrintText(window, "WINNER", 1200, 800, 55, sf::Color::Cyan);
                window.display();
                Sleep(1000);
                return false;
            }
            else {
                PrintText(window, "WINNER", 500, 800, 55, sf::Color::Cyan);
                PrintPicture(window, file_dino2_4, 1100, 300, sf::Vector2f(450.0f, 450.0f));
                window.display();
                Sleep(1000);
                return true;
            }

        }

        window.display();
    }
}

void Fight(sf::RenderWindow& window) {

    std::string pool;
    std::string line;
    std::ifstream file_pool("fighters.txt");
    if (file_pool.is_open()) {
        while (std::getline(file_pool, line)) {
            pool = line;
        }
        std::ofstream file_pool("fighters.txt");
        file_pool << "";
    }
    file_pool.close();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 3);
    std::string enemy_pool;
    for (int i = 0; i < 3; ++i) {
        enemy_pool += std::to_string(distr(gen));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();

        int cur_cash;
        std::string cash;
        std::ifstream file_cash("cash.txt");
        if (file_cash.is_open()) {
            while (std::getline(file_cash, cash)) {
                cur_cash = stoi(cash);
            }
        }
        file_cash.close();

        while (pool.length() != 0 and enemy_pool.length() != 0) {

            if (Round(window, pool, enemy_pool)) {

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> distr(14, 21);
                int prise = distr(gen);

                cur_cash = cur_cash + prise;
                std::ofstream file_cash;
                file_cash.open("cash.txt");
                if (file_cash.is_open())
                {
                    file_cash << cur_cash;
                }
                file_cash.close();

                enemy_pool.erase(enemy_pool.begin());
            }
            else {
                pool.erase(pool.begin());
            }
        }

        Sleep(1000);
        window.display();

        Menu(window);
    }
}

void Choosing_fighters(sf::RenderWindow &window) {

    int c = 3;
    bool Tyr1 = false;
    bool Bra1 = false;
    bool Tri1 = false;
    bool Tyr2 = false;
    bool Bra2 = false;
    bool Tri2 = false;
    bool Tyr3 = false;
    bool Bra3 = false;
    bool Tri3 = false;
    
    while (window.isOpen()) {

        window.clear();

        sf::RectangleShape buttonSelectTyr;
        buttonSelectTyr.setSize(sf::Vector2f(200, 70));
        buttonSelectTyr.setPosition(600, 400);
        buttonSelectTyr.setFillColor(sf::Color::Black);
        buttonSelectTyr.setOutlineThickness(4);
        buttonSelectTyr.setOutlineColor(sf::Color::Cyan);

        sf::RectangleShape buttonSelectBra;
        buttonSelectBra.setSize(sf::Vector2f(200, 70));
        buttonSelectBra.setPosition(600, 500);
        buttonSelectBra.setFillColor(sf::Color::Black);
        buttonSelectBra.setOutlineThickness(4);
        buttonSelectBra.setOutlineColor(sf::Color::Cyan);

        sf::RectangleShape buttonSelectTri;
        buttonSelectTri.setSize(sf::Vector2f(200, 70));
        buttonSelectTri.setPosition(600, 600);
        buttonSelectTri.setFillColor(sf::Color::Black);
        buttonSelectTri.setOutlineThickness(4);
        buttonSelectTri.setOutlineColor(sf::Color::Cyan);

        sf::RectangleShape buttonMenu;
        buttonMenu.setSize(sf::Vector2f(200, 110));
        buttonMenu.setPosition(1650, 60);
        buttonMenu.setFillColor(sf::Color::Black);
        buttonMenu.setOutlineThickness(5);
        buttonMenu.setOutlineColor(sf::Color::Cyan);

        sf::RectangleShape buttonNext;
        buttonNext.setSize(sf::Vector2f(300, 165));
        buttonNext.setPosition(1550, 730);
        buttonNext.setFillColor(sf::Color::Black);
        buttonNext.setOutlineThickness(5);
        buttonNext.setOutlineColor(sf::Color::Red);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    sf::Vector2i mouse = sf::Mouse::getPosition(window);

                    if (c > 0) {

                        if (buttonSelectTyr.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {

                            int cntTyr = 0;
                            std::string cnt_dino_number;
                            std::ifstream cnt_file_dino("dino_numbers.txt");
                            if (cnt_file_dino.is_open()) {
                                while (std::getline(cnt_file_dino, cnt_dino_number)) {
                                    cntTyr = std::count(cnt_dino_number.begin(), cnt_dino_number.end(), '1');
                                }
                            }
                            cnt_file_dino.close();
                            if (cntTyr == 0) {
                                Error("You don't have any Tyrannosaurs");
                                break;
                            }

                            if (c == 3) { Tyr1 = true; }
                            if (c == 2) { Tyr2 = true; }
                            if (c == 1) { Tyr3 = true; }
                            
                            std::ofstream file_fighters;
                            file_fighters.open("fighters.txt", std::ios::app);
                            file_fighters << 1;
                            file_fighters.close();

                            std::string dino_number;
                            std::string content;
                            std::ifstream file_dino("dino_numbers.txt");
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    content += dino_number + '\n';
                                }
                            }
                            file_dino.close();
                            if (!content.empty() && content.back() == '\n') {
                                content.pop_back();
                            }
                            bool replaced = false;
                            for (char& ch : content) {
                                if (ch == '1') {
                                    ch = '0';
                                    std::ofstream file_dino("dino_numbers.txt");
                                    file_dino << content;
                                    break;
                                }
                            }
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '1')), 510, 402, 50, sf::Color::White);
                                }
                            }
                            file_dino.close();
                            c--;
                            break;
                        }

                        if (buttonSelectBra.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {

                            int cntBra = 0;
                            std::string cnt_dino_number;
                            std::ifstream cnt_file_dino("dino_numbers.txt");
                            if (cnt_file_dino.is_open()) {
                                while (std::getline(cnt_file_dino, cnt_dino_number)) {
                                    cntBra = std::count(cnt_dino_number.begin(), cnt_dino_number.end(), '2');
                                }
                            }
                            cnt_file_dino.close();
                            if (cntBra == 0) {
                                Error("You don't have any Brachiosaurs");
                                break;
                            }

                            if (c == 3) { Bra1 = true; }
                            if (c == 2) { Bra2 = true; }
                            if (c == 1) { Bra3 = true; }

                            std::ofstream file_fighters;
                            file_fighters.open("fighters.txt", std::ios::app);
                            file_fighters << 2;
                            file_fighters.close();

                            std::string dino_number;
                            std::string content;
                            std::ifstream file_dino("dino_numbers.txt");
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    content += dino_number + '\n';
                                }
                            }
                            file_dino.close();
                            if (!content.empty() && content.back() == '\n') {
                                content.pop_back();
                            }
                            bool replaced = false;
                            for (char& ch : content) {
                                if (ch == '2') {
                                    ch = '0';
                                    std::ofstream file_dino("dino_numbers.txt");
                                    file_dino << content;
                                    break;
                                }
                            }
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '2')), 510, 402, 50, sf::Color::White);
                                }
                            }
                            file_dino.close();
                            c--;
                            break;
                        }

                        if (buttonSelectTri.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                            
                            int cntTri = 0;
                            std::string cnt_dino_number;
                            std::ifstream cnt_file_dino("dino_numbers.txt");
                            if (cnt_file_dino.is_open()) {
                                while (std::getline(cnt_file_dino, cnt_dino_number)) {
                                    cntTri = std::count(cnt_dino_number.begin(), cnt_dino_number.end(), '3');
                                }
                            }
                            cnt_file_dino.close();
                            if (cntTri == 0) {
                                Error("You don't have any Triceratopses");
                                break;
                            }

                            if (c == 3) { Tri1 = true; }
                            if (c == 2) { Tri2 = true; }
                            if (c == 1) { Tri3 = true; }

                            std::ofstream file_fighters;
                            file_fighters.open("fighters.txt", std::ios::app);
                            file_fighters << 3;
                            file_fighters.close();

                            std::string dino_number;
                            std::string content;
                            std::ifstream file_dino("dino_numbers.txt");
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    content += dino_number + '\n';
                                }
                            }
                            file_dino.close();
                            if (!content.empty() && content.back() == '\n') {
                                content.pop_back();
                            }
                            bool replaced = false;
                            for (char& ch : content) {
                                if (ch == '3') {
                                    ch = '0';
                                    std::ofstream file_dino("dino_numbers.txt");
                                    file_dino << content;
                                    break;
                                }
                            }
                            if (file_dino.is_open()) {
                                while (std::getline(file_dino, dino_number)) {
                                    PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '3')), 510, 402, 50, sf::Color::White);
                                }
                            }
                            file_dino.close();
                            c--;
                            break;
                        }
                    }

                    if (buttonNext.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        if (c < 3) {
                            Fight(window);
                        }
                        else {
                            Error("You didn't choose the fighters");
                        }
                    }

                    if (buttonMenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {

                        std::ofstream file_pool("fighters.txt");
                        if (file_pool.is_open()) {
                            file_pool << "";
                        }
                        file_pool.close();

                        Menu(window);
                    }
                }
            }
        }

        std::string dino_number;
        std::ifstream file_dino("dino_numbers.txt");
        if (file_dino.is_open()) {
            while (std::getline(file_dino, dino_number)) {
                PrintText(window, "YOUR POOL", 305, 250, 55, sf::Color::White);
                PrintText(window, "Tyrannosaurs:", 140, 400, 50, sf::Color::White);
                PrintText(window, "Brachiosaurs:", 140, 500, 50, sf::Color::White);
                PrintText(window, "Triceratopses:", 140, 600, 50, sf::Color::White);
                PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '1')), 510, 402, 50, sf::Color::White);
                PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '2')), 500, 502, 50, sf::Color::White);
                PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '3')), 510, 602, 50, sf::Color::White);
            }
        }
        file_dino.close();

        window.draw(buttonSelectTyr);
        window.draw(buttonSelectBra);
        window.draw(buttonSelectTri);
        window.draw(buttonMenu);
        window.draw(buttonNext);

        PrintText(window, "Choose your fighters (1-3 Dinos)", 470, 100, 60, sf::Color::Cyan);
        PrintText(window, "YOUR FIGHTERS", 1160, 250, 55, sf::Color::White);
        PrintText(window, "SELECT", 634, 412, 35, sf::Color::White);
        PrintText(window, "SELECT", 634, 512, 35, sf::Color::White);
        PrintText(window, "SELECT", 634, 612, 35, sf::Color::White);
        PrintText(window, "Menu", 1700, 90, 35, sf::Color::White);
        PrintText(window, "Next", 1640, 775, 50, sf::Color::White);

        PrintSquare(window, 990, 410);
        PrintSquare(window, 1260, 410);
        PrintSquare(window, 1530, 410);

        if (Tyr1 == true) { PrintPicture(window, "Tyr1.png", 990, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Tyr2 == true) { PrintPicture(window, "Tyr1.png", 1260, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Tyr3 == true) { PrintPicture(window, "Tyr1.png", 1530, 410, sf::Vector2f(250.0f, 250.0f)); }

        if (Bra1 == true) { PrintPicture(window, "Bra1.png", 990, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Bra2 == true) { PrintPicture(window, "Bra1.png", 1260, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Bra3 == true) { PrintPicture(window, "Bra1.png", 1530, 410, sf::Vector2f(250.0f, 250.0f)); }

        if (Tri1 == true) { PrintPicture(window, "Tri1.png", 990, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Tri2 == true) { PrintPicture(window, "Tri1.png", 1260, 410, sf::Vector2f(250.0f, 250.0f)); }
        if (Tri3 == true) { PrintPicture(window, "Tri1.png", 1530, 410, sf::Vector2f(250.0f, 250.0f)); }

        window.display();
    }
}

void Shop(sf::RenderWindow &window) {
    
    window.clear();

    int cur_cash = 0;
    std::string cash;
    std::ifstream file_cash("cash.txt");
    if (file_cash.is_open()) {
        while (std::getline(file_cash, cash)) {
            PrintText(window, "Balance: ", 800, 240, 50, sf::Color::White);
            PrintText(window, cash, 1025, 242, 50, sf::Color::White);
            cur_cash = stoi(cash);
        }
    }
    file_cash.close();

    sf::Vector2f targetSize(350.0f, 350.0f);

    sf::Image imTyr;
    imTyr.loadFromFile("Tyr1.png");
    sf::Texture tTyr;
    tTyr.loadFromImage(imTyr);
    sf::Sprite buttonTyr;
    buttonTyr.setTexture(tTyr);
    buttonTyr.setScale(targetSize.x / buttonTyr.getLocalBounds().width, targetSize.y / buttonTyr.getLocalBounds().height);
    buttonTyr.setPosition(270, 360);

    sf::Image imBra;
    imBra.loadFromFile("Bra1.png");
    sf::Texture tBra;
    tBra.loadFromImage(imBra);
    sf::Sprite buttonBra;
    buttonBra.setTexture(tBra);
    buttonBra.setScale(targetSize.x / buttonBra.getLocalBounds().width, targetSize.y / buttonBra.getLocalBounds().height);
    buttonBra.setPosition(770, 360);

    sf::Image imTri;
    imTri.loadFromFile("Tri1.png");
    sf::Texture tTri;
    tTri.loadFromImage(imTri);
    sf::Sprite buttonTri;
    buttonTri.setTexture(tTri);
    buttonTri.setScale(targetSize.x / buttonTri.getLocalBounds().width, targetSize.y / buttonTri.getLocalBounds().height);
    buttonTri.setPosition(1270, 360);

    sf::RectangleShape buttonMenu;
    buttonMenu.setSize(sf::Vector2f(200, 110));
    buttonMenu.setPosition(1650, 60);
    buttonMenu.setFillColor(sf::Color::Black);
    buttonMenu.setOutlineThickness(5);
    buttonMenu.setOutlineColor(sf::Color::Cyan);

    window.draw(buttonTyr);
    window.draw(buttonBra);
    window.draw(buttonTri);
    window.draw(buttonMenu);

    PrintText(window, "SHOP", 840, 100, 70, sf::Color::Cyan);

    PrintText(window, "Tyrannosaur", 320, 750, 40, sf::Color::Cyan);
    PrintText(window, "Brachiosaur", 825, 750, 40, sf::Color::Cyan);
    PrintText(window, "Triceratops", 1330, 750, 40, sf::Color::Cyan);

    PrintText(window, "price: 21", 365, 810, 40, sf::Color::White);
    PrintText(window, "price: 14", 865, 810, 40, sf::Color::White);
    PrintText(window, "price: 17", 1365, 810, 40, sf::Color::White);

    PrintText(window, "Menu", 1700, 90, 35, sf::Color::White);
    
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);

                    if (buttonTyr.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        if (cur_cash >= 21) {
                            cur_cash = cur_cash - 21;
                            std::ofstream file_dino;
                            file_dino.open("dino_numbers.txt", std::ios::app);
                            file_dino << 1;
                            file_dino.close();
                            std::ofstream file_cash;
                            file_cash.open("cash.txt");
                            if (file_cash.is_open())
                            {
                                file_cash << cur_cash;
                            }
                            file_cash.close();

                            Shop(window);
                        }
                        else {
                            Error("You don't have enought money :(");
                        }
                    }
                    if (buttonBra.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        if (cur_cash >= 14) {
                            cur_cash = cur_cash - 14;
                            std::ofstream file_dino;
                            file_dino.open("dino_numbers.txt", std::ios::app);
                            file_dino << 2;
                            file_dino.close();
                            std::ofstream file_cash;
                            file_cash.open("cash.txt");
                            if (file_cash.is_open())
                            {
                                file_cash << cur_cash;
                            }
                            file_cash.close();

                            Shop(window);
                        }
                        else {
                            Error("You don't have enought money :(");
                        }
                    }
                    if (buttonTri.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        if (cur_cash >= 17) {
                            cur_cash = cur_cash - 17;
                            std::ofstream file_dino;
                            file_dino.open("dino_numbers.txt", std::ios::app);
                            file_dino << 3;
                            file_dino.close();
                            std::ofstream file_cash;
                            file_cash.open("cash.txt");
                            if (file_cash.is_open())
                            {
                                file_cash << cur_cash;
                            }
                            file_cash.close();

                            Shop(window);
                        }
                        else {
                            Error("You don't have enought money :(");
                        }
                    }
                    if (buttonMenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        Menu(window);
                    }
                }
            }
        }
    }
}

void Menu(sf::RenderWindow &window) {

    window.clear();

    sf::RectangleShape buttonShop;
    sf::RectangleShape buttonFight;
    sf::RectangleShape buttonExit;

    buttonShop.setSize(sf::Vector2f(400, 220));
    buttonShop.setPosition(200, 360);
    buttonShop.setFillColor(sf::Color::Black);
    buttonShop.setOutlineThickness(8);
    buttonShop.setOutlineColor(sf::Color::Cyan);
    
    buttonFight.setSize(sf::Vector2f(400, 220));
    buttonFight.setPosition(750, 360);
    buttonFight.setFillColor(sf::Color::Black);
    buttonFight.setOutlineThickness(8);
    buttonFight.setOutlineColor(sf::Color::Red);

    buttonExit.setSize(sf::Vector2f(400, 220));
    buttonExit.setPosition(1300, 360);
    buttonExit.setFillColor(sf::Color::Black);
    buttonExit.setOutlineThickness(8);
    buttonExit.setOutlineColor(sf::Color::Cyan);

    window.draw(buttonShop);
    window.draw(buttonFight);
    window.draw(buttonExit);

    PrintText(window, "MENU", 840, 100, 70, sf::Color::Cyan);
    PrintText(window, "Shop", 325, 425, 60, sf::Color::White);
    PrintText(window, "Fight!", 865, 425, 60, sf::Color::White);
    PrintText(window, "Exit", 1445, 425, 60, sf::Color::White);

    int cur_cash = 0;
    std::string cash;
    std::ifstream file_cash("cash.txt");
    if (file_cash.is_open()) {
        while (std::getline(file_cash, cash)) {
            PrintText(window, "Balance: ", 265, 640, 45, sf::Color::White);
            PrintText(window, cash, 470, 642, 45, sf::Color::White);
            cur_cash = stoi(cash);
        }
    }
    file_cash.close();

    std::string dino_number;
    std::ifstream file_dino("dino_numbers.txt");
    if (file_dino.is_open()) {
        while (std::getline(file_dino, dino_number)) {
            PrintText(window, "Your pool:", 830, 640, 45, sf::Color::White);
            PrintText(window, "Tyrannosaurs:", 770, 725, 45, sf::Color::White);
            PrintText(window, "Brachiosaurs:", 770, 785, 45, sf::Color::White);
            PrintText(window, "Triceratopses:", 770, 845, 45, sf::Color::White);
            PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '1')), 1100, 727, 45, sf::Color::White);
            PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '2')), 1090, 787, 45, sf::Color::White);
            PrintText(window, std::to_string(std::count(dino_number.begin(), dino_number.end(), '3')), 1100, 847, 45, sf::Color::White);
        }
    }
    file_dino.close();

    window.display();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);

                    if (buttonShop.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        Shop(window);
                    }
                    if (buttonFight.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        Choosing_fighters(window);
                    }
                    if (buttonExit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                        window.close();
                    }
                    /*
                    if (event.type == sf::Event::MouseButtonReleased) {
                        if (event.key.code == sf::Mouse::Left) {
                        }
                    }*/
                }
            }
        }
    }
}

int main() {

    std::ofstream file_cash;
    file_cash.open("cash.txt");
    if (file_cash.is_open())
    {
        file_cash << 52;
    }
    file_cash.close();

    std::ofstream file_dino;
    file_dino.open("dino_numbers.txt");
    if (file_dino.is_open())
    {
        file_dino << 0;
    }
    file_dino.close();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "menu");
    Menu(window);
}