#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cassert>
#include "menu.h"
#include "handleFight.h"

int main() {
    int coinsEarned = 0, coinsUser = 0, cntUserTyrannosaurus = 0, cntUserStegosaurus = 0, cntUserTriceratops = 0;
        
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Dinosaurs Battlesauce");
    window.setFramerateLimit(144);
    sf::Event event;

    // Чтение количества монет из файла
    std::ifstream inCoins("coins.txt");
    if (inCoins.is_open()) {
        std::string line;
        while (std::getline(inCoins, line)) {
            coinsUser = std::stoi(line);
        }
    }
    inCoins.close();

    std::ifstream inDinos("userDinoInventory.txt");

    // Чтение количества динозавров
    if (inDinos.is_open()) {
        // Читаем по одному числу из каждой строки
        inDinos >> cntUserTyrannosaurus;
        inDinos >> cntUserStegosaurus;
        inDinos >> cntUserTriceratops;
    }
    inDinos.close();

    //Вызов меню
    menu(event, window, coinsEarned, coinsUser, cntUserTyrannosaurus, cntUserStegosaurus, cntUserTriceratops);

    std::ofstream outCoins("coins.txt");
    if (outCoins.is_open()) {
        outCoins << coinsUser << std::endl;
    }
    outCoins.close();

    // Открываем файл заново для записи (режим перезаписи)
    std::ofstream outDinos("userDinoInventory.txt");
    if (outDinos.is_open()) {
        // Записываем новые числа в файл построчно
        outDinos << cntUserTyrannosaurus << std::endl;
        outDinos << cntUserStegosaurus << std::endl;
        outDinos << cntUserTriceratops << std::endl;
    }
    outDinos.close();

    return 0;
}